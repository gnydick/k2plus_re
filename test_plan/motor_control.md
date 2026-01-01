# Motor Control Methods

Methods and approaches for controlling filament motors on the K2 Plus.

## Overview

Motor control can be done at multiple levels:

1. **High-level Gcode** - `T2A`, `T2B`, etc. - Full load sequences
2. **Box wrapper methods** - `Tn_action()`, `cmd_ctrl_connection_motor_action`
3. **Low-level RS-485** - Direct serial commands to motor controllers

## Gcode Commands

### Slot Selection Commands

```gcode
T1A  ; Select/load Box 1 Slot A
T1B  ; Select/load Box 1 Slot B
T1C  ; Select/load Box 1 Slot C
T1D  ; Select/load Box 1 Slot D
T2A  ; Select/load Box 2 Slot A
...etc
```

### Motor Control Commands

```gcode
CTRL_CONNECTION_MOTOR_ACTION Tnn=T2A ACTION=<action>
; Where ACTION might be: forward, backward, stop, 1, 0, etc.
; (exact parameters need testing)

BOX_EXTRUDE_MATERIAL
; Extrude material (needs parameters)

BOX_RETRUDE_MATERIAL
; Retract material (needs parameters)

SET_PRE_LOADING Tnn=T2A
; Pre-loading setup

MEASURING_WHEEL
; Measuring wheel control
```

### Status Commands

```gcode
GET_BOX_STATE
GET_BUFFER_STATE
GET_FILAMENT_SENSOR_STATE
GET_REMAIN_LEN
GET_RFID
PRINT_ADDR_TABLE
```

## Using Gcode from REPL

Box methods take `gcmd` parameter, so must be invoked via gcode:

```python
import threading

def run_gcode(cmd):
    """Run gcode command from REPL safely."""
    result = [None]
    done = threading.Event()

    def _run(eventtime):
        try:
            gcode.run_script(cmd)
            result[0] = "OK"
        except Exception as e:
            result[0] = str(e)
        done.set()

    reactor.register_callback(_run)
    done.wait(timeout=10)
    return result[0]

# Examples:
run_gcode("T2A")  # Load slot T2A
run_gcode("GET_BOX_STATE")
run_gcode("CTRL_CONNECTION_MOTOR_ACTION Tnn=T2A ACTION=1")
```

## Direct Method Calls

### Tn_action (Full Load Sequence)

```python
import threading

def load_slot(slot_name, timeout=180):
    """Load filament from slot (e.g., 'T2A')."""
    result = [None]
    done = threading.Event()

    def _load(eventtime):
        b = printer.lookup_object('box')
        result[0] = b.Tn_action(slot_name)
        done.set()

    reactor.register_callback(_load)
    done.wait(timeout=timeout)
    return result[0]

# Usage:
load_slot("T2A")  # Takes ~2 minutes
```

### Filament Rack Methods

```python
fr = printer.lookup_object('filament_rack')

# Enable filament feeding (may need reactor)
def enable_feed():
    result = [None]
    done = threading.Event()
    def _run(e):
        result[0] = fr.enable_get_filament()
        done.set()
    reactor.register_callback(_run)
    done.wait(5)
    return result[0]

enable_feed()
```

## Low-Level RS-485 Motor Commands

### Address Mapping

**Filament feeder motors** are controlled via the box addresses, NOT the CLM addresses:

| Box  | Box Address | Slots              | Notes                           |
|------|-------------|--------------------|---------------------------------|
| 1    | 0x01        | T1A, T1B, T1C, T1D | Feeder motor commands go here   |
| 2    | 0x02        | T2A, T2B, T2C, T2D | Feeder motor commands go here   |
| 3    | 0x03        | T3A, T3B, T3C, T3D | Feeder motor commands go here   |
| 4    | 0x04        | T4A, T4B, T4C, T4D | Feeder motor commands go here   |

**Closed-Loop Motors (CLM)** at 0x81-0x84 are for **printer XY axis motors**, not filament:

| Address | Purpose                              |
|---------|--------------------------------------|
| 0x81    | Printer closed-loop motor 1 (X/Y)    |
| 0x82    | Printer closed-loop motor 2 (X/Y)    |
| 0x83    | Printer closed-loop motor 3 (X/Y)    |
| 0x84    | Printer closed-loop motor 4 (X/Y)    |

### Command Format

```
[addr] [len] [status] [func] [data...]
```

Where:
- `addr` = device address
- `len` = length of following bytes (status + func + data)
- `status` = 0x00 for requests
- `func` = function code
- `data` = command-specific data

### Motor Commands (Unverified)

Based on protocol analysis, these commands *might* work:

```python
# Motor enable (0x08)
[addr, 0x04, 0x00, 0x08, 0x01]  # enable
[addr, 0x04, 0x00, 0x08, 0x00]  # disable

# Motor control (0x10)
[addr, 0x06, 0x00, 0x10, variant, subcmd, param]

# Variants:
#   0x01 = basic control
#   0x02 = extended control with position

# Subcmds (for variant 0x01):
#   0x00 = initialize
#   0x04 = pre-feed
#   0x05 = start feed
#   0x06 = continue feed
#   0x07 = stop

# Sensor read (0x0A)
[addr, 0x03, 0x00, 0x0A]

# Online check (0xA2)
[addr, 0x03, 0x00, 0xA2]
```

### Using auto_addr for Proper Packet Format

```python
aa = printer.lookup_object('auto_addr')

# Check if device is online
def check_online(addr):
    result = [None]
    done = threading.Event()
    def _run(e):
        aa.communication_online_check(addr)
        result[0] = "sent"
        done.set()
    reactor.register_callback(_run)
    done.wait(2)
    return result[0]

check_online(0x02)  # Check Box 2
check_online(0x82)  # Check Box 2's motor controller
```

## Slot Selection in Material Commands

**Important:** Slot selection is NOT a separate command. Instead, the slot is embedded as a parameter (byte 5) in each material operation command.

### Slot Encoding

| Slot Letter | Slot Value | Example Tnn |
|-------------|------------|-------------|
| A           | 0x00       | T1A, T2A    |
| B           | 0x01       | T1B, T2B    |
| C           | 0x02       | T1C, T2C    |
| D           | 0x03       | T1D, T2D    |

### How Tnn Maps to Address + Slot

```
T2A → Box Address 0x02, Slot 0
T2B → Box Address 0x02, Slot 1
T3C → Box Address 0x03, Slot 2
T4D → Box Address 0x04, Slot 3
```

### Material Commands with Slot Parameter

All commands use this format:
```
F7 [addr] [len] 00 [cmd] [slot] [extra...] [crc]
```

| Command | Code | Purpose                    | Example for T2B                      |
|---------|------|----------------------------|--------------------------------------|
| RFID    | 0x20 | Read RFID from slot        | `F7 02 05 00 20 01 00 [crc]`         |
| Length  | 0x21 | Get remaining length       | `F7 02 05 00 21 01 00 [crc]`         |
| Extrude | 0x40 | Start extrusion from slot  | `F7 02 05 00 40 01 00 [crc]`         |
| Retract | 0x50 | Retract filament to slot   | `F7 02 05 00 50 01 00 [crc]`         |
| PreLoad | 0x71 | Enable pre-loading         | `F7 02 06 00 71 01 01 00 [crc]`      |
| Measure | 0x80 | Measuring wheel position   | `F7 02 05 00 80 01 00 [crc]`         |

### Python Example: Extrude from T2B

```python
def extrude_slot(box_addr, slot, timeout=10):
    """Extrude from specific slot."""
    # Packet: F7 [addr] 05 00 40 [slot] 00 [crc]
    data = [0xF7, box_addr, 0x05, 0x00, 0x40, slot, 0x00]
    crc = calc_crc8(data[2:])  # CRC over len, status, cmd, slot, 00
    data.append(crc)
    return send_485(data, timeout)

# Extrude from T2B (Box 2, Slot B=1)
extrude_slot(0x02, 0x01)

# Extrude from T3C (Box 3, Slot C=2)
extrude_slot(0x03, 0x02)
```

## Testing Strategy

### Phase 1: Verify Communication

1. Test online check commands to verify devices respond
2. Test sensor read commands
3. Log responses to understand packet format

```python
# Test online check
resp = rs.online_check(0x02)
print("Box 2:", resp.hex() if resp else "No response")

resp = rs.online_check(0x82)
print("Motor 2:", resp.hex() if resp else "No response")
```

### Phase 2: Test Gcode Commands

1. Test individual gcode commands with logging
2. Monitor klippy.log for command execution
3. Observe physical motor movement

```python
run_gcode("GET_BOX_STATE")
run_gcode("GET_FILAMENT_SENSOR_STATE")
```

### Phase 3: Motor Control

1. Start with short movements
2. Monitor for errors
3. Implement emergency stop capability

```python
# Safe motor test with timeout
run_gcode("CTRL_CONNECTION_MOTOR_ACTION Tnn=T2A ACTION=1")
import time
time.sleep(0.5)
run_gcode("CTRL_CONNECTION_MOTOR_ACTION Tnn=T2A ACTION=0")
```

## Safety Notes

1. **Always have emergency stop ready** - Power button or `M112`
2. **Start with short durations** - Test with 0.5s movements first
3. **Monitor for jams** - Listen for motor stalling sounds
4. **Check temperature** - Ensure hotend is at appropriate temp for material
5. **Clear filament path** - Ensure no obstructions before testing
