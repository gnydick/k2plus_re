# RS-485 Serial Protocol Details

Details on the RS-485 communication protocol used by the K2 Plus filament system.

## Physical Layer

| Parameter    | Value           |
|--------------|-----------------|
| Bus          | RS-485          |
| Baud Rate    | 230400          |
| Port         | /dev/ttyS5      |
| Config Name  | serial485       |

## Packet Format

### Request Packet

```
[ADDR] [LEN] [STATUS] [FUNC] [DATA...]
```

| Field    | Size   | Description                          |
|----------|--------|--------------------------------------|
| ADDR     | 1 byte | Device address                       |
| LEN      | 1 byte | Length of remaining bytes (status + func + data) |
| STATUS   | 1 byte | Status (0x00 for requests)           |
| FUNC     | 1 byte | Function code                        |
| DATA     | N bytes| Command-specific data                |

Note: The `cmd_send_data_with_response` method adds the header (0xF7) and CRC automatically.

### Response Packet

```
[HEAD] [ADDR] [LEN] [STATUS] [FUNC] [DATA...] [CRC]
```

| Field    | Size   | Description                          |
|----------|--------|--------------------------------------|
| HEAD     | 1 byte | Header (0xF7)                        |
| ADDR     | 1 byte | Device address                       |
| LEN      | 1 byte | Length                               |
| STATUS   | 1 byte | Status (0x00 = OK)                   |
| FUNC     | 1 byte | Function code (echoed)               |
| DATA     | N bytes| Response data                        |
| CRC      | 1 byte | CRC-8 checksum                       |

## Device Addresses

### Material Boxes (MB) - DEV_TYPE=1

Filament boxes containing feeder motors. Motor control commands go to these addresses.

| Address | Device           | Tnn Slots         |
|---------|------------------|-------------------|
| 0x01    | Box 1            | T1A, T1B, T1C, T1D|
| 0x02    | Box 2            | T2A, T2B, T2C, T2D|
| 0x03    | Box 3            | T3A, T3B, T3C, T3D|
| 0x04    | Box 4            | T4A, T4B, T4C, T4D|

### Closed-Loop Motors (CLM) - DEV_TYPE=2

Printer XY axis motors for input shaping. **NOT the filament feeder motors.**

| Address | Device                    |
|---------|---------------------------|
| 0x81    | Closed-loop motor 1 (X/Y) |
| 0x82    | Closed-loop motor 2 (X/Y) |
| 0x83    | Closed-loop motor 3 (X/Y) |
| 0x84    | Closed-loop motor 4 (X/Y) |

### Belt Tension Motors (BTM) - DEV_TYPE=3

Belt tensioning system motors.

| Address | Device              |
|---------|---------------------|
| 0x91    | Belt tension motor 1|
| 0x92    | Belt tension motor 2|

### Other Addresses

| Address | Device                                  |
|---------|-----------------------------------------|
| 0x11    | Filament Rack (from filament_rack.addr) |
| 0xFE    | Broadcast - all material boxes          |
| 0xFD    | Broadcast - all closed-loop motors      |
| 0xFC    | Broadcast - all belt tension motors     |
| 0xFF    | General broadcast                       |

### Important Note

The **filament feeder motors** inside each box are controlled by sending motor commands (0x08, 0x10) to the **box addresses (0x01-0x04)**, not to 0x81-0x84. The CLM addresses are for the printer's axis steppers.

## Function Codes

### Device Status

| Code | Name              | Description                     | Verified |
|------|-------------------|---------------------------------|----------|
| 0xA2 | ONLINE_CHECK      | Check if device is online       | ✓        |

### Motor Control

| Code   | Name           | Description                     | Verified |
|--------|----------------|---------------------------------|----------|
| 0xFF08 | MOTOR_ENABLE   | Enable/disable motor            | ✓        |
| 0xFF10 | MOTOR_CONTROL  | Motor control commands          | ✓        |

### Sensor/Status

| Code   | Name              | Description                     | Verified |
|--------|-------------------|---------------------------------|----------|
| 0xFF0A | SENSOR_READ       | Read sensor values              | ✓        |

### Material/Slot Operations (0xFF-prefixed)

These commands use `0xFF` as a prefix byte and include slot parameters.

| Code   | Name              | Description                     | Verified |
|--------|-------------------|---------------------------------|----------|
| 0xFF04 | LOAD_TRIGGER      | Trigger load from slot          | ✓        |
| 0xFF05 | FILAMENT_STATUS   | Check filament presence         | ✓        |
| 0xFF0F | SLOT_STATUS       | Query status of all slots       | ✓        |
| 0xFF11 | FILAMENT_DETECT   | Filament detection/calibration  | ✓        |

## Command Details

### 0xA2 - Online Check

**Request:**
```
[addr] 03 00 A2
```

**Response:**
```
F7 [addr] [len] 00 A2 [dev_type] [mode] [uniid...] [crc]
```

Where:
- dev_type: 1=box, 2=motor, 3=belt
- mode: 0=app, 1=bootloader
- uniid: unique device ID (up to 12 bytes)

**Captured Traces:**
```
# Box 1 online check
TX: 01 03 00 a2
RX: f7 01 11 00 a2 01 00 69 06 30 02 18 53 33 11 52 35 38 32 44

# Box 2 online check
TX: 02 03 00 a2
RX: f7 02 11 00 a2 01 00 a4 55 30 02 18 53 33 10 52 35 38 32 82

# Box 3 online check
TX: 03 03 00 a2
RX: f7 03 11 00 a2 01 00 4b 9b 30 02 18 53 33 10 52 35 38 32 cc
```

### 0x08 - Motor Enable

**Request:**
```
[addr] 04 FF 08 [enable]
```

Where enable: 0x00=disable, 0x01=enable

**Response:**
```
F7 [addr] 04 00 08 [state] [crc]
```

Where state: 0x00=stopped, 0x0F=active

**Captured Traces:**
```
# Enable motor on Box 1
TX: 01 04 ff 08 01
RX: f7 01 04 00 08 00 f0
     │  │  │  │  │  │  └─ CRC
     │  │  │  │  │  └──── state=0x00 (was stopped)
     │  │  │  │  └─────── cmd=0x08
     │  │  │  └────────── status=0x00 (OK)
     │  │  └───────────── len=0x04
     │  └──────────────── addr=0x01
     └─────────────────── header=0xF7

# Disable motor on Box 1 (was active)
TX: 01 04 ff 08 00
RX: f7 01 04 00 08 0f dd
                    └──── state=0x0F (was active, now stopped)

# Enable motor on Box 2
TX: 02 04 ff 08 01
RX: f7 02 04 00 08 00 e3
```

### 0x10 - Motor Control

**Request:**
```
[addr] 06 FF 10 [variant] [subcmd] [param]
```

**Variants:**
- 0x01 = Basic motor control
- 0x02 = Extended motor control with position feedback

**Subcommands (variant 0x02):**

| Subcmd | Param | Purpose              |
|--------|-------|----------------------|
| 0x00   | 0x00  | Initialize/reset     |
| 0x04   | 0x00  | Pre-feed preparation |
| 0x05   | 0x00  | Start feed           |
| 0x06   | 0x00  | Continue feed        |
| 0x07   | 0x00  | Stop/complete        |

**Response:**
```
F7 [addr] [len] 00 10 [status/data...] [crc]
```

**Captured Traces:**
```
# Initialize motor on Box 2 (variant=0x02, subcmd=0x00)
TX: 02 06 ff 10 02 00 00
RX: f7 02 04 00 10 00 0f
     │  │  │  │  │  │  └─ CRC
     │  │  │  │  │  └──── status=0x00
     │  │  │  │  └─────── cmd=0x10
     │  │  │  └────────── status=0x00 (OK)
     │  │  └───────────── len=0x04
     │  └──────────────── addr=0x02
     └─────────────────── header=0xF7

# Pre-feed on Box 2 (variant=0x02, subcmd=0x04)
TX: 02 06 ff 10 02 04 00
RX: f7 02 03 00 10 cd
              └──────── short response, status only

# Start feed on Box 2 (variant=0x02, subcmd=0x05)
TX: 02 06 ff 10 02 05 00
RX: f7 02 0a 00 10 44 8b c4 8b 04 c5
              └──────── extended response with encoder position
```

### 0x0A - Sensor Read

**Request:**
```
[addr] 03 FF 0A
```

**Response:**
```
F7 [addr] [len] 00 0A [sensor_data...] [crc]
```

Sensor data format varies by device.

**Captured Traces:**
```
# Sensor read Box 1
TX: 01 03 ff 0a
RX: f7 01 07 00 0a 19 24 00 00 e7
     │  │  │  │  │  └──────────── sensor data (4 bytes) + CRC
     │  │  │  │  └─────────────── cmd=0x0A
     │  │  │  └────────────────── status=0x00
     │  │  └───────────────────── len=0x07
     │  └──────────────────────── addr=0x01
     └─────────────────────────── header=0xF7

# Sensor read Box 2
TX: 02 03 ff 0a
RX: f7 02 07 00 0a 17 26 00 00 f5

# Sensor read Box 3
TX: 03 03 ff 0a
RX: f7 03 07 00 0a 17 26 00 00 f5

# Sensor read Box 4
TX: 04 03 ff 0a
RX: f7 04 07 00 0a 17 26 00 00 f5
```

## Slot-Based Material Commands

These commands target a specific slot within a box. There is **NO separate "select slot" command**. Instead, the slot is embedded as a parameter in each material operation command.

### How Tnn String is Parsed

The Tnn string (e.g., "T2A") is parsed at the Klipper Python level to extract two values:

```
Tnn String    →    Box Address    +    Slot Index
─────────────────────────────────────────────────
   T1A        →       0x01              0 (A)
   T1B        →       0x01              1 (B)
   T1C        →       0x01              2 (C)
   T1D        →       0x01              3 (D)
   T2A        →       0x02              0 (A)
   T2B        →       0x02              1 (B)
   T3C        →       0x03              2 (C)
   T4D        →       0x04              3 (D)
```

**Parsing logic (observed from traces):**
```
Tnn format: T<box><slot>
  - box  = digit 1-4 → becomes RS-485 address 0x01-0x04
  - slot = letter A-D → becomes slot index 0-3
```

### Slot Encoding

| Slot | Value | Tnn Example |
|------|-------|-------------|
| A    | 0x00  | T1A, T2A... |
| B    | 0x01  | T1B, T2B... |
| C    | 0x02  | T1C, T2C... |
| D    | 0x03  | T1D, T2D... |

### Packet Structure for Slot Commands

All slot-based commands follow this format (TX without header/CRC, RX with):
```
TX: [addr] [len] FF [cmd] [slot] [extra...]
RX: F7 [addr] [len] 00 [cmd] [data...] [crc]
                          ↑
                    slot in data for some responses
```

### 0xFF04 - Load Trigger / Slot Select

Trigger filament load from a specific slot.

**Request:**
```
[addr] 05 FF 04 [slot] [param]
```

**Captured Traces:**
```
# Load trigger Box 2, Slot A (slot=0x00), param=0x01
TX: 02 05 ff 04 00 01
RX: f7 02 03 00 04 a1

# Load trigger Box 2, Slot C (slot=0x02), param=0x00
TX: 02 05 ff 04 02 00
RX: f7 02 03 00 04 a3
```

### 0xFF05 - Filament Status

Check if filament is present.

**Request:**
```
[addr] 03 FF 05
```

**Captured Traces:**
```
# Filament status Box 2
TX: 02 03 ff 05
RX: f7 02 04 00 05 01 1e
     │  │  │  │  │  │  └─ CRC
     │  │  │  │  │  └──── status=0x01 (filament present)
     │  │  │  │  └─────── cmd=0x05
     │  │  │  └────────── status=0x00 (OK)
     │  │  └───────────── len=0x04
     │  └──────────────── addr=0x02
     └─────────────────── header=0xF7

# Filament status when no filament
TX: 02 03 ff 05
RX: f7 02 04 00 05 00 1f
                    └──── status=0x00 (no filament)
```

### 0xFF0F - Slot Status Query

Query status of all slots in a box.

**Request:**
```
[addr] 04 FF 0F [query_type]
```

**Captured Traces:**
```
# Query slot status Box 1
TX: 01 04 ff 0f 01
RX: f7 01 04 00 0f 90 5c

# Query slot status Box 2
TX: 02 04 ff 0f 01
RX: f7 02 04 00 0f 90 4f

# Query slot status Box 3
TX: 03 04 ff 0f 01
RX: f7 03 04 00 0f 90 7a

# Query slot status Box 4
TX: 04 04 ff 0f 01
RX: f7 04 04 00 0f 90 6d
```

### 0xFF11 - Filament Detection/Calibration

Filament detection control for a slot.

**Request:**
```
[addr] 05 FF 11 [mode] [param]
```

**Captured Traces:**
```
# Query detection Box 2 (mode=0x00, param=0x00)
TX: 02 05 ff 11 00 00
RX: f7 02 03 00 11 d2

# Set detection Box 2 (mode=0x01, param=0x01)
TX: 02 05 ff 11 01 01
RX: f7 02 03 00 11 d2
```

## CRC-8 Calculation

Polynomial: 0x07

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

CRC is calculated over: LEN + STATUS + FUNC + DATA

## Using from REPL

### Direct Send

```python
def send_485(data, timeout=0.1):
    result = [None]
    done = threading.Event()
    def _send(eventtime):
        s = printer.lookup_object('serial_485 serial485')
        result[0] = s.cmd_send_data_with_response(bytes(data), timeout, False)
        done.set()
    reactor.register_callback(_send)
    done.wait(timeout=timeout + 1)
    return result[0]

# Examples:
resp = send_485([0x02, 0x03, 0x00, 0xA2])  # Online check box 2
print(resp.hex() if resp else "No response")
```

### Using auto_addr for Proper Format

```python
aa = printer.lookup_object('auto_addr')

# The auto_addr module has proper packet formatting
def check_device(addr):
    result = [None]
    done = threading.Event()
    def _run(e):
        aa.communication_online_check(addr)
        result[0] = "sent"
        done.set()
    reactor.register_callback(_run)
    done.wait(2)
    return result[0]
```

## Debugging Tips

1. **Check klippy.log** for serial traffic when debug is enabled
2. **Use PRINT_ADDR_TABLE** to see known devices
3. **Start with online_check** to verify communication
4. **Monitor responses** - None means timeout/no device
5. **Compare with known-working sequences** from trace captures
