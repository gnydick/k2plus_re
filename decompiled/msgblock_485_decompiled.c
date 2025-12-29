/**
 * Decompiled and annotated from: msgblock_485.o
 * Purpose: RS-485 message framing, CRC-8 calculation, and packet validation
 *
 * This module handles the low-level packet format for RS-485 communication
 * with Creality K2 Series peripherals (material box, motors, etc.)
 *
 * Packet Format:
 * +------+------+------+--------+------+------+-----+
 * | HEAD | ADDR | LEN  | STATUS | FUNC | DATA | CRC |
 * +------+------+------+--------+------+------+-----+
 * | 0xF7 | 1B   | 1B   |   1B   |  1B  | var  | 1B  |
 * +------+------+------+--------+------+------+-----+
 *
 * Tool: Ghidra + Manual RE analysis
 * Original: klippy/chelper/msgblock_485.c
 *
 * =============================================================================
 * PROVENANCE NOTICE - READ BEFORE USING THIS CODE
 * =============================================================================
 *
 * This file was decompiled from compiled ARM object code using Ghidra.
 * The accuracy varies by category:
 *
 * GHIDRA DECOMPILATION (high confidence):
 *   - CRC-8 algorithm loop structure and XOR operations
 *   - Packet parsing state machine control flow
 *   - Buffer manipulation (memchr, memmove patterns)
 *   - Return value semantics (positive=valid, negative=discard, zero=need more)
 *
 * DATA SECTION EXTRACTION (high confidence):
 *   - PACK_HEAD = 0xF7 (from immediate values)
 *   - CRC8_POLYNOMIAL = 0x07 (from XOR operation)
 *   - MIN_PACKET_SIZE = 6 (from comparison)
 *
 * HUMAN INTERPRETATION (lower confidence):
 *   - Function names: msgblock_485_crc8, msgblock_485_check
 *   - Variable names: crc, buffer, msg_len, packet_crc
 *   - Packet format documentation (derived from field access patterns)
 *   - Comments explaining CRC algorithm and state machine
 *   - Parse state enum values (IDLE=0, IN_PACKET=1)
 *
 * UNCERTAIN:
 *   - Original error message strings (errorf calls reconstructed)
 *   - Exact behavior on malformed packets
 * =============================================================================
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ============================================
 * Constants
 * ============================================ */

#define PACK_HEAD           0xF7    // Packet header byte
#define MIN_PACKET_SIZE     6       // Minimum valid packet: HEAD + ADDR + LEN + STATUS + FUNC + CRC
#define CRC8_POLYNOMIAL     0x07    // CRC-8 polynomial: x^8 + x^2 + x + 1

/* ============================================
 * Parser State
 * ============================================ */

typedef enum {
    PARSE_STATE_IDLE = 0,       // Looking for HEAD byte
    PARSE_STATE_IN_PACKET = 1   // Currently parsing a packet
} parse_state_t;

/* ============================================
 * External Functions (from Klipper)
 * ============================================ */

extern void errorf(const char *fmt, ...);

/* ============================================
 * CRC-8 Calculation
 * ============================================ */

/**
 * Calculate CRC-8 checksum for RS-485 packet.
 *
 * Uses polynomial 0x07 (x^8 + x^2 + x + 1), which is the standard
 * CRC-8-CCITT polynomial commonly used in embedded systems.
 *
 * @param data      Pointer to data buffer
 * @param length    Length of data in bytes
 * @return          8-bit CRC checksum
 */
uint8_t msgblock_485_crc8(const uint8_t *data, int length)
{
    uint8_t crc = 0;

    if (length == 0) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        crc ^= data[i];

        // Process each bit
        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ CRC8_POLYNOMIAL;
            } else {
                crc = crc << 1;
            }
        }
    }

    return crc;
}

/* ============================================
 * Packet Validation
 * ============================================ */

/**
 * Check and validate an RS-485 packet from a buffer.
 *
 * This function parses the receive buffer looking for valid packets.
 * It handles:
 * - Finding the HEAD byte (0xF7)
 * - Validating packet length
 * - Checking CRC-8
 * - Discarding invalid data and resynchronizing
 *
 * @param state     Parser state (0 = idle, 1 = in packet)
 * @param buf       Receive buffer
 * @param buf_len   Length of data in buffer
 * @return          Positive: packet length (valid packet found)
 *                  Negative: bytes to discard (resync needed)
 *                  Zero: need more data
 */
int msgblock_485_check(char *state, char *buf, size_t buf_len)
{
    uint8_t *buffer = (uint8_t *)buf;

    // Need minimum packet size
    if ((int)buf_len < MIN_PACKET_SIZE) {
        errorf("buf_len = 0x%x", buf_len);

        // Debug: dump buffer contents
        for (size_t i = 0; i < buf_len; i++) {
            errorf("buf[%d] = 0x%x", i, buffer[i]);
        }
        return 0;
    }

    // Check if we're starting fresh (looking for HEAD)
    if (*state == PARSE_STATE_IDLE) {
        // Check for packet header
        if (buffer[0] != PACK_HEAD) {
            errorf("msghead = 0x%x, buf_len = 0x%x", buffer[0], buf_len);

            // Debug: dump buffer
            for (size_t i = 0; i < buf_len; i++) {
                errorf("buf[%d] = 0x%x", i, buffer[i]);
            }

            // Search for next HEAD byte
            goto find_next_head;
        }

        // Extract message length from packet
        uint8_t msg_len = buffer[2];  // LEN field

        // Validate length field
        if (msg_len < 3) {
            errorf("msglen = 0x%x, buf_len = 0x%x", msg_len, buf_len);

            // Debug: dump buffer
            for (size_t i = 0; i < buf_len; i++) {
                errorf("buf[%d] = 0x%x", i, buffer[i]);
            }

            goto find_next_head;
        }

        // Check if we have enough data for complete packet
        // Packet = HEAD + ADDR + LEN + [msg_len bytes] + CRC
        size_t packet_len = msg_len + 3;  // +3 for HEAD, ADDR, LEN
        if (buf_len < packet_len) {
            errorf("buf_len = 0x%x, msglen = 0x%x", buf_len, msg_len);

            // Debug: dump buffer
            for (size_t i = 0; i < buf_len; i++) {
                errorf("buf[%d] = 0x%x", i, buffer[i]);
            }
            return 0;  // Need more data
        }

        // Calculate CRC over LEN + payload (excludes HEAD, ADDR, and CRC byte)
        // CRC is calculated from buffer[2] for msg_len bytes
        uint8_t calc_crc = msgblock_485_crc8(&buffer[2], msg_len);

        // Get CRC from packet (last byte of message)
        uint8_t packet_crc = buffer[2 + msg_len];

        // Validate CRC
        if (calc_crc == packet_crc) {
            // Valid packet found
            return (int)packet_len;
        }

        // CRC mismatch
        errorf("crc = 0x%x, msgcrc8 = 0x%x, buf_len = 0x%x",
               calc_crc, packet_crc, buf_len);
    }

find_next_head:
    // Search for next HEAD byte to resynchronize
    errorf("Discard bytes until next HEAD found");

    // Debug: dump discarded bytes
    for (size_t i = 0; i < buf_len; i++) {
        errorf("buf[%d] = 0x%x", i, buffer[i]);
    }

    // Look for next 0xF7 in buffer (skip first byte)
    uint8_t *next_head = (uint8_t *)memchr(buf + 1, PACK_HEAD, buf_len - 1);

    if (next_head != NULL) {
        // Found next HEAD, return negative offset to discard
        *state = PARSE_STATE_IDLE;
        int discard = (int)(buf - (char *)next_head);
        errorf("-(next_head - buf) = %d", discard);
        return discard;  // Negative: bytes to discard
    }

    // No HEAD found, discard entire buffer
    errorf("-buf_len = %d", -(int)buf_len);
    *state = PARSE_STATE_IN_PACKET;  // Will keep looking
    return -(int)buf_len;
}

/* ============================================
 * Notes on Protocol
 * ============================================
 *
 * RS-485 Packet Structure:
 *
 * Byte 0: HEAD (0xF7) - Packet start marker
 * Byte 1: ADDR - Device address
 *         0x01-0x04: Material Box
 *         0x81-0x84: Closed-loop Motors
 *         0x91-0x92: Belt Tension Motors
 *         0xFE/0xFD/0xFC: Broadcast addresses
 * Byte 2: LEN - Length of remaining data (STATUS + FUNC + DATA + CRC)
 * Byte 3: STATUS - Response status (0x00 = OK)
 * Byte 4: FUNC - Function/command code
 * Bytes 5..N-1: DATA - Variable length payload
 * Byte N: CRC - CRC-8 checksum (over bytes 2 to N-1)
 *
 * CRC-8 Calculation:
 * - Polynomial: 0x07 (x^8 + x^2 + x + 1)
 * - Initial value: 0x00
 * - Calculated over: LEN + STATUS + FUNC + DATA
 *
 * Parser States:
 * - IDLE (0): Looking for HEAD byte (0xF7)
 * - IN_PACKET (1): Accumulating packet data
 *
 * Return Values from msgblock_485_check():
 * - Positive: Valid packet length, packet ready
 * - Zero: Need more data, keep buffering
 * - Negative: Bytes to discard for resync
 */
