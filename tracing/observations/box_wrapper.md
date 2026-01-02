# Box Wrapper (MultiColorMeterialBoxWrapper)

Multi-color material box controller for filament switching, flushing, and cutting.

## Module

`extras.box_wrapper` → `MultiColorMeterialBoxWrapper`

## Configuration

```ini
[box]
bus: serial485
filament_sensor: filament_sensor
buffer_empty_len: 30        # Buffer reserve length in mm
Tn_retrude: -10             # Retraction after cut (mm)
Tn_retrude_velocity: 600    # Retraction speed (mm/min)
Tn_extrude_temp: 220        # Extrusion temperature (C)
Tn_extrude: 140             # Extrusion length (mm)
Tn_extrude_velocity: 360    # Extrusion speed (mm/min)
```

## Key Methods

| Method | Arguments | Returns | Duration | Description |
|--------|-----------|---------|----------|-------------|
| `Tn_action` | `"T2A"` | `true` | ~135 sec | Full filament load sequence |
| `material_change_flush` | `prev, next` | `true` | ~23-41 sec | Flush during material change |
| `get_flush_len` | `prev, next` | `float` | <1 sec | Get required flush length (mm) |
| `has_flushing_sign` | - | `false` | <1 ms | Check if flushing required |
| `error_clear` | - | `null` | <3 ms | Clear error state |

### Flush Length Examples

```python
get_flush_len(None, "T2A")   # → 160.83 (first load)
get_flush_len("T2A", "T3A")  # → 140.0  (material change)
get_flush_len(None, "T2B")   # → 81.25
```

## Slot Naming Convention

`T<box><slot>` = Box number (1-4) + Slot letter (A/B/C/D)

| Slot | Box 1 | Box 2 | Box 3 | Box 4 |
|------|-------|-------|-------|-------|
| A | T1A | T2A | T3A | T4A |
| B | T1B | T2B | T3B | T4B |
| C | T1C | T2C | T3C | T4C |
| D | T1D | T2D | T3D | T4D |

4 boxes x 4 slots = 16 total slots

## RS-485 Commands

### FF08 - Motor Enable/Disable
```
TX: [addr] 04 ff 08 [enable]
    enable: 0x00=disable, 0x01=enable
RX: f7 [addr] 04 00 08 [state] [checksum]
    state: 0x0F=active, 0x00=stopped
```

### FF10 - Motor Control (LOAD)
```
TX: [addr] 06 ff 10 [variant] [subcmd] [param]
    variant: 0x01=slot A, 0x02=slot B, 0x03=slot C, 0x04=slot D
    subcmd: 0x00=init, 0x04=pre-feed, 0x05=pulse, 0x06=continuous, 0x07=stop
RX: f7 [addr] [len] 00 10 [data...] [checksum]
```

### FF11 - Filament UNLOAD
```
TX: [addr] 05 ff 11 [variant] [param]
RX: f7 [addr] 03 00 11 [checksum]
```

## Load Sequence (T2B Example)

```
1. Tn_action("T2B") called
2. Motor enable: 0xFF08 01
3. Motor disable: 0xFF08 00
4. Load trigger: 0xFF04 00 01
5. Detection queries: 0xFF11 00 00 (repeated)
6. Detection set: 0xFF11 01 01
7. Load trigger: 0xFF04 00 01
8. Status check: 0xFF0F 01 → 0x90
9. Motor disable: 0xFF08 00
10. Init: 0xFF10 02 00 00 → status 0x0F
11. Pre-feed: 0xFF10 02 04 00
12. Start feed: 0xFF10 02 05 00 (returns encoder)
13. Continue monitoring...
14. Broadcast: 0x00A1 FE FE
15. Continue feed: 0xFF10 02 06 00
16. Stop: 0xFF10 02 07 03
17. Filament status: 0xFF05 → 0x01 (present)
18. Retract trigger: 0xFF04 02 00
19. Final encoder read: 0xFF0E 01
20. material_change_flush() called
```

## State Attributes

From attr_read traces:
- `Tnn_content` - Tool slot contents
- `Tn_map` / `Tnn_map` - Tool mappings
- `Tn_data` / `Tn_inner_data` - Tool data
- `data_parts` / `data_upper_parts` - Data sections
- `tn_save_data_path` - Persistence path

## GCode Macros

```gcode
[gcode_macro BOX_LOAD_MATERIAL_WITH_MATERIAL]
gcode:
  BOX_CHECK_MATERIAL
  BOX_CUT_MATERIAL
  BOX_SAVE_FAN
  BOX_RETRUDE_MATERIAL_WITH_TNN
  BOX_EXTRUDE_MATERIAL
  BOX_EXTRUDER_EXTRUDE
  BOX_MATERIAL_CHANGE_FLUSH
  BOX_RESTORE_FAN
  BOX_MOVE_TO_SAFE_POS

[gcode_macro BOX_QUIT_MATERIAL]
gcode:
  BOX_CHECK_MATERIAL
  BOX_CUT_MATERIAL
  BOX_RETRUDE_MATERIAL_WITH_TNN
  BOX_MOVE_TO_SAFE_POS
```

## Unknown / Future Work

- `calc_flushing_volume` algorithm not captured
- Full flush table structure
- Error recovery sequences
