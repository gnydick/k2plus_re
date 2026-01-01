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

### Device Status (0xA0-0xA3)

| Code | Name              | Description                     |
|------|-------------------|---------------------------------|
| 0xA0 | SET_SLAVE_ADDR    | Set device address              |
| 0xA1 | GET_SLAVE_INFO    | Get device info (broadcast)     |
| 0xA2 | ONLINE_CHECK      | Check if device is online       |
| 0xA3 | GET_ADDR_TABLE    | Get address table               |

### Motor Control (0x08, 0x10)

| Code | Name           | Description                     |
|------|----------------|---------------------------------|
| 0x08 | MOTOR_ENABLE   | Enable/disable motor            |
| 0x10 | MOTOR_CONTROL  | Motor control commands          |

### Sensor/Status (0x0A, 0x0B, 0x0D, 0x0E, 0x11)

| Code | Name              | Description                     |
|------|-------------------|---------------------------------|
| 0x0A | SENSOR_READ       | Read sensor values              |
| 0x0B | LOADER_TO_APP     | Switch from bootloader to app   |
| 0x0D | SET_PRE_LOADING   | Pre-loading command             |
| 0x0E | ENCODER_READ      | Read encoder position           |
| 0x11 | FILAMENT_DETECT   | Filament detection/calibration  |

### Material Operations (0x20-0x80) - Slot Selection

These commands include a **slot parameter** (byte 5) to select which slot (A=0, B=1, C=2, D=3) within the box.

| Code | Name              | Description                     |
|------|-------------------|---------------------------------|
| 0x20 | GET_RFID          | Read RFID from slot             |
| 0x21 | GET_REMAIN_LEN    | Get remaining filament length   |
| 0x40 | EXTRUDE_PROCESS   | Start extrusion from slot       |
| 0x41 | EXTRUDE_PARTIAL   | Extrude specific length         |
| 0x50 | RETRACT_PROCESS   | Retract filament to slot        |
| 0x60 | MOTOR_ACTION      | Direct motor action control     |
| 0x70 | SET_BOX_MODE      | Set box operating mode          |
| 0x71 | SET_PRE_LOADING   | Enable/disable pre-loading      |
| 0x72 | TIGHTEN_UP        | Tighten filament                |
| 0x80 | MEASURING_WHEEL   | Read measuring wheel position   |

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

### 0x08 - Motor Enable

**Request:**
```
[addr] 04 00 08 [enable]
```

Where enable: 0x00=disable, 0x01=enable

**Response:**
```
F7 [addr] 04 00 08 [state] [crc]
```

Where state: 0x00=stopped, 0x0F=active

### 0x10 - Motor Control

**Request:**
```
[addr] 06 00 10 [variant] [subcmd] [param]
```

**Variants:**
- 0x01 = Basic motor control
- 0x02 = Extended motor control with position feedback

**Subcommands (variant 0x01):**

| Subcmd | Param | Purpose              |
|--------|-------|----------------------|
| 0x00   | 0x00  | Initialize/reset     |
| 0x04   | 0x00  | Pre-feed preparation |
| 0x05   | 0x00  | Start feed           |
| 0x06   | 0x00  | Continue feed        |
| 0x07   | 0x00  | Stop/complete        |

**Response (variant 0x01):**
```
F7 [addr] 03 00 10 [status] [crc]
```

### 0x0A - Sensor Read

**Request:**
```
[addr] 03 00 0A
```

**Response:**
```
F7 [addr] [len] 00 0A [sensor_data...] [crc]
```

Sensor data format varies by device.

## Slot-Based Material Commands

These commands target a specific slot within a box. The slot is encoded as byte 5.

### Slot Encoding

| Slot | Value | Tnn Example |
|------|-------|-------------|
| A    | 0x00  | T1A, T2A... |
| B    | 0x01  | T1B, T2B... |
| C    | 0x02  | T1C, T2C... |
| D    | 0x03  | T1D, T2D... |

### 0x20 - Get RFID

**Request:**
```
F7 [addr] 05 00 20 [slot] 00 [crc]
```

**Response:**
```
F7 [addr] [len] 00 20 [rfid_bytes...] [crc]
```

RFID is typically bytes 6-17 in hex format.

### 0x21 - Get Remaining Length

**Request:**
```
F7 [addr] 05 00 21 [slot] 00 [crc]
```

**Response:**
```
F7 [addr] 0A 00 21 [len_bytes...] [crc]
```

Length is 4 bytes, divide by 100 to get mm.

### 0x40 - Extrude Process

Start extrusion from a slot.

**Request:**
```
F7 [addr] 05 00 40 [slot] 00 [crc]
```

**Response:**
```
F7 [addr] 03 00 40 [status] [crc]
```

### 0x41 - Extrude Partial

Extrude a specific length.

**Request:**
```
F7 [addr] 07 00 41 [slot] [len_hi] [len_lo] 00 [crc]
```

Where length is in units of 0.01mm (multiply mm by 100).

### 0x50 - Retract Process

Retract filament back to slot.

**Request:**
```
F7 [addr] 05 00 50 [slot] 00 [crc]
```

**Response:**
```
F7 [addr] 03 00 50 [status] [crc]
```

### 0x71 - Set Pre-Loading

Enable or disable pre-loading for a slot.

**Request:**
```
F7 [addr] 06 00 71 [slot] [enable] 00 [crc]
```

Where enable: 0x00=disable, 0x01=enable

### 0x80 - Measuring Wheel

Get measuring wheel position for a slot.

**Request:**
```
F7 [addr] 05 00 80 [slot] 00 [crc]
```

**Response:**
```
F7 [addr] 08 00 80 [pos_hi] [pos_lo] ... [crc]
```

Position is in 0.01mm units.

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
