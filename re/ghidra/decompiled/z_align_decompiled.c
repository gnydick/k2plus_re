/**
 * Decompiled and annotated from: z_align.o
 * Purpose: Z-axis alignment MCU firmware for dual Z steppers
 *
 * This module implements Z-axis alignment for the Creality K2 Series.
 * It controls dual Z steppers to level the gantry by stepping each
 * motor until their respective endstops trigger.
 *
 * Key Features:
 * - Multi-motor Z alignment (up to 4 motors)
 * - Per-motor endstop monitoring
 * - Timer-based step generation
 * - Position tracking and reporting
 * - Fine-tuning mode for precise adjustment
 *
 * Architecture:
 * - Uses Klipper's OID (object ID) system for instance management
 * - Timer-driven step generation with configurable intervals
 * - Per-motor direction control with endstop feedback
 * - Two modes: alignment (rough) and fine-tuning (precise)
 *
 * Tool: Ghidra + Manual RE analysis
 * Original: src/z_align.c (MCU firmware)
 *
 * =============================================================================
 * PROVENANCE NOTICE - READ BEFORE USING THIS CODE
 * =============================================================================
 *
 * This file was decompiled from compiled ARM MCU firmware using Ghidra.
 * The accuracy varies by category:
 *
 * GHIDRA DECOMPILATION (high confidence):
 *   - Klipper OID allocation and lookup patterns
 *   - Timer callback registration and scheduling
 *   - GPIO operations for step/dir/endstop pins
 *   - Per-motor iteration loops (up to MAX_Z_MOTORS)
 *   - Endstop state checking and motor stopping logic
 *
 * DATA SECTION EXTRACTION (high confidence):
 *   - MAX_Z_MOTORS = 4
 *   - MOTOR_ENTRY_SIZE = 0x14 (20 bytes per motor)
 *   - REPORT_INTERVAL_US = 100000
 *   - Step timing constants
 *
 * HUMAN INTERPRETATION (lower confidence):
 *   - Function names: z_align_event, config_z_align, add_motor
 *   - Structure definitions: z_align_t, motor_entry_t
 *   - Field names: step_pin, dir_pin, endstop_pin, position
 *   - Alignment vs fine-tuning mode distinction
 *   - Position reporting format
 *
 * UNCERTAIN:
 *   - Exact endstop debouncing behavior
 *   - Fine-tuning step size calculations
 *   - Error recovery on endstop failure
 *   - Original command/response message formats
 * =============================================================================
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ============================================
 * Constants
 * ============================================ */

#define MAX_Z_MOTORS        4       // Maximum Z motors supported
#define MOTOR_ENTRY_SIZE    0x14    // Size of per-motor data (20 bytes)
#define REPORT_INTERVAL_US  100000  // Report interval in microseconds

/* ============================================
 * External Dependencies (Klipper MCU)
 * ============================================ */

extern void *oid_alloc(uint8_t oid, const char *type, size_t size);
extern void *oid_lookup(uint8_t oid, const char *type);
extern void *oid_next(uint8_t *oid, const char *type);

extern uint32_t timer_read_time(void);
extern uint32_t timer_from_us(uint32_t us);
extern int timer_is_before(uint32_t a, uint32_t b);
extern void sched_add_timer(void *timer);
extern void sched_del_timer(void *timer);
extern void sched_wake_task(void *task);
extern int sched_check_wake(void *task);

extern void gpio_out_write(uint32_t gpio, uint8_t value);
extern uint8_t gpio_in_read(uint8_t gpio);
extern void gpio_out_toggle(uint32_t gpio);
extern void gpio_out_setup(void *out, uint8_t pin, uint8_t value);
extern uint8_t gpio_out_read(uint8_t pin);
extern uint8_t gpio_in_setup(uint8_t pin, uint8_t pull);

extern void *ctr_lookup_encoder(const char *name);
extern void *ctr_lookup_static_string(const char *name);
extern void command_sendf(void *encoder, ...);
extern void sched_shutdown(void);

extern void irq_disable(void);
extern void irq_enable(void);

/* ============================================
 * Data Structures
 * ============================================ */

/**
 * Timer structure (from Klipper)
 */
typedef struct timer {
    uint32_t waketime;                  // Next wake time
    void (*func)(struct timer *);       // Callback function
    struct timer *next;                 // Linked list next
} timer_t;

/**
 * Per-motor state structure
 * Size: 0x14 (20) bytes per motor
 */
typedef struct z_motor {
    uint32_t step_count;                // 0x0C: Current step count
    uint32_t step_gpio;                 // 0x10: Step GPIO
    uint32_t dir_gpio;                  // 0x14: Direction GPIO
    uint8_t endstop_gpio;               // 0x18: Endstop GPIO
    uint8_t dir_invert;                 // 0x19: Direction invert flag
    uint8_t saved_dir;                  // 0x1A: Saved direction state
    uint8_t endstop_state;              // 0x1B: Expected endstop state
    uint8_t debounce_count;             // 0x1C: Endstop debounce counter
} z_motor_t;

/**
 * Z-align context structure
 *
 * Offsets derived from decompiled code:
 * 0x00: Timer structure
 * 0x08: Timer waketime
 * 0x0C-0x5C: Per-motor data (4 motors x 0x14 bytes)
 * 0x5C: Timer interval
 * 0x60: Start timer interval
 * 0x64: Mid timer interval
 * 0x68: Target step count
 * 0x6C: Max position difference
 * 0x70: Completion mask
 * 0x74: Number of motors
 * 0x78: Report time
 * 0x7C-0x88: Position offsets per motor
 * 0x8C: State flags
 * 0x8E: Mode
 * 0x8F: Result status
 * 0x90: Max debounce count
 * 0x91: Direction flag
 */
typedef struct z_align {
    timer_t timer;                      // 0x00: Timer for step events
    uint32_t waketime;                  // 0x08: Current wake time

    // Per-motor data starts at 0x0C
    z_motor_t motors[MAX_Z_MOTORS];     // 0x0C: Motor data

    uint32_t timer_interval;            // 0x5C: Current step interval
    uint32_t start_interval;            // 0x60: Start interval (slow)
    uint32_t mid_interval;              // 0x64: Mid interval (normal)
    uint32_t target_steps;              // 0x68: Target step count
    uint32_t max_diff;                  // 0x6C: Maximum allowed position difference
    uint32_t completion_mask;           // 0x70: Bitmask of completed motors
    uint32_t num_motors;                // 0x74: Number of configured motors
    uint32_t report_time;               // 0x78: Next report time

    int32_t position_offset[MAX_Z_MOTORS]; // 0x7C: Position offsets

    uint16_t state_flags;               // 0x8C: State flags
    uint8_t mode;                       // 0x8E: Operating mode
    uint8_t result;                     // 0x8F: Result status
    uint8_t max_debounce;               // 0x90: Max debounce count
    uint8_t direction;                  // 0x91: Current direction
} z_align_t;

/* State flag bits */
#define STATE_ACTIVE        0x0001      // Alignment active
#define STATE_MOVING_OUT    0x0002      // Moving outward (away from endstop)
#define STATE_AT_ENDSTOP    0x0004      // At endstop
#define STATE_MOVING_IN     0x0006      // Moving inward (toward endstop)
#define STATE_TRIGGERED     0x0008      // Trigger detected

/* Result codes */
#define RESULT_NONE         0           // No result yet
#define RESULT_SUCCESS      1           // Completed successfully
#define RESULT_ERROR        2           // Error occurred

/* Task handles */
static void *z_align_task_handle = NULL;
static void *finetuning_task_handle = NULL;

/* Type string for OID lookup */
static const char *Z_ALIGN_TYPE = "z_align";

/* ============================================
 * Timer Event Handler
 * ============================================ */

/**
 * Z-align timer event handler.
 * Called at regular intervals to generate step pulses.
 *
 * @param t     Timer structure (actually z_align_t pointer)
 * @return      1 to reschedule, 0 to stop
 */
uint_fast8_t z_align_event(timer_t *t)
{
    z_align_t *za = (z_align_t *)t;

    // Update wake time
    za->waketime += za->timer_interval;
    t->waketime = za->waketime;

    // Check state flags
    uint16_t state = za->state_flags;

    if (state & STATE_ACTIVE) {
        // Wake task for processing
        sched_wake_task(z_align_task_handle);
        return 1;
    }

    if (state & STATE_TRIGGERED) {
        // Wake finetuning task
        sched_wake_task(finetuning_task_handle);
        return 1;
    }

    return state & STATE_TRIGGERED;
}

/* ============================================
 * G-Code Command Handlers
 * ============================================ */

/**
 * Z_ALIGN_CONFIG - Configure Z alignment object.
 *
 * Args:
 *   [0]: OID
 */
void command_z_align_config(uint32_t *args)
{
    uint8_t oid = (uint8_t)args[0];

    z_align_t *za = (z_align_t *)oid_alloc(oid, Z_ALIGN_TYPE, sizeof(z_align_t));

    // Initialize timer callback
    za->timer.func = (void (*)(timer_t *))z_align_event;

    // Clear state
    za->state_flags = 0;
    za->result = 0;
    za->timer_interval = 0;
    za->start_interval = 0;
    za->mid_interval = 0;
    za->target_steps = 0;
    za->max_diff = 0;
    za->completion_mask = 0;
    za->num_motors = 0;
}

/**
 * Z_ALIGN_ADD - Add a Z motor channel.
 *
 * Args:
 *   [0]: OID
 *   [1]: Motor index (0-3)
 *   [2]: Step GPIO pin
 *   [3]: Direction GPIO pin
 *   [4]: Direction invert flag
 *   [5]: Endstop GPIO pin
 *   [6]: Endstop trigger state
 */
void command_z_align_add(uint32_t *args)
{
    uint8_t oid = (uint8_t)args[0];
    z_align_t *za = (z_align_t *)oid_lookup(oid, Z_ALIGN_TYPE);

    if (args[1] >= MAX_Z_MOTORS) {
        ctr_lookup_static_string("z_align: motor index out of range");
        sched_shutdown();
        return;
    }

    uint32_t idx = args[1];
    z_motor_t *motor = &za->motors[idx];

    za->num_motors++;

    // Setup step GPIO as output (low)
    gpio_out_setup(&motor->step_gpio, (uint8_t)args[2], 0);

    // Read current direction state
    motor->saved_dir = gpio_out_read((uint8_t)args[3]);

    // Setup direction GPIO with saved state
    gpio_out_setup(&motor->dir_gpio, (uint8_t)args[3], motor->saved_dir);

    // Store direction invert flag
    motor->dir_invert = (uint8_t)args[4];

    // Setup endstop GPIO as input with pull-up
    motor->endstop_gpio = gpio_in_setup((uint8_t)args[5], (uint8_t)args[6]);
    motor->endstop_state = (uint8_t)args[6];

    // Clear state
    motor->step_count = 0;
    motor->debounce_count = 0;

    za->result = 0;
    za->target_steps = 0;
    za->max_diff = 0;
    za->state_flags = 0;
    za->timer_interval = 0;
    za->completion_mask = 0;
}

/**
 * Z_ALIGN_FORCE_STOP - Force stop Z alignment.
 *
 * Args:
 *   [0]: OID
 */
void command_z_align_force_stop(uint32_t *args)
{
    uint8_t oid = (uint8_t)args[0];
    z_align_t *za = (z_align_t *)oid_lookup(oid, Z_ALIGN_TYPE);

    // Restore all motors to saved direction state
    for (uint32_t i = 0; i < za->num_motors; i++) {
        z_motor_t *motor = &za->motors[i];
        gpio_out_write(motor->dir_gpio, motor->saved_dir);
    }

    // Clear state
    za->result = 0;
    za->target_steps = 0;
    za->max_diff = 0;
    za->state_flags = 0;
    za->timer_interval = 0;
    za->completion_mask = 0;

    sched_del_timer(&za->timer);
}

/**
 * QUERY_Z_ALIGN - Query or start Z alignment.
 *
 * Args:
 *   [0]: OID
 *   [1]: Mode (0=query, 1=start)
 *   [2]: Start interval
 *   [3]: Mid interval
 *   [4]: Target steps
 *   [5]: Max debounce
 *   [6]: Max difference
 */
void command_query_z_align(uint32_t *args)
{
    uint8_t oid = (uint8_t)args[0];
    z_align_t *za = (z_align_t *)oid_lookup(oid, Z_ALIGN_TYPE);

    sched_del_timer(&za->timer);

    // Validate parameters
    if (args[2] == 0 || args[3] == 0 || args[4] == 0) {
        ctr_lookup_static_string("z_align: invalid parameters");
        sched_shutdown();
        return;
    }

    uint8_t mode = (uint8_t)args[1];
    za->mode = mode;
    za->start_interval = args[2];
    za->mid_interval = args[3];

    if (mode != 1) {
        // Query mode - just report current state
        za->state_flags &= ~STATE_ACTIVE;
        goto report;
    }

    // Start alignment mode
    za->target_steps = args[4];
    za->max_debounce = (uint8_t)args[5];
    za->max_diff = args[6];

    // Check initial endstop states
    uint16_t state = za->state_flags & 0xFFF7;  // Clear trigger flag
    state |= STATE_ACTIVE;
    za->completion_mask = 0;

    if (za->num_motors == 0) {
        // No motors - already at endstop
        state |= STATE_AT_ENDSTOP;
        za->timer_interval = za->start_interval;
    } else {
        int any_triggered = 0;

        for (uint32_t i = 0; i < za->num_motors; i++) {
            z_motor_t *motor = &za->motors[i];
            uint8_t endstop = gpio_in_read(motor->endstop_gpio);

            if (endstop != motor->endstop_state) {
                any_triggered = 1;
            }
        }

        if (!any_triggered) {
            // All at endstop - move outward first
            state |= STATE_AT_ENDSTOP;

            for (uint32_t i = 0; i < za->num_motors; i++) {
                z_motor_t *motor = &za->motors[i];
                motor->saved_dir = gpio_out_read(motor->dir_gpio);
                gpio_out_write(motor->dir_gpio, motor->dir_invert == 0);
                motor->debounce_count = 0;
                motor->step_count = 0;
            }

            za->timer_interval = za->start_interval;
        } else {
            // Some triggered - move inward
            state |= STATE_MOVING_IN;

            for (uint32_t i = 0; i < za->num_motors; i++) {
                z_motor_t *motor = &za->motors[i];
                motor->saved_dir = gpio_out_read(motor->dir_gpio);
                gpio_out_write(motor->dir_gpio, motor->dir_invert != 0);
                motor->debounce_count = 0;
                motor->step_count = 0;
            }

            za->timer_interval = za->mid_interval;
        }
    }

    za->state_flags = state;

    // Start timer
    irq_disable();
    za->result = 0;
    za->direction = 0;

    uint32_t now = timer_read_time();
    za->waketime = now + za->timer_interval;
    za->timer.waketime = za->waketime;

    uint32_t report_delay = timer_from_us(REPORT_INTERVAL_US);
    za->report_time = za->waketime + report_delay;

    sched_add_timer(&za->timer);
    irq_enable();

report:
    void *encoder = ctr_lookup_encoder("z_align_state");
    command_sendf(encoder, oid, za->result, za->position_offset[0]);
}

/**
 * Main Z alignment task.
 * Called when timer wakes up to process stepping.
 */
void z_align_task(void)
{
    uint8_t oid = 0xFF;
    uint32_t max_pos = 0;
    uint32_t min_pos = 0xFFFFFFFF;

    if (!sched_check_wake(z_align_task_handle)) {
        return;
    }

    // Iterate through all z_align instances
    z_align_t *za;
    while ((za = (z_align_t *)oid_next(&oid, Z_ALIGN_TYPE)) != NULL) {
        uint16_t state = za->state_flags;

        if (!(state & STATE_MOVING_OUT)) {
            // Normal stepping mode
            if (za->num_motors == 0) {
                if (za->max_diff < max_pos - min_pos) {
                    goto stop_alignment;
                }
                continue;
            }

            for (uint32_t i = 0; i < za->num_motors; i++) {
                z_motor_t *motor = &za->motors[i];

                uint8_t endstop = gpio_in_read(motor->endstop_gpio);

                if (endstop == motor->endstop_state) {
                    // Endstop triggered - step motor
                    gpio_out_toggle(motor->step_gpio);
                    motor->step_count++;
                    za->completion_mask &= ~(1 << i);
                    motor->debounce_count = 0;
                } else {
                    // Endstop not triggered
                    motor->debounce_count++;

                    if (motor->debounce_count >= za->max_debounce) {
                        za->completion_mask |= (1 << i);
                    }
                }

                // Track position range
                if (motor->step_count > max_pos) {
                    max_pos = motor->step_count;
                }
                if (motor->step_count < min_pos) {
                    min_pos = motor->step_count;
                }
            }

            // Check for completion
            if (za->max_diff < max_pos - min_pos) {
                goto stop_alignment;
            }

            // Check if all motors completed
            if (za->completion_mask == (uint32_t)((1 << za->num_motors) - 1) &&
                za->result != RESULT_ERROR) {

                za->timer_interval = za->mid_interval;

                if (state & STATE_AT_ENDSTOP) {
                    // Completed first phase - reverse and move in
                    za->direction++;

                    if (za->direction == 2) {
                        // Both phases complete - record offsets
                        for (uint32_t i = 0; i < za->num_motors; i++) {
                            z_motor_t *motor = &za->motors[i];
                            gpio_out_write(motor->dir_gpio, motor->saved_dir);
                        }

                        za->result = RESULT_SUCCESS;
                        za->state_flags = 0;
                        sched_del_timer(&za->timer);
                        continue;
                    }

                    // Switch to moving in
                    za->state_flags = (state & 0xFFF9) | STATE_MOVING_IN;

                    for (uint32_t i = 0; i < za->num_motors; i++) {
                        z_motor_t *motor = &za->motors[i];
                        gpio_out_write(motor->dir_gpio, motor->dir_invert != 0);
                        motor->step_count = 0;
                        motor->debounce_count = 0;
                    }

                    za->completion_mask = 0;
                } else {
                    // Normal mode - switch to moving out
                    za->state_flags = (state & 0xFFF9) | STATE_MOVING_OUT;

                    if (za->num_motors > 1) {
                        // Record position offsets
                        int32_t base = za->motors[0].step_count;
                        for (uint32_t i = 0; i < za->num_motors; i++) {
                            za->position_offset[i] = za->motors[i].step_count - base;

                            // Handle phase 1 offset
                            if (!(state & STATE_AT_ENDSTOP)) {
                                za->position_offset[i] = -za->motors[i].step_count;
                            }
                        }
                    }

                    za->direction++;
                    if (za->direction == 2) {
                        for (uint32_t i = 0; i < za->num_motors; i++) {
                            z_motor_t *motor = &za->motors[i];
                            gpio_out_write(motor->dir_gpio, motor->saved_dir);
                        }

                        za->result = RESULT_SUCCESS;
                        za->state_flags = 0;
                        sched_del_timer(&za->timer);
                        continue;
                    }

                    for (uint32_t i = 0; i < za->num_motors; i++) {
                        z_motor_t *motor = &za->motors[i];
                        gpio_out_write(motor->dir_gpio, motor->dir_invert == 0);
                        za->completion_mask = 0;
                        motor->debounce_count = 0;
                        motor->step_count = 0;
                    }
                }
            }
        } else {
            // Moving outward phase
            int all_clear = 1;

            for (uint32_t i = 0; i < za->num_motors; i++) {
                z_motor_t *motor = &za->motors[i];

                gpio_out_toggle(motor->step_gpio);
                motor->step_count++;

                if (motor->step_count < za->target_steps) {
                    all_clear = 0;
                }
            }

            if (all_clear) {
                // Check all endstops cleared
                int any_still_triggered = 0;
                for (uint32_t i = 0; i < za->num_motors; i++) {
                    z_motor_t *motor = &za->motors[i];
                    uint8_t endstop = gpio_in_read(motor->endstop_gpio);

                    if (endstop != motor->endstop_state) {
                        any_still_triggered = 1;
                        break;
                    }
                }

                if (!any_still_triggered) {
                    // Error - endstop still triggered
                    za->result = RESULT_ERROR;

                    for (uint32_t i = 0; i < za->num_motors; i++) {
                        gpio_out_write(za->motors[i].dir_gpio, za->motors[i].saved_dir);
                    }

                    za->state_flags = 0;
                    sched_del_timer(&za->timer);
                    continue;
                }

                // Switch to normal stepping
                za->state_flags &= ~STATE_MOVING_OUT;

                for (uint32_t i = 0; i < za->num_motors; i++) {
                    z_motor_t *motor = &za->motors[i];
                    gpio_out_write(motor->dir_gpio, motor->dir_invert == 0);
                    za->completion_mask = 0;
                    motor->debounce_count = 0;
                    motor->step_count = 0;
                }
            }
        }

        continue;

stop_alignment:
        // Position difference too large - stop
        for (uint32_t i = 0; i < za->num_motors; i++) {
            gpio_out_write(za->motors[i].dir_gpio, za->motors[i].saved_dir);
        }

        za->result = RESULT_ERROR;
        za->state_flags = 0;
        sched_del_timer(&za->timer);

        // Report status
        uint32_t now = timer_read_time();
        if (timer_is_before(za->report_time, now) || za->result != 0) {
            uint32_t report_delay = timer_from_us(REPORT_INTERVAL_US);
            za->report_time = now + report_delay;

            void *encoder = ctr_lookup_encoder("z_align_state");
            command_sendf(encoder, oid, za->result, za->position_offset[0]);
            za->result = 0;
        }
    }
}

/**
 * QUERY_FINETUNING - Query or start fine tuning mode.
 *
 * Args:
 *   [0]: OID
 *   [1]: Mode (0=query, 1=start)
 *   [2]: Mid interval
 *   [3]: Target steps
 *   [4]: Max debounce
 */
void command_query_finetuning(uint32_t *args)
{
    uint8_t oid = (uint8_t)args[0];
    z_align_t *za = (z_align_t *)oid_lookup(oid, Z_ALIGN_TYPE);

    sched_del_timer(&za->timer);

    if (args[2] == 0 || args[3] == 0 || args[4] == 0) {
        ctr_lookup_static_string("finetuning: invalid parameters");
        sched_shutdown();
        return;
    }

    uint8_t mode = (uint8_t)args[1];
    za->mode = mode;
    za->mid_interval = args[2];
    za->state_flags &= ~STATE_ACTIVE;

    if (mode != 1) {
        za->result = 0;
        za->state_flags = 0;
        goto report;
    }

    za->target_steps = args[3];
    za->max_debounce = (uint8_t)args[4];
    za->state_flags |= STATE_TRIGGERED;

    // Check initial endstop states
    if (za->num_motors > 0) {
        int any_triggered = 0;

        for (uint32_t i = 0; i < za->num_motors; i++) {
            z_motor_t *motor = &za->motors[i];
            uint8_t endstop = gpio_in_read(motor->endstop_gpio);

            if (endstop != motor->endstop_state) {
                any_triggered = 1;
            }
        }

        if (any_triggered) {
            za->result = RESULT_SUCCESS;
            goto report;
        }

        // Setup motors for fine tuning
        for (uint32_t i = 0; i < za->num_motors; i++) {
            z_motor_t *motor = &za->motors[i];
            motor->saved_dir = gpio_out_read(motor->dir_gpio);
            gpio_out_write(motor->dir_gpio, motor->dir_invert == 0);
            motor->step_count = 0;
        }
    }

    za->timer_interval = args[2];
    za->result = 0;

    irq_disable();
    za->direction = 0;

    uint32_t now = timer_read_time();
    za->waketime = now + za->timer_interval;
    za->timer.waketime = za->waketime;

    uint32_t report_delay = timer_from_us(REPORT_INTERVAL_US);
    za->report_time = za->waketime + report_delay;

    sched_add_timer(&za->timer);
    irq_enable();

report:
    void *encoder = ctr_lookup_encoder("finetuning_state");
    command_sendf(encoder, oid, za->result, 0);
}

/**
 * Fine tuning task.
 * Called for precise position adjustment.
 */
void finetuning_task(void)
{
    uint8_t oid = 0xFF;
    uint32_t position = 0;

    if (!sched_check_wake(finetuning_task_handle)) {
        return;
    }

    z_align_t *za;
    while ((za = (z_align_t *)oid_next(&oid, Z_ALIGN_TYPE)) != NULL) {
        if (za->num_motors == 0) continue;

        for (uint32_t i = 0; i < za->num_motors; i++) {
            z_motor_t *motor = &za->motors[i];

            if (motor->step_count < za->target_steps) {
                uint8_t endstop = gpio_in_read(motor->endstop_gpio);

                if (endstop == motor->endstop_state) {
                    gpio_out_toggle(motor->step_gpio);
                    motor->debounce_count = 0;
                    motor->step_count++;
                } else {
                    motor->debounce_count++;

                    if (motor->debounce_count >= za->max_debounce) {
                        position = motor->step_count;
                        za->result = RESULT_SUCCESS;
                        goto done;
                    }
                }

                if (za->result != 0) {
                    goto done;
                }
            } else {
                za->result = RESULT_ERROR;
done:
                if (za->num_motors > 0) {
                    for (uint32_t j = 0; j < za->num_motors; j++) {
                        gpio_out_write(za->motors[j].dir_gpio, za->motors[j].saved_dir);
                    }
                }

                za->state_flags = 0;
                sched_del_timer(&za->timer);
            }
        }

        // Report status
        uint32_t now = timer_read_time();
        if (timer_is_before(za->report_time, now) || za->result != 0) {
            uint32_t report_delay = timer_from_us(REPORT_INTERVAL_US);
            za->report_time = now + report_delay;

            void *encoder = ctr_lookup_encoder("finetuning_state");
            command_sendf(encoder, oid, za->result, position);
            za->result = 0;
        }
    }
}

/**
 * Shutdown handler.
 * Called on MCU shutdown to clean up resources.
 */
void z_align_shutdown(void)
{
    uint8_t oid = 0xFF;

    z_align_t *za;
    while ((za = (z_align_t *)oid_next(&oid, Z_ALIGN_TYPE)) != NULL) {
        za->num_motors = 0;
        za->timer_interval = 0;
        za->target_steps = 0;
        za->completion_mask = 0;
        za->state_flags = 0;
        za->max_debounce = 0;

        sched_del_timer(&za->timer);
    }
}

/* ============================================
 * Notes on Z-Align Algorithm
 * ============================================
 *
 * Purpose:
 * The Z-align module is used to level the gantry on dual-Z printers.
 * It steps each Z motor until its endstop triggers, then records
 * the position difference to calculate the needed offset.
 *
 * Alignment Sequence:
 * 1. Check initial endstop states
 * 2. If at endstop: move outward until clear
 * 3. Move inward until endstops trigger
 * 4. Record position differences
 * 5. Optionally repeat for verification
 *
 * Fine Tuning:
 * A second mode for precise adjustment after initial alignment.
 * Steps motors slowly while monitoring endstops for exact positioning.
 *
 * Position Tracking:
 * Each motor's step count is tracked independently.
 * Position offsets are calculated relative to the first motor.
 * Maximum allowed difference prevents damage from severe misalignment.
 *
 * Error Handling:
 * - Invalid parameters cause shutdown
 * - Position difference exceeding limit stops alignment
 * - Endstop debouncing prevents false triggers
 */
