# Serial 485 Protocol

Reverse-engineered from Creality K2 Plus Klipper firmware traces.

## Provenance

| Field              | Value                                                                |
|--------------------|----------------------------------------------------------------------|
| **Printer**        | Creality K2 Plus                                                     |
| **Firmware**       | Klipper (Creality fork)                                              |
| **Source**         | Compiled Cython modules (`klippy/extras/*.cpython-39.so`)            |
| **Method**         | Runtime tracing via `trace_hooks_streaming.py` injected into Klipper |
| **Capture Dates**  | 2024-12-30                                                           |
| **Capture Files**  | `../../tracing/captures/serial_485_serial485_*.jsonl`                |
| **Primary Module** | `serial_485.cpython-39.so` (`Serial_485_Wrapper` class)              |
| **Analysis Tool**  | Claude Code (Anthropic)                                              |

### Trace Method

Traces captured by:
1. Deploying `trace_hooks_streaming.py` to printer via rsync
2. Streaming method calls over TCP port 9876
3. Triggering operations via Moonraker API (`http://k2plus:7125/printer/gcode/script`)
4. Parsing JSONL trace logs for `cmd_send_data_with_response` calls

### Operations Captured

- Idle state polling (addresses 1-4, 129-132)
- Filament load (slot 2) - 2024-12-30
- Filament load with buffer feed (box 2, slot B) - 2024-12-30
- 500mm extrusion at 5mm/sec - 2024-12-30

---

## Overview

The K2 Plus uses RS-485 serial communication to talk to peripheral devices like filament feeders and sensors. The `Serial_485_Wrapper` class handles this communication.

## Protocol Structure

### TX (Command) Format
```
byte[0]   = Device address
byte[1]   = Payload length (including this byte)
byte[2:]  = Command + parameters
```

### RX (Response) Format
```
byte[0]   = 0xF7 (response header)
byte[1]   = Device address (echo)
byte[2]   = Response payload length
byte[3:]  = Response payload
byte[-1]  = Checksum
```

## Device Addresses

### Filament Boxes (1-4)
Each address corresponds to a filament box with 2 slots (A/B).

| Address | Device            |
|---------|-------------------|
| 1       | Box 1 (T1A, T1B)  |
| 2       | Box 2 (T2A, T2B)  |
| 3       | Box 3 (T3A, T3B)  |
| 4       | Box 4 (T4A, T4B)  |

### Secondary Controllers (129-132 / 0x81-0x84)
Secondary devices on the same boxes (possibly filament presence sensors).

| Address      | Device       |
|--------------|--------------|
| 129 (0x81)   | Box 1 Sensor |
| 130 (0x82)   | Box 2 Sensor |
| 131 (0x83)   | Box 3 Sensor |
| 132 (0x84)   | Box 4 Sensor |

## Commands

### Command 0x00A2 - Device Info
**Request:** `[addr] 03 00 a2`

**Response:** 20 bytes
```
f7 [addr] 11 00 a2 [status] [id_lo] [id_hi] [model_info...]
```

**Fields:**
- `status`: 0x01 = OK
- `id_lo/hi`: Device-specific ID
- `model_info`: ASCII model/serial like "S310R582"

**Example:**
```
TX: 01 03 00 a2
RX: f7 01 11 00 a2 01 00 69 06 30 02 18 53 33 11 52 35 38 32 44
                          ^^^^^ id=0x0669
                                   ^^^^^^^^^^^^^^^^^^^ "S311R582"
```

### Command 0xFF0A - Sensor Reading
**Request:** `[addr] 03 ff 0a`

**Response:** 10 bytes
```
f7 [addr] 07 00 0a [value_lo] [value_hi] 00 00 [checksum]
```

**Fields:**
- `value`: 16-bit sensor reading (purpose unknown, ~9241-9751 observed)

**Example:**
```
TX: 01 03 ff 0a
RX: f7 01 07 00 0a 19 24 00 00 e7
                   ^^^^^ value=0x2419=9241
```

### Command 0x0C0B - Status Check (High Addresses)
**Request:** `[addr] 04 00 0c 0b`

**Response:** 14 bytes
```
f7 [addr] 0b 00 0c [status_bytes...] [checksum]
```

All zeros typically indicates no filament/inactive sensor.

**Example:**
```
TX: 81 04 00 0c 0b
RX: f7 81 0b 00 0c 00 00 00 00 00 00 00 00 fb
```

### Command 0x1101 / 0x1102 - Configuration Read (High Addresses)
**Request:** `[addr] 04 00 11 01` or `[addr] 04 00 11 02`

**Response:** 7 bytes
```
f7 [addr] 04 00 11 [param] [checksum]
```

**Example:**
```
TX: 81 04 00 11 01
RX: f7 81 04 00 11 01 1d
```

---

## Filament Load/Unload Commands

Commands observed during filament loading operations (slot 2).

### Command 0xFF05 - Filament Status Check
**Request:** `[addr] 03 ff 05`

**Response:** 6 bytes
```
f7 [addr] 03 00 05 [status] [checksum]
```

**Fields:**
- `status`: 0x01 = filament present/active, 0x00 = inactive

**Example:**
```
TX: 02 03 ff 05
RX: f7 02 03 00 05 01 f5    (filament present)
RX: f7 02 03 00 05 00 f4    (filament cleared)
```

### Command 0xFF08 - Motor Enable/Disable
**Request:** `[addr] 04 ff 08 [enable]`

**Parameters:**
- `enable`: 0x00 = disable motor, 0x01 = enable motor

**Response:** 6 bytes
```
f7 [addr] 03 00 08 [motor_state] [checksum]
```

**Fields:**
- `motor_state`: 0x0F = motor active, 0x00 = motor stopped

**Example:**
```
TX: 02 04 ff 08 01          (enable motor)
RX: f7 02 03 00 08 0f f8    (motor active)

TX: 02 04 ff 08 00          (disable motor)
RX: f7 02 03 00 08 00 ef    (motor stopped)
```

### Command 0xFF0E - Encoder/Position Reading
**Request:** `[addr] 04 ff 0e 01`

**Response:** 8 bytes
```
f7 [addr] 05 00 0e [pos_lo] [pos_hi] [checksum]
```

**Fields:**
- `pos`: 16-bit encoder position (incrementing during feed, ~63685-64965 observed)

**Example:**
```
TX: 02 04 ff 0e 01
RX: f7 02 05 00 0e 85 f8 82   (position=0xF885=63621)
RX: f7 02 05 00 0e 89 fd 8a   (position=0xFD89=64905)
```

### Command 0xFF0F - Motor Status Query
**Request:** `[addr] 04 ff 0f [param]`

**Parameters:**
- `param`: 0x00 or 0x01

**Response:** 6 bytes
```
f7 [addr] 03 00 0f [status] [checksum]
```

**Fields:**
- `status`: 0x90 observed (meaning unknown)

**Example:**
```
TX: 02 04 ff 0f 00
RX: f7 02 03 00 0f 90 8a

TX: 02 04 ff 0f 01
RX: f7 02 03 00 0f 90 8a
```

### Command 0x00A1 - Broadcast (Address 254)
**Request:** `[addr] 05 00 a1 fe fe`

Sent to address 254 (0xFE) - broadcast. No response expected.

**Example:**
```
TX: fe 05 00 a1 fe fe
RX: (no response)
```

### Command 0xFF04 - Filament Load/Unload Trigger
**Request:** `[addr] 05 ff 04 [action] [param]`

**Parameters:**
- `action`: 0x00 = unload trigger, 0x01 = load trigger
- `param`: 0x00 or 0x01 (secondary flag)

**Response:** 6 bytes
```
f7 [addr] 03 00 04 [status] [checksum]
```

**Example:**
```
TX: 02 05 ff 04 00 01       (load command)
RX: f7 02 03 00 04 01 fc

TX: 02 05 ff 04 01 00       (unload command)
RX: f7 02 03 00 04 01 fc
```

### Command 0xFF11 - Filament Detection/Calibration
**Request:** `[addr] 05 ff 11 [mode] [param]`

**Parameters:**
- `mode`: 0x00 = query, 0x01 = set
- `param`: 0x00 or 0x01

**Response:** 6 bytes
```
f7 [addr] 03 00 11 [checksum]
```

**Example:**
```
TX: 02 05 ff 11 00 00       (query mode)
RX: f7 02 03 00 11 ca

TX: 02 05 ff 11 01 01       (set mode)
RX: f7 02 03 00 11 ca
```

### Command 0xFF10 - Motor Control with Parameters
**Request:** `[addr] 06 ff 10 [variant] [subcmd] [param]`

**Variants:**
- `0x01` = Basic motor control (6-byte response)
- `0x02` = Extended motor control (may return position data)

**Subcommands for variant 0x01:**

| Subcmd | Param | Purpose            |
|--------|-------|--------------------|
| 0x00   | 0x00  | Initialize/reset   |
| 0x04   | 0x00  | Pre-feed preparation |
| 0x05   | 0x00  | Start feed         |
| 0x06   | 0x00  | Continue feed      |
| 0x07   | 0x00  | Stop/complete      |

**Subcommands for variant 0x02 (extended):**

| Subcmd | Param | Purpose                    | Response                   |
|--------|-------|----------------------------|----------------------------|
| 0x00   | 0x00  | Initialize                 | Returns 0x0F status        |
| 0x04   | 0x00  | Pre-feed                   | 6-byte ack                 |
| 0x05   | 0x00  | Start feed (with position) | 10-byte with encoder data  |
| 0x06   | 0x00  | Continue feed              | 6-byte ack                 |
| 0x07   | 0x03  | Stop/complete with flag    | 6-byte ack                 |

**Response (variant 0x01):** 6 bytes
```
f7 [addr] 03 00 10 [status] [checksum]
```

**Response (variant 0x02, subcmd 0x05):** 10 bytes with encoder position
```
f7 [addr] 07 00 10 [pos_byte0-3] [checksum]
```

**Example sequence during buffer feed (variant 0x02):**
```
TX: 02 06 ff 10 02 00 00    (init extended)
RX: f7 02 04 00 10 00 0f    (status=0x0F)

TX: 02 06 ff 10 02 04 00    (pre-feed)
RX: f7 02 03 00 10 cd

TX: 02 06 ff 10 02 05 00    (start feed - returns position)
RX: f7 02 07 00 10 44 8b c4 8b 04   (encoder position data)

TX: 02 06 ff 10 02 06 00    (continue)
RX: f7 02 03 00 10 cd

TX: 02 06 ff 10 02 07 03    (stop with flag 0x03)
RX: f7 02 03 00 10 cd
```

**Example sequence during filament load (variant 0x01):**
```
TX: 02 06 ff 10 01 00 00    (init)
RX: f7 02 03 00 10 01 ea

TX: 02 06 ff 10 01 04 00    (pre-feed)
RX: f7 02 03 00 10 01 ea

TX: 02 06 ff 10 01 05 00    (start feed)
RX: f7 02 03 00 10 01 ea

TX: 02 06 ff 10 01 07 00    (complete)
RX: f7 02 03 00 10 01 ea
```

---

## Checksum Calculation

The last byte appears to be a checksum. Algorithm not yet determined (likely XOR or modular sum of payload bytes).

## Timing

Commands use various timeouts:
- Info queries (0x00A2): 0.1 second timeout
- Sensor readings (0xFF0A): 3600 second timeout (1 hour - likely blocking until data)
- Status checks: Default timeout

## API Methods

### `cmd_send_data_with_response(bytes, timeout, flag=False)`
Sends command and waits for response.

### `add_send_data(bytes, timeout, addr_tag, cmd_tag, flag)`
Adds command to send queue.

### `remove_send_data(params)`
Removes command from queue after processing.
