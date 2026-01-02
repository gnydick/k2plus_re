# PRTouch (Pressure Touch Probe)

Pressure-based touch probe for bed leveling and Z homing.

## Module

`extras.prtouch_v3_wrapper` → `PRTouchEndstopWrapper`

Also: `prtouch_v1_wrapper`, `prtouch_v2_wrapper` (older versions)

## unzip_data Algorithm

Decompresses pressure sensor data. Two compression types identified:

### Usage
```python
unzip_data(bytes, is_signed) -> [count, [values...]]
```

### Unsigned (Type 0x0a)
```python
unzip_data("060aaba982a7f61e7a098f7001007201dc7101927001", False)
# → [6, [4138173097, 4138794183, 4138888534, 4138983254, 4139077938, 4139172292]]
```

### Signed (Type 0x05)
```python
unzip_data("06051a6842ecd2850af600dea8feccfe", True)
# → [6, [-1293720, -604102, -603856, -603890, -604234, -604542]]
```

**Note:** Full algorithm not yet decoded. Uses delta encoding.

## Probing Methods

| Method | Signature | Description |
|--------|-----------|-------------|
| `probe_prepare` | `(homing_move)` | Setup before probe |
| `home_start` | `(position, steptime, steps, tolerance, triggered=True) -> ReactorCompletion` | Start homing |
| `home_wait` | `(timeout) -> float` | Wait for home, return position |
| `probe_finish` | `(homing_move)` | Cleanup after probe |
| `multi_probe_begin` | `()` | Start multi-point probing |
| `multi_probe_end` | `()` | End multi-point probing |

## Utility Methods

| Method | Signature | Description |
|--------|-----------|-------------|
| `get_z_now_comp` | `() -> float` | Current Z compensation (usually 0.0) |
| `delay_s` | `(seconds)` | Sleep function |
| `print_msg` | `(level, message)` | Debug logging |
| `get_steppers` | `() -> list` | Get MCU_stepper objects |
| `run_script_from_command` | `(gcode)` | Execute GCode |
| `check_reise` | `(bool, check_type, error_info)` | Error checking |
| `disturb_ctl` | `(enable)` | Disturbance control |

## Bed Mesh Calibration Workflow

Uses axis_twist_compensation module internally.

### Method Call Frequency (from traces)

| Method | Count | Purpose |
|--------|-------|---------|
| `unzip_data` | 600 | Decompress pressure sensor data |
| `get_z_now_comp` | 434 | Get current Z compensation value |
| `print_msg` | 228 | Debug logging |
| `delay_s` | 82 | Timing delays |
| `get_steppers` | 36 | Get stepper motor objects |
| `run_script_from_command` | 24 | Execute GCode (e.g., BED_MESH_CLEAR) |
| `probe_prepare/finish` | 12 each | Setup/teardown for probing |
| `home_start/wait` | 12 each | Homing operations |
| `multi_probe_begin/end` | 6 each | Multi-point probe sequences |

### Sequence

1. `BED_MESH_CLEAR` via `run_script_from_command`
2. `multi_probe_begin()` - start calibration
3. Loop: `probe_prepare` → `home_start` → `home_wait` → `probe_finish`
4. `unzip_data` called repeatedly for pressure readings
5. `multi_probe_end()` - complete calibration

## State Attributes

- `on_turb`: False
- `pres_state`: True
- `pres_data`: [0, 0, 0, ...] (20 pressure readings)
