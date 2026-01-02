# Filament Rack

External filament rack and buffer system.

## Module

`extras.filament_rack_wrapper` → `FilamentRackWrapper`

## Configuration

```ini
[filament_rack]
not_pin: !PA5
```

## Architecture

```
┌──────────────────────────────────────────────────────────────────────────┐
│                           FILAMENT RACK                                   │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐  ┌───────────────┐
│  │     Box 1       │  │     Box 2       │  │     Box 3       │  │     Box 4     │
│  │    Addr=0x01    │  │    Addr=0x02    │  │    Addr=0x03    │  │   Addr=0x04   │
│  │ [A] [B] [C] [D] │  │ [A] [B] [C] [D] │  │ [A] [B] [C] [D] │  │ [A][B][C][D]  │
│  └────────┬────────┘  └────────┬────────┘  └────────┬────────┘  └───────┬───────┘
│           └────────────────────┴──────────┬─────────┴───────────────────┘        │
│                                           │                                       │
│                                 RS-485 Bus (/dev/ttyS5)                           │
└───────────────────────────────────────────┼───────────────────────────────────────┘
                                            │
                                            ▼
┌───────────────────────────────────────────────────────────────────────────┐
│                           BUFFER SYSTEM                                    │
│  ┌──────────────┐    ┌──────────────┐    ┌──────────────┐                 │
│  │ Feeder Motor │───▶│   Buffer     │───▶│   Extruder   │                 │
│  │ (RS-485)     │    │ (30mm len)   │    │              │                 │
│  └──────────────┘    └──────────────┘    └──────────────┘                 │
│                             │                                              │
│                      GPIO PA5 (not_pin)                                    │
│                      Buffer state signal                                   │
└───────────────────────────────────────────────────────────────────────────┘
```

## Methods

| Method | Arguments | Returns | Description |
|--------|-----------|---------|-------------|
| `get_material_target_speed` | `type=str` | `int` | Feed speed for material type (mm/min) |
| `get_material_target_temp` | `type` | `float` | Target temperature for material |
| `send_data` | `bytes` | - | Send raw data to rack |
| `enable_get_filament` | - | - | Enable filament dispensing |
| `_button_handler` | - | - | GPIO interrupt handler |

### Material Type Codes

| Code | Description | Speed (mm/min) |
|------|-------------|----------------|
| `011002` | Standard PLA | 360 |
| `0P1002` | High-speed material | 450 |
| `-1` | Default/unknown | 360 |

## State Attributes

```python
filament_rack_data = {
    'vender': '-1',
    'color_value': '07a92ac',
    'material_type': '000018'
}

remain_material = RemainMaterial(
    path=...,
    config=...,
    color=...,
    type=...,
    velocity=...
)
```

## Buffer Feeding Mechanism

1. **Buffer Depletion Detection**
   - GPIO PA5 (`not_pin`) signals when buffer needs refilling
   - Pin is active-low (`!PA5` in config)

2. **Feed Trigger**
   - Klipper internal logic monitors buffer state
   - Triggers feeder motor via RS-485 commands

3. **Observed Behavior**
   - During 500mm extrusion at 5mm/sec: no explicit buffer commands visible at Python level
   - Buffer feeding happens at MCU level or via GPIO interrupts
   - RS-485 polling continues (device info 0x00A2, sensor readings 0xFF0A)

## Sensor Readings (0xFF0A)

16-bit values of unknown purpose (possibly temperature/humidity/calibration):

| Slot | Typical Value |
|------|---------------|
| 1 | 9240-9241 |
| 2 | 9751 |
| 3 | 9495-9751 |
| 4 | 9751 |

Values remain stable during extrusion (~9200-9700 range).

## Related Modules

- [box_wrapper.md](box_wrapper.md) - Material box control
- [serial_485.md](serial_485.md) - RS-485 protocol
