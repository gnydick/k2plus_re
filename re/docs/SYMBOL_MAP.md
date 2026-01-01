# K2 Series Klipper - Symbol Mapping

## Object Files (.o) - Exported Functions

### filament_change.o (chelper)
```
get_flushing_volume     -> Main API entry point
m_max_flush_volume      -> Max volume accessor  
calc_flushing_volume_constprop_0  -> Core calculation (internal)
```

### msgblock_485.o (chelper)
```
msgblock_485_crc8       -> CRC-8 calculation
msgblock_485_check      -> Packet validation
```

### serial_485_queue.o (chelper)
```
serial_485_queue_alloc          -> Create queue instance
serial_485_queue_free           -> Destroy queue
serial_485_queue_exit           -> Signal exit
serial_485_queue_send           -> Send message
serial_485_queue_pull           -> Receive message
serial_485_queue_extract_old    -> Cleanup old messages
serial_485_queue_get_stats      -> Statistics
```

### prtouch_v2.o (MCU firmware)
```
# Configuration
command_config_pres_prtouch     -> Configure pressure sensor
command_config_step_prtouch     -> Configure stepper
swap_cfg / pres_cfg / step_cfg  -> Config handlers

# Operations
command_start_pres_prtouch      -> Start pressure reading
command_start_step_prtouch      -> Start step counting
command_read_pres_prtouch       -> Read pressure data
command_manual_get_pres         -> Manual pressure read
command_manual_get_steps        -> Manual step read
command_deal_avgs_prtouch       -> Average calculation

# Data
command_read_swap_prtouch       -> Read swap status
command_write_swap_prtouch      -> Write swap status
command_add_pres_prtouch        -> Add pressure data point
command_add_step_prtouch        -> Add step data point

# Internal
prtouch_task                    -> Main task loop
prtouch_pres_task               -> Pressure subtask
prtouch_step_task               -> Step subtask
check_pres_tri_prtouch          -> Trigger detection
filter_datas_prtouch            -> Data filtering
deal_steps_prtouch              -> Step processing
deal_dirs_prtouch               -> Direction processing
sigmoid_ary                     -> Sigmoid lookup
```

### prtouch_v3.o (MCU firmware)
```
# Configuration
command_config_prtouch_pres     -> Configure pressure
command_config_prtouch_step     -> Configure stepper
command_config_prtouch_apax     -> Configure APAX

# Start/Stop
command_start_prtouch_pres      -> Start pressure mode
command_start_prtouch_step      -> Start step mode
command_start_prtouch_apax      -> Start APAX mode
command_stop_prtouch_pres       -> Stop pressure
command_stop_prtouch_step       -> Stop step
command_stop_prtouch_apax       -> Stop APAX

# Data
command_read_prtouch_pres       -> Read pressure
command_read_prtouch_step       -> Read step
command_cont_prtouch_step       -> Continue step

# Core
prtouch_task                    -> Main task
prtouch_pres_task               -> Pressure task
prtouch_step_task               -> Step task
prtouch_apax_task               -> APAX task

# Helpers
pres_get_datas                  -> Read ADC
pres_tri_check                  -> Trigger detection
pres_hftr_cal                   -> High-freq filter
prtouch_write_zip               -> Delta compress
prtouch_read_zip                -> Delta decompress
prtouch_reset_zip               -> Reset compressor
prtouch_delay_us                -> Microsecond delay
prtouch_ck_delay                -> Check delay elapsed
prtouch_tick_intv_ms            -> Time interval calc
pres_csx_w_cfg                  -> Write CSX config
pres_csx_r_cfg                  -> Read CSX config
```

### z_align.o (MCU firmware)
```
command_z_align_config          -> Configure Z align
command_z_align_add             -> Add alignment point
command_z_align_force_stop      -> Emergency stop
command_query_z_align           -> Query state
command_query_finetuning        -> Query fine-tune state
z_align_task                    -> Main Z align task
finetuning_task                 -> Fine-tuning subtask
z_align_shutdown                -> Shutdown handler
```

---

## Cython Modules - Python API to C Mapping

### serial_485_wrapper.cpython-39.so

**Python Class**: `Serial_485_Wrapper`
```python
__init__(config)                 # Initialize from Klipper config
cmd_485_send_data(gcmd)          # G-code: send raw data
cmd_send_data_with_response(...) # Send and wait for response
add_send_data(data)              # Queue data for sending
remove_send_data(data)           # Remove from queue
is_exist_in_send_list(data)      # Check queue
register_response(callback)      # Register response handler
handle_callback(response)        # Process response
send_queue_process()             # Process send queue
_connect()                       # Connect serial port
_disconnect()                    # Disconnect
_firmware_restart()              # Restart firmware
_shutdown()                      # Shutdown
```

**Python Class**: `Serialhdl_485`
```python
__init__(...)                    # Initialize handler
connect_uart()                   # Open UART
disconnect()                     # Close UART
raw_send(data)                   # Send without wait
raw_send_wait_ack(data, timeout) # Send and wait
get_response(timeout)            # Get response
register_response(callback)      # Register handler
handle_default(response)         # Default handler
_bg_thread()                     # Background RX thread
_start_session()                 # Start session
stats()                          # Get statistics
```

### box_wrapper.cpython-39.so

**Python Class**: `MultiColorMeterialBoxWrapper`
Primary entry point for AMS-style multi-color material box control.

G-Code Commands (50+):
- `cmd_box_start_print` / `cmd_box_end_print`
- `cmd_box_extrude_material` / `cmd_box_retrude_material`
- `cmd_material_flush` / `cmd_material_change_flush`
- `cmd_cut_material` / `cmd_move_to_cut`
- `cmd_get_rfid` / `cmd_get_remain_len`
- etc.

**Python Class**: `BoxAction`
Core material handling operations.

**Python Class**: `BoxState`
State management for T0-Tn material slots.

### motor_control_wrapper.cpython-39.so

**Python Class**: `Motor_Control`
Closed-loop motor control via RS-485.

Key operations:
- `motor_init`, `motor_x_init`, `motor_y_init`, `motor_z_init`
- `motor_elec_offset_calibrate`, `motor_encoder_calibrate_official`
- `motor_control`, `motor_extruder_control`
- `check_protection_code`, `motor_auto_check_protection`

### prtouch_v1_wrapper.cpython-39.so

**Architecture Note**: v1 has **NO MCU firmware** (.o file). It is purely Python/Cython.

**Python Class**: `PRTouchEndstopWrapper`
Main probe interface implementing Klipper probe protocol.

**Key Methods**:
```python
# Probe Protocol
probe_prepare(hmove)           # Prepare for probing
probe_finish(hmove)            # Finish probing
probe_ready()                  # Check probe readiness
query_endstop(time)            # Query endstop state
multi_probe_begin()            # Begin multi-probe sequence
multi_probe_end()              # End multi-probe sequence

# Homing
home_start(print_time, ...)    # Start homing
home_wait(home_end_time)       # Wait for home complete
run_G28_Z()                    # Run accurate Z homing
run_G29_Z()                    # Run bed mesh probing

# Movement
run_step_prtouch(...)          # Execute stepping probe
run_to_next(x, y, z, speed)    # Move to next position
safe_move_z(z)                 # Safe Z movement
move(pos, speed)               # General movement

# Calibration
cal_tri_data(data)             # Calculate trigger data
get_best_rdy_z(positions)      # Get best ready Z position
env_self_check()               # Environment self-check

# MCU Communication
ck_and_manual_get_pres()       # Check and get pressure manually
ck_and_manual_get_step()       # Check and get steps manually
_handle_result_run_pres_prtouch(params)   # Handle pressure result
_handle_result_run_step_prtouch(params)   # Handle step result
_handle_result_read_pres_prtouch(params)  # Handle pressure read
_handle_pres_debug_prtouch(params)        # Handle pressure debug
_handle_step_debug_prtouch(params)        # Handle step debug

# Configuration
add_stepper(stepper)           # Add stepper to probe
get_steppers()                 # Get registered steppers
get_mcu()                      # Get MCU object
get_mm_per_step()              # Get mm per step
get_step_cnts()                # Get step counts
get_position_endstop()         # Get endstop position

# Temperature
set_hot_temps(temp)            # Set hotend temperature
set_bed_temps(temp)            # Set bed temperature
set_fan_speed(speed)           # Set fan speed
change_hot_min_temp(temp)      # Change minimum hotend temp

# Nozzle Cleaning
clear_nozzle()                 # Full nozzle cleaning
clear_nozzle_quick()           # Quick nozzle cleaning

# Utility
shake_motor()                  # Shake motor (settling)
quick_shake_motor()            # Quick shake
enable_steps()                 # Enable steppers
disable_steps()                # Disable steppers
delay_s(seconds)               # Delay in seconds
print_msg(msg)                 # Print message
print_ary(array)               # Print array
print_res(result)              # Print result
report_run_dis()               # Report run distance
ck_g28ed()                     # Check if G28 completed
ck_and_raise_error(code)       # Check and raise error
```

**MCU Protocol Commands** (sent to MCU):
```
config_pres_prtouch oid=%d use_adc=%d pres_cnt=%d swap_pin=%s sys_time_duty=%u
config_step_prtouch oid=%d step_cnt=%d swap_pin=%s sys_time_duty=%u
add_pres_prtouch oid=%d index=%d clk_pin=%s sda_pin=%s
add_step_prtouch oid=%d index=%d dir_pin=%s step_pin=%s dir_invert=%d step_invert=%d
start_pres_prtouch oid=%c tri_dir=%c acq_ms=%c send_ms=%c need_cnt=%c tri_hftr_cut=%u tri_lftr_k1=%u min_hold=%u max_hold=%u
start_step_prtouch oid=%c dir=%c send_ms=%c step_cnt=%u step_us=%u acc_ctl_cnt=%u low_spd_nul=%c send_step_duty=%c auto_rtn=%c
read_pres_prtouch oid=%c acq_ms=%u cnt=%u
deal_avgs_prtouch oid=%c base_cnt=%c
read_swap_prtouch oid=%c
write_swap_prtouch oid=%c sta=%c
manual_get_pres oid=%c index=%c
manual_get_steps oid=%c index=%c
```

**MCU Response Messages**:
```
result_run_pres_prtouch
result_run_step_prtouch
result_read_pres_prtouch
result_deal_avgs_prtouch oid=%c ch0=%i ch1=%i ch2=%i ch3=%i
result_read_swap_prtouch oid=%c sta=%c
result_manual_get_steps oid=%c index=%c tri_time=%u tick0=%u tick1=%u tick2=%u tick3=%u step0=%u step1=%u step2=%u step3=%u
pres_debug_prtouch
step_debug_prtouch
```

### prtouch_v3_wrapper.cpython-39.so

**Python Class**: `PRTouchEndstopWrapper`
Main probe interface implementing Klipper probe protocol.

**Python Class**: `PrtouchApax`
APAX calibration system.

**Python Class**: `PrtouchPres`
Pressure sensor interface.

**Python Class**: `PrtouchStep`
Stepper-based probing.

---

## C FFI Interface (cffi)

The chelper modules are loaded via cffi. Expected interface:

```python
ffi = cffi.FFI()
ffi.cdef("""
    // filament_change.h
    int get_flushing_volume(uint32_t from_color, uint32_t to_color);
    
    // msgblock_485.h
    uint8_t msgblock_485_crc8(uint8_t *data, int len);
    int msgblock_485_check(char *state, char *buf, size_t len);
    
    // serial_485_queue.h  
    struct serial_485_queue *serial_485_queue_alloc(...);
    void serial_485_queue_free(struct serial_485_queue *sq);
    int serial_485_queue_send(struct serial_485_queue *sq, ...);
    int serial_485_queue_pull(struct serial_485_queue *sq, ...);
""")
```

