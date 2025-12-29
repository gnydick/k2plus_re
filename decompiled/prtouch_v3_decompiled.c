/**
 * Decompiled and annotated from: prtouch_v3.o
 * Purpose: PRTouch v3 MCU firmware for multi-channel pressure sensing
 *
 * This module implements the latest PRTouch pressure sensing system for the
 * Creality K2 Series. It adds support for multiple pressure sensor channels,
 * data compression for efficient communication, and advanced trigger detection.
 *
 * Key Features:
 * - Multi-channel HX711-style pressure sensor support
 * - SPI-like bit-banged communication for sensor configuration
 * - Delta compression for efficient data transfer
 * - High-frequency filtering for noise reduction
 * - Sophisticated trigger detection algorithm
 *
 * Sensor Protocol:
 * - 24-bit ADC readings via clocked serial interface
 * - Configuration registers for gain/channel selection
 * - Clock line (SCK) generated via GPIO bit-banging
 * - Data line (SDI/SDO) for bidirectional communication
 *
 * Tool: Ghidra + Manual RE analysis
 * Original: src/prtouch_v3.c (MCU firmware)
 *
 * =============================================================================
 * PROVENANCE NOTICE - READ BEFORE USING THIS CODE
 * =============================================================================
 *
 * This file was decompiled from compiled ARM MCU firmware using Ghidra.
 * The accuracy varies by category:
 *
 * GHIDRA DECOMPILATION (high confidence):
 *   - Bit-banged SPI/HX711 clock and data line manipulation
 *   - 24-bit ADC reading loop structure (24 clock pulses)
 *   - Delta compression algorithm structure
 *   - Multi-channel iteration patterns
 *   - Klipper command/response message construction
 *
 * DATA SECTION EXTRACTION (high confidence):
 *   - MAX_CHANNELS = 4
 *   - SAMPLES_PER_CHANNEL = 64 (0x40)
 *   - ZIP_BUFFER_SIZE = 80 (0x50)
 *   - ADC_BITS = 24
 *   - ADC timeout and delay constants
 *
 * HUMAN INTERPRETATION (lower confidence):
 *   - Function names: read_adc, zip_data, unzip_data, hftr_filter
 *   - Structure definitions for multi-channel sensor state
 *   - Delta compression explanation
 *   - High-frequency filter algorithm description
 *   - Trigger detection threshold logic
 *
 * UNCERTAIN:
 *   - Exact HX711 timing requirements
 *   - Filter coefficients and window sizes
 *   - Compression ratio expectations
 *   - ADC calibration/offset handling
 * =============================================================================
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ============================================
 * Constants
 * ============================================ */

#define MAX_CHANNELS        4       // Maximum pressure sensor channels
#define SAMPLES_PER_CHANNEL 64      // Samples per channel (0x40)
#define ZIP_BUFFER_SIZE     80      // 0x50 - compression buffer size
#define ZIP_DATA_OFFSET     16      // 0x10 - data offset in zip buffer
#define ADC_BITS            24      // HX711-style ADC resolution
#define ADC_SIGN_EXT_MASK   0xFF000000  // Sign extension for 24-bit
#define ADC_BUSY_FLAG       0x80000000  // ADC busy/invalid reading
#define FILTER_WINDOW       5       // High-frequency filter window size

/* Delay loop iterations for timing */
#define DELAY_LOOP_COUNT    10

/* ADC timeout in ticks */
#define ADC_TIMEOUT_TICKS   0x1F6   // ~500 iterations

/* ============================================
 * External Dependencies (Klipper MCU)
 * ============================================ */

extern uint32_t timer_read_time(void);
extern void gpio_out_write(uint32_t gpio, int32_t value);
extern int32_t gpio_in_read(uint8_t gpio);
extern void gpio_out_setup(void *out, uint8_t pin, int value);
extern uint8_t gpio_in_setup(uint8_t pin, int pull);
extern uint32_t gpio_adc_setup(uint8_t pin);
extern int32_t gpio_adc_sample(uint32_t adc);
extern uint32_t gpio_adc_read(uint32_t adc);

extern void *ctr_lookup_encoder(const char *name);
extern void command_sendf(void *encoder, ...);

/* Floating point helpers (ARM EABI) */
extern float __aeabi_ui2f(uint32_t a);
extern float __aeabi_fdiv(float a, float b);
extern float __aeabi_fmul(float a, float b);
extern float __aeabi_fadd(float a, float b);
extern float __aeabi_fsub(float a, float b);
extern float __aeabi_i2f(int32_t a);
extern int32_t __aeabi_f2iz(float a);
extern double __aeabi_f2d(float a);
extern int __aeabi_dcmpgt(double a, double b);

/* ============================================
 * Data Structures
 * ============================================ */

/**
 * Delay/timing checker structure
 */
typedef struct syst_dly {
    uint32_t last_tick;             // Last recorded tick
} syst_dly_t;

/**
 * Data compression (zip) structure
 * Uses delta encoding with variable-length fields
 */
typedef struct syst_zip {
    uint32_t idx_data;              // Current data index
    uint8_t *buf_data;              // Pointer to data buffer
    int32_t lst_data;               // Last data value (for delta)
    uint32_t idx_tile;              // Tile/header index
    uint8_t out_data[ZIP_BUFFER_SIZE];  // Output buffer
    uint8_t tmp_data[ZIP_BUFFER_SIZE];  // Temporary buffer for read
} syst_zip_t;

/**
 * Per-channel sensor state
 */
typedef struct pres_channel {
    uint32_t last_tick;             // Last read timestamp
    uint32_t sck_gpio;              // Serial clock GPIO
    uint32_t sdo_gpio;              // Serial data out GPIO
    uint8_t sdi_gpio;               // Serial data in GPIO
    uint32_t adc_handle;            // ADC handle (for analog mode)
    int32_t config_state;           // Configuration state machine
    uint32_t current_cfg;           // Current configuration
    syst_zip_t tick_zip;            // Tick compression
    syst_zip_t data_zip;            // Data compression
} pres_channel_t;

/**
 * PRTouch v3 context structure
 */
typedef struct prtouch_v3 {
    uint32_t oid;                   // Object ID
    uint32_t use_adc;               // Use ADC mode (vs bit-bang SPI)
    uint32_t num_channels;          // Number of active channels
    uint32_t target_cfg;            // Target configuration register

    uint32_t sample_idx;            // Current sample index
    uint32_t last_sample_tick;      // Timestamp of last sample

    // Per-channel data storage
    uint32_t tick_data[MAX_CHANNELS][SAMPLES_PER_CHANNEL];  // Timestamps
    int32_t raw_data[MAX_CHANNELS][SAMPLES_PER_CHANNEL];    // Raw ADC values
    int32_t filtered_data[MAX_CHANNELS][SAMPLES_PER_CHANNEL]; // Filtered values

    // Per-channel state
    pres_channel_t channels[MAX_CHANNELS];

    // Trigger detection state
    uint32_t trigger_mask;          // Triggered channels bitmask
    int32_t use_filter;             // Enable high-frequency filter
    int32_t filter_alpha;           // Filter coefficient (IIR)
    int32_t trigger_threshold;      // Trigger threshold
    int32_t trigger_count;          // Required consecutive samples
    int32_t trigger_delta;          // Delta threshold

    // Sampling parameters
    uint32_t sample_interval;       // Ticks between samples
    uint32_t trigger_out_low;       // Trigger output when tripped
    uint32_t trigger_out_high;      // Trigger output when not tripped
    uint32_t min_samples;           // Minimum samples before trigger

    // Output GPIO
    uint32_t output_gpio;           // Trigger output GPIO
} prtouch_v3_t;

/**
 * Global PRTouch v3 context
 */
static prtouch_v3_t *g_prtouch_v3 = NULL;

/* ============================================
 * Timing Functions
 * ============================================ */

/**
 * Check if delay has elapsed.
 *
 * @param dly       Delay structure
 * @param dly_tick  Delay in ticks
 * @return          1 if elapsed, 0 otherwise
 */
uint8_t prtouch_ck_delay(syst_dly_t *dly, uint32_t dly_tick)
{
    uint32_t now = timer_read_time();
    uint32_t elapsed = now;

    // Handle wrap-around
    if (dly->last_tick < now) {
        elapsed = now - dly->last_tick;
    }

    if (elapsed >= dly_tick) {
        dly->last_tick = now;
        return 1;
    }

    return 0;
}

/**
 * Calculate tick interval in milliseconds.
 *
 * @param last_tick Previous tick
 * @param now_tick  Current tick
 * @return          Interval in ticks
 */
uint32_t prtouch_tick_intv_ms(uint32_t last_tick, uint32_t now_tick)
{
    if (last_tick < now_tick) {
        return now_tick - last_tick;
    }
    return now_tick;  // Wrap-around case
}

/**
 * Busy-wait delay in microseconds.
 * Uses NOP loop for timing.
 *
 * @param us    Microseconds to delay
 */
void prtouch_delay_us(uint32_t us)
{
    if (us == 0) return;

    for (uint32_t i = 0; i < us; i++) {
        // Inner loop provides ~1us delay
        for (volatile uint32_t j = DELAY_LOOP_COUNT; j > 0; j--);
    }
}

/* ============================================
 * Data Compression Functions
 * ============================================ */

/**
 * Reset compression state.
 *
 * @param zip   Compression structure
 */
void prtouch_reset_zip(syst_zip_t *zip)
{
    zip->idx_data = 0;
    zip->buf_data = zip->out_data + ZIP_DATA_OFFSET;
    zip->lst_data = 0;
    zip->idx_tile = 0;
    memset(zip->out_data, 0, ZIP_BUFFER_SIZE);
}

/**
 * Write a value with delta compression.
 *
 * Uses variable-length encoding:
 * - 1 byte for delta in [-128, 127]
 * - 2 bytes for delta in [-32768, 32767]
 * - 3 bytes for delta in [-8388608, 8388607]
 * - 4 bytes otherwise
 *
 * @param zip   Compression structure
 * @param data  Data value to write
 * @return      Total compressed size so far
 */
uint32_t prtouch_write_zip(syst_zip_t *zip, int32_t data)
{
    uint32_t tile_bytes = zip->idx_tile >> 2;

    if (data == (int32_t)0x80000000) {
        // Special marker - don't write
        return zip->idx_data + 2 + tile_bytes;
    }

    int32_t delta = data - zip->lst_data;
    size_t len;
    int size_code;

    // Determine encoding size needed
    if ((uint32_t)(delta + 0x80) < 0x100) {
        size_code = 0;  // 1 byte
        len = 1;
    } else if ((uint32_t)(delta + 0x8000) < 0x10000) {
        size_code = 1;  // 2 bytes
        len = 2;
    } else if ((uint32_t)(delta + 0x800000) < 0x1000000) {
        size_code = 2;  // 3 bytes
        len = 3;
    } else {
        size_code = 3;  // 4 bytes
        len = 4;
    }

    // Write delta value
    memcpy(zip->buf_data + zip->idx_data, &delta, len);

    // Update tile header (2 bits per entry)
    uint32_t tile_idx = ~tile_bytes;  // Negative offset from buffer start
    zip->buf_data[tile_idx] |= (size_code << ((zip->idx_tile & 3) << 1));

    // Update state
    zip->idx_data += len;
    zip->lst_data = data;
    zip->idx_tile++;

    return zip->idx_data + tile_bytes + 2;
}

/**
 * Read compressed data for transmission.
 *
 * @param zip   Compression structure
 * @return      Pointer to compressed data
 */
uint8_t *prtouch_read_zip(syst_zip_t *zip)
{
    uint32_t tile_bytes = (zip->idx_tile + 3) >> 2;
    if (zip->idx_tile == 0) tile_bytes++;

    uint32_t offset = ~tile_bytes;
    zip->buf_data[offset] = (uint8_t)zip->idx_tile;

    // Copy to temp buffer for return
    uint32_t total_len = zip->idx_data + 2 + (zip->idx_tile >> 2);
    memcpy(zip->tmp_data, zip->buf_data + offset, total_len);

    // Reset for next batch
    prtouch_reset_zip(zip);

    return zip->tmp_data;
}

/* ============================================
 * Pressure Sensor Communication
 * ============================================ */

/**
 * Write configuration register to pressure sensor.
 * Uses SPI-like bit-banged protocol for HX711-style ADC.
 *
 * Protocol:
 * 1. Pull clock low, wait for data ready
 * 2. Read 24-bit ADC value (MSB first)
 * 3. Send 7-bit command (0x65 = write config)
 * 4. Send 8-bit configuration value
 * 5. Generate final clock pulse
 *
 * @param ch        Channel index
 * @param cfg_regs  Configuration value to write
 * @return          ADC reading, or 0x80000000 on error
 */
uint32_t pres_csx_w_cfg(int32_t ch, uint32_t cfg_regs)
{
    prtouch_v3_t *pt = g_prtouch_v3;
    pres_channel_t *channel = &pt->channels[ch];

    // Pull clock low to start
    gpio_out_write(channel->sck_gpio, 0);
    prtouch_delay_us(1);

    // Check if data line is ready (low = ready)
    if (gpio_in_read(channel->sdi_gpio) != 0) {
        // Check timeout
        uint32_t last_tick = channel->last_tick;
        uint32_t elapsed = timer_read_time();
        if (last_tick < elapsed) {
            elapsed -= last_tick;
        }
        if (elapsed < ADC_TIMEOUT_TICKS) {
            return ADC_BUSY_FLAG;  // Still busy
        }
    }

    // Record timestamp
    channel->last_tick = timer_read_time();
    prtouch_delay_us(1);

    // Read 29-bit value (24-bit ADC + 5 unused)
    uint32_t data = 0;
    for (int i = 0; i < 29; i++) {
        gpio_out_write(channel->sck_gpio, 1);
        prtouch_delay_us(1);
        data = (data << 1) | (gpio_in_read(channel->sdi_gpio) & 1);
        gpio_out_write(channel->sck_gpio, 0);
        prtouch_delay_us(1);
    }

    // Extract 24-bit value with sign extension
    uint32_t adc_value = data >> 5;
    if (data & 0x80000000) {  // Sign bit
        adc_value |= ADC_SIGN_EXT_MASK;
    }

    // Switch data line to output for command
    gpio_out_setup(&channel->sdo_gpio, channel->sdi_gpio, 0);

    // Send 7-bit write command (0x65)
    const uint8_t WRITE_CMD = 0x65;
    for (int i = 0; i < 7; i++) {
        gpio_out_write(channel->sck_gpio, 1);
        prtouch_delay_us(1);
        gpio_out_write(channel->sdo_gpio, (WRITE_CMD >> (6 - i)) & 1);
        prtouch_delay_us(1);
        gpio_out_write(channel->sck_gpio, 0);
        prtouch_delay_us(1);
    }

    // Extra clock pulse
    gpio_out_write(channel->sck_gpio, 1);
    prtouch_delay_us(1);
    gpio_out_write(channel->sck_gpio, 0);
    prtouch_delay_us(1);

    // Send 8-bit configuration value
    for (int i = 0; i < 8; i++) {
        gpio_out_write(channel->sck_gpio, 1);
        prtouch_delay_us(1);
        gpio_out_write(channel->sdo_gpio, (cfg_regs >> (7 - i)) & 1);
        prtouch_delay_us(1);
        gpio_out_write(channel->sck_gpio, 0);
        prtouch_delay_us(1);
    }

    // Switch data line back to input
    channel->sdi_gpio = gpio_in_setup(channel->sdi_gpio, 1);

    // Final clock pulses
    gpio_out_write(channel->sck_gpio, 1);
    prtouch_delay_us(1);
    gpio_out_write(channel->sck_gpio, 0);
    prtouch_delay_us(1);

    channel->last_tick = timer_read_time();
    return adc_value;
}

/**
 * Read configuration register from pressure sensor.
 *
 * @param ch    Channel index
 * @param r_reg Output: configuration register value
 * @return      ADC reading, or 0x80000000 on error
 */
uint32_t pres_csx_r_cfg(uint32_t ch, uint32_t *r_reg)
{
    prtouch_v3_t *pt = g_prtouch_v3;
    pres_channel_t *channel = &pt->channels[ch];

    *r_reg = 0;

    // Pull clock low to start
    gpio_out_write(channel->sck_gpio, 0);
    prtouch_delay_us(1);

    // Check if data line is ready
    if (gpio_in_read(channel->sdi_gpio) != 0) {
        uint32_t last_tick = channel->last_tick;
        uint32_t elapsed = timer_read_time();
        if (last_tick < elapsed) {
            elapsed -= last_tick;
        }
        if (elapsed < ADC_TIMEOUT_TICKS) {
            return ADC_BUSY_FLAG;
        }
    }

    channel->last_tick = timer_read_time();
    prtouch_delay_us(1);

    // Read 29-bit ADC value
    uint32_t data = 0;
    for (int i = 0; i < 29; i++) {
        gpio_out_write(channel->sck_gpio, 1);
        prtouch_delay_us(1);
        data = (data << 1) | (gpio_in_read(channel->sdi_gpio) & 1);
        gpio_out_write(channel->sck_gpio, 0);
        prtouch_delay_us(1);
    }

    uint32_t adc_value = data >> 5;
    if (data & 0x80000000) {
        adc_value |= ADC_SIGN_EXT_MASK;
    }

    // Switch to output for command
    gpio_out_setup(&channel->sdo_gpio, channel->sdi_gpio, 0);

    // Send 7-bit read command (0x56)
    const uint8_t READ_CMD = 0x56;
    for (int i = 0; i < 7; i++) {
        gpio_out_write(channel->sck_gpio, 1);
        prtouch_delay_us(1);
        gpio_out_write(channel->sdo_gpio, (READ_CMD >> (6 - i)) & 1);
        prtouch_delay_us(1);
        gpio_out_write(channel->sck_gpio, 0);
        prtouch_delay_us(1);
    }

    // Extra clock pulse
    gpio_out_write(channel->sck_gpio, 1);
    prtouch_delay_us(1);
    gpio_out_write(channel->sck_gpio, 0);
    prtouch_delay_us(1);

    // Switch back to input
    channel->sdi_gpio = gpio_in_setup(channel->sdi_gpio, 1);

    // Read 8-bit configuration register
    for (int i = 7; i >= 0; i--) {
        gpio_out_write(channel->sck_gpio, 1);
        prtouch_delay_us(1);
        gpio_out_write(channel->sck_gpio, 0);
        prtouch_delay_us(1);
        *r_reg |= gpio_in_read(channel->sdi_gpio) << i;
    }

    // Final clock pulses
    gpio_out_write(channel->sck_gpio, 1);
    prtouch_delay_us(1);
    gpio_out_write(channel->sck_gpio, 0);
    prtouch_delay_us(1);

    channel->last_tick = timer_read_time();
    return adc_value;
}

/**
 * Get pressure sensor data.
 * Supports both bit-banged SPI and hardware ADC modes.
 *
 * @param ch    Channel index
 * @return      ADC reading, or 0x80000000 on error
 */
uint32_t pres_get_datas(int32_t ch)
{
    prtouch_v3_t *pt = g_prtouch_v3;

    if (pt->use_adc) {
        // Hardware ADC mode
        pres_channel_t *channel = &pt->channels[ch];
        int timeout = ADC_TIMEOUT_TICKS;

        // Wait for ADC ready with timeout
        while (gpio_adc_sample(channel->adc_handle) != 0 && --timeout > 0) {
            prtouch_delay_us(1);
        }

        return gpio_adc_read(channel->adc_handle);
    }

    // Bit-banged SPI mode
    pres_channel_t *channel = &pt->channels[ch];

    gpio_out_write(channel->sck_gpio, 0);
    prtouch_delay_us(1);

    // Check data ready
    if (gpio_in_read(channel->sdi_gpio) != 0) {
        uint32_t last_tick = channel->last_tick;
        uint32_t elapsed = timer_read_time();
        if (last_tick < elapsed) {
            elapsed -= last_tick;
        }
        if (elapsed <= ADC_TIMEOUT_TICKS) {
            return ADC_BUSY_FLAG;
        }
    }

    channel->last_tick = timer_read_time();
    prtouch_delay_us(1);

    // Read 27-bit value
    uint32_t data = 0;
    for (int i = 0; i < 27; i++) {
        gpio_out_write(channel->sck_gpio, 1);
        prtouch_delay_us(1);
        data = (data << 1) | (gpio_in_read(channel->sdi_gpio) & 1);
        gpio_out_write(channel->sck_gpio, 0);
        prtouch_delay_us(1);
    }

    // Extract 24-bit value
    uint32_t adc_value = data >> 3;
    if (data & 0x80000000) {
        adc_value |= ADC_SIGN_EXT_MASK;
    }

    return adc_value;
}

/* ============================================
 * Signal Processing Functions
 * ============================================ */

/**
 * High-frequency filter calculation.
 * Finds the value with minimum absolute difference from previous.
 *
 * @param ftr_data  Filter data array
 * @param ftr_len   Number of elements
 */
void pres_hftr_cal(int32_t *ftr_data, int32_t ftr_len)
{
    if (ftr_len <= 0) return;

    int32_t abs_diff[FILTER_WINDOW] = {0};
    int32_t prev = ftr_data[-1];

    // Calculate absolute differences
    for (int i = 0; i < ftr_len; i++) {
        int32_t diff = ftr_data[i] - prev;
        abs_diff[i] = (diff < 0) ? -diff : diff;
    }

    // Find minimum difference index
    int min_idx = 0;
    int32_t min_val = 0x7FFFFF;
    for (int i = 0; i < ftr_len; i++) {
        if (abs_diff[i] < min_val) {
            min_idx = i;
            min_val = abs_diff[i];
        }
    }

    // Replace first element with minimum difference value
    *ftr_data = ftr_data[min_idx];
}

/**
 * Check for pressure trigger condition.
 * Analyzes pressure data to detect contact with bed.
 *
 * Algorithm:
 * 1. Shift sample buffers (FIFO behavior)
 * 2. Store new sample
 * 3. Apply high-frequency filtering if enabled
 * 4. Apply IIR low-pass filter if enabled
 * 5. Check for monotonic increasing/decreasing pattern
 * 6. Check against threshold
 *
 * @param ch    Channel index
 * @param tick  Current timestamp
 * @param data  New pressure reading
 * @return      Trigger bitmask
 */
uint8_t pres_tri_check(int32_t ch, uint32_t tick, int32_t data)
{
    prtouch_v3_t *pt = g_prtouch_v3;

    // Reset trigger mask for new check
    pt->trigger_mask = 0;

    // Shift sample arrays (oldest drops off)
    int32_t *tick_buf = pt->tick_data[ch];
    int32_t *raw_buf = pt->raw_data[ch];
    int32_t *filt_buf = pt->filtered_data[ch];

    for (int i = 0; i < SAMPLES_PER_CHANNEL - 1; i++) {
        tick_buf[i] = tick_buf[i + 1];
        raw_buf[i] = raw_buf[i + 1];
        filt_buf[i] = filt_buf[i + 1];
    }

    // Increment sample count
    pt->channels[ch].config_state++;

    // Store new sample
    tick_buf[SAMPLES_PER_CHANNEL - 1] = tick;
    raw_buf[SAMPLES_PER_CHANNEL - 1] = data;
    filt_buf[SAMPLES_PER_CHANNEL - 1] = data;

    // Apply high-frequency filter to raw data
    if (pt->use_filter) {
        pres_hftr_cal(&filt_buf[SAMPLES_PER_CHANNEL - FILTER_WINDOW], FILTER_WINDOW);
    }

    // Apply IIR low-pass filter
    float alpha = *(float *)&pt->filter_alpha;
    if (alpha > 0.0f && pt->channels[ch].config_state > 5) {
        float prev = __aeabi_i2f(filt_buf[SAMPLES_PER_CHANNEL - 2]);
        float curr = __aeabi_i2f(filt_buf[SAMPLES_PER_CHANNEL - 1]);
        float filtered = __aeabi_fmul(prev, __aeabi_fsub(1.0f, alpha));
        filtered = __aeabi_fadd(filtered, __aeabi_fmul(curr, alpha));
        filt_buf[SAMPLES_PER_CHANNEL - 1] = __aeabi_f2iz(filtered);
    }

    // Check if we have enough samples
    if (pt->channels[ch].config_state < pt->min_samples) {
        return pt->trigger_mask;
    }

    // Mode 1: Simple threshold check
    if (pt->trigger_out_low) {
        int count = 0;
        for (int i = SAMPLES_PER_CHANNEL - pt->trigger_count; i < SAMPLES_PER_CHANNEL; i++) {
            if (filt_buf[i] >= pt->trigger_threshold) {
                count++;
            }
        }
        if (count == pt->trigger_count) {
            pt->trigger_mask |= (1 << ch);
        }
        return pt->trigger_mask;
    }

    // Mode 2: Pattern-based trigger detection
    int32_t check_data[FILTER_WINDOW] = {0};

    // Copy last 5 samples
    for (int i = 0; i < FILTER_WINDOW; i++) {
        check_data[i] = filt_buf[SAMPLES_PER_CHANNEL - FILTER_WINDOW + i];
    }

    // Apply additional filtering
    pres_hftr_cal(&check_data[1], 3);
    pres_hftr_cal(&check_data[2], 3);

    // Check direction (invert if decreasing)
    int32_t first_val = raw_buf[SAMPLES_PER_CHANNEL - FILTER_WINDOW];
    int32_t last_val = filt_buf[SAMPLES_PER_CHANNEL - 1];

    if (last_val < first_val) {
        for (int i = 0; i < FILTER_WINDOW; i++) {
            check_data[i] = -check_data[i];
        }
    }

    // Check for monotonic increasing pattern with thresholds
    if (check_data[3] >= check_data[4] || check_data[2] >= check_data[3]) {
        return pt->trigger_mask;
    }

    int32_t thresh = pt->trigger_threshold;
    int32_t delta = pt->trigger_delta;

    if (check_data[4] >= thresh + delta * 2 &&
        check_data[3] >= thresh + delta &&
        check_data[2] >= thresh) {
        // Check first sample against threshold
        if (first_val <= check_data[2]) {
            pt->trigger_mask |= (1 << ch);
        }
    }

    return pt->trigger_mask;
}

/* ============================================
 * G-Code Command Handlers
 * ============================================ */

/**
 * PRTOUCH_PRES_CONFIG - Configure pressure sensing.
 *
 * Args:
 *   [0]: OID
 *   [1]: Channel index
 *   [2]: Data/clock GPIO pin
 *   [3]: Clock GPIO pin (SPI mode) or same as [2] (ADC mode)
 *   [4]: ADC GPIO pin (ADC mode) or same as [3] (SPI mode)
 */
void command_config_prtouch_pres(uint32_t *args)
{
    prtouch_v3_t *pt = g_prtouch_v3;

    pt->oid = args[0];
    pt->num_channels = args[1] + 1;

    uint32_t ch = args[1];
    uint32_t data_pin = args[2];
    uint32_t clk_pin = args[3];
    uint32_t adc_pin = args[4];

    // Setup data line as input
    pt->channels[ch].sdi_gpio = gpio_in_setup(data_pin, 0);

    // Setup clock as output (high initially)
    gpio_out_setup(&pt->channels[ch].sck_gpio, data_pin, 1);

    // Determine mode
    pt->use_adc = (clk_pin == adc_pin);

    if (!pt->use_adc) {
        // SPI mode
        gpio_out_setup(&pt->channels[ch].sck_gpio, clk_pin, 1);
        pt->channels[ch].sdi_gpio = gpio_in_setup(adc_pin, 1);
    } else {
        // ADC mode
        pt->channels[ch].adc_handle = gpio_adc_setup(clk_pin);
    }

    void *encoder = ctr_lookup_encoder("prtouch_pres_config_resp");
    command_sendf(encoder, pt->oid, 0, 0, 0);
}

/**
 * PRTOUCH_PRES_START - Start pressure sensing.
 *
 * Args:
 *   [0]: OID
 *   [1]: Mode
 *   [2]: Trigger output high value
 *   [3]: Trigger output low value
 *   [4]: Sample interval (microseconds)
 *   [5]: Unused
 *   [6]: Trigger threshold
 *   [7]: Trigger count
 *   [8]: Trigger delta
 *   [9]: Minimum samples before trigger
 */
void command_start_prtouch_pres(uint32_t *args)
{
    prtouch_v3_t *pt = g_prtouch_v3;

    pt->target_cfg = args[1];
    pt->sample_interval = args[2];
    pt->trigger_out_high = args[3];
    pt->trigger_out_low = args[4];

    // Calculate sample interval
    float interval_us = __aeabi_ui2f(args[5]);
    pt->filter_alpha = *(int32_t *)&interval_us;  // Store as int bits

    pt->trigger_threshold = args[6];
    pt->trigger_count = args[7];
    pt->trigger_delta = args[8];

    uint32_t min_samples = args[9];
    if (min_samples < SAMPLES_PER_CHANNEL) {
        min_samples = SAMPLES_PER_CHANNEL;
    }
    pt->min_samples = min_samples;

    pt->sample_idx = 0;
    pt->last_sample_tick = timer_read_time();

    // Initialize channel data structures
    for (uint32_t ch = 0; ch < pt->num_channels; ch++) {
        prtouch_reset_zip(&pt->channels[ch].tick_zip);
        prtouch_reset_zip(&pt->channels[ch].data_zip);
    }

    // Clear sample buffers
    memset(pt->tick_data, 0, sizeof(pt->tick_data));
    memset(pt->raw_data, 0, sizeof(pt->raw_data));
    memset(pt->filtered_data, 0, sizeof(pt->filtered_data));

    // Initialize with current timestamp
    uint32_t now = timer_read_time();
    for (uint32_t ch = 0; ch < pt->num_channels; ch++) {
        for (int i = 0; i < SAMPLES_PER_CHANNEL; i++) {
            pt->tick_data[ch][i] = now;
        }
    }

    // Enable output
    gpio_out_write(pt->output_gpio, 1);

    void *encoder = ctr_lookup_encoder("prtouch_pres_start_resp");
    command_sendf(encoder, pt->oid, 0, SAMPLES_PER_CHANNEL, 0);
}

/**
 * PRTOUCH_PRES_STOP - Stop pressure sensing.
 *
 * Args:
 *   [0]: OID
 *   [1]: Output value
 */
void command_stop_prtouch_pres(uint32_t *args)
{
    prtouch_v3_t *pt = g_prtouch_v3;

    pt->sample_interval = 0;

    void *encoder = ctr_lookup_encoder("prtouch_pres_stop_resp");
    command_sendf(encoder, pt->oid, 0, 0, 0x47);

    gpio_out_write(pt->output_gpio, (uint8_t)args[1]);
}

/**
 * PRTOUCH_PRES_READ - Read pressure data.
 *
 * Args:
 *   [0]: OID
 *   [1]: Data type (0=filtered, 1=raw)
 *   [2]: Channel
 *   [3]: Start index
 *   [4]: Count
 */
void command_read_prtouch_pres(uint32_t *args)
{
    prtouch_v3_t *pt = g_prtouch_v3;

    if (args[1] > 1) {
        void *encoder = ctr_lookup_encoder("prtouch_pres_data");
        command_sendf(encoder, pt->oid, pt->sample_idx, SAMPLES_PER_CHANNEL,
                      0, 0, 0, 0, 0, 0, 0);
        return;
    }

    uint32_t channel = args[2];
    uint32_t start = args[3];
    uint32_t count = args[4];

    uint32_t end = start + count;
    if (end > SAMPLES_PER_CHANNEL) {
        end = SAMPLES_PER_CHANNEL;
    }

    // Select data source
    int32_t *data_buf = (args[1] == 0) ? pt->filtered_data[channel] : pt->raw_data[channel];
    uint32_t *tick_buf = pt->tick_data[channel];

    // Compress data
    syst_zip_t tick_zip, data_zip;
    prtouch_reset_zip(&tick_zip);
    prtouch_reset_zip(&data_zip);

    uint32_t tick_size = 0, data_size = 0;
    uint32_t actual_count = 0;

    for (uint32_t i = start; i < end; i++) {
        tick_size = prtouch_write_zip(&tick_zip, tick_buf[i]);
        data_size = prtouch_write_zip(&data_zip, data_buf[i]);

        if (tick_size + data_size > 0x29) break;  // Buffer full
        actual_count++;
    }

    void *encoder = ctr_lookup_encoder("prtouch_pres_data");
    uint8_t *tick_data = prtouch_read_zip(&tick_zip);
    uint8_t *pres_data = prtouch_read_zip(&data_zip);

    command_sendf(encoder, pt->oid, pt->sample_idx, SAMPLES_PER_CHANNEL,
                  channel, start, actual_count + 1, tick_size, tick_data,
                  data_size, pres_data);
}

/**
 * Main pressure sensing task.
 * Called from scheduler loop to sample pressure sensors.
 */
void prtouch_pres_task(void)
{
    prtouch_v3_t *pt = g_prtouch_v3;

    if (pt->sample_interval == 0) {
        return;  // Not active
    }

    // Check sample interval
    if (!pt->use_adc) {
        uint32_t now = timer_read_time();
        uint32_t elapsed = now;
        if (pt->last_sample_tick < now) {
            elapsed = now - pt->last_sample_tick;
        }
        if (elapsed < pt->sample_interval) {
            return;
        }
        pt->last_sample_tick = now;
    }

    // Sample each channel
    uint32_t tick = timer_read_time();
    uint8_t trigger_mask = 0;

    for (uint32_t ch = 0; ch < pt->num_channels; ch++) {
        pres_channel_t *channel = &pt->channels[ch];

        if (channel->tick_zip.lst_data == 0) break;  // Not initialized

        uint32_t sample_tick = timer_read_time();
        uint32_t data;

        // Handle configuration mode
        if (!pt->use_adc && channel->current_cfg != pt->target_cfg) {
            if (channel->config_state & 1) {
                data = pres_csx_r_cfg(ch, &channel->current_cfg);
            } else {
                data = pres_csx_w_cfg(ch, pt->target_cfg);
            }
            if (data != ADC_BUSY_FLAG) {
                channel->config_state++;
            }
        } else {
            data = pres_get_datas(ch);
        }

        if (data == ADC_BUSY_FLAG) {
            continue;
        }

        // Check for streaming mode
        if (channel->tick_zip.out_data[0] == pt->sample_idx) {
            // Streaming - compress and send when buffer full
            uint32_t tick_size = prtouch_write_zip(&channel->tick_zip, sample_tick);
            uint32_t data_size = prtouch_write_zip(&channel->data_zip, data);

            if (tick_size + data_size > 0x29) {
                void *encoder = ctr_lookup_encoder("prtouch_pres_stream");
                uint8_t *tick_data = prtouch_read_zip(&channel->tick_zip);
                uint8_t *pres_data = prtouch_read_zip(&channel->data_zip);

                command_sendf(encoder, pt->oid, pt->sample_idx, 0x3F, ch,
                              0, 0, tick_size, tick_data, data_size, pres_data);

                prtouch_reset_zip(&channel->tick_zip);
                prtouch_reset_zip(&channel->data_zip);
            }
        } else {
            // Trigger detection mode
            uint8_t ch_trigger = pres_tri_check(ch, sample_tick, data);
            trigger_mask |= ch_trigger;
        }
    }

    // Check if trigger condition met
    if (pt->trigger_out_low != pt->trigger_out_high && trigger_mask) {
        pt->sample_interval = 0;  // Stop sampling
        gpio_out_write(pt->output_gpio, 0);
    }
}

/* ============================================
 * Notes on PRTouch v3 Algorithm
 * ============================================
 *
 * Pressure Sensor Interface:
 * - Uses HX711-style 24-bit ADC chips
 * - Bit-banged SPI protocol for communication
 * - Supports multiple channels (typically 2 for dual Z)
 * - Optional hardware ADC mode for simpler sensors
 *
 * Data Compression:
 * - Delta encoding reduces data size significantly
 * - Variable-length encoding (1-4 bytes per sample)
 * - Tile header stores size codes (2 bits each)
 * - Efficient for streaming high-sample-rate data
 *
 * Trigger Detection:
 * - Two modes: threshold-based and pattern-based
 * - Threshold mode: N consecutive samples above threshold
 * - Pattern mode: monotonic increasing with gradient check
 * - High-frequency filtering removes noise spikes
 * - IIR low-pass filter smooths readings
 *
 * Sampling Flow:
 * 1. Timer interrupt triggers sample
 * 2. Each channel's ADC is read
 * 3. Data stored in circular buffer
 * 4. Trigger detection runs on new data
 * 5. If triggered, output GPIO goes low
 * 6. Data available for retrieval via command
 */
