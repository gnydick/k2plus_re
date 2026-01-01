# Serial 485 Protocol

Reverse-engineered from Creality K2 Plus Klipper firmware traces.

## Provenance

| Field              | Value                                                                |
|--------------------|----------------------------------------------------------------------|
| **Printer**        | Creality K2 Plus                                                     |
| **Firmware**       | Klipper (Creality fork)                                              |
| **Source**         | Compiled Cython modules (`klippy/extras/*.cpython-39.so`)            |
| **Method**         | Runtime tracing via `trace_hooks_streaming.py` injected into Klipper |
| **Capture Dates**  | 2024-12-30, 2026-01-01                                               |
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
- **T2A complete load/unload cycle** - 2026-01-01 (verified FF10=load, FF11=unload)

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

### Command 0xFF11 - Filament UNLOAD (Retract)
**Request:** `[addr] 05 ff 11 [phase] [param]`

**Purpose:** Triggers filament retraction/unload from the slot. This is a **separate command** from FF10 (load) - direction is NOT controlled by a parameter byte on FF10.

**Parameters:**
- `phase`: 0x01 = unload phase
- `param`: 0x00 = continue unload, 0x01 = complete unload

**Response:** 6 bytes
```
f7 [addr] 03 00 11 [status] [checksum]
```

**Fields:**
- `status`: 0xCA observed (meaning: acknowledged)

**Unload Sequence (verified 2026-01-01):**
```
TX: 02 05 ff 11 01 00       (unload - continue, ~250-620ms)
RX: f7 02 03 00 11 ca

TX: 02 05 ff 11 01 00       (unload - continue, repeats 3-4x)
RX: f7 02 03 00 11 ca

TX: 02 05 ff 11 01 01       (unload - complete, ~12.5 sec)
RX: f7 02 03 00 11 ca
```

**Key Finding:** The unload operation uses FF11 with multiple calls:
1. Several `0100` calls to retract in phases
2. Final `0101` call to complete the retraction (longest duration)

### Command 0xFF10 - Filament LOAD (Feed)
**Request:** `[addr] 06 ff 10 [variant] [subcmd] [param]`

**Purpose:** Controls filament feeding/loading into the slot. This is a **multi-step command** with different subcmds for each phase. Unload uses the separate FF11 command.

**Variants:**
- `0x01` = Basic motor control (6-byte response)
- `0x02` = Extended motor control (may return position data)

**Subcommands for variant 0x01:**

| Subcmd | Param | Purpose            |
|--------|-------|--------------------|
| 0x00   | 0x00  | Initialize/reset   |
| 0x04   | 0x00  | Pre-feed preparation |
| 0x05   | 0x00  | Short calibration pulse (returns encoder data) |
| 0x06   | 0x00  | Start continuous feed |
| 0x07   | 0x03  | Stop motor / complete |

**Motor Timing Control (TO BE VERIFIED):**

Based on T2A load trace analysis (2026-01-01):

| Subcmd | Behavior | Duration Control |
|--------|----------|------------------|
| 0x05   | **Self-limiting pulse** - short stutter movement, returns encoder position | Built-in, ~24-135ms observed |
| 0x06   | **Starts continuous feed** - motor runs until explicitly stopped | None - runs indefinitely |
| 0x07   | **Stop command** - halts motor | Immediate stop |

The load sequence uses 5x subcmd 0x05 calls (audible as short stutter steps) for calibration/engagement,
then subcmd 0x06 to start the long continuous feed, and finally subcmd 0x07 to stop.

**Hypothesis:** To run motor for controlled duration:
```
TX: 02 06 ff 10 01 06 00    (start continuous feed)
... wait desired time ...
TX: 02 06 ff 10 01 07 03    (stop motor)
```

Previous attempts that ran without stopping likely omitted the 0x07 stop command.

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

---

## Verified Command Sequences

### T2A Load/Unload Cycle (2026-01-01)

Complete sequence captured from T2A (Box 2, Slot A) load followed by unload.

**Source:** `tracing/captures/captures/serial_485_serial485_20260101_105436.jsonl`

#### Phase 1: Initialization (all slots)
```
TX: 01 04 ff 08 01    (slot 1: motor enable check)
TX: 01 04 ff 08 00    (slot 1: motor disable)
TX: 02 04 ff 08 01    (slot 2: motor enable check)
TX: 02 04 ff 08 00    (slot 2: motor disable)
TX: 03 04 ff 08 01    (slot 3: motor enable check)
TX: 03 04 ff 08 00    (slot 3: motor disable)
TX: 04 04 ff 08 01    (slot 4: motor enable check)
TX: 04 04 ff 08 00    (slot 4: motor disable)
```

#### Phase 2: Slot Selection
```
TX: 02 05 ff 04 00 01    (select slot 2 for operation)
RX: f7 02 03 00 04 a1
```

#### Phase 3: Motor Status Query (all slots)
```
TX: 01 04 ff 0f 01    (slot 1 motor status)
TX: 02 04 ff 0f 01    (slot 2 motor status)
TX: 03 04 ff 0f 01    (slot 3 motor status)
TX: 04 04 ff 0f 01    (slot 4 motor status)
```

#### Phase 4: LOAD via FF10 (~35 seconds)
```
TX: 02 06 ff 10 01 00 00    (init, ~4.5 sec)
RX: f7 02 04 00 10 00 0f

TX: 02 06 ff 10 01 04 00    (pre-feed)
RX: f7 02 03 00 10 cd

TX: 02 06 ff 10 01 05 00    (start feed - repeats ~5x with encoder data)
RX: f7 02 07 00 10 c4 12 ce 55 30    (encoder position)

TX: 02 06 ff 10 01 06 00    (continue feed)
RX: f7 02 03 00 10 cd

TX: 02 06 ff 10 01 07 03    (complete with flag 0x03)
RX: f7 02 03 00 10 cd
```

#### Phase 5: Load Finalization
```
TX: 02 03 ff 05             (filament status check)
RX: f7 02 04 00 05 00 19    (status=0x19)

TX: 02 05 ff 04 01 00       (confirm load complete)
RX: f7 02 03 00 04 a1

TX: 01-04 04 ff 0f 00       (motor status query all slots)

TX: 02 04 ff 0e 01          (encoder/position read)
RX: f7 02 07 00 0e c4 ...   (position data)
```

#### Phase 6: UNLOAD via FF11 (~22 seconds)
```
TX: 02 05 ff 04 00 01       (select slot 2)
RX: f7 02 03 00 04 a1

TX: 02 04 ff 08 00          (motor enable)
RX: f7 02 04 00 08 01 f7

TX: 02 05 ff 11 01 00       (unload phase 1, ~618ms)
RX: f7 02 03 00 11 ca

TX: 02 05 ff 11 01 00       (unload phase 2, ~465ms)
RX: f7 02 03 00 11 ca

TX: 02 05 ff 11 01 00       (unload phase 3, ~257ms)
RX: f7 02 03 00 11 ca

TX: 02 05 ff 11 01 00       (unload phase 4, ~253ms)
RX: f7 02 03 00 11 ca

TX: 02 05 ff 11 01 01       (unload complete, ~12.5 sec)
RX: f7 02 03 00 11 ca
```

**Key Findings:**
1. **FF10** = LOAD command (multi-phase with subcmds 0x00→0x04→0x05→0x06→0x07)
2. **FF11** = UNLOAD command (phase 0x01, param 0x00=continue, 0x01=complete)
3. Motor direction is controlled by using different commands, NOT by a parameter byte
4. FF08 with param 0x00 enables motor for unload (counterintuitive naming)
5. Unload consists of 4 short retract pulses followed by 1 long final retract

---

## Unverified Hypotheses - To Test

**Session: 2025-12-31**

The following observations need verification in a future session:

### 1. Motor Direction Control (FF10 subcmd 0x05)

**Hypothesis:** The last byte (param) of subcmd 0x05 controls feed direction:
- `param=0x00` = FEED (forward)
- `param=0xFF` = RETRACT (reverse)

**Status:** ❌ **DISPROVEN** (2026-01-01)

**Finding:** Motor direction is NOT controlled by a parameter byte on FF10. Instead:
- **FF10** = LOAD/FEED command (forward direction only)
- **FF11** = UNLOAD/RETRACT command (separate command entirely)

**Evidence from T2A load/unload trace:**
- Load sequence used only FF10 commands with various subcmds (0x00, 0x04, 0x05, 0x06, 0x07)
- Unload sequence used FF11 commands (`0205ff110100`, `0205ff110101`)
- FF10 was NOT used during unload at all
- The `0x05ff` pattern previously observed was misinterpreted - it was likely FF05 (status) not FF10 with 0xFF param

### 2. FF10 Motor Timing Control (Subcmd 0x06/0x07)

**Hypothesis:** Subcmd 0x06 starts continuous motor feed, subcmd 0x07 stops it.

**Evidence:**
- T2A load trace shows 0x06 followed by ~4.3s gap, then 0x07
- Subcmd 0x05 calls are very short (24-135ms) and return encoder data - self-limiting
- Previous motor tests ran indefinitely - likely missing the 0x07 stop command
- User reported audible "stutter steps" matching the 5x short 0x05 pulses

**Status:** UNVERIFIED - needs controlled test

**To Test:**
1. Send `02 06 ff 10 01 06 00` (start feed)
2. Wait 2 seconds
3. Send `02 06 ff 10 01 07 03` (stop)
4. Verify motor runs only during the 2-second window
5. Compare to sending 0x06 without 0x07 (expect indefinite run)

---

### 3. Motor Speed

**Hypothesis:** Feeder motor speed is approximately 62mm/s (not 6mm/s)

**Evidence:**
- Sent motor run for 8 seconds, expected 50mm at 6mm/s
- User reported ~500mm of movement
- Calculated: 500mm / 8s ≈ 62mm/s

**Status:** UNVERIFIED - Single observation, needs multiple measurements

**To Test:**
1. Run motor for known time
2. Measure actual filament movement
3. Calculate speed from multiple trials

### 4. Sensor Read Error Status

**Hypothesis:** Sensor read (FF0A) status byte `0x0b` indicates error state

**Evidence:**
- Normal response: `f7 02 07 00 0a ...` (status=0x00)
- Observed: `f7 02 07 0b 0a ...` (status=0x0b)
- Box was not responding to motor commands when this status was observed

**Status:** UNVERIFIED - Correlation observed but causation not confirmed

**To Test:**
1. Query sensor status when box is working normally (expect 0x00)
2. Induce error condition, query again (expect non-zero?)
3. Clear error, verify status returns to 0x00

### 5. FF10 Variant Byte = Slot Selection

**Hypothesis:** The "variant" byte in FF10 commands selects the slot:
- `variant=0x01` = Slot A
- `variant=0x02` = Slot B
- `variant=0x03` = Slot C
- `variant=0x04` = Slot D

**Evidence:**
- Sent `variant=0x02` expecting motor control variant, activated Slot B instead
- User feedback: "that test activated slot B"

**Status:** PARTIALLY VERIFIED - Observed variant=0x02 activating slot B

**To Test:**
1. Send FF10 with variant=0x01, confirm slot A activates
2. Send FF10 with variant=0x03, confirm slot C activates
3. Send FF10 with variant=0x04, confirm slot D activates

### 6. Filament Status 0x02 = Empty Slot

**Status:** VERIFIED - Added to `verified/test_plan/serial_protocol.md`

| Value | Meaning |
|-------|---------|
| 0x00  | Filament cleared/ejected |
| 0x01  | Filament present |
| 0x02  | No filament (empty slot) |
