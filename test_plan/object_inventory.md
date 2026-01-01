# Klipper Object Inventory

Complete inventory of relevant Klipper objects discovered via REPL inspection.

## How to Access Objects

```python
# Direct lookup
s = printer.lookup_object('serial_485 serial485')
b = printer.lookup_object('box')
fr = printer.lookup_object('filament_rack')
aa = printer.lookup_object('auto_addr')

# Or use REPL shortcuts (these are lambdas, call them)
s = serial_485()
b = box()
fr = filament_rack()
aa = auto_addr()
```

---

## serial_485 (Serial_485_Wrapper)

**Lookup:** `printer.lookup_object('serial_485 serial485')`

### Attributes

| Attribute      | Type   | Description                    |
|----------------|--------|--------------------------------|
| `baud`         | int    | Baud rate (230400)             |
| `serial_port`  | str    | Port path (/dev/ttyS5)         |
| `name`         | str    | Instance name                  |
| `send_list`    | list   | Pending send queue             |
| `last_params`  | -      | Last command parameters        |

### Methods

| Method                         | Signature                              | Description                          |
|--------------------------------|----------------------------------------|--------------------------------------|
| `cmd_send_data_with_response`  | `(data, timeout, flag)`                | Send data and wait for response      |
| `cmd_485_send_data`            | `(data)`                               | Lower-level send                     |
| `add_send_data`                | `(...)`                                | Add to send queue                    |
| `remove_send_data`             | `(...)`                                | Remove from send queue               |
| `is_exist_in_send_list`        | `(...)`                                | Check if in queue                    |
| `register_response`            | `(...)`                                | Register response callback           |
| `handle_callback`              | `(...)`                                | Handle response callback             |
| `send_queue_process`           | `(...)`                                | Process send queue                   |

### Threading Note

`cmd_send_data_with_response` uses Klipper's reactor/greenlet system. **Cannot be called directly from REPL thread.** Must use:

```python
import threading
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
```

---

## box (MultiColorMeterialBoxWrapper)

**Lookup:** `printer.lookup_object('box')`

### Key Attributes

| Attribute    | Type       | Description                      |
|--------------|------------|----------------------------------|
| `boxcfg`     | BoxCfg     | Box configuration parameters     |
| `box_state`  | BoxState   | Current box state                |
| `parse`      | object     | Command parser                   |
| `gcode`      | object     | Gcode handler                    |

### Slot Commands (Gcode)

All take `(gcmd)` parameter - must be invoked via gcode:

| Command    | Description                |
|------------|----------------------------|
| `cmd_T1A`  | Select/load slot T1A       |
| `cmd_T1B`  | Select/load slot T1B       |
| `cmd_T1C`  | Select/load slot T1C       |
| `cmd_T1D`  | Select/load slot T1D       |
| `cmd_T2A`  | Select/load slot T2A       |
| `cmd_T2B`  | Select/load slot T2B       |
| ... etc for T3x, T4x       |

### Motor/Extrusion Methods

| Method                            | Signature | Description                          |
|-----------------------------------|-----------|--------------------------------------|
| `Tn_action`                       | `(slot)`  | Full filament load sequence          |
| `cmd_ctrl_connection_motor_action`| `(gcmd)`  | Direct motor control                 |
| `cmd_extrude_process`             | `(gcmd)`  | Extrusion process                    |
| `cmd_retrude_process`             | `(gcmd)`  | Retraction process                   |
| `cmd_box_extrude_material`        | `(gcmd)`  | Box-level extrude                    |
| `cmd_box_retrude_material`        | `(gcmd)`  | Box-level retract                    |
| `cmd_set_pre_loading`             | `(gcmd)`  | Pre-load setup                       |
| `cmd_measuring_wheel`             | `(gcmd)`  | Measuring wheel control              |

### State/Info Methods

| Method                         | Signature | Description                          |
|--------------------------------|-----------|--------------------------------------|
| `cmd_get_box_state`            | `(gcmd)`  | Get current box state                |
| `cmd_get_buffer_state`         | `(gcmd)`  | Get buffer state                     |
| `cmd_get_filament_sensor_state`| `(gcmd)`  | Get filament sensor state            |
| `cmd_get_remain_len`           | `(gcmd)`  | Get remaining filament length        |
| `cmd_get_rfid`                 | `(gcmd)`  | Read RFID from spool                 |
| `cmd_get_flush_len`            | `(gcmd)`  | Get flush length                     |
| `cmd_get_hardware_status`      | `(gcmd)`  | Get hardware status                  |
| `get_status`                   | `()`      | Get status dict (direct call OK)     |
| `get_flush_len`                | `(...)`   | Get flush length                     |
| `get_connect_state`            | `()`      | Get connection state                 |
| `has_flushing_sign`            | `()`      | Check if flushing needed             |

### Other Methods

| Method                         | Signature | Description                          |
|--------------------------------|-----------|--------------------------------------|
| `cmd_send_data`                | `(gcmd)`  | Send raw serial data                 |
| `cmd_cut_material`             | `(gcmd)`  | Cut filament                         |
| `cmd_blow`                     | `(gcmd)`  | Blow air                             |
| `cmd_error_clear`              | `(gcmd)`  | Clear errors                         |
| `error_clear`                  | `()`      | Clear errors (direct)                |
| `flush_material`               | `(...)`   | Flush material                       |
| `material_change_flush`        | `(...)`   | Material change flush                |

---

## box.boxcfg (BoxCfg)

Configuration parameters for the box.

### Key Parameters

| Parameter                  | Description                          |
|----------------------------|--------------------------------------|
| `bus`                      | Serial bus name ("serial485")        |
| `filament_sensor`          | Filament sensor name                 |
| `Tn_extrude`               | Extrusion distance                   |
| `Tn_extrude_velocity`      | Extrusion velocity                   |
| `Tn_extrude_temp`          | Extrusion temperature                |
| `Tn_retrude`               | Retraction distance                  |
| `Tn_retrude_velocity`      | Retraction velocity                  |
| `extrude_material_velocity`| Material extrusion velocity          |
| `extrude_material_len_for_box` | Extrusion length for box          |
| `buffer_empty_len`         | Buffer empty length                  |
| `max_tube_length`          | Max tube length                      |
| `cut_pos_x`, `cut_pos_y`   | Cut position coordinates             |
| `clean_velocity`           | Cleaning velocity                    |
| `flush_multiplier`         | Flush multiplier                     |

---

## box.box_state (BoxState)

Current state of the box system.

### Key Attributes/Methods

| Attribute/Method      | Description                                |
|-----------------------|--------------------------------------------|
| `Tn_data`             | Slot data                                  |
| `Tn_inner_data`       | Internal slot data                         |
| `Tn_map`              | Slot mapping                               |
| `Tnn_map`             | Tnn slot mapping                           |
| `Tnn_content`         | Tnn content                                |
| `get_Tn_data()`       | Get slot data (requires params)            |
| `get_Tnn_map()`       | Get Tnn map - returns dict                 |
| `modify_Tn_data()`    | Modify slot data                           |

### Tnn Map (Slot Layout)

```python
{
    'T1A': 'T1A', 'T1B': 'T1B', 'T1C': 'T1C', 'T1D': 'T1D',
    'T2A': 'T2A', 'T2B': 'T2B', 'T2C': 'T2C', 'T2D': 'T2D',
    'T3A': 'T3A', 'T3B': 'T3B', 'T3C': 'T3C', 'T3D': 'T3D',
    'T4A': 'T4A', 'T4B': 'T4B', 'T4C': 'T4C', 'T4D': 'T4D'
}
```

**Note:** 4 slots per box (A, B, C, D), not 2 as previously documented!

---

## box.parse

Parser utilities for box commands.

| Method                      | Description                          |
|-----------------------------|--------------------------------------|
| `get_cmd_num`               | Get command number                   |
| `get_key_from_value`        | Lookup key from value                |
| `get_measuring_wheel`       | Get measuring wheel data             |
| `get_remain_len`            | Parse remaining length               |
| `get_rfid`                  | Parse RFID data                      |
| `parse_num_string_to_byte`  | Parse number string to bytes         |
| `parse_num_to_byte`         | Parse number to bytes                |

---

## filament_rack (FilamentRackWrapper)

**Lookup:** `printer.lookup_object('filament_rack')`

### Attributes

| Attribute            | Value/Type | Description                          |
|----------------------|------------|--------------------------------------|
| `addr`               | 17 (0x11)  | RS-485 address (different from box!) |
| `velocity`           | 360        | Feed velocity                        |
| `extrude`            | 140        | Extrusion amount (attribute, not method) |
| `temp`               | -          | Temperature setting                  |
| `material_database`  | dict       | Material database                    |
| `filament_rack_data` | -          | Rack data                            |

### Methods

| Method                    | Signature        | Description                          |
|---------------------------|------------------|--------------------------------------|
| `send_data`               | `(eventtime=None)` | Send data to rack                  |
| `enable_get_filament`     | `()`             | Enable filament dispensing           |
| `get_material_target_speed`| `(type)`        | Get speed for material type          |
| `get_material_target_temp` | `(type)`        | Get temp for material type           |
| `cmd_filament_rack`       | `(gcmd)`         | Main filament rack command           |
| `cmd_filament_rack_flush` | `(gcmd)`         | Flush command                        |
| `cmd_filament_rack_modify`| `(gcmd)`         | Modify rack settings                 |
| `cmd_set_cool_temp`       | `(gcmd)`         | Set cooling temperature              |
| `get_status`              | `()`             | Get status dict                      |
| `beep`                    | `(...)`          | Beeper control                       |
| `blow`                    | `(...)`          | Air blow                             |

---

## auto_addr (AutoAddrWrapper)

**Lookup:** `printer.lookup_object('auto_addr')`

Handles RS-485 auto-addressing protocol.

### Methods

| Method                        | Description                          |
|-------------------------------|--------------------------------------|
| `cmd_PRINT_ADDR_TABLE`        | Gcode: Print address table           |
| `send_package`                | Send RS-485 package (proper format)  |
| `data_pack`                   | Create data package                  |
| `cal_pack_crc`                | Calculate package CRC                |
| `crc8_cal`                    | CRC-8 calculation                    |
| `communication_online_check`  | Check device online                  |
| `communication_get_addr_table`| Get address table                    |
| `communication_get_slave_info`| Get slave info                       |
| `communication_set_slave_addr`| Set slave address                    |
| `online_check`                | Online check logic                   |
| `get_addr_table`              | Get address table logic              |
| `addr_allocate`               | Allocate address                     |
| `get_addr_table_uniids`       | Get stored UNIIDs                    |
| `save_addr_table_uniids`      | Save UNIIDs to config                |

---

## Address Summary

| Device Type              | Address Range | Dev Code | Purpose                              |
|--------------------------|---------------|----------|--------------------------------------|
| Material Box (MB)        | 0x01 - 0x04   | 1        | Filament boxes with feeder motors    |
| Closed-Loop Motor (CLM)  | 0x81 - 0x84   | 2        | Printer XY axis motors (input shaping) |
| Belt Tension Motor (BTM) | 0x91 - 0x92   | 3        | Belt tensioning motors               |
| Filament Rack            | 0x11 (17)     | -        | From `filament_rack.addr`            |
| Broadcast (Box)          | 0xFE          | -        | All material boxes                   |
| Broadcast (CLM)          | 0xFD          | -        | All closed-loop motors               |
| Broadcast (BTM)          | 0xFC          | -        | All belt tension motors              |

**Important:** The filament feeder motors inside each box are controlled via the box address (0x01-0x04), NOT the closed-loop motor addresses (0x81-0x84). The CLM addresses are for the printer's axis motors.
