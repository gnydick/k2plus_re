# Trace Capture Analysis - K2 Plus Firmware

## Session: 2025-12-30

### Serial_485_Wrapper Protocol

The RS-485 protocol uses a packet format:
```
Request:  [addr][len][cmd][data...]
Response: [0xF7][addr][len_lo][len_hi][cmd][data...][checksum]
```

**Example Exchange:**
- Request: `0203ff0a` = addr=2, len=3, cmd=0xFF, data=0x0A
- Response: `f70207000a182700004c` = header=0xF7, addr=2, len=7, cmd=0x0A, data..., checksum

**Methods:**
- `cmd_send_data_with_response(bytes, timeout, wait_response=True)` -> bytes
- `add_send_data(bytes, timeout, addr_marker, cmd_marker, wait)` -> None
- `remove_send_data(list)` -> None

### Motor_Control Protocol

**Packet Format:**
```python
data_pack(addr=129, cmd=12, data=[11]) -> bytes("f78104000c0b95")
```
- Header: 0xF7
- Address: 0x81 (129 = motor address)
- Length: 0x04 0x00 (little endian)
- Command: 0x0C
- Data: 0x0B
- Checksum: 0x95

**Methods:**
- `bytes_to_int(bytes)` -> int (e.g., `{'_bytes': '81'}` -> 129)
- `bytes_to_int(bytes, is_data_obj=True)` -> list (e.g., `{'_bytes': '0b'}` -> [11])
- `data_pack(addr, cmd, data)` -> bytes
- `validate_data_params(gcmd)` -> True

### MultiColorMeterialBoxWrapper (Box)

**Material Change Methods:**
- `Tn_action(tool_str)` -> bool
  - Example: `Tn_action("T2A")` takes ~150 seconds, returns True
  - Performs full tool change including flush

- `material_change_flush(prev_tool, next_tool)` -> bool
  - Example: `material_change_flush("T2A", "T3A")` takes ~41 seconds

- `get_flush_len(prev_tool, next_tool)` -> float
  - Example: `get_flush_len(None, "T2A")` -> 160.83
  - Example: `get_flush_len("T2A", "T3A")` -> 140.0
  - Returns flush length in mm

- `has_flushing_sign()` -> bool (always False in idle state)

### FilamentRackWrapper

**Methods:**
- `get_material_target_speed(type=str)` -> int
  - Example: `get_material_target_speed(type="011002")` -> 360
  - Example: `get_material_target_speed(type="-1")` -> 360
  - Returns speed in mm/min

### PRTouchEndstopWrapper (prtouch_v3)

**Pressure Sensor Data Decompression:**
- `unzip_data(bytes, is_signed)` -> [count, [values...]]
  - Unsigned: `unzip_data("060aaba982a7f61e7a098f7001007201dc7101927001", False)`
    -> `[6, [4138173097, 4138794183, 4138888534, 4138983254, 4139077938, 4139172292]]`
  - Signed: `unzip_data("06051a6842ecd2850af600dea8feccfe", True)`
    -> `[6, [-1293720, -604102, -603856, -603890, -604234, -604542]]`

**Probing Methods:**
- `probe_prepare(homing_move)` - Setup before probe
- `home_start(position, steptime, steps, tolerance, triggered=True)` -> ReactorCompletion
- `home_wait(timeout)` -> position (float)
- `probe_finish(homing_move)` - Cleanup after probe
- `multi_probe_begin()` / `multi_probe_end()` - Multi-point probing

**Utility Methods:**
- `get_z_now_comp()` -> float (current Z compensation, usually 0.0)
- `delay_s(seconds)` - Sleep function
- `print_msg(level, message)` - Debug logging
- `get_steppers()` -> list of MCU_stepper objects
- `run_script_from_command(gcode)` - Execute gcode
- `check_reise(bool, check_type, error_info)` - Error checking
- `disturb_ctl(enable)` - Disturbance control

### Axis Twist Compensation

Uses PRTouchEndstopWrapper methods during bed mesh calibration. Captured as separate object due to Klipper's axis_twist_compensation module.

**Top Methods Called:**
| Method | Count | Purpose |
|--------|-------|---------|
| `unzip_data` | 600 | Decompress pressure sensor data |
| `get_z_now_comp` | 434 | Get current Z compensation value |
| `print_msg` | 228 | Debug logging |
| `delay_s` | 82 | Timing delays |
| `get_steppers` | 36 | Get stepper motor objects |
| `run_script_from_command` | 24 | Execute gcode (e.g., BED_MESH_CLEAR) |
| `probe_prepare/finish` | 12 each | Setup/teardown for probing |
| `home_start/wait` | 12 each | Homing operations |
| `multi_probe_begin/end` | 6 each | Multi-point probe sequences |

**Workflow:**
1. `BED_MESH_CLEAR` via `run_script_from_command`
2. `multi_probe_begin()` - start calibration
3. Loop: `probe_prepare` → `home_start` → `home_wait` → `probe_finish`
4. `unzip_data` called repeatedly for pressure readings
5. `multi_probe_end()` - complete calibration

---

### Discovered Constants

**Device Addresses:**

| Type | Range | Description |
|------|-------|-------------|
| Material Boxes (MB) | 0x01-0x04 | Filament feeder boxes (DEV_TYPE=1) |
| Closed-Loop Motors (CLM) | 0x81-0x84 | XY axis motors for input shaping (DEV_TYPE=2) |
| Belt Tension Motors (BTM) | 0x91-0x92 | Belt tensioning system (DEV_TYPE=3) |
| Filament Rack | 0x11 | Filament rack sensor |
| Broadcast (boxes) | 0xFE | All material boxes |
| Broadcast (CLM) | 0xFD | All closed-loop motors |
| Broadcast (BTM) | 0xFC | All belt tension motors |
| General Broadcast | 0xFF | All devices |

**Important:** Filament feeder motors are controlled via box addresses (0x01-0x04), NOT 0x81-0x84.

**Slot Encoding (within boxes):**

| Slot | Value | Tnn Examples |
|------|-------|--------------|
| A | 0x00 | T1A, T2A, T3A, T4A |
| B | 0x01 | T1B, T2B, T3B, T4B |
| C | 0x02 | T1C, T2C, T3C, T4C |
| D | 0x03 | T1D, T2D, T3D, T4D |

**Tnn Parsing:** `T<box><slot>` → box digit becomes address 0x01-0x04, slot letter becomes index 0-3

**Motor Commands:**
- 0x01: reboot
- 0x03: encoder_calibrate_official
- 0x04: elec_offset_calibrate
- 0x05: control
- 0x06: sys_param
- 0x07: flash_param
- 0x08: get
- 0x0B: boot
- 0x0C: protection
- 0x0D: systemid
- 0x0E: read485_addr/set485_addr
- 0x0F: version
- 0x11: stall_mode

### Material Type Codes

From traces:
- "011002" - Standard material (360 mm/min)
- "0P1002" - High-speed material (450 mm/min)
- "-1" - Default/unknown (360 mm/min)

---

## Tracing Methodology

### Tools Used
- `trace_hooks_streaming.py` - Klipper extra for runtime method wrapping
- `trace_capture.py` - TCP client capturing to per-object JSONL files
- Live introspection via `dir()`, `getattr()`, `type()`

### Trace Commands
```gcode
TRACE_ALL OBJECT=box           ; Trace public methods
TRACE_DEEP OBJECT=box          ; Include _private methods
TRACE_ATTRS OBJECT=box ENABLE=1 ; Trace attribute reads
TRACE_ATTRS OBJECT=box ENABLE=1 RECURSIVE=1  ; Recursive attr tracing
```

### Data Format
Each line in JSONL files:
```json
{"type": "call", "id": 123, "object": "box", "method": "get_flush_len", "args": "None, \"T2A\""}
{"type": "return", "id": 123, "result": 160.83333333333334, "duration_ms": 0.5}
{"type": "attr_read", "object": "box", "attr": "flush_table", "value": {...}}
```

---

## Verified Algorithms

### CRC-8 Checksum
Polynomial: 0x07. CRC calculated over: LEN + STATUS + FUNC + DATA

```python
def crc8_cal(data, length):
    crc = 0
    for i in range(length):
        crc ^= data[i]
        for j in range(8):
            if crc & 0x80:
                crc = (crc << 1) ^ 0x07
            else:
                crc <<= 1
            crc &= 0xFF
    return crc
```

---

## Known Limitations

### unzip_data Compression
Two compression types identified:
- Type 0x0a: Unsigned values with delta encoding
- Type 0x05: Signed values with delta encoding
Full algorithm needs more trace samples.

### calc_flushing_volume
Algorithm not yet captured. Requires:
1. `TRACE_DEEP OBJECT=box`
2. `TRACE_ATTRS OBJECT=box ENABLE=1 RECURSIVE=1`
3. Trigger tool changes to capture input→output pairs

---

## Object State Discovered

### BoxState Attributes
From attr_read traces:
- `Tnn_content` - Tool slot contents
- `Tn_map` / `Tnn_map` - Tool mappings
- `Tn_data` / `Tn_inner_data` - Tool data
- `data_parts` / `data_upper_parts` - Data sections
- `tn_save_data_path` - Persistence path

### FilamentRackWrapper Attributes
- `filament_rack_data`: `{'vender': '-1', 'color_value': '07a92ac', 'material_type': '000018'}`
- `remain_material`: RemainMaterial object with `path`, `config`, `color`, `type`, `velocity`

### Motor_Control Attributes
- `is_ready`: True
- `is_homing`: False
- `box_action`: BoxAction object

### PRTouch State
- `on_turb`: False
- `pres_state`: True
- `pres_data`: [0, 0, 0, ...] (20 pressure readings)
