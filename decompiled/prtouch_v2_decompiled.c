/**
 * Decompiled and annotated from: prtouch_v2.o
 * Purpose: PRTouch v2 MCU firmware for pressure-based Z probing
 *
 * This module implements pressure-based touch probing for the Creality K2 Series.
 * It uses strain gauge/load cell sensors to detect bed contact during probing.
 *
 * Key Features:
 * - Timer-based event system for precise stepping
 * - Circular FIFO buffer for pressure data sampling
 * - GPIO-controlled stepper motor direction/stepping
 * - Acceleration/deceleration S-curve lookup table
 * - Multi-channel pressure sensor support
 *
 * Architecture:
 * - Background timer runs at high frequency for step generation
 * - Pressure data sampled into circular buffer
 * - S-curve velocity profile for smooth motion
 * - Swap pin for hot-swappable probe detection
 *
 * Tool: Ghidra + Manual RE analysis
 * Original: src/prtouch_v2.c (MCU firmware)
 *
 * =============================================================================
 * PROVENANCE NOTICE - READ BEFORE USING THIS CODE
 * =============================================================================
 *
 * This file was decompiled from compiled ARM MCU firmware using Ghidra.
 * The accuracy varies by category:
 *
 * GHIDRA DECOMPILATION (high confidence):
 *   - Timer callback structure and scheduling patterns
 *   - GPIO read/write operations for step/direction pins
 *   - FIFO buffer indexing and masking (0x1F for 32-entry buffer)
 *   - Klipper OID allocation and lookup patterns
 *   - MCU command parsing structure
 *
 * DATA SECTION EXTRACTION (high confidence):
 *   - FIFO_SIZE = 32, FIFO_MASK = 0x1F
 *   - MAX_STEPPERS = 4
 *   - Timer interval calculations
 *   - S-curve lookup table values (if present)
 *
 * HUMAN INTERPRETATION (lower confidence):
 *   - Function names: step_event, pres_event, config_*, command_*
 *   - Structure definitions: prtouch_v2_t, stepper_entry_t
 *   - Field names and offsets within structures
 *   - S-curve algorithm explanation
 *   - Trigger detection logic description
 *
 * UNCERTAIN:
 *   - Exact trigger threshold calculations
 *   - Filter coefficient values and algorithms
 *   - Timing-critical edge cases
 *   - Original source organization
 * =============================================================================
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ============================================
 * Constants
 * ============================================ */

#define FIFO_SIZE           32      // Circular buffer size (0x20)
#define FIFO_MASK           0x1F    // Mask for FIFO index wrapping
#define MAX_STEPPERS        4       // Maximum stepper channels
#define PRESSURE_SAMPLES    32      // Pressure sample buffer size
#define STEP_SAMPLES        32      // Step count sample buffer size

/* ============================================
 * External Dependencies (Klipper MCU)
 * ============================================ */

// Timer functions
extern uint32_t timer_read_time(void);
extern void sched_add_timer(void *timer);
extern void sched_del_timer(void *timer);

// GPIO functions
extern void gpio_out_write(uint32_t gpio, uint32_t pin, int32_t value);
extern int32_t gpio_in_read(uint32_t gpio, uint32_t pin);
extern void gpio_out_toggle_noirq(uint32_t gpio, uint32_t pin);
extern void gpio_in_setup(void *out, uint32_t pin, int pull);
extern void gpio_out_setup(void *out, uint32_t pin, int value);

// Command/encoder functions
extern void *ctr_lookup_encoder(const char *name);
extern void command_sendf(void *encoder, ...);

// Floating point helpers (ARM EABI)
extern float __aeabi_fmul(float a, float b);
extern float __aeabi_fdiv(float a, float b);
extern float __aeabi_ui2f(uint32_t a);
extern double __aeabi_dmul(double a, double b);
extern int32_t __aeabi_f2uiz(float a);
extern int32_t __aeabi_d2uiz(double a);
extern double __aeabi_ui2d(uint32_t a);
extern double __aeabi_ddiv(double a, double b);
extern double __aeabi_dsub(double a, double b);
extern double __aeabi_dadd(double a, double b);
extern double __aeabi_f2d(float a);
extern int __aeabi_dcmplt(double a, double b);

/* ============================================
 * Data Structures
 * ============================================ */

/**
 * Circular FIFO buffer for pressure readings
 */
typedef struct pr_fifo {
    int32_t index;                      // Current write index
    uint32_t buf[FIFO_SIZE];            // Circular buffer
} pr_fifo_t;

/**
 * Asynchronous delay tracker
 */
typedef struct asy_delay {
    double last_tick_s;                 // Last tick in seconds
    double now_tick_s;                  // Current tick in seconds
} asy_delay_t;

/**
 * Timer structure (from Klipper)
 */
typedef struct timer {
    uint32_t waketime;                  // Next wake time
    void (*func)(struct timer *);       // Callback function
    struct timer *next;                 // Linked list next
} timer_t;

/**
 * Stepper channel configuration
 */
typedef struct stepper_channel {
    uint32_t dir_gpio[2];               // Direction GPIO (port, pin)
    uint32_t step_gpio[2];              // Step GPIO (port, pin)
    uint32_t endstop_gpio[2];           // Endstop GPIO (port, pin)
    int16_t saved_dir;                  // Saved direction state
    int16_t target_dir;                 // Target direction
} stepper_channel_t;

/**
 * PRTouch v2 context structure
 *
 * Offsets derived from decompiled code:
 * 0x00-0x08: Timer structure
 * 0x0C: Next waketime
 * 0x10-0x18: System time accumulator (double)
 * 0x18: Tick rate (float)
 * 0x20: Number of steppers
 * 0x22-0x3A: Saved direction states
 * 0x3C-0x7C: Direction GPIOs
 * 0x5C-0x7C: Step GPIOs
 * 0x7C-0xA0: Endstop GPIOs
 * 0x9C: Probe trigger countdown
 * 0xA0: State flags
 * 0xA2: Mode flags
 * 0xA4: Step sample index
 * 0xA8-0x128: Step sample buffer (32 entries)
 * 0x128: Pressure sample index
 * 0x12C-0x1AC: Pressure sample buffer (32 entries)
 * 0x1AC: Direction flag
 * 0x1AE: Stop flag
 * 0x1B0: Total step count
 * 0x1B4: Remaining step count
 * 0x1B8: Step interval (ticks)
 * 0x1BC: Ramp steps
 * 0x1C0: S-curve factor 1
 * 0x1C2: S-curve factor 2
 * 0x1C4: Multi-probe flag
 */
typedef struct prtouch_v2 {
    timer_t timer;                      // 0x00: Timer for step events
    uint32_t next_waketime;             // 0x0C: Next scheduled wake
    double sys_time_s;                  // 0x10: System time accumulator
    float tick_rate;                    // 0x18: Timer tick rate

    int16_t num_steppers;               // 0x20: Number of stepper channels
    int16_t saved_dirs[MAX_STEPPERS];   // 0x22: Saved direction states
    int16_t target_dirs[MAX_STEPPERS];  // 0x2A: Target directions

    uint32_t dir_gpio[MAX_STEPPERS][2]; // 0x3C: Direction GPIOs
    uint32_t step_gpio[MAX_STEPPERS][2];// 0x5C: Step GPIOs
    uint32_t endstop_gpio[MAX_STEPPERS][2]; // 0x7C: Endstop GPIOs

    uint32_t trigger_countdown;         // 0x9C: Probe trigger countdown
    uint16_t state;                     // 0xA0: State flags
    uint16_t mode;                      // 0xA2: Operating mode

    uint32_t step_sample_idx;           // 0xA4: Step sample write index
    uint32_t step_samples[STEP_SAMPLES];// 0xA8: Step count samples

    uint32_t pressure_sample_idx;       // 0x128: Pressure sample index
    uint32_t pressure_samples[PRESSURE_SAMPLES]; // 0x12C: Pressure readings

    int16_t direction;                  // 0x1AC: Current direction
    int16_t stop_flag;                  // 0x1AE: Stop requested
    uint32_t total_steps;               // 0x1B0: Total steps to move
    uint32_t remaining_steps;           // 0x1B4: Steps remaining
    uint32_t step_interval;             // 0x1B8: Ticks per step
    uint32_t ramp_steps;                // 0x1BC: Steps for accel/decel
    uint16_t scurve_factor1;            // 0x1C0: S-curve parameter 1
    uint16_t scurve_factor2;            // 0x1C2: S-curve parameter 2
    int16_t multi_probe;                // 0x1C4: Multi-probe mode

    // Swap detection
    uint32_t swap_gpio[2];              // Swap detect GPIO
} prtouch_v2_t;

/**
 * Global PRTouch context pointer
 */
static prtouch_v2_t *g_prtouch = NULL;

/**
 * System time context for async timing
 */
static struct {
    int enabled;                        // Timer enabled flag
    timer_t timer;                      // System time timer
    uint32_t next_waketime;             // Next wake time
    double accumulated_time;            // Accumulated time in seconds
    float tick_period;                  // Period per tick
} g_sys_time;

/**
 * S-curve velocity lookup table
 * Maps position (0-255) to velocity multiplier
 * Used for smooth acceleration/deceleration profiles
 */
static const uint16_t s_curve_table[256] = {
    /* Entries from 0x00 to 0xFF providing smooth velocity profile */
    /* Values increase from low to high for acceleration phase */
    /* This is a sigmoid-like curve for jerk-limited motion */
};

/* ============================================
 * System Timer Functions
 * ============================================ */

/**
 * System time timer event handler.
 * Accumulates high-precision time for async operations.
 *
 * @param t     Timer structure
 * @return      1 to reschedule timer
 */
uint_fast8_t sys_time_event(timer_t *t)
{
    uint32_t now = timer_read_time();

    // Calculate next wake time
    uint32_t interval = (uint32_t)(g_sys_time.tick_period * g_sys_time.tick_period);
    g_sys_time.next_waketime = now + interval;

    // Accumulate time in seconds
    g_sys_time.accumulated_time += (double)g_sys_time.tick_period;

    return 1;  // Reschedule
}

/**
 * Start the system time accumulator.
 */
void start_sys_time(void)
{
    if (g_sys_time.enabled) {
        return;  // Already running
    }

    g_sys_time.enabled = 1;
    g_sys_time.timer.func = (void (*)(timer_t *))sys_time_event;

    uint32_t now = timer_read_time();
    uint32_t interval = (uint32_t)(g_sys_time.tick_period * 1000000.0f);
    g_sys_time.next_waketime = now + interval;

    sched_add_timer(&g_sys_time.timer);
}

/**
 * Stop the system time accumulator.
 */
void stop_sys_time(void)
{
    if (g_sys_time.enabled != 1) {
        return;  // Not running
    }

    sched_del_timer(&g_sys_time.timer);
    g_sys_time.enabled = 0;
}

/**
 * Get current system time in seconds.
 *
 * @return      System time in seconds
 */
double get_sys_tick_s(void)
{
    return g_sys_time.accumulated_time;
}

/* ============================================
 * FIFO Buffer Operations
 * ============================================ */

/**
 * Write a value to the circular FIFO.
 *
 * @param pf    FIFO structure
 * @param data  Value to write
 */
void pr_fifo_write(pr_fifo_t *pf, uint32_t data)
{
    int32_t idx = pf->index;
    int32_t wrapped_idx;

    // Handle negative indices for wrap-around
    if (idx >= 0) {
        wrapped_idx = idx & FIFO_MASK;
    } else {
        wrapped_idx = -((-idx) & FIFO_MASK);
    }

    pf->buf[wrapped_idx] = data;
    pf->index = idx + 1;
}

/**
 * Read all values from the circular FIFO.
 * Reads FIFO_SIZE values starting from oldest.
 *
 * @param pf        FIFO structure
 * @param out_buf   Output buffer (must hold FIFO_SIZE entries)
 */
void pr_fifo_read(pr_fifo_t *pf, uint32_t *out_buf)
{
    for (int i = 0; i < FIFO_SIZE; i++) {
        int32_t read_idx = pf->index + i;
        int32_t wrapped_idx;

        if (read_idx >= 0) {
            wrapped_idx = read_idx & FIFO_MASK;
        } else {
            wrapped_idx = -((-read_idx) & FIFO_MASK);
        }

        out_buf[i] = pf->buf[wrapped_idx];
    }
}

/* ============================================
 * GPIO Helper Functions
 * ============================================ */

/**
 * Write to swap detection pin.
 *
 * @param sta   State to write (0 or 1)
 */
void write_swap_sta(int32_t sta)
{
    gpio_out_write(g_prtouch->swap_gpio[0], g_prtouch->swap_gpio[1], sta);
}

/**
 * Read swap detection pin state.
 *
 * @return      Pin state (0 or 1)
 */
int32_t read_swap_sta(void)
{
    return gpio_in_read(g_prtouch->swap_gpio[0], g_prtouch->swap_gpio[1]);
}

/* ============================================
 * Debug Functions
 * ============================================ */

/**
 * Send debug arguments via command encoder.
 *
 * @param args  Arguments array
 */
void send_debug_args(uint32_t *args)
{
    void *encoder = ctr_lookup_encoder("prtouch_debug");
    command_sendf(encoder, args[0] & 0xFF, 0x133,
                  args[0], args[1], args[2], args[3], args[4], args[5]);
}

/* ============================================
 * Delay Functions
 * ============================================ */

/**
 * Check if async delay has elapsed.
 *
 * @param ad    Delay structure
 * @param s     Delay time in seconds
 * @return      1 if delay elapsed, 0 otherwise
 */
int32_t check_delay(asy_delay_t *ad, float s)
{
    ad->now_tick_s = g_sys_time.accumulated_time;

    double elapsed = ad->now_tick_s - ad->last_tick_s;
    double threshold = (double)s;

    if (elapsed >= threshold) {
        ad->last_tick_s = ad->now_tick_s;
        return 1;
    }

    return 0;
}

/* ============================================
 * Stepper Control Functions
 * ============================================ */

/**
 * Set stepper direction pins.
 * Can save current state or set to specified direction.
 *
 * @param dir       Target direction (0=down, 1=up)
 * @param is_save   1 to save current state, 0 to set direction
 */
void deal_dirs_prtouch(int dir, int is_save)
{
    prtouch_v2_t *pt = g_prtouch;

    if (pt->num_steppers == 0) {
        return;
    }

    for (int i = 0; i < pt->num_steppers; i++) {
        int16_t dir_state;

        if (is_save) {
            // Read and save current direction
            dir_state = gpio_in_read(pt->endstop_gpio[i][0], pt->endstop_gpio[i][1]);
            pt->saved_dirs[i] = dir_state;
            // Set to target if different from dir
            dir_state = (pt->target_dirs[i] != dir) ? 1 : 0;
        } else {
            // Use saved state
            dir_state = pt->saved_dirs[i];
        }

        gpio_out_write(pt->dir_gpio[i][0], pt->dir_gpio[i][1], dir_state);
    }
}

/**
 * Toggle all stepper step pins (no IRQ disable).
 * Used during active stepping.
 */
void deal_steps_prtouch(void)
{
    prtouch_v2_t *pt = g_prtouch;

    if (pt->num_steppers == 0) {
        return;
    }

    for (int i = 0; i < pt->num_steppers; i++) {
        gpio_out_toggle_noirq(pt->step_gpio[i][0], pt->step_gpio[i][1]);
    }
}

/* ============================================
 * Main Probe Event Handler
 * ============================================ */

/**
 * PRTouch timer event handler.
 * Called at high frequency to generate step pulses and sample pressure.
 *
 * Implements S-curve velocity profile for smooth motion:
 * - Accelerates at start using lookup table
 * - Maintains cruise velocity
 * - Decelerates at end using lookup table
 *
 * @param t     Timer structure
 * @return      1 to reschedule, 0 to stop
 */
uint_fast8_t prtouch_event(timer_t *t)
{
    prtouch_v2_t *pt = g_prtouch;

    // Toggle step pins for all active steppers
    for (int i = 0; i < pt->num_steppers; i++) {
        gpio_out_toggle_noirq(pt->step_gpio[i][0], pt->step_gpio[i][1]);
    }

    // Decrement remaining steps
    pt->remaining_steps--;

    // Check for trigger (e.g., probe in contact with bed)
    if (pt->trigger_countdown == 0) {
        int swap_state = gpio_in_read(pt->swap_gpio[0], pt->swap_gpio[1]);
        if (swap_state == 1) {
            // Trigger detected - calculate countdown based on system time
            double tick_mult = g_sys_time.accumulated_time * 1000000.0;
            pt->trigger_countdown = (uint32_t)tick_mult;
        }
    }

    // Check if move complete
    if (pt->remaining_steps == 0) {
        // Sample final pressure
        uint32_t idx = pt->pressure_sample_idx;
        uint32_t wrapped = (idx >= 0) ? (idx & FIFO_MASK) : -((-idx) & FIFO_MASK);

        double pressure = g_sys_time.accumulated_time * 1000000.0;
        pt->pressure_samples[wrapped] = (uint32_t)pressure;

        uint32_t step_idx = pt->step_sample_idx;
        uint32_t step_wrapped = (step_idx >= 0) ? (step_idx & FIFO_MASK) : -((-step_idx) & FIFO_MASK);

        pt->pressure_sample_idx++;
        pt->step_sample_idx++;
        pt->step_samples[step_wrapped] = pt->remaining_steps / 2;

        // Check for multi-probe mode
        if (pt->multi_probe != 1) {
            sched_del_timer(&pt->timer);
            deal_dirs_prtouch(0, 0);
            pt->state = 8;  // Complete
            pt->stop_flag = 0;
            pt->remaining_steps = 0;
            return 1;
        }

        // Multi-probe: reverse and continue
        pt->multi_probe = 0;
        pt->remaining_steps = pt->total_steps;
        deal_dirs_prtouch(0, 0);
        deal_dirs_prtouch((pt->direction == 0) ? 1 : 0, 1);

        uint32_t now = timer_read_time();
        pt->next_waketime = now + pt->step_interval;
    }

    // Calculate next step timing using S-curve
    int32_t remaining = pt->remaining_steps;
    int32_t total = pt->total_steps;
    int32_t ramp = pt->ramp_steps;
    int32_t progress = total - remaining;

    if (progress < ramp) {
        // Acceleration phase - use S-curve lookup
        int32_t index = 0x100 - ((progress << 8) / ramp);
        if (index > 0xFE) index = 0xFF;
        if (index < 0) index = 0;

        uint16_t velocity_mult = s_curve_table[index];
        uint32_t interval = velocity_mult * pt->step_interval * pt->scurve_factor1;
        interval = (interval >> 16) + pt->step_interval;  // Fixed-point math

        uint32_t now = timer_read_time();
        pt->next_waketime = now + interval;
    } else if (remaining < ramp) {
        // Deceleration phase
        int32_t index = 0x100 - ((remaining << 8) / ramp);
        if (index > 0xFE) index = 0xFF;
        if (index < 0) index = 0;

        uint16_t velocity_mult = s_curve_table[index];
        uint32_t interval = velocity_mult * pt->step_interval * pt->scurve_factor1;
        interval = (interval >> 16) + pt->step_interval;

        uint32_t now = timer_read_time();
        pt->next_waketime = now + interval;
    } else {
        // Cruise phase - constant velocity
        uint32_t now = timer_read_time();
        pt->next_waketime = now + pt->step_interval;
    }

    // Periodic pressure sampling
    if ((remaining & 1) == 0 || pt->stop_flag == 1) {
        int swap_state = gpio_in_read(pt->swap_gpio[0], pt->swap_gpio[1]);
        if (swap_state == 1 || pt->stop_flag == 1) {
            // Sample pressure
            uint32_t idx = pt->pressure_sample_idx & FIFO_MASK;
            double pressure = g_sys_time.accumulated_time * 1000000.0;
            pt->pressure_samples[idx] = (uint32_t)pressure;
            pt->pressure_sample_idx++;

            uint32_t step_idx = pt->step_sample_idx & FIFO_MASK;
            pt->step_samples[step_idx] = remaining / 2;
            pt->step_sample_idx++;
        }
    }

    return 1;  // Continue stepping
}

/* ============================================
 * G-Code Command Handlers
 * ============================================ */

/**
 * PRTOUCH_CONFIG_STEP - Configure stepper parameters.
 *
 * Args:
 *   [0]: Number of steppers
 *   [1]: Reserved
 *   [2]: Swap detect GPIO pin
 *   [3]: Timer tick frequency
 */
void command_config_step_prtouch(uint32_t *args)
{
    prtouch_v2_t *pt = g_prtouch;

    pt->num_steppers = (int16_t)args[0];
    pt->mode = (int16_t)args[1];

    // Calculate tick period from frequency
    float freq = __aeabi_ui2f(args[3]);
    pt->tick_rate = __aeabi_fdiv(freq, 1000000.0f);

    // Setup swap detect GPIO as input
    gpio_in_setup(&pt->swap_gpio, args[2], 1);

    send_debug_args(args);
}

/**
 * PRTOUCH_ADD_STEP - Add a stepper channel.
 *
 * Args:
 *   [0]: Reserved
 *   [1]: Channel index (0-3)
 *   [2]: Step GPIO pin
 *   [3]: Direction GPIO pin
 *   [4]: Invert direction flag
 *   [5]: Endstop GPIO pin
 *   [6]: Endstop trigger state
 */
void command_add_step_prtouch(uint32_t *args)
{
    prtouch_v2_t *pt = g_prtouch;
    uint32_t channel = args[1];

    // Setup endstop as input
    gpio_in_setup(&pt->endstop_gpio[channel], args[2], 0);

    // Setup step as output
    gpio_out_setup(&pt->step_gpio[channel], args[2], 0);

    // Setup direction as output with invert flag
    gpio_out_setup(&pt->dir_gpio[channel], args[3], args[5]);

    pt->target_dirs[channel] = (int16_t)args[4];
    pt->saved_dirs[channel] = (int16_t)args[5];

    send_debug_args(args);
}

/**
 * PRTOUCH_READ_SWAP - Read swap detection pin.
 *
 * Returns: Current swap pin state
 */
void command_read_swap_prtouch(uint32_t *args)
{
    void *encoder = ctr_lookup_encoder("prtouch_swap_state");
    int16_t num_steppers = g_prtouch->num_steppers;
    int32_t swap_state = read_swap_sta();

    command_sendf(encoder, num_steppers, swap_state);
    send_debug_args(args);
}

/**
 * PRTOUCH_START_STEP - Start a probe move.
 *
 * Args:
 *   [0]: Reserved
 *   [1]: Direction (0=down, 1=up)
 *   [2]: Enable flag (0=stop, 1=start)
 *   [3]: Total steps
 *   [4]: Step interval (microseconds)
 *   [5]: Ramp steps for accel/decel
 *   [6]: S-curve factor 1
 *   [7]: S-curve factor 2
 *   [8]: Multi-probe flag
 */
void command_start_step_prtouch(uint32_t *args)
{
    prtouch_v2_t *pt = g_prtouch;

    if (args[2] == 0) {
        // Stop command
        pt->stop_flag = 1;
        send_debug_args(args);

        if (g_sys_time.enabled == 1) {
            stop_sys_time();
        }
        return;
    }

    // Start probe move
    if (g_sys_time.enabled == 0) {
        start_sys_time();
    }

    // Clear sample buffers
    pt->pressure_sample_idx = 0;
    pt->step_sample_idx = 0;
    memset(pt->pressure_samples, 0, sizeof(pt->pressure_samples));
    memset(pt->step_samples, 0, sizeof(pt->step_samples));

    // Initialize samples with current time
    double init_time = g_sys_time.accumulated_time * 1000000.0;
    for (int i = 0; i < PRESSURE_SAMPLES; i++) {
        pt->pressure_samples[i] = (uint32_t)init_time;
    }

    // Set direction
    deal_dirs_prtouch(args[1], 1);

    // Configure move parameters
    pt->direction = (int16_t)args[1];
    pt->mode = (int16_t)args[2];
    pt->total_steps = args[3] << 1;  // Double for step/dir toggle
    pt->remaining_steps = args[3] << 1;

    // Calculate step interval in timer ticks
    double us_per_step = (double)args[4];
    double interval = (us_per_step / 1000000.0) * 1000000.0;  // Convert to ticks
    pt->step_interval = (uint32_t)(interval / 2);  // Half for toggle

    pt->ramp_steps = args[5] << 1;
    pt->trigger_countdown = 0;
    pt->scurve_factor1 = (uint16_t)args[6];
    pt->scurve_factor2 = (uint16_t)args[7];
    pt->multi_probe = (int16_t)args[8];

    pt->state = 0;
    pt->stop_flag = 0;

    // Schedule first step
    uint32_t now = timer_read_time();
    uint32_t first_interval = pt->scurve_factor1 * pt->step_interval + pt->step_interval;
    pt->next_waketime = now + first_interval;

    sched_add_timer(&pt->timer);
    send_debug_args(args);
}

/**
 * PRTOUCH_MANUAL_GET_STEPS - Get step/pressure sample data.
 *
 * Args:
 *   [0]: Reserved
 *   [1]: Sample index to retrieve
 *
 * Returns: Sample data for specified index
 */
void command_manual_get_steps(uint32_t *args)
{
    uint32_t index = args[1];

    // Return pressure and step samples for index
    void *encoder = ctr_lookup_encoder("prtouch_step_data");
    command_sendf(encoder,
                  g_prtouch->pressure_samples[index & FIFO_MASK],
                  g_prtouch->step_samples[index & FIFO_MASK]);

    send_debug_args(args);
}

/* ============================================
 * Notes on PRTouch v2 Algorithm
 * ============================================
 *
 * Probe Sequence:
 * 1. Python side sends PRTOUCH_CONFIG_STEP with timer frequency
 * 2. PRTOUCH_ADD_STEP called for each stepper (typically 2 for Z1/Z2)
 * 3. PRTOUCH_START_STEP initiates probe move downward
 * 4. Timer event handler generates step pulses at calculated intervals
 * 5. S-curve profile provides smooth acceleration/deceleration
 * 6. Swap pin state monitored for contact detection
 * 7. Pressure samples recorded at regular intervals
 * 8. On contact/completion, samples returned via PRTOUCH_MANUAL_GET_STEPS
 *
 * S-Curve Motion Profile:
 * - Uses precomputed lookup table for smooth velocity transitions
 * - Avoids jerky motion that could affect pressure readings
 * - Index calculated from position within ramp region
 * - Velocity multiplier applied to base step interval
 *
 * Pressure Sampling:
 * - Samples taken at each step (or every 2 steps)
 * - Stored in circular buffer for later retrieval
 * - Python side analyzes samples to determine contact point
 *
 * Contact Detection:
 * - Swap pin transitions indicate probe contact
 * - Countdown timer allows settling before reading
 * - Multi-probe mode reverses for touch/retract/touch cycle
 */
