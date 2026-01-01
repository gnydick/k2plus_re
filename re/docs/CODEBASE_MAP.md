# K2 Series Klipper Codebase Analysis

## Overview

This document maps the Creality K2 Series Klipper firmware codebase. The source is located at `../K2_Series_Klipper/`. The firmware extends standard Klipper with proprietary modules for multi-material printing, closed-loop motor control, and pressure-based Z probing.

### Related Documents
- **[ALGORITHMS.md](ALGORITHMS.md)** - Reverse engineered algorithm details
- **[SYMBOL_MAP.md](SYMBOL_MAP.md)** - Function symbol mappings
- **[../decompiled/](../decompiled/)** - Ghidra decompiled C code
- **[../reconstructed/](../reconstructed/)** - Reconstructed Python source from Cython binaries

---

## Binary Components (Cython Compiled - No Source Available)

### 1. `serial_485_wrapper.cpython-39.so` (141KB)
**Purpose**: RS-485 serial communication layer

**Classes**:
- `Serial_485_Wrapper` - High-level Klipper interface
- `Serialhdl_485` - Low-level serial handler

**Key Methods**:
| Method | Description |
|--------|-------------|
| `__init__` | Initialize from Klipper config |
| `cmd_485_send_data` | G-code command to send raw data |
| `cmd_send_data_with_response` | Send and wait for response |
| `add_send_data` / `remove_send_data` | Queue management |
| `raw_send` / `raw_send_wait_ack` | Low-level transmit |
| `register_response` / `handle_callback` | Response handling |
| `_bg_thread` | Background receive thread |

---

### 2. `box_wrapper.cpython-39.so` (1.7MB)
**Purpose**: Multi-color Material Box (AMS-style) control

**Classes**:
- `MultiColorMeterialBoxWrapper` - Main Klipper interface
- `BoxAction` - Material handling operations
- `BoxState` - State management for Tn slots
- `BoxSave` - Persistence layer
- `BoxCfg` - Configuration
- `CutSensor` - Filament cut sensor
- `ParseData` - Protocol parsing

**Key Operations**:

| Category | Methods |
|----------|---------|
| **Material Extrusion** | `box_extrude_material`, `box_extrude_material_part`, `extruder_extrude`, `extrusion_all_materials` |
| **Material Retraction** | `box_retrude_material`, `box_retrude_material_filament_err_part` |
| **Flushing** | `material_flush`, `cal_flush_list`, `get_flush_len`, `get_flush_temp` |
| **RFID** | `communication_get_rfid`, `check_rfid_valid`, `generate_auto_get_rfid_func` |
| **Cutting** | `cut_material`, `move_to_cut`, `cut_hall_zero`, `cut_hall_find_zero` |
| **Communication** | `send_data`, `communication_*` methods |
| **State** | `generate_Tn_data`, `generate_Tnn_map`, `update_state_process` |

**G-Code Commands** (cmd_* methods):
- `BOX_SET_CURRENT_BOX_IDLE_MODE`
- `box_start_print` / `box_end_print`
- `box_extrude_material` / `box_retrude_material`
- `cut_material` / `cut_state`
- `material_flush` / `material_change_flush`
- `create_connect` / `get_box_state`
- `get_rfid` / `get_remain_len`
- And many more...

---

### 3. `motor_control_wrapper.cpython-39.so` (852KB)
**Purpose**: Closed-loop motor control via RS-485

**Classes**:
- `Motor_Control` - Main controller

**Key Methods**:

| Category | Methods |
|----------|---------|
| **Initialization** | `motor_init`, `motor_x_init`, `motor_y_init`, `motor_z_init`, `motor_z1_init`, `motor_e_init` |
| **Calibration** | `motor_elec_offset_calibrate`, `motor_encoder_calibrate_official` |
| **Control** | `motor_control`, `motor_extruder_control`, `force_stop` |
| **Protection** | `check_protection_code`, `motor_check_protection_after_home`, `motor_auto_check_protection` |
| **Configuration** | `motor_sys_param`, `motor_flash_param`, `motor_config_params_init` |
| **Stall Detection** | `set_z_stall_mode`, `set_e_stall_mode`, `_button_handler_*` |
| **RS-485** | `motor_read485_addr`, `motor_set485_addr` |

**Protocol Messages Observed**:
- `MOTOR_ENCODER_CALIBRATE_OFFICIAL NUM=1`
- `MOTOR_ELEC_OFFSET_CALIBRATE NUM=1-4`
- `MOTOR_CHECK_PROTECTION_AFTER_HOME DATA=11`
- `MOTOR_CLEAR_ERR_WARN_CODE NUM=0 DATA=5`

---

### 4. `prtouch_v1_wrapper.cpython-39.so` (1.1MB)
**Purpose**: Pressure-based touch probe v1 (Python/Cython only - NO MCU C code)

**Architecture Note**: Unlike v2/v3, prtouch_v1 has NO corresponding `.o` MCU firmware file. It is purely a Python/Cython implementation that communicates with the MCU via existing Klipper infrastructure. The v2/v3 versions add MCU-level C firmware for timer-driven stepping and ADC operations.

**Classes**:
- `PRTouchEndstopWrapper` - Main probe interface implementing Klipper's probe protocol

**Key Methods**:

| Category | Methods |
|----------|---------|
| **Probing** | `probe_prepare`, `probe_finish`, `probe_ready`, `query_endstop` |
| **Homing** | `home_start`, `home_wait`, `run_G28_Z` |
| **Bed Mesh** | `run_G29_Z`, `run_re_g29s`, `bed_mesh_post_proc`, `check_bed_mesh` |
| **Movement** | `move`, `safe_move_z`, `run_to_next`, `run_step_prtouch` |
| **Calibration** | `get_best_rdy_z`, `cal_tri_data`, `env_self_check` |
| **Nozzle** | `clear_nozzle`, `clear_nozzle_quick` |
| **Temperature** | `set_hot_temps`, `set_bed_temps`, `set_fan_speed`, `change_hot_min_temp` |
| **Stepper** | `add_stepper`, `get_steppers`, `enable_steps`, `disable_steps`, `shake_motor` |
| **MCU Comm** | `ck_and_manual_get_pres`, `ck_and_manual_get_step`, `_handle_result_*` |

**MCU Protocol Commands** (sent to prtouch MCU module):
| Command | Description |
|---------|-------------|
| `config_pres_prtouch` | Configure pressure sensor (ADC, pin, duty cycle) |
| `config_step_prtouch` | Configure stepper (step count, swap pin) |
| `add_pres_prtouch` | Add pressure channel (CLK/SDA pins) |
| `add_step_prtouch` | Add stepper (dir/step pins, inversion) |
| `start_pres_prtouch` | Start pressure acquisition with trigger params |
| `start_step_prtouch` | Start stepping with velocity params |
| `read_pres_prtouch` | Read pressure data buffer |
| `deal_avgs_prtouch` | Calculate averages |
| `read_swap_prtouch` | Read swap pin status |
| `write_swap_prtouch` | Write swap pin status |

**Error Codes**:
- `PR_ERR_CODE_SWAP_PIN_DETECTI` - Sync pin test failed
- `PR_ERR_CODE_PRES_READ_DATA_TIMEOUT` - Pressure data timeout
- `PR_ERR_CODE_PRES_NOT_BE_SENSED` - Pressure sensor not detected
- `PR_ERR_CODE_PRES_NOISE_TOO_BIG` - Excessive noise
- `PR_ERR_CODE_PRES_VAL_IS_CONSTANT` - Stuck sensor value

---

### 5. `prtouch_v2_wrapper.cpython-39.so` (1.1MB)
**Purpose**: Pressure-based touch probe v2 (enhanced with MCU firmware)

**Architecture Note**: v2 adds MCU-level firmware (`src/prtouch_v2.o`) for timer-driven stepping with S-curve velocity profiles. The Python wrapper coordinates with this firmware.

Same structure as v1, adds:
- `correct_bed_mesh_data` - Bed mesh correction algorithm
- MCU firmware handles step generation and pressure sampling

---

### 6. `prtouch_v3_wrapper.cpython-39.so` (1.2MB)
**Purpose**: Pressure-based touch probe v3 (latest with multi-channel ADC)

**Architecture Note**: v3 adds MCU-level firmware (`src/prtouch_v3.o`) for multi-channel HX711-style ADC with delta compression. Most sophisticated version with APAX calibration.

**Classes**:
- `PRTouchEndstopWrapper` - Main interface
- `PrtouchApax` - APAX calibration
- `PrtouchPres` - Pressure sensor
- `PrtouchStep` - Stepper-based probing

**New in v3**:

| Method | Purpose |
|--------|---------|
| `cmd_BED_MESH_CALIBRATE` | Full bed mesh with regional calibration |
| `cmd_BED_MESH_PROFILE` | Profile management |
| `probe_outlier_check` | Statistical outlier detection |
| `get_temp_compensate` | Temperature compensation |
| `cmd_AUTO_APAX` | Automatic APAX calibration |

---

### 7. `filament_rack_wrapper.cpython-39.so` (178KB)
**Purpose**: Filament rack management

**Classes**:
- `FilamentRackWrapper` - Main interface
- `RemainMaterial` - Remaining material tracking

**Methods**:
- `beep`, `blow`
- `check_rfid_valid`
- `cmd_filament_rack_flush`
- `get_material_target_temp`, `get_material_target_speed`
- `quickly_wait_heating`

---

### 8. `mymovie.cpython-39.so` (147KB, in mymodule/)
**Purpose**: Move planner/splitter (compiled from move.pyx)

**Classes**:
- `PyMove` - Movement representation with kinematics
- `PyMoveSplitter` - Splits moves for motion planning

**Key Functions**:
- `Py_set_extruder_info` - Configure extruder parameters
- `Py_set_corexykin_info` - Configure CoreXY kinematics
- `Py_zmesh_calc_c` - Z mesh compensation calculation
- `Py_move_queue_add/del/flush_cal` - Move queue operations

---

## Reconstructed Python Source

7 of 8 Cython-compiled modules have been reverse engineered and reconstructed as Python source code. (`serial_485_wrapper.py` was removed due to unreliable implementation logic - use `serial_485_queue_decompiled.c` for the C backend instead.)

### Location: `reconstructed/`

| File | Lines | Classes | Description |
|------|-------|---------|-------------|
| `box_wrapper.py` | 1938 | `MultiColorMeterialBoxWrapper`, `BoxAction`, `BoxState`, `BoxSave`, `BoxCfg`, `CutSensor`, `ParseData` | AMS-style material box control |
| `motor_control_wrapper.py` | 956 | `Motor_Control` | Closed-loop motor control via RS-485 |
| `prtouch_v1_wrapper.py` | 1193 | `PRTouchEndstopWrapper` | Pressure probe v1 (base) |
| `prtouch_v2_wrapper.py` | 1000 | `PRTouchEndstopWrapper` | Pressure probe v2 (+bed mesh correction) |
| `prtouch_v3_wrapper.py` | 720 | `PRTouchEndstopWrapper`, `PrtouchApax`, `PrtouchPres`, `PrtouchStep` | Pressure probe v3 (+APAX, outlier detection) |
| `filament_rack_wrapper.py` | 969 | `FilamentRackWrapper`, `RemainMaterial` | Filament rack with RFID |
| `mymovie.py` | 875 | `PyMove`, `PyMoveSplitter` | Move planner/splitter |

### Reconstruction Notes

- Extracted from Cython 0.29.21 compiled ARM32 binaries
- Method signatures recovered via `strings` analysis
- Implementation logic reconstructed from decompiled C code
- G-code commands fully documented
- RS-485 protocol messages matched to handlers
- **Stub methods filled in** with logic from Ghidra decompilation
- **Provenance headers added** to all files documenting confidence levels:
  - GHIDRA DECOMPILATION (high) - control flow, arithmetic from machine code
  - DATA SECTION EXTRACTION (high) - constants from DAT_* addresses
  - HUMAN INTERPRETATION (lower) - variable names, comments, function names
  - UNCERTAIN - edge cases, original naming

---

## Object Files (Decompiled - See `decompiled/` Directory)

All decompiled files include **provenance headers** documenting the source of different elements (Ghidra decompilation vs human interpretation). Only `.o` object files are decompiled here; Cython `.cpython-39.so` binaries produce unusable output and are represented by the reconstructed Python files in `reconstructed/` instead.

### `klippy/chelper/` (C Helper Modules)

| File | Size | Purpose | Decompiled |
|------|------|---------|------------|
| `filament_change.o` | 23KB | Color flush volume calculation | Yes |
| `msgblock_485.o` | 15KB | RS-485 message framing & CRC-8 | Yes |
| `serial_485_queue.o` | 55KB | Async RS-485 queue with poll reactor | Yes |

### `src/` (MCU Firmware)

| File | Size | Purpose | Decompiled |
|------|------|---------|------------|
| `prtouch_v2.o` | 628KB | PRTouch v2: Timer-driven stepping, S-curve velocity | Yes |
| `prtouch_v3.o` | 325KB | PRTouch v3: Multi-channel ADC, delta compression | Yes |
| `z_align.o` | 164KB | Z-axis alignment with OID management | Yes |

### PRTouch Version Architecture

```
┌─────────────────────────────────────────────────────────────────────────┐
│                          PRTouch Versions                                │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                          │
│  v1 (Python Only)          v2 (Python + MCU)        v3 (Python + MCU)   │
│  ┌──────────────────┐      ┌──────────────────┐     ┌──────────────────┐│
│  │prtouch_v1_wrapper│      │prtouch_v2_wrapper│     │prtouch_v3_wrapper││
│  │   .cpython-39.so │      │   .cpython-39.so │     │   .cpython-39.so ││
│  └────────┬─────────┘      └────────┬─────────┘     └────────┬─────────┘│
│           │                         │                        │          │
│           │                         ▼                        ▼          │
│           │                ┌──────────────────┐     ┌──────────────────┐│
│           │                │  prtouch_v2.o    │     │  prtouch_v3.o    ││
│           │                │  (MCU firmware)  │     │  (MCU firmware)  ││
│           │                │  - S-curve step  │     │  - Multi-ch ADC  ││
│           │                │  - FIFO buffers  │     │  - Delta compress││
│           │                │  - Pressure FIFO │     │  - IIR filtering ││
│           │                └──────────────────┘     └──────────────────┘│
│           │                                                              │
│           ▼                                                              │
│  Uses existing Klipper MCU commands (no custom firmware)                 │
│                                                                          │
└─────────────────────────────────────────────────────────────────────────┘
```

**Key Insight**: `prtouch_v1` uses standard Klipper stepper/endstop infrastructure. v2/v3 add custom MCU firmware for enhanced real-time performance.

---

## RS-485 Protocol (from auto_addr_wrapper.py)

### Packet Format
```
+------+------+------+--------+------+------+-----+
| HEAD | ADDR | LEN  | STATUS | FUNC | DATA | CRC |
+------+------+------+--------+------+------+-----+
| 0xF7 | 1B   | 1B   |   1B   |  1B  | var  | 1B  |
+------+------+------+--------+------+------+-----+
```

### Device Types & Addresses
| Type | Code | Broadcast | Address Range |
|------|------|-----------|---------------|
| Material Box (MB) | 0x01 | 0xFE | 0x01-0x04 |
| Closed-Loop Motor (CLM) | 0x02 | 0xFD | 0x81-0x84 |
| Belt Tension Motor (BTM) | 0x03 | 0xFC | 0x91-0x92 |

### Commands
| Code | Name | Description |
|------|------|-------------|
| 0xA0 | SET_SLAVE_ADDR | Assign address to device |
| 0xA1 | GET_SLAVE_INFO | Query device info (broadcast) |
| 0xA2 | ONLINE_CHECK | Heartbeat/presence check |
| 0xA3 | GET_ADDR_TABLE | Get current address mapping |
| 0x0B | LOADER_TO_APP | Switch from bootloader to app |

### CRC-8 Polynomial
- Polynomial: 0x07
- Calculated over: LEN + STATUS + FUNC + DATA

---

## Python Source Files (Available)

### Key Files with Source

| File | Lines | Purpose |
|------|-------|---------|
| `auto_addr_wrapper.py` | 691 | RS-485 auto-addressing protocol |
| `prtouch.py` | 818 | PRTouch v1 reference implementation |
| `bed_mesh.py` | 59K | Bed mesh calibration (modified) |
| `belt_mdl.py` | 31K | Belt tension modeling |
| `bl24c16f.py` | 13K | I2C EEPROM driver |

### Stub Files (Import from Wrappers)
- `box.py` → `box_wrapper.MultiColorMeterialBoxWrapper`
- `serial_485.py` → `serial_485_wrapper.Serial_485_Wrapper`
- `motor_control.py` → `motor_control_wrapper.Motor_Control`
- `prtouch_v1/v2/v3.py` → respective wrappers
- `filament_rack.py` → `filament_rack_wrapper.FilamentRackWrapper`

---

## Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                        Klipper Host                              │
├─────────────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────────┐  │
│  │ bed_mesh.py │  │ prtouch.py  │  │   auto_addr_wrapper.py  │  │
│  └──────┬──────┘  └──────┬──────┘  └────────────┬────────────┘  │
│         │                │                      │                │
│  ┌──────▼──────┐  ┌──────▼──────┐       ┌──────▼──────┐         │
│  │ prtouch_v3  │  │ box_wrapper │       │serial_485   │         │
│  │  _wrapper   │  │   .so       │       │ _wrapper.so │         │
│  │    .so      │  └──────┬──────┘       └──────┬──────┘         │
│  └──────┬──────┘         │                     │                │
│         │         ┌──────▼──────┐       ┌──────▼──────┐         │
│         │         │motor_control│       │serial_485   │         │
│         │         │ _wrapper.so │       │  _queue.o   │         │
│         │         └──────┬──────┘       └──────┬──────┘         │
├─────────┼────────────────┼─────────────────────┼────────────────┤
│         │     RS-485 Bus │                     │                │
│         ▼                ▼                     ▼                │
│  ┌────────────┐   ┌────────────┐       ┌────────────┐           │
│  │  PRTouch   │   │  Material  │       │ Closed-Loop│           │
│  │  Sensor    │   │    Box     │       │   Motors   │           │
│  │ (HX711)    │   │ (0x01-04)  │       │ (0x81-84)  │           │
│  └────────────┘   └────────────┘       └────────────┘           │
└─────────────────────────────────────────────────────────────────┘
```

---

## Ghidra Project

**Location**: `../ghidra/projects/k2plus_re`

**Imported Files** (14 total):
- 8 Cython .so files (ARM 32-bit LE v7)
- 6 .o object files

**Export Script**: `../ghidra/scripts/ExportDecompiled.java`

---

## Live Tracing Infrastructure (NEW - 2024-12-30)

Runtime method tracing system for capturing live behavior from compiled modules.

### Components

| File | Purpose |
|------|---------|
| `../../tracing/scripts/trace_hooks_streaming.py` | Klipper extra that wraps methods and streams traces over TCP |
| `../../tracing/scripts/trace_capture.py` | Client that captures streaming traces to per-object JSONL files |
| `../../tracing/scripts/flush_data_collector.py` | Automation for systematic tool change data collection |

### Tracing Commands

| Command | Description |
|---------|-------------|
| `TRACE_ALL OBJECT=<name>` | Trace all public methods |
| `TRACE_DEEP OBJECT=<name>` | Trace all methods including `_private` |
| `TRACE_ATTRS OBJECT=<name> ENABLE=1` | Trace attribute access |
| `TRACE_ATTRS OBJECT=<name> ENABLE=1 RECURSIVE=1` | Recursive attribute tracing |
| `TRACE_EVERYTHING` | Trace all discovered objects |

### Deployment

```bash
scp ../../tracing/scripts/trace_hooks_streaming.py root@<printer>:/usr/share/klipper/klippy/extras/trace_hooks.py
# Add [trace_hooks] to printer.cfg, restart Klipper
python3 ../../tracing/scripts/trace_capture.py <printer-ip>
```

### Captured Data (in `../../tracing/captures/`)

- Per-object JSONL files: `box_<timestamp>.jsonl`, `prtouch_v3_<timestamp>.jsonl`
- Event types: `call`, `return`, `error`, `attr_read`
- Full argument and return value capture with hex-encoded bytes

---

## RE Directory Structure

| Directory | Purpose | Confidence |
|-----------|---------|------------|
| `../introspection/` | Pure runtime inspection (method lists, module dumps) | HIGH - facts from `dir()` |
| `../reconstructed/` | Full implementations from Ghidra + trace analysis | Varies by method |
| `../decompiled/` | C code exported from Ghidra | LOW - machine output |
| `../from_printer/` | Original binaries pulled from printer | Source material |

### Key Reconstructed Files

- `../reconstructed/serial_485_wrapper.py` - RS-485 protocol implementation from traces
- `../reconstructed/filament_rack_wrapper.py` - Material speed mappings from traces
- `../reconstructed/prtouch_v3_wrapper.py` - `unzip_data()` decompression algorithm

---

## Discovered from Live Traces

### RS-485 Protocol (verified)
```
Request:  [addr][len][cmd][data...]
Response: [0xF7][addr][len_lo][len_hi][cmd][data...][checksum]
```

### Material Type Codes
| Code | Material | Speed (mm/min) |
|------|----------|----------------|
| `011002` | Standard PLA | 360 |
| `0P1002` | High-speed material | 450 |
| `-1` | Default/unknown | 360 |

### Box Flushing (partial)
- `get_flush_len(None, "T2A")` → 160.83 (first load)
- `get_flush_len("T2A", "T3A")` → 140.0 (color change)
- `calc_flushing_volume` algorithm still under investigation

---

## Next Steps for RE

1. ~~Analyze Ghidra decompiled C code for algorithm details~~ DONE
2. ~~Map C FFI functions in chelper .o files~~ DONE
3. ~~Extract firmware communication protocols from prtouch_v2.o/v3.o~~ PARTIAL
4. **Document flush volume algorithms** - Use TRACE_DEEP + TRACE_ATTRS on box
5. **Complete unzip_data() algorithm** - Need more trace samples
6. **Verify checksum algorithm** - Current implementation doesn't match observed values

---

## Files Location Summary

```
$KLIPPER_SOURCE/
├── klippy/
│   ├── extras/           # Klipper extras modules
│   │   ├── *.py          # Python source (some)
│   │   └── *_wrapper.cpython-39.so  # Compiled modules
│   ├── chelper/          # C helper modules
│   │   ├── *.o           # Compiled objects
│   │   └── *.h           # Headers (some)
│   └── mymodule/
│       └── mymovie.cpython-39.so
└── src/
    ├── prtouch_v2.o      # MCU firmware
    ├── prtouch_v3.o
    └── z_align.o
```
