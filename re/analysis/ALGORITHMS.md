# K2 Series Klipper - Reverse Engineered Algorithms

## 1. Flush Volume Calculation (`filament_change.o`)

### Functions
- `get_flushing_volume()` - Main entry point
- `calc_flushing_volume_constprop_0(uint param_1, uint param_2)` - Core algorithm
- `FUN_00010000()` - RGB to HSV-like color space conversion

### Algorithm Analysis

The flush volume calculation determines how much filament to purge when switching colors.

#### Color Representation
Colors are packed as 24-bit RGB:
```
param_1 = (R1 << 16) | (G1 << 8) | B1  // Source color
param_2 = (R2 << 16) | (G2 << 8) | B2  // Target color
```

#### Step 1: RGB Normalization
```c
R = (color >> 16) & 0xFF / 255.0
G = (color >> 8) & 0xFF / 255.0
B = color & 0xFF / 255.0
```

#### Step 2: Color Space Conversion (FUN_00010000)
Converts to a color space similar to HSV:
```c
max_val = fmax(fmax(R, G), B)
min_val = fmin(fmin(R, G), B)
delta = max_val - min_val

// Hue calculation
if (delta < 0.0001) {
    H = 0
} else if (R == max_val) {
    H = fmod((G - B) / delta, 6.0) * 60.0
} else if (G == max_val) {
    H = ((B - R) / delta + 2.0) * 60.0
} else {
    H = ((R - G) / delta + 4.0) * 60.0
}

// Saturation
S = (max_val < 0.0001) ? 0 : delta / max_val

// Value
V = max_val
```

#### Step 3: Color Difference Calculation
Uses a perceptual color difference model:
```c
// Convert hue to radians and compute in polar coordinates
sincos(H1_rad, &sin1, &cos1)
sincos(H2_rad, &sin2, &cos2)

// Chroma difference in polar space
chroma_diff_x = cos1 * S1 * V1 - cos2 * S2 * V2
chroma_diff_y = sin1 * S1 * V1 - sin2 * S2 * V2
chroma_distance = sqrt(chroma_diff_x^2 + chroma_diff_y^2)
chroma_distance = min(chroma_distance, MAX_CHROMA_DIFF)

// Luminance calculation (weighted RGB)
L1 = R1 * 0.299 + G1 * 0.587 + B1 * 0.114  // Standard luminance
L2 = R2 * 0.299 + G2 * 0.587 + B2 * 0.114
```

#### Step 4: Flush Volume Formula
```c
if (L2 >= L1) {
    // Lighter to darker transition
    lum_factor = (L1 - L2) * K1
    chroma_adj = min(V1 * K2 + V2 * K3, chroma_distance)
} else {
    // Darker to lighter transition (harder, needs more purge)
    lum_factor = pow(L2 - L1, EXPONENT) * K4
}

combined = sqrt(chroma_factor^2 + lum_factor^2 - 2 * chroma * lum * K5)
volume = max(combined, MIN_VOLUME)
volume = min(volume + OFFSET, MAX_VOLUME)
```

### Constants (from DAT_* references)
- `DAT_000103f0`: Max chroma difference
- `DAT_000103f8/00010400/00010408`: Luminance weights (0.299, 0.587, 0.114)
- `DAT_00010438`: Exponent for darker->lighter (~2.0)
- `DAT_00010440/00010450`: Scaling factors
- `DAT_00010428`: Minimum flush volume
- `DAT_00010430`: Maximum flush volume

---

## 2. RS-485 Protocol (`msgblock_485.o`)

### CRC-8 Algorithm
Standard CRC-8-CCITT with polynomial 0x07:
```c
uint8_t msgblock_485_crc8(const uint8_t *data, int length) {
    uint8_t crc = 0;

    for (int i = 0; i < length; i++) {
        crc ^= data[i];

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;  // Polynomial: x^8 + x^2 + x + 1
            } else {
                crc = crc << 1;
            }
        }
    }
    return crc;
}
```

### Packet Format
```
+------+------+------+--------+------+------+-----+
| HEAD | ADDR | LEN  | STATUS | FUNC | DATA | CRC |
+------+------+------+--------+------+------+-----+
| 0xF7 | 1B   | 1B   |   1B   |  1B  | var  | 1B  |
+------+------+------+--------+------+------+-----+
```

### Device Addresses
| Address Range | Device Type |
|---------------|-------------|
| 0x01-0x04 | Material Box slots |
| 0x81-0x84 | Closed-loop stepper motors |
| 0x91-0x92 | Belt tension motors |
| 0xFE/0xFD/0xFC | Broadcast addresses |

### Packet Validation State Machine (`msgblock_485_check`)

```c
typedef enum {
    PARSE_STATE_IDLE = 0,       // Looking for HEAD byte
    PARSE_STATE_IN_PACKET = 1   // Currently parsing a packet
} parse_state_t;

int msgblock_485_check(char *state, char *buf, size_t buf_len) {
    // 1. Check minimum length (6 bytes)
    if (buf_len < MIN_PACKET_SIZE) return 0;  // Need more data

    // 2. Verify HEAD byte is 0xF7
    if (buffer[0] != PACK_HEAD) goto find_next_head;

    // 3. Validate LEN field (must be >= 3)
    uint8_t msg_len = buffer[2];
    if (msg_len < 3) goto find_next_head;

    // 4. Check buffer has enough data
    size_t packet_len = msg_len + 3;  // HEAD + ADDR + LEN + payload
    if (buf_len < packet_len) return 0;  // Need more data

    // 5. Calculate CRC over LEN through DATA
    uint8_t calc_crc = msgblock_485_crc8(&buffer[2], msg_len);
    uint8_t packet_crc = buffer[2 + msg_len];

    // 6. Validate CRC
    if (calc_crc == packet_crc) {
        return packet_len;  // Valid packet
    }

find_next_head:
    // Scan for next 0xF7 header to resynchronize
    uint8_t *next = memchr(buf + 1, PACK_HEAD, buf_len - 1);
    if (next) {
        *state = PARSE_STATE_IDLE;
        return -(next - buf);  // Negative = bytes to discard
    }
    return -buf_len;  // Discard entire buffer
}
```

### Return Value Semantics
| Return Value | Meaning |
|--------------|---------|
| Positive N | Valid packet of N bytes |
| Zero | Need more data |
| Negative N | Discard N bytes, resync |

---

## 3. PRTouch v1 - Python-Only Probe (`prtouch_v1_wrapper.cpython-39.so`)

### Architecture Overview

PRTouch v1 is the base implementation, written entirely in Python/Cython with **no custom MCU firmware**. It uses standard Klipper stepper and endstop infrastructure, sending commands to the MCU's built-in modules rather than custom firmware.

**Key Difference from v2/v3**: No `.o` MCU firmware file exists for v1. The Python wrapper directly manages probing logic.

### MCU Protocol Commands

v1 sends these commands to the MCU (handled by existing prtouch modules):

```python
# Pressure sensor configuration
"config_pres_prtouch oid=%d use_adc=%d pres_cnt=%d swap_pin=%s sys_time_duty=%u"
"add_pres_prtouch oid=%d index=%d clk_pin=%s sda_pin=%s"

# Stepper configuration
"config_step_prtouch oid=%d step_cnt=%d swap_pin=%s sys_time_duty=%u"
"add_step_prtouch oid=%d index=%d dir_pin=%s step_pin=%s dir_invert=%d step_invert=%d"

# Start acquisition
"start_pres_prtouch oid=%c tri_dir=%c acq_ms=%c send_ms=%c need_cnt=%c \
    tri_hftr_cut=%u tri_lftr_k1=%u min_hold=%u max_hold=%u"
"start_step_prtouch oid=%c dir=%c send_ms=%c step_cnt=%u step_us=%u \
    acc_ctl_cnt=%u low_spd_nul=%c send_step_duty=%c auto_rtn=%c"

# Data reading
"read_pres_prtouch oid=%c acq_ms=%u cnt=%u"
"deal_avgs_prtouch oid=%c base_cnt=%c"
"read_swap_prtouch oid=%c"
"write_swap_prtouch oid=%c sta=%c"
```

### MCU Response Handlers

```python
# Registered response handlers
"result_run_pres_prtouch"      # Pressure run complete
"result_run_step_prtouch"      # Step run complete
"result_read_pres_prtouch"     # Pressure data buffer
"result_deal_avgs_prtouch oid=%c ch0=%i ch1=%i ch2=%i ch3=%i"
"result_read_swap_prtouch oid=%c sta=%c"
"result_manual_get_steps oid=%c index=%c tri_time=%u tick0=%u tick1=%u ..."
```

### Configuration Parameters

```python
# Trigger detection parameters
tri_hftr_cut     # High-frequency filter cutoff
tri_lftr_k1      # Low-frequency filter coefficient
tri_min_hold     # Minimum hold time (3000 default)
tri_max_hold     # Maximum hold time (50000 default)
tri_need_cnt     # Required trigger count
tri_acq_ms       # Acquisition interval
tri_send_ms      # Send interval

# Probe speeds
g28_sta0_speed   # Initial G28 speed (2.0 mm/s default)
g28_sta1_speed   # Secondary G28 speed (2.5 mm/s default)
g29_speed        # G29 probing speed (2.0 mm/s default)
g29_rdy_speed    # G29 ready position speed (2.5 mm/s default)
g29_xy_speed     # XY movement speed (150 mm/s default)

# Nozzle cleaning
clr_noz_start_x/y    # Cleaning start position
clr_noz_len_x/y      # Cleaning travel distance
pa_clr_dis_mm        # Purge distance
pa_clr_down_mm       # Z offset for cleaning (-0.1 default)
```

### Probing Algorithm Flow

```python
def run_step_prtouch(self):
    """Main stepping probe routine."""

    # 1. Calculate step parameters
    mm_per_step = self.get_mm_per_step()
    step_cnt = int(run_dis / mm_per_step)
    step_us = int(1e6 / (run_spd / mm_per_step))  # Microseconds per step

    # 2. Send start command to MCU
    self.pres_mcu.send_cmd(
        "start_step_prtouch oid=%c dir=%c send_ms=%c step_cnt=%u "
        "step_us=%u acc_ctl_cnt=%u low_spd_nul=%c send_step_duty=%c auto_rtn=%c",
        self.pres_oid, direction, send_ms, step_cnt, step_us,
        acc_ctl_cnt, low_spd_nul, send_step_duty, auto_rtn
    )

    # 3. Wait for trigger callback
    self.run_step_prtouch_flag = True
    while self.run_step_prtouch_flag:
        self.reactor.pause(self.reactor.monotonic() + 0.001)

    # 4. Calculate trigger position from response
    # result_run_step_prtouch provides tri_time, step counts, etc.
    return trigger_z_position

def _handle_result_run_step_prtouch(self, params):
    """Handle step result from MCU."""
    self.step_tri_time = params['tri_time']
    self.step_tri_index = params['tri_index']
    self.run_step_prtouch_flag = False
```

### Self-Check Sequence

```python
def env_self_check(self):
    """Environment self-check for probe readiness."""

    # Test 1: Read pressure data, check for timeout
    # Test 2: Check if values are constant (stuck sensor)
    # Test 3: Check noise levels
    # Test 4: Verify all channels responding
    # Test 5: Validate swap pin detection

    # Error codes:
    # PR_ERR_CODE_PRES_READ_DATA_TIMEOUT
    # PR_ERR_CODE_PRES_VAL_IS_CONSTANT
    # PR_ERR_CODE_PRES_NOISE_TOO_BIG
    # PR_ERR_CODE_PRES_NOT_BE_SENSED
    # PR_ERR_CODE_SWAP_PIN_DETECTI
```

### G28 Z Homing Flow

```python
def run_G28_Z(self):
    """Accurate Z homing with temperature management."""

    # 1. Wait for nozzle to cool if needed
    if current_temp > hot_max_temp:
        self.gcode.run_script("M106 P0 S255")  # Fan on
        # Wait for cooldown

    # 2. Move to safe position
    self.safe_move_z(tri_z_max)

    # 3. First probe (fast)
    self.run_step_prtouch(speed=g28_sta0_speed)

    # 4. Retract and second probe (slow, accurate)
    self.safe_move_z(current_z + 2.0)
    result = self.run_step_prtouch(speed=g28_sta1_speed)

    # 5. Set Z position
    self.toolhead.set_position([None, None, result + fix_z_offset])
```

---

## 4. PRTouch v2 - Timer-Based Stepping (`prtouch_v2.o`)

### Architecture Overview
PRTouch v2 uses timer-driven stepper control with S-curve velocity profiles for pressure-based bed probing. Unlike v3 which is ADC-focused, v2 manages stepper motion directly.

### Key Data Structures

```c
typedef struct prtouch_v2 {
    // Timer configuration
    timer_t step_timer;              // Step generation timer
    uint32_t step_interval;          // Current step interval (ticks)
    uint32_t add_interval;           // Acceleration increment

    // Motion state
    int32_t remaining_steps;         // Steps remaining in move
    uint8_t step_dir;                // Current direction
    uint8_t step_active;             // Step pulse active

    // S-curve parameters
    uint32_t accel_steps;            // Steps in acceleration phase
    uint32_t cruise_steps;           // Steps at constant velocity
    uint32_t decel_steps;            // Steps in deceleration phase

    // Pressure sensing
    pr_fifo_t pressure_fifo;         // Circular buffer for samples
    int32_t trigger_threshold;       // Pressure delta for trigger
    uint8_t triggered;               // Trigger detected flag

    // Multi-stepper support
    uint8_t stepper_count;           // Number of steppers
    gpio_out_t step_pins[4];         // Step output pins
    gpio_out_t dir_pins[4];          // Direction output pins
} prtouch_v2_t;
```

### S-Curve Velocity Profile

```c
// Phase detection based on remaining steps
if (pv2->remaining_steps > decel_start) {
    // Acceleration phase
    pv2->step_interval -= pv2->add_interval;
    if (pv2->step_interval < min_interval) {
        pv2->step_interval = min_interval;
    }
} else if (pv2->remaining_steps > 0) {
    // Deceleration phase
    pv2->step_interval += pv2->add_interval;
}

// Schedule next step
timer_set(pv2->step_timer, now + pv2->step_interval);
```

### Step Generation Timer Event

```c
uint32_t prtouch_event(prtouch_v2_t *pv2) {
    // Toggle step pulse
    if (pv2->step_active) {
        gpio_out_write(step_pin, 0);  // End pulse
        pv2->step_active = 0;
        return now + STEP_PULSE_WIDTH;
    }

    // Check if motion complete
    if (pv2->remaining_steps <= 0) {
        return TIMER_DISABLED;
    }

    // Generate step pulse
    gpio_out_write(step_pin, 1);
    pv2->step_active = 1;
    pv2->remaining_steps--;

    // Update velocity for S-curve
    update_velocity(pv2);

    return now + pv2->step_interval;
}
```

### Pressure FIFO Buffer

```c
typedef struct pr_fifo {
    int32_t samples[FIFO_SIZE];      // Circular buffer
    uint32_t write_idx;              // Write position
    uint32_t read_idx;               // Read position
    uint32_t count;                  // Sample count
} pr_fifo_t;

void fifo_push(pr_fifo_t *fifo, int32_t sample) {
    fifo->samples[fifo->write_idx] = sample;
    fifo->write_idx = (fifo->write_idx + 1) % FIFO_SIZE;
    fifo->count++;
}

int32_t fifo_average(pr_fifo_t *fifo, int n) {
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        int idx = (fifo->write_idx - 1 - i + FIFO_SIZE) % FIFO_SIZE;
        sum += fifo->samples[idx];
    }
    return sum / n;
}
```

### Direction Calculation (deal_dirs_prtouch)

```c
uint8_t deal_dirs_prtouch(prtouch_v2_t *pv2, int8_t dir) {
    // Handle multi-stepper direction with swap detection
    for (int i = 0; i < pv2->stepper_count; i++) {
        uint8_t actual_dir = dir;

        // Apply direction inversion if configured
        if (pv2->dir_invert[i]) {
            actual_dir = !actual_dir;
        }

        gpio_out_write(pv2->dir_pins[i], actual_dir);
    }

    pv2->step_dir = dir;
    return dir;
}
```

---

## 5. PRTouch v3 - Multi-Channel ADC (`prtouch_v3.o`)

### Architecture Overview
PRTouch v3 focuses on multi-channel pressure sensing using HX711-style 24-bit ADCs with SPI bit-banging. It includes sophisticated trigger detection and delta compression for data transfer.

### Key Data Structures

```c
typedef struct prtouch_v3 {
    // Channel configuration
    pres_channel_t channels[MAX_CHANNELS];
    uint8_t channel_count;
    uint8_t active_channel;

    // Sampling state
    uint32_t sample_tick;            // Current sample timestamp
    uint32_t sample_count;           // Total samples collected
    uint8_t sampling_active;         // Sampling enabled

    // Trigger detection
    int32_t trigger_threshold;       // Delta threshold for trigger
    int32_t baseline;                // Calibrated baseline value
    uint8_t trigger_detected;        // Trigger flag
    uint32_t trigger_tick;           // Timestamp of trigger

    // Data compression
    syst_zip_t compressor;           // Delta compression state

    // Async delay
    syst_dly_t delay_state;          // Async delay state machine
} prtouch_v3_t;

typedef struct pres_channel {
    gpio_out_t clk_pin;              // SPI clock output
    gpio_in_t data_pin;              // SPI data input
    int32_t last_reading;            // Previous ADC reading
    int32_t filtered_value;          // IIR filtered value
    uint8_t gain_config;             // ADC gain (25/32/64 pulses)
} pres_channel_t;
```

### HX711-Style ADC Protocol

The HX711 is a 24-bit ADC commonly used with load cells. Data is read via bit-banging:

```c
int32_t pres_get_datas(prtouch_v3_t *pv3, int channel) {
    pres_channel_t *ch = &pv3->channels[channel];

    // Wait for data ready (DOUT goes low)
    gpio_out_write(ch->clk_pin, 0);
    while (gpio_in_read(ch->data_pin) != 0) {
        // Busy wait with timeout
    }

    // Read 24 bits MSB first
    int32_t data = 0;
    for (int i = 0; i < 24; i++) {
        gpio_out_write(ch->clk_pin, 1);
        delay_us(1);

        data = (data << 1) | gpio_in_read(ch->data_pin);

        gpio_out_write(ch->clk_pin, 0);
        delay_us(1);
    }

    // Additional pulses set gain for next reading
    // 25 pulses = gain 128, channel A
    // 26 pulses = gain 32, channel B
    // 27 pulses = gain 64, channel A
    for (int i = 0; i < ch->gain_config - 24; i++) {
        gpio_out_write(ch->clk_pin, 1);
        delay_us(1);
        gpio_out_write(ch->clk_pin, 0);
        delay_us(1);
    }

    // Sign extend 24-bit to 32-bit
    if (data & 0x800000) {
        data |= 0xFF000000;
    }

    return data;
}
```

### Trigger Detection Algorithm

```c
uint8_t pres_tri_check(prtouch_v3_t *pv3, uint32_t tick, int32_t data) {
    // Shift history buffer
    for (int j = HISTORY_SIZE - 1; j > 0; j--) {
        pv3->pressure_history[j] = pv3->pressure_history[j-1];
        pv3->time_history[j] = pv3->time_history[j-1];
    }
    pv3->pressure_history[0] = data;
    pv3->time_history[0] = tick;
    pv3->sample_count++;

    // Need minimum samples for detection
    if (pv3->sample_count < MIN_SAMPLES) {
        return 0;
    }

    // Apply IIR low-pass filter
    // filtered = alpha * new + (1-alpha) * filtered
    int32_t alpha = pv3->filter_alpha;  // Fixed-point, e.g., 0.1 = 3277
    pv3->filtered_value = (alpha * data + (32768 - alpha) * pv3->filtered_value) >> 15;

    // Apply high-frequency filter
    pres_hftr_cal(pv3);

    // Check pressure delta against threshold
    int32_t delta = pv3->filtered_value - pv3->baseline;

    if (abs(delta) > pv3->trigger_threshold) {
        // Verify trigger stability (multiple consecutive samples)
        int stable_count = 0;
        for (int i = 0; i < VERIFY_SAMPLES; i++) {
            int32_t hist_delta = pv3->pressure_history[i] - pv3->baseline;
            if (abs(hist_delta) > pv3->trigger_threshold) {
                stable_count++;
            }
        }

        if (stable_count >= REQUIRED_STABLE) {
            pv3->trigger_detected = 1;
            pv3->trigger_tick = tick;
            return 1;
        }
    }

    return 0;
}
```

### High-Frequency Filter

```c
void pres_hftr_cal(prtouch_v3_t *pv3) {
    // Calculate rate of change (derivative)
    int32_t sum = 0;
    for (int i = 0; i < FILTER_WINDOW - 1; i++) {
        int32_t delta = pv3->pressure_history[i] - pv3->pressure_history[i+1];
        int32_t dt = pv3->time_history[i] - pv3->time_history[i+1];
        if (dt > 0) {
            sum += (delta * 1000) / dt;  // Normalize by time
        }
    }

    pv3->rate_of_change = sum / (FILTER_WINDOW - 1);

    // Filter out high-frequency noise
    if (abs(pv3->rate_of_change) > HF_THRESHOLD) {
        pv3->hf_noise_detected = 1;
    }
}
```

### Delta Compression (prtouch_write_zip)

Efficient encoding for pressure data transmission:

```c
typedef struct syst_zip {
    uint8_t buffer[ZIP_BUFFER_SIZE];  // Compressed data
    uint8_t type_buffer[TYPE_BUFFER_SIZE];  // Size type bits
    uint32_t data_index;              // Position in data buffer
    uint32_t type_index;              // Position in type buffer
    int32_t last_value;               // Previous value for delta
} syst_zip_t;

// Type encoding: 2 bits per sample
// 00 = 1 byte delta (-128 to 127)
// 01 = 2 byte delta (-32768 to 32767)
// 10 = 3 byte delta
// 11 = 4 byte full value

uint32_t prtouch_write_zip(syst_zip_t *zip, int32_t data) {
    int32_t delta = data - zip->last_value;
    uint8_t type;
    uint8_t size;

    // Determine encoding size
    if (delta >= -128 && delta <= 127) {
        size = 1; type = 0;
    } else if (delta >= -32768 && delta <= 32767) {
        size = 2; type = 1;
    } else if (delta >= -8388608 && delta <= 8388607) {
        size = 3; type = 2;
    } else {
        size = 4; type = 3;
    }

    // Store delta value
    memcpy(&zip->buffer[zip->data_index], &delta, size);
    zip->data_index += size;

    // Store type bits (4 samples per byte)
    uint32_t byte_idx = zip->type_index / 4;
    uint32_t bit_pos = (zip->type_index % 4) * 2;
    zip->type_buffer[byte_idx] |= (type << bit_pos);
    zip->type_index++;

    zip->last_value = data;
    return size;
}
```

### Compression Output Format

```
+----------------+------------------+
| Type Bits      | Delta Values     |
+----------------+------------------+
| N/4 bytes      | Variable length  |
+----------------+------------------+

Type bits: packed 4 per byte, 2 bits each
Delta values: variable 1-4 bytes per sample
```

---

## 6. Serial 485 Queue (`serial_485_queue.o`)

### Architecture Overview
Implements an asynchronous message queue with a background thread for non-blocking RS-485 I/O. Uses Klipper's poll reactor pattern.

### Threading Model

```
+-------------------+              +--------------------+
|   Main Thread     |              | Background Thread  |
+-------------------+              +--------------------+
|                   |   send()     |                    |
| serial_485_send() |------------->| command_event()    |
|                   |   (pipe)     |   write(serial)    |
|                   |              |                    |
| serial_485_pull() |<-------------|  input_event()     |
|    (blocking)     |   (cond)     |   read(serial)     |
+-------------------+              +--------------------+
         |                                  |
         v                                  v
   pthread_cond_wait             pollreactor_run
```

### Key Data Structures

```c
typedef struct serial_485_queue {
    // Poll reactor
    void *poll_reactor;              // Klipper pollreactor handle

    // File descriptors
    int serial_fd;                   // Serial port
    int kick_pipe[2];                // Thread wake-up pipe

    // Input buffer
    uint8_t input_buffer[4096];      // Receive buffer
    size_t input_len;                // Bytes in buffer
    char parse_state;                // Parser state

    // Thread synchronization
    pthread_mutex_t lock;            // Protects queues
    pthread_cond_t cond;             // For blocking pull
    pthread_t thread;                // Background thread

    // Message queues
    message_node_t *send_queue;      // Pending send
    message_node_t *recv_queue;      // Received message
    int waiting;                     // Thread waiting flag

    // Statistics
    size_t bytes_write;
    size_t bytes_read;
    size_t bytes_invalid;
} serial_485_queue_t;
```

### Initialization Sequence

```c
serial_485_queue_t *serial_485_queue_alloc(int serial_fd, int device_type) {
    serial_485_queue_t *sq = calloc(sizeof(*sq), 1);

    // Create inter-thread signaling pipe
    pipe(sq->kick_pipe);

    // Setup poll reactor with 2 FDs + 1 timer
    sq->poll_reactor = pollreactor_alloc(2, 1, sq);

    // Register event handlers
    pollreactor_add_fd(sq->poll_reactor, 0, serial_fd, input_event,
                       device_type == 0x66);  // Write mode
    pollreactor_add_fd(sq->poll_reactor, 1, sq->kick_pipe[0], kick_event, 0);
    pollreactor_add_timer(sq->poll_reactor, 0, command_event);

    // Set non-blocking mode
    fd_set_non_blocking(serial_fd);
    fd_set_non_blocking(sq->kick_pipe[0]);
    fd_set_non_blocking(sq->kick_pipe[1]);

    // Initialize synchronization
    pthread_mutex_init(&sq->lock, NULL);
    pthread_cond_init(&sq->cond, NULL);

    // Start background thread with high priority
    pthread_create(&sq->thread, NULL, background_thread, sq);

    return sq;
}
```

### Send Flow

```c
void serial_485_queue_send(serial_485_queue_t *sq, const void *data, size_t len) {
    pthread_mutex_lock(&sq->lock);

    // Queue message
    message_node_t *msg = alloc_message_node();
    memcpy(msg->data, data, len);
    msg->length = len;
    sq->send_queue = msg;

    pthread_mutex_unlock(&sq->lock);

    // Wake background thread via pipe
    write(sq->kick_pipe[1], "k", 1);
}

// Background thread handler
int command_event(serial_485_queue_t *sq) {
    uint8_t tx_buffer[512];

    pthread_mutex_lock(&sq->lock);

    message_node_t *msg = sq->send_queue;
    if (msg) {
        // Build packet: HEAD + data + CRC
        tx_buffer[0] = 0xF7;
        memcpy(&tx_buffer[1], msg->data, msg->length);

        // CRC over LEN field onward
        uint8_t crc = msgblock_485_crc8(&tx_buffer[2], tx_buffer[2]);
        size_t tx_len = msg->length + 2;
        tx_buffer[tx_len - 1] = crc;

        // Send
        write(sq->serial_fd, tx_buffer, tx_len);
        sq->bytes_write += tx_len;

        free(msg);
        sq->send_queue = NULL;
    }

    pthread_mutex_unlock(&sq->lock);
    return 0;  // One-shot timer
}
```

### Receive Flow

```c
void input_event(serial_485_queue_t *sq) {
    // Read available data
    ssize_t ret = read(sq->serial_fd,
                       sq->input_buffer + sq->input_len,
                       sizeof(sq->input_buffer) - sq->input_len);

    if (ret > 0) {
        sq->input_len += ret;

        // Parse packets
        while (1) {
            int result = msgblock_485_check(&sq->parse_state,
                                            sq->input_buffer,
                                            sq->input_len);
            if (result == 0) break;  // Need more data

            size_t consume;
            if (result < 0) {
                // Discard invalid bytes
                consume = -result;
                sq->bytes_invalid += consume;
            } else {
                // Valid packet
                consume = result;

                pthread_mutex_lock(&sq->lock);
                sq->bytes_read += consume;

                // Copy to receive queue
                message_node_t *msg = alloc_message_node();
                memcpy(msg->data, sq->input_buffer, consume);
                msg->length = consume;
                sq->recv_queue = msg;

                // Signal waiting thread
                if (sq->waiting) {
                    sq->waiting = 0;
                    pthread_cond_signal(&sq->cond);
                }
                pthread_mutex_unlock(&sq->lock);
            }

            // Remove consumed bytes
            sq->input_len -= consume;
            memmove(sq->input_buffer, sq->input_buffer + consume, sq->input_len);
        }
    }
}

// Blocking pull from main thread
void serial_485_queue_pull(serial_485_queue_t *sq, message_node_t *out) {
    pthread_mutex_lock(&sq->lock);

    while (1) {
        if (sq->recv_queue) {
            memcpy(out, sq->recv_queue, sizeof(*out));
            free(sq->recv_queue);
            sq->recv_queue = NULL;
            pthread_mutex_unlock(&sq->lock);
            return;
        }

        if (pollreactor_is_exit(sq->poll_reactor)) {
            out->length = -1;  // Error
            pthread_mutex_unlock(&sq->lock);
            return;
        }

        sq->waiting = 1;
        pthread_cond_wait(&sq->cond, &sq->lock);
    }
}
```

---

## 7. Z-Axis Alignment (`z_align.o`)

### Architecture Overview
Manages dual Z-axis stepper alignment using endstop detection. Uses OID (Object ID) based instance management compatible with Klipper's MCU protocol.

### Key Data Structures

```c
typedef struct z_align {
    // Instance management
    uint8_t oid;                     // Object ID for Klipper

    // Motor configuration
    z_motor_t motors[MAX_Z_MOTORS];  // Up to 2 Z motors
    uint8_t motor_count;             // Number of motors

    // Endstop configuration
    gpio_in_t endstop_pin;           // Endstop input
    uint8_t endstop_invert;          // Invert logic
    uint8_t endstop_pullup;          // Enable pullup

    // State machine
    uint8_t state;                   // Current state
    uint8_t result;                  // Operation result

    // Position tracking
    int32_t position_offset[2];      // Offset per motor
    int32_t target_position;         // Target position

    // Timing
    timer_t move_timer;              // Motion timer
    uint32_t step_interval;          // Step timing

    // Fine-tuning
    uint8_t finetuning_active;       // Fine-tune mode
    int32_t finetuning_steps;        // Steps to fine-tune
} z_align_t;

typedef struct z_motor {
    gpio_out_t step_pin;             // Step output
    gpio_out_t dir_pin;              // Direction output
    uint8_t dir_invert;              // Invert direction
    int32_t position;                // Current position
} z_motor_t;
```

### State Machine

```c
typedef enum {
    STATE_IDLE = 0,
    STATE_ACTIVE = 1,
    STATE_MOVING_OUT = 2,
    STATE_AT_ENDSTOP = 3,
    STATE_COMPLETE = 4,
    STATE_ERROR = 5
} z_align_state_t;

typedef enum {
    RESULT_SUCCESS = 0,
    RESULT_TIMEOUT = 1,
    RESULT_NOT_TRIGGERED = 2,
    RESULT_ALREADY_TRIGGERED = 3
} z_align_result_t;
```

### Alignment Algorithm

```c
void z_align_task(z_align_t *za) {
    switch (za->state) {
        case STATE_IDLE:
            // Waiting for command
            break;

        case STATE_ACTIVE:
            // Check endstop status
            uint8_t triggered = read_endstop(za);

            if (triggered) {
                // Already at endstop, move away first
                za->state = STATE_MOVING_OUT;
                start_move(za, DIRECTION_UP, BACKOFF_STEPS);
            } else {
                // Move toward endstop
                start_move(za, DIRECTION_DOWN, MAX_PROBE_STEPS);
            }
            break;

        case STATE_MOVING_OUT:
            // Wait for move complete
            if (move_complete(za)) {
                // Now move toward endstop
                za->state = STATE_AT_ENDSTOP;
                start_move(za, DIRECTION_DOWN, MAX_PROBE_STEPS);
            }
            break;

        case STATE_AT_ENDSTOP:
            // Check for trigger during move
            if (read_endstop(za)) {
                stop_move(za);
                record_position(za);
                za->state = STATE_COMPLETE;
                za->result = RESULT_SUCCESS;
            } else if (move_complete(za)) {
                za->state = STATE_ERROR;
                za->result = RESULT_NOT_TRIGGERED;
            }
            break;

        case STATE_COMPLETE:
        case STATE_ERROR:
            // Report result
            send_result(za);
            za->state = STATE_IDLE;
            break;
    }
}
```

### Endstop Debouncing

```c
uint8_t read_endstop(z_align_t *za) {
    static uint8_t history = 0;
    static uint8_t stable_count = 0;

    uint8_t current = gpio_in_read(za->endstop_pin);
    if (za->endstop_invert) {
        current = !current;
    }

    // Shift history
    history = (history << 1) | current;

    // Require N consecutive same readings
    if ((history & DEBOUNCE_MASK) == DEBOUNCE_MASK) {
        stable_count++;
        if (stable_count >= DEBOUNCE_COUNT) {
            return 1;  // Triggered
        }
    } else if ((history & DEBOUNCE_MASK) == 0) {
        stable_count = 0;
        return 0;  // Not triggered
    }

    return 0;  // Still debouncing
}
```

### Fine-Tuning Mode

```c
void finetuning_task(z_align_t *za) {
    if (!za->finetuning_active) return;

    // Move specified motor by fine-tune amount
    for (int i = 0; i < za->finetuning_steps; i++) {
        gpio_out_write(za->motors[za->finetuning_motor].step_pin, 1);
        delay_us(STEP_PULSE_WIDTH);
        gpio_out_write(za->motors[za->finetuning_motor].step_pin, 0);
        delay_us(za->step_interval);

        za->motors[za->finetuning_motor].position += za->finetuning_dir;
    }

    za->finetuning_active = 0;
}
```

### OID-Based Instance Management

```c
// Global instance table
static z_align_t *z_align_instances[MAX_OIDS];

void command_z_align_config(uint32_t *args) {
    uint8_t oid = args[0];

    // Allocate or get existing instance
    z_align_t *za = z_align_instances[oid];
    if (!za) {
        za = oid_alloc(oid, command_z_align_config, sizeof(z_align_t));
        z_align_instances[oid] = za;
    }

    // Configure from arguments
    za->oid = oid;
    za->endstop_pin = gpio_in_setup(args[1], args[2]);
    za->endstop_invert = args[3];
    za->step_interval = args[4];
}

void command_z_align_add(uint32_t *args) {
    uint8_t oid = args[0];
    z_align_t *za = z_align_instances[oid];

    // Add motor to instance
    int idx = za->motor_count++;
    za->motors[idx].step_pin = gpio_out_setup(args[1], 0);
    za->motors[idx].dir_pin = gpio_out_setup(args[2], 0);
    za->motors[idx].dir_invert = args[3];
}
```

---

## Files Summary

### C Object Files (MCU Firmware & Helpers)

| File | Functions | Size | Key Algorithm |
|------|-----------|------|---------------|
| `filament_change.o` | 20 | 23KB | Color-based flush volume with perceptual model |
| `msgblock_485.o` | 6 | 15KB | RS-485 CRC-8 & packet state machine |
| `serial_485_queue.o` | 75 | 55KB | Async queue with poll reactor threading |
| `prtouch_v2.o` | 97 | 628KB | Timer-driven stepping with S-curve velocity |
| `prtouch_v3.o` | 75 | 325KB | Multi-channel ADC with delta compression |
| `z_align.o` | 53 | 164KB | Dual Z alignment with OID management |

### Python/Cython Wrappers

| File | Type | MCU Firmware | Key Features |
|------|------|--------------|--------------|
| `prtouch_v1_wrapper.cpython-39.so` | Cython | **None** | Python-only, uses standard Klipper MCU |
| `prtouch_v2_wrapper.cpython-39.so` | Cython | `prtouch_v2.o` | S-curve velocity, FIFO buffers |
| `prtouch_v3_wrapper.cpython-39.so` | Cython | `prtouch_v3.o` | Multi-channel ADC, APAX, compression |

---

## PRTouch Version Evolution

```
v1 (Base)                  v2 (Enhanced)              v3 (Advanced)
─────────────────────────────────────────────────────────────────────
Python/Cython only         + MCU firmware             + MCU firmware

Standard Klipper MCU       Custom timer stepping      Multi-channel ADC
No custom firmware         S-curve velocity           Delta compression
                          Pressure FIFO               IIR filtering
                                                     APAX calibration
                                                     Outlier detection
```

---

## Key Insights

### Communication Architecture
- RS-485 half-duplex with 0xF7 framing
- CRC-8 CCITT (polynomial 0x07)
- Background thread with poll reactor for async I/O
- Mutex/condvar synchronization between threads

### Pressure Sensing
- HX711-style 24-bit ADC with SPI bit-banging (v2/v3)
- IIR low-pass filtering for noise reduction
- Multi-sample trigger verification
- Delta compression for efficient data transfer (1-4 bytes per sample)
- v1 uses standard Klipper stepper/endstop commands

### Motion Control
- Timer-driven step generation (v2/v3 MCU firmware)
- S-curve velocity profiles (accel/cruise/decel phases)
- Multi-stepper synchronization
- Endstop debouncing with history buffer

### Klipper Integration
- OID-based object management
- Command handlers registered at startup
- Timer callbacks for periodic tasks
- GPIO abstraction layer
- v1 relies entirely on existing Klipper infrastructure
