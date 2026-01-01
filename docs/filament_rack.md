# Filament Rack System

Reverse-engineered from Creality K2 Plus Klipper firmware traces.

## Provenance

| Field               | Value                                                                |
|---------------------|----------------------------------------------------------------------|
| **Printer**         | Creality K2 Plus                                                     |
| **Firmware**        | Klipper (Creality fork)                                              |
| **Source**          | Compiled Cython modules (`klippy/extras/*.cpython-39.so`)            |
| **Method**          | Runtime tracing via `trace_hooks_streaming.py` injected into Klipper |
| **Capture Dates**   | 2024-12-30                                                           |
| **Capture Files**   | `captures/filament_rack_*.jsonl`, `captures/serial_485_*.jsonl`      |
| **Primary Modules** | `filament_rack_wrapper.cpython-39.so`, `box_wrapper.cpython-39.so`   |
| **Analysis Tool**   | Claude Code (Anthropic)                                              |

### Operations Captured

- Filament load from box 2, slot B (T2B)
- 500mm extrusion at 5mm/sec with buffer feeding
- Material change flush operations

---

## Overview

The K2 Plus filament rack system consists of:

1. **Filament Rack** - External spool holder with 4 slots per box (up to 4 boxes = 16 slots)
2. **Filament Boxes** - RS-485 controlled units at addresses 1-4, each with 4 slots (A/B/C/D)
3. **Buffer System** - Intermediate filament storage between rack and extruder
4. **Box Controller** - Manages filament routing, cutting, and flushing

## Architecture

```
┌──────────────────────────────────────────────────────────────────────────┐
│                           FILAMENT RACK                                   │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐  ┌───────────────┐
│  │     Box 1       │  │     Box 2       │  │     Box 3       │  │     Box 4     │
│  │    Addr=0x01    │  │    Addr=0x02    │  │    Addr=0x03    │  │   Addr=0x04   │
│  │ [A] [B] [C] [D] │  │ [A] [B] [C] [D] │  │ [A] [B] [C] [D] │  │ [A][B][C][D]  │
│  └────────┬────────┘  └────────┬────────┘  └────────┬────────┘  └───────┬───────┘
│           │                    │                    │                   │        │
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

---

## Configuration

From `/mnt/UDISK/printer_data/config/box.cfg`:

```ini
[serial_485 serial485]
serial: /dev/ttyS5
baud: 230400

[filament_rack]
not_pin: !PA5

[box]
bus: serial485
filament_sensor: filament_sensor
buffer_empty_len: 30        # Buffer reserve length in mm
Tn_retrude: -10             # Retraction after cut (mm)
Tn_retrude_velocity: 600    # Retraction speed (mm/min)
Tn_extrude_temp: 220        # Extrusion temperature (°C)
Tn_extrude: 140             # Extrusion length (mm)
Tn_extrude_velocity: 360    # Extrusion speed (mm/min)
```

---

## Klipper Classes

### FilamentRackWrapper

**Module:** `extras.filament_rack_wrapper`

**Purpose:** High-level interface for filament rack operations.

**Methods Observed:**

| Method                      | Arguments      | Returns  | Description                              |
|-----------------------------|----------------|----------|------------------------------------------|
| `get_material_target_speed` | `type=0P1002`  | `450.0`  | Get feed speed for material type (mm/min)|
| `get_material_target_temp`  | type           | float    | Get target temperature for material      |
| `send_data`                 | bytes          | -        | Send raw data to rack                    |
| `enable_get_filament`       | -              | -        | Enable filament dispensing               |
| `_button_handler`           | -              | -        | GPIO interrupt handler                   |

**Material Type Codes:**
- `011002` - Standard PLA (360 mm/min)
- `0P1002` - Unknown type (450 mm/min)

### MultiColorMeterialBoxWrapper

**Module:** `extras.box_wrapper`

**Purpose:** Manages multi-color box operations including filament switching.

**Key Methods:**

| Method                  | Arguments    | Returns  | Duration  | Description                    |
|-------------------------|--------------|----------|-----------|--------------------------------|
| `Tn_action`             | `"T2B"`      | `true`   | ~135 sec  | Full filament load sequence    |
| `material_change_flush` | `None, T2B`  | `true`   | ~23 sec   | Flush during material change   |
| `get_flush_len`         | `None, T2B`  | `81.25`  | <1 sec    | Get required flush length (mm) |
| `has_flushing_sign`     | -            | `false`  | <1 ms     | Check if flushing required     |
| `error_clear`           | -            | `null`   | <3 ms     | Clear error state              |

**Slot Naming Convention:**
- `T<box><slot>` = Box number + Slot letter (A, B, C, or D)
- The number is the box address (1-4), A/B/C/D are slots within that box
- Each box has 4 slots, so 4 boxes = 16 total slots

Examples:
- `T1A` = Box 1 (address 0x01), Slot A
- `T1B` = Box 1 (address 0x01), Slot B
- `T1C` = Box 1 (address 0x01), Slot C
- `T1D` = Box 1 (address 0x01), Slot D
- `T2A` = Box 2 (address 0x02), Slot A
- `T2B` = Box 2 (address 0x02), Slot B
- ...etc through T4D

---

## RS-485 Protocol

The filament rack communicates via RS-485 serial at 230400 baud.

### Device Addresses

| Address              | Device                                                  |
|----------------------|---------------------------------------------------------|
| 1 (0x01)             | Box 1 (T1A, T1B, T1C, T1D) - Filament feeder motors     |
| 2 (0x02)             | Box 2 (T2A, T2B, T2C, T2D) - Filament feeder motors     |
| 3 (0x03)             | Box 3 (T3A, T3B, T3C, T3D) - Filament feeder motors     |
| 4 (0x04)             | Box 4 (T4A, T4B, T4C, T4D) - Filament feeder motors     |
| 17 (0x11)            | Filament Rack controller                                |
| 129-132 (0x81-0x84)  | Closed-Loop Motors (CLM) - Printer XY axis steppers     |
| 145-146 (0x91-0x92)  | Belt Tension Motors (BTM) - Belt tensioning system      |
| 253 (0xFD)           | Broadcast - all closed-loop motors                      |
| 254 (0xFE)           | Broadcast - all material boxes                          |
| 255 (0xFF)           | General broadcast                                       |

**Important:** The filament feeder motors inside each box are controlled by sending motor commands (0x08, 0x10) to the box addresses (0x01-0x04). The CLM addresses (0x81-0x84) are for the printer's XY axis stepper motors used for input shaping, NOT the filament system.

### Feeder Commands

#### 0xFF08 - Motor Enable/Disable
```
TX: [addr] 04 ff 08 [enable]
    enable: 0x00=disable, 0x01=enable
RX: f7 [addr] 04 00 08 [state] [checksum]
    state: 0x0F=active, 0x00=stopped
```

#### 0xFF0E - Encoder Position Reading
```
TX: [addr] 04 ff 0e 01
RX: f7 [addr] 07 00 0e [pos_bytes...] [checksum]
    pos_bytes: 4-byte encoder position
```

#### 0xFF10 - Motor Control (Basic - Variant 0x01)
```
TX: [addr] 06 ff 10 01 [subcmd] [param]
    subcmd: 0x00=init, 0x04=pre-feed, 0x05=start, 0x06=continue, 0x07=stop
RX: f7 [addr] 03 00 10 [status] [checksum]
```

#### 0xFF10 - Motor Control (Extended - Variant 0x02)
```
TX: [addr] 06 ff 10 02 [subcmd] [param]
RX: f7 [addr] 07 00 10 [pos_bytes...] [checksum]  (for subcmd 0x05)

Subcmd 0x05 returns real-time encoder position during feeding.
```

#### 0xFF11 - Filament Detection/Calibration
```
TX: [addr] 05 ff 11 [mode] [param]
    mode: 0x00=query, 0x01=set
RX: f7 [addr] 03 00 11 [checksum]
```

---

## Buffer Feeding Mechanism

### How It Works

1. **Buffer Depletion Detection**
   - GPIO PA5 (`not_pin`) signals when buffer needs refilling
   - Pin is active-low (`!PA5` in config)

2. **Feed Trigger**
   - Klipper internal logic monitors buffer state
   - Triggers feeder motor via RS-485 commands

3. **Feed Sequence (Extended Motor Control)**
   ```
   1. 0xFF10 02 00 00  → Initialize (returns status 0x0F)
   2. 0xFF10 02 04 00  → Pre-feed preparation
   3. 0xFF10 02 05 00  → Start feed (returns encoder position)
   4. (repeat 0xFF10 02 05 00 to monitor position)
   5. 0xFF10 02 06 00  → Continue feed
   6. 0xFF10 02 07 03  → Stop with completion flag
   ```

4. **Position Feedback**
   - Command `0xFF10 02 05 00` returns 10-byte response with encoder data
   - Example positions observed: `448bc48b04`, `444b516b87`, `43f48fad78`

### Observed Behavior

During 500mm extrusion at 5mm/sec:
- **No explicit buffer commands** visible at Python wrapper level
- Buffer feeding happens at **MCU level** or via GPIO interrupts
- RS-485 polling continues (device info 0x00A2, sensor readings 0xFF0A)
- Sensor values remain stable (~9200-9700 range)

During filament load (T2B):
- Full motor control sequence observed
- Multiple `0xFF10 02 05 00` calls with position feedback
- Total load time: ~135 seconds

---

## Filament Load Sequence

Complete sequence for loading filament from Box 2, Slot B:

```
1. Tn_action("T2B") called
2. Motor enable: 0xFF08 01 → status 0x00 (was off)
3. Motor disable: 0xFF08 00 → status 0x0F (now stopped)
4. Load trigger: 0xFF04 00 01
5. Detection queries: 0xFF11 00 00 (repeated)
6. Detection set: 0xFF11 01 01
7. Load trigger: 0xFF04 00 01
8. Status check all slots: 0xFF0F 01 → 0x90
9. Motor disable: 0xFF08 00
10. Extended init: 0xFF10 02 00 00 → status 0x0F
11. Pre-feed: 0xFF10 02 04 00
12. Start feed: 0xFF10 02 05 00 (with position feedback)
13. Continue monitoring position...
14. Broadcast: 0x00A1 FE FE (addr 254)
15. Continue feed: 0xFF10 02 06 00
16. Stop: 0xFF10 02 07 03
17. Filament status: 0xFF05 → 0x01 (present)
18. Repeat stop/status until 0xFF05 → 0x00 (cleared)
19. Retract trigger: 0xFF04 02 00
20. Status check all slots: 0xFF0F 00
21. Final encoder read: 0xFF0E 01
22. material_change_flush() called
23. get_flush_len() → 81.25mm
24. get_material_target_speed() → 450 mm/min
```

---

## GCode Macros

From `box.cfg`:

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

---

## Sensor Readings (0xFF0A)

The sensor command returns 16-bit values that appear to be:
- **Not** filament position or buffer state
- Possibly temperature, humidity, or calibration reference
- Values remain stable during extrusion (~9200-9700 range)

| Slot | Typical Value |
|------|---------------|
| 1    | 9240-9241     |
| 2    | 9751          |
| 3    | 9495-9751     |
| 4    | 9751          |

---

## Future Work

1. **Decode GPIO PA5 signaling** - Monitor at MCU level to understand buffer trigger
2. **Decode encoder position format** - Convert raw bytes to mm or steps
3. **Understand sensor readings** - Determine purpose of 0xFF0A values
4. **Multi-box support** - Test with multiple filament boxes connected
5. **Error handling** - Capture error conditions and recovery sequences

---

## Related Documentation

- [Serial 485 Protocol](serial_485_protocol.md) - Low-level RS-485 command reference
- [unzip_data Algorithm](unzip_data_algorithm.md) - Compression used in Z-probe data
