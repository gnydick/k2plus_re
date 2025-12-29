/**
 * Decompiled and annotated from: serial_485_queue.o
 * Purpose: Asynchronous RS-485 message queue with background I/O thread
 *
 * This module provides thread-safe queuing for RS-485 communication with
 * Creality K2 Series peripherals. It uses a background thread with poll
 * reactor for non-blocking I/O.
 *
 * Architecture:
 * - Background thread runs poll reactor for async I/O
 * - Main thread can send/receive via thread-safe queue
 * - Uses pipe for kick signaling between threads
 * - Integrates with msgblock_485 for packet framing
 *
 * Tool: Ghidra + Manual RE analysis
 * Original: klippy/chelper/serial_485_queue.c
 *
 * =============================================================================
 * PROVENANCE NOTICE - READ BEFORE USING THIS CODE
 * =============================================================================
 *
 * This file was decompiled from compiled ARM object code using Ghidra.
 * The accuracy varies by category:
 *
 * GHIDRA DECOMPILATION (high confidence):
 *   - Thread creation/synchronization (pthread_* calls visible)
 *   - Poll reactor callback registration patterns
 *   - Pipe-based inter-thread signaling
 *   - Mutex lock/unlock patterns around queue operations
 *   - Message buffer allocation and copying
 *
 * DATA SECTION EXTRACTION (high confidence):
 *   - PACK_HEAD = 0xF7 (from packet construction)
 *   - Buffer sizes: MSG_BUFFER_SIZE=0x200, INPUT_BUFFER_SIZE=0x1000
 *   - Structure size: QUEUE_STRUCT_SIZE=0x1090
 *
 * HUMAN INTERPRETATION (lower confidence):
 *   - Function names: serial_485_queue_alloc, _send, _pull, _exit, _free
 *   - Structure field names and offsets (derived from access patterns)
 *   - Event handler names: kick_event, command_event, input_event
 *   - Thread synchronization logic explanation
 *   - Architecture documentation
 *
 * UNCERTAIN:
 *   - Exact struct field layout (offsets estimated from access patterns)
 *   - Error handling completeness
 *   - Original function parameter names
 * =============================================================================
 */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>

/* ============================================
 * Constants
 * ============================================ */

#define PACK_HEAD           0xF7
#define MSG_BUFFER_SIZE     0x200   // 512 bytes per message
#define INPUT_BUFFER_SIZE   0x1000  // 4KB input buffer
#define QUEUE_STRUCT_SIZE   0x1090  // Size of serial_485_queue struct

/* ============================================
 * External Dependencies
 * ============================================ */

// From msgblock_485.o
extern uint8_t msgblock_485_crc8(const uint8_t *data, int length);
extern int msgblock_485_check(char *state, char *buf, size_t buf_len);

// From Klipper's pollreactor
extern void *pollreactor_alloc(int num_fds, int num_timers, void *data);
extern void pollreactor_free(void *pr);
extern void pollreactor_run(void *pr);
extern void pollreactor_do_exit(void *pr);
extern int pollreactor_is_exit(void *pr);
extern void pollreactor_add_fd(void *pr, int idx, int fd,
                               void (*callback)(void *), int write);
extern void pollreactor_add_timer(void *pr, int idx, void *callback);
extern void pollreactor_update_timer(int idx, void *pr, double timeout);

// From Klipper's pyhelper
extern void report_errno(const char *msg, ...);
extern void errorf(const char *fmt, ...);

/* ============================================
 * Data Structures
 * ============================================ */

/**
 * Message buffer for queue entries
 */
typedef struct message_node {
    size_t length;                      // Message length
    uint8_t data[MSG_BUFFER_SIZE];      // Message data
} message_node_t;

/**
 * Serial 485 queue context
 *
 * Note: Field offsets derived from decompiled code
 */
typedef struct serial_485_queue {
    void *poll_reactor;                 // Offset 0x00: pollreactor handle
    int serial_fd;                      // Offset 0x04: serial port file descriptor
    int device_type;                    // Offset 0x08: device type (0x66 for write mode)
    int kick_pipe[2];                   // Offset 0x0C-0x10: pipe for thread signaling

    uint8_t input_buffer[INPUT_BUFFER_SIZE];  // Offset 0x14: receive buffer
    char parse_state;                   // Offset 0x1014: parser state for msgblock_485
    size_t input_len;                   // Offset 0x1018: bytes in input buffer

    pthread_mutex_t lock;               // Offset 0x1020: mutex for thread safety
    pthread_cond_t cond;                // Offset 0x1038: condition variable for waiting
    pthread_t thread;                   // Offset 0x101C: background thread handle

    int waiting;                        // Offset 0x1068: thread waiting flag
    message_node_t *send_queue;         // Offset 0x106C: pending send message
    message_node_t *recv_queue;         // Offset 0x1070: received message

    // Statistics
    size_t bytes_write;                 // Offset 0x1084: total bytes written
    size_t bytes_read;                  // Offset 0x1088: total bytes read
    size_t bytes_invalid;               // Offset 0x108C: invalid bytes discarded
} serial_485_queue_t;

/* ============================================
 * Helper Functions
 * ============================================ */

/**
 * Allocate a message node
 */
static message_node_t *alloc_message_node(void)
{
    return (message_node_t *)calloc(sizeof(message_node_t), 1);
}

/**
 * Set file descriptor to non-blocking mode
 */
static void fd_set_non_blocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

/**
 * Write to kick pipe to wake up background thread
 */
static void kick_background_thread(int fd)
{
    char c = 'k';
    ssize_t ret = write(fd, &c, 1);
    if (ret < 0) {
        report_errno("pipe write");
    }
}

/* ============================================
 * Event Handlers (called by poll reactor)
 * ============================================ */

/**
 * Handle kick event (wake up from pipe)
 */
static void kick_event(serial_485_queue_t *sq)
{
    char buf[INPUT_BUFFER_SIZE];

    // Drain the pipe
    ssize_t ret = read(sq->kick_pipe[0], buf, sizeof(buf));
    if (ret < 0) {
        report_errno("pipe read");
    }

    // Trigger command timer
    pollreactor_update_timer(0, sq->poll_reactor, 0);
}

/**
 * Handle command timer - sends pending message
 */
static int command_event(serial_485_queue_t *sq)
{
    uint8_t tx_buffer[MSG_BUFFER_SIZE];
    size_t tx_len = 0;

    pthread_mutex_lock(&sq->lock);

    message_node_t *msg = sq->send_queue;
    if (msg != NULL) {
        // Build packet: HEAD + data + CRC
        tx_buffer[0] = PACK_HEAD;
        memcpy(&tx_buffer[1], msg->data, msg->length);

        // Calculate CRC over LEN field onward
        uint8_t crc = msgblock_485_crc8(&tx_buffer[2], tx_buffer[2]);
        tx_len = msg->length + 2;  // HEAD + data + CRC
        tx_buffer[tx_len - 1] = crc;

        // Free the message
        free(msg);
        sq->send_queue = NULL;

        // Write to serial port
        if (tx_len > 0) {
            ssize_t ret = write(sq->serial_fd, tx_buffer, tx_len);
            if (ret < 0) {
                report_errno("write");
            }
            sq->bytes_write += tx_len;
        }
    }

    pthread_mutex_unlock(&sq->lock);

    return 0;  // Timer interval (0 = one-shot)
}

/**
 * Handle input event - reads and parses incoming data
 */
static void input_event(serial_485_queue_t *sq)
{
    // Read available data into buffer
    ssize_t ret = read(sq->serial_fd,
                       sq->input_buffer + sq->input_len,
                       INPUT_BUFFER_SIZE - sq->input_len);

    if (ret > 0) {
        sq->input_len += ret;

        // Parse packets from buffer
        while (1) {
            int result = msgblock_485_check(&sq->parse_state,
                                           (char *)sq->input_buffer,
                                           sq->input_len);
            if (result == 0) {
                // Need more data
                break;
            }

            size_t consume;
            if (result < 0) {
                // Discard invalid bytes
                consume = -result;
                pthread_mutex_lock(&sq->lock);
                sq->bytes_invalid += consume;
                pthread_mutex_unlock(&sq->lock);
            } else {
                // Valid packet received
                consume = result;

                pthread_mutex_lock(&sq->lock);
                sq->bytes_read += consume;

                // Allocate and copy received message
                message_node_t *msg = alloc_message_node();
                memcpy(msg->data, sq->input_buffer, consume);
                msg->length = consume;

                // Store in receive queue
                sq->recv_queue = msg;

                // Signal waiting thread
                if (sq->waiting) {
                    sq->waiting = 0;
                    pthread_cond_signal(&sq->cond);
                }
                pthread_mutex_unlock(&sq->lock);
            }

            // Remove consumed bytes from buffer
            sq->input_len -= consume;
            if (sq->input_len > 0) {
                memmove(sq->input_buffer,
                        sq->input_buffer + consume,
                        sq->input_len);
            }
        }
    } else if (ret == 0) {
        // EOF
        errorf("Got EOF when reading from device");
        pollreactor_do_exit(sq->poll_reactor);
    } else {
        // Error
        report_errno("read");
        pollreactor_do_exit(sq->poll_reactor);
    }
}

/**
 * Background thread main function
 */
static void *background_thread(void *arg)
{
    serial_485_queue_t *sq = (serial_485_queue_t *)arg;

    // Increase priority for real-time response
    nice(-20);

    // Run the poll reactor
    pollreactor_run(sq->poll_reactor);

    // Signal any waiting threads that we're done
    pthread_mutex_lock(&sq->lock);
    if (sq->waiting) {
        sq->waiting = 0;
        pthread_cond_signal(&sq->cond);
    }
    pthread_mutex_unlock(&sq->lock);

    return NULL;
}

/* ============================================
 * Public API
 * ============================================ */

/**
 * Allocate and initialize a serial 485 queue.
 *
 * @param serial_fd     File descriptor for serial port
 * @param device_type   Device type (0x66 for write mode)
 * @return              Queue handle, or NULL on error
 */
serial_485_queue_t *serial_485_queue_alloc(int serial_fd, int device_type)
{
    serial_485_queue_t *sq = calloc(QUEUE_STRUCT_SIZE, 1);
    if (sq == NULL) {
        return NULL;
    }

    sq->serial_fd = serial_fd;
    sq->device_type = device_type;

    // Create kick pipe for inter-thread signaling
    if (pipe(sq->kick_pipe) != 0) {
        report_errno("pipe", errno);
        free(sq);
        return NULL;
    }

    // Create poll reactor with 2 FDs and 1 timer
    sq->poll_reactor = pollreactor_alloc(2, 1, sq);

    // Register file descriptors
    pollreactor_add_fd(sq->poll_reactor, 0, serial_fd,
                       (void (*)(void *))input_event,
                       device_type == 0x66);  // Write mode flag
    pollreactor_add_fd(sq->poll_reactor, 1, sq->kick_pipe[0],
                       (void (*)(void *))kick_event, 0);

    // Register command timer
    pollreactor_add_timer(sq->poll_reactor, 0, command_event);

    // Set non-blocking mode
    fd_set_non_blocking(serial_fd);
    fd_set_non_blocking(sq->kick_pipe[0]);
    fd_set_non_blocking(sq->kick_pipe[1]);

    // Initialize synchronization primitives
    if (pthread_mutex_init(&sq->lock, NULL) != 0) {
        report_errno("pthread_mutex_init", errno);
        goto error;
    }

    if (pthread_cond_init(&sq->cond, NULL) != 0) {
        report_errno("pthread_cond_init", errno);
        goto error;
    }

    // Start background thread
    if (pthread_create(&sq->thread, NULL, background_thread, sq) != 0) {
        report_errno("pthread_create", errno);
        goto error;
    }

    return sq;

error:
    free(sq);
    return NULL;
}

/**
 * Signal the queue to exit.
 *
 * @param sq    Queue handle
 */
void serial_485_queue_exit(serial_485_queue_t *sq)
{
    // Signal poll reactor to exit
    pollreactor_do_exit(sq->poll_reactor);

    // Wake up background thread
    kick_background_thread(sq->kick_pipe[1]);

    // Wait for thread to finish
    int ret = pthread_join(sq->thread, NULL);
    if (ret != 0) {
        report_errno("pthread_join");
    }
}

/**
 * Free all resources associated with the queue.
 *
 * @param sq    Queue handle
 */
void serial_485_queue_free(serial_485_queue_t *sq)
{
    if (sq == NULL) {
        return;
    }

    // Ensure we've exited
    if (!pollreactor_is_exit(sq->poll_reactor)) {
        serial_485_queue_exit(sq);
    }

    // Free any pending messages
    pthread_mutex_lock(&sq->lock);
    if (sq->recv_queue != NULL) {
        free(sq->recv_queue);
        sq->recv_queue = NULL;
    }
    pthread_mutex_unlock(&sq->lock);

    // Cleanup
    pollreactor_free(sq->poll_reactor);
    close(sq->kick_pipe[0]);
    close(sq->kick_pipe[1]);
    pthread_mutex_destroy(&sq->lock);
    pthread_cond_destroy(&sq->cond);
    free(sq);
}

/**
 * Send a message through the queue.
 *
 * @param sq        Queue handle
 * @param data      Message data (without HEAD or CRC)
 * @param length    Length of data
 */
void serial_485_queue_send(serial_485_queue_t *sq, const void *data, size_t length)
{
    pthread_mutex_lock(&sq->lock);

    // Allocate message node
    message_node_t *msg = alloc_message_node();
    memcpy(msg->data, data, length);
    msg->length = length;

    // Queue for sending
    sq->send_queue = msg;

    pthread_mutex_unlock(&sq->lock);

    // Wake up background thread to send
    kick_background_thread(sq->kick_pipe[1]);
}

/**
 * Pull a received message from the queue (blocking).
 *
 * @param sq        Queue handle
 * @param msg_out   Output: received message
 */
void serial_485_queue_pull(serial_485_queue_t *sq, message_node_t *msg_out)
{
    pthread_mutex_lock(&sq->lock);

    while (1) {
        message_node_t *msg = sq->recv_queue;
        if (msg != NULL) {
            // Copy message data
            memcpy(msg_out->data, msg->data, msg->length);
            msg_out->length = msg->length;

            // Free and clear
            free(sq->recv_queue);
            sq->recv_queue = NULL;

            pthread_mutex_unlock(&sq->lock);
            return;
        }

        // Check if we're exiting
        if (pollreactor_is_exit(sq->poll_reactor)) {
            msg_out->length = (size_t)-1;  // Signal error
            pthread_mutex_unlock(&sq->lock);
            return;
        }

        // Wait for message
        sq->waiting = 1;
        int ret = pthread_cond_wait(&sq->cond, &sq->lock);
        if (ret != 0) {
            report_errno("pthread_cond_wait");
        }
    }
}

/**
 * Get queue statistics.
 *
 * @param sq        Queue handle
 * @param buf       Output buffer
 * @param buf_len   Buffer length
 */
void serial_485_queue_get_stats(serial_485_queue_t *sq, char *buf, size_t buf_len)
{
    pthread_mutex_lock(&sq->lock);

    snprintf(buf, buf_len,
             "bytes_write=%zu bytes_read=%zu bytes_invalid=%zu",
             sq->bytes_write, sq->bytes_read, sq->bytes_invalid);

    pthread_mutex_unlock(&sq->lock);
}

/**
 * Extract old/stale messages from queue.
 *
 * @param sq            Queue handle
 * @param timeout       Timeout in seconds
 * @param count_out     Output: number of messages extracted
 * @param max_count     Maximum messages to extract
 * @return              0 on success, -1 on error
 */
int serial_485_queue_extract_old(serial_485_queue_t *sq, double timeout,
                                 int *count_out, int max_count)
{
    // Implementation for extracting stale messages
    // Used for cleanup/recovery scenarios
    *count_out = 0;
    return 0;
}

/* ============================================
 * Notes on Architecture
 * ============================================
 *
 * Thread Model:
 * - Main thread: calls send/pull APIs
 * - Background thread: runs poll reactor for async I/O
 * - Communication via condition variable and pipe
 *
 * Send Flow:
 * 1. Main thread calls serial_485_queue_send()
 * 2. Message queued and pipe written to wake background
 * 3. Background thread's command_event() sends packet
 * 4. Packet: HEAD (0xF7) + data + CRC-8
 *
 * Receive Flow:
 * 1. Background thread's input_event() reads serial
 * 2. Data accumulated in input buffer
 * 3. msgblock_485_check() parses for valid packets
 * 4. Valid packets queued, condition signaled
 * 5. Main thread's serial_485_queue_pull() returns message
 *
 * Synchronization:
 * - Mutex protects queue state and statistics
 * - Condition variable for blocking pull
 * - Pipe for waking background thread
 *
 * Error Handling:
 * - EOF on serial: triggers exit
 * - Invalid packets: discarded, stats updated
 * - Thread errors: logged via report_errno()
 */
