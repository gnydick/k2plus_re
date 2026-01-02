# Serial 485 Protocol

RS-485 serial communication protocol for K2 Plus peripherals.

## Configuration

```ini
[serial_485 serial485]
serial: /dev/ttyS5
baud: 230400
```

## Packet Format

### Request
```
[addr] [len] [cmd] [data...]
```

### Response
```
[0xF7] [addr] [len_lo] [len_hi] [cmd] [data...] [checksum]
```

**Example Exchange:**
- Request: `02 03 ff 0a` = addr=2, len=3, cmd=0xFF0A
- Response: `f7 02 07 00 0a 18 27 00 00 4c` = header, addr=2, len=7, cmd=0x0A, data, checksum

## Device Addresses

| Address | Type | Description |
|---------|------|-------------|
| 0x01-0x04 | Material Boxes (MB) | Filament feeder boxes (DEV_TYPE=1) |
| 0x11 | Filament Rack | Filament rack controller |
| 0x81-0x84 | Closed-Loop Motors (CLM) | XY axis motors for input shaping (DEV_TYPE=2) |
| 0x91-0x92 | Belt Tension Motors (BTM) | Belt tensioning system (DEV_TYPE=3) |
| 0xFC | Broadcast (BTM) | All belt tension motors |
| 0xFD | Broadcast (CLM) | All closed-loop motors |
| 0xFE | Broadcast (boxes) | All material boxes |
| 0xFF | General Broadcast | All devices |

**Important:** Filament feeder motors are controlled via box addresses (0x01-0x04), NOT 0x81-0x84.

## Slot Encoding

| Slot | Value | Examples |
|------|-------|----------|
| A | 0x00 | T1A, T2A, T3A, T4A |
| B | 0x01 | T1B, T2B, T3B, T4B |
| C | 0x02 | T1C, T2C, T3C, T4C |
| D | 0x03 | T1D, T2D, T3D, T4D |

**Tnn Parsing:** `T<box><slot>` → box digit becomes address 0x01-0x04, slot letter becomes index 0-3

## CRC-8 Checksum

Polynomial: 0x07. CRC calculated over: LEN + STATUS + FUNC + DATA

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

## Wrapper Methods

| Method | Signature | Description |
|--------|-----------|-------------|
| `cmd_send_data_with_response` | `(bytes, timeout, wait_response=True) -> bytes` | Send command, get response |
| `add_send_data` | `(bytes, timeout, addr_marker, cmd_marker, wait) -> None` | Queue async send |
| `remove_send_data` | `(list) -> None` | Remove queued send |

## Polling Commands (Filtered)

These are sent frequently and filtered from traces by default:
- `0x00A2` - Device online check
- `0xFF0A` - Sensor readings
