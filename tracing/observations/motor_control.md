# Motor Control

Closed-loop motor control protocol for XY axis steppers (input shaping) and belt tensioning.

## Module

`extras.motor_control` → `MotorControlWrapper`

## Device Addresses

| Address | Type | Description |
|---------|------|-------------|
| 0x81-0x84 | CLM | Closed-Loop Motors - XY axis steppers |
| 0x91-0x92 | BTM | Belt Tension Motors |
| 0xFC | Broadcast | All belt tension motors |
| 0xFD | Broadcast | All closed-loop motors |

**Note:** These are NOT the filament feeder motors. Feeder motors use box addresses 0x01-0x04.

## Packet Format

```python
data_pack(addr=129, cmd=12, data=[11]) -> bytes("f78104000c0b95")
```

| Byte | Field | Description |
|------|-------|-------------|
| 0 | Header | 0xF7 |
| 1 | Address | 0x81 (129 = CLM motor) |
| 2-3 | Length | Little endian (0x04 0x00) |
| 4 | Command | 0x0C |
| 5+ | Data | Variable |
| Last | Checksum | CRC-8 |

## Methods

| Method | Signature | Description |
|--------|-----------|-------------|
| `bytes_to_int` | `(bytes) -> int` | Convert bytes to integer |
| `bytes_to_int` | `(bytes, is_data_obj=True) -> list` | Convert to list |
| `data_pack` | `(addr, cmd, data) -> bytes` | Pack command packet |
| `validate_data_params` | `(gcmd) -> True` | Validate GCode params |

### bytes_to_int Examples

```python
bytes_to_int({'_bytes': '81'})                    # → 129
bytes_to_int({'_bytes': '0b'}, is_data_obj=True)  # → [11]
```

## Motor Commands

| Cmd | Name | Description |
|-----|------|-------------|
| 0x01 | reboot | Reboot motor controller |
| 0x03 | encoder_calibrate_official | Official encoder calibration |
| 0x04 | elec_offset_calibrate | Electrical offset calibration |
| 0x05 | control | Motor control |
| 0x06 | sys_param | System parameters |
| 0x07 | flash_param | Flash parameters |
| 0x08 | get | Get status/data |
| 0x0B | boot | Boot mode |
| 0x0C | protection | Protection settings |
| 0x0D | systemid | System ID |
| 0x0E | read485_addr / set485_addr | Address management |
| 0x0F | version | Version query |
| 0x11 | stall_mode | Stall detection mode |

## State Attributes

- `is_ready`: True
- `is_homing`: False
- `box_action`: BoxAction object
