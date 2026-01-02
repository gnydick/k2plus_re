# Gcode Commands for Box/Filament Control

Gcode commands discovered via REPL inspection of the box and filament_rack objects.

## Box Commands

### Slot Selection

| Command | Description                     |
|---------|---------------------------------|
| `T1A`   | Select/load Box 1 Slot A        |
| `T1B`   | Select/load Box 1 Slot B        |
| `T1C`   | Select/load Box 1 Slot C        |
| `T1D`   | Select/load Box 1 Slot D        |
| `T2A`   | Select/load Box 2 Slot A        |
| `T2B`   | Select/load Box 2 Slot B        |
| `T2C`   | Select/load Box 2 Slot C        |
| `T2D`   | Select/load Box 2 Slot D        |
| `T3A`   | Select/load Box 3 Slot A        |
| `T3B`   | Select/load Box 3 Slot B        |
| `T3C`   | Select/load Box 3 Slot C        |
| `T3D`   | Select/load Box 3 Slot D        |
| `T4A`   | Select/load Box 4 Slot A        |
| `T4B`   | Select/load Box 4 Slot B        |
| `T4C`   | Select/load Box 4 Slot C        |
| `T4D`   | Select/load Box 4 Slot D        |

Also available: `T0` through `T15` (alternate numbering)

### Motor/Extrusion Control

| Command                       | Parameters          | Description                     |
|-------------------------------|---------------------|---------------------------------|
| `BOX_CTRL_CONNECTION_MOTOR_ACTION`| `ADDR=2 ACTION=?`  | Direct motor control (cmd 0x60) |
| `BOX_EXTRUDE_MATERIAL`        | (unknown)           | Extrude material from box       |
| `BOX_RETRUDE_MATERIAL`        | (unknown)           | Retract material to box         |
| `EXTRUDE_PROCESS`             | (unknown)           | Extrusion process               |
| `RETRUDE_PROCESS`             | (unknown)           | Retraction process              |
| `BOX_SET_PRE_LOADING`         | `ADDR=2 SLOT=0 ENABLE=1` | Pre-loading setup          |
| `BOX_MEASURING_WHEEL`         | `ADDR=2 SLOT=0`     | Get measuring wheel position    |
| `BOX_TN_EXTRUDE`              | `SLOT=0 LENGTH=50.0`| Extrude from slot               |
| `EXTRUDER_EXTRUDE`            | (unknown)           | Extruder extrusion              |

### Cutting/Cleaning

| Command            | Parameters | Description                     |
|--------------------|------------|---------------------------------|
| `CUT_MATERIAL`     | (unknown)  | Cut filament                    |
| `CUT_STATE`        | (unknown)  | Get cut state                   |
| `MOVE_TO_CUT`      | (unknown)  | Move to cut position            |
| `MOVE_TO_SAFE_POS` | (unknown)  | Move to safe position           |
| `NOZZLE_CLEAN`     | (unknown)  | Clean nozzle                    |
| `BLOW`             | (unknown)  | Blow air                        |
| `MATERIAL_FLUSH`   | (unknown)  | Flush material                  |
| `MATERIAL_CHANGE_FLUSH` | (unknown) | Flush for material change    |

### Status/Query

| Command                    | Parameters | Description                     |
|----------------------------|------------|---------------------------------|
| `GET_BOX_STATE`            | (none)     | Get current box state           |
| `GET_BUFFER_STATE`         | (none)     | Get buffer state                |
| `GET_FILAMENT_SENSOR_STATE`| (none)     | Get filament sensor state       |
| `GET_REMAIN_LEN`           | (unknown)  | Get remaining filament length   |
| `GET_RFID`                 | (unknown)  | Read RFID from spool            |
| `GET_FLUSH_LEN`            | (unknown)  | Get flush length                |
| `GET_FLUSH_VELOCITY_TEST`  | (unknown)  | Get flush velocity              |
| `GET_HARDWARE_STATUS`      | (unknown)  | Get hardware status             |
| `GET_VERSION_SN`           | (unknown)  | Get version/serial number       |
| `GET_GCODE_USED_TNN`       | (unknown)  | Get gcode used Tnn              |
| `SHOW_TNN_DATA`            | (unknown)  | Show Tnn data                   |
| `SHOW_ERROR`               | (unknown)  | Show error                      |
| `SHOW_FLUSH_LIST`          | (unknown)  | Show flush list                 |

### Configuration

| Command                    | Parameters | Description                     |
|----------------------------|------------|---------------------------------|
| `BOX_SET_CURRENT_BOX_IDLE_MODE` | (unknown) | Set idle mode               |
| `SET_BOX_MODE`             | (unknown)  | Set box mode                    |
| `SET_ENABLE_AUTO_REFILL`   | (unknown)  | Enable/disable auto refill      |
| `SET_TEMP`                 | (unknown)  | Set temperature                 |
| `MODIFY_TN_DATA`           | (unknown)  | Modify Tn data                  |
| `MODIFY_TN_INNER_DATA`     | (unknown)  | Modify Tn inner data            |
| `MODIFY_TNN_MAP`           | (unknown)  | Modify Tnn map                  |
| `TIGHTEN_UP_ENABLE`        | (unknown)  | Tighten up enable               |
| `UPDATE_SAME_MATERIAL_LIST`| (unknown)  | Update material list            |
| `GENERATE_FLUSH_ARRAY`     | (unknown)  | Generate flush array            |

### Error Handling

| Command              | Parameters | Description                     |
|----------------------|------------|---------------------------------|
| `ERROR_CLEAR`        | (none)     | Clear errors                    |
| `ERROR_RESUME_PROCESS`| (unknown) | Resume from error               |
| `MAKE_ERROR`         | (unknown)  | Force error (testing?)          |

### Print Control

| Command                | Parameters | Description                     |
|------------------------|------------|---------------------------------|
| `BOX_START_PRINT`      | (unknown)  | Start print mode                |
| `BOX_END_PRINT`        | (unknown)  | End print mode                  |
| `BOX_END`              | (unknown)  | End box operation               |
| `BOX_ENABLE_CFS_PRINT` | (unknown)  | Enable CFS print                |
| `CHECK_MATERIAL_REFILL`| (unknown)  | Check material refill           |
| `FIRST_POWER_ON_PRELOAD`| (unknown) | First power on preload          |
| `POWER_LOSS_RESTORE`   | (unknown)  | Power loss restore              |
| `EXTRUSION_ALL_MATERIALS`| (unknown)| Extrusion all materials         |

### Communication

| Command             | Parameters | Description                     |
|---------------------|------------|---------------------------------|
| `SEND_DATA`         | (unknown)  | Send raw serial data            |
| `CREATE_CONNECT`    | (unknown)  | Create connection               |
| `COMMUNICATION_TEST`| (unknown)  | Test communication              |
| `ENABLE_HEART_PROCESS`| (none)   | Enable heartbeat                |
| `DISABLE_HEART_PROCESS`| (none)  | Disable heartbeat               |

### Fan Control

| Command        | Parameters | Description                     |
|----------------|------------|---------------------------------|
| `SAVE_FAN`     | (unknown)  | Save fan state                  |
| `RESTORE_FAN`  | (unknown)  | Restore fan state               |

---

## Filament Rack Commands

| Command                   | Parameters | Description                     |
|---------------------------|------------|---------------------------------|
| `FILAMENT_RACK`           | (unknown)  | Main filament rack command      |
| `FILAMENT_RACK_FLUSH`     | (unknown)  | Flush command                   |
| `FILAMENT_RACK_PRE_FLUSH` | (unknown)  | Pre-flush                       |
| `FILAMENT_RACK_MODIFY`    | (unknown)  | Modify rack settings            |
| `FILAMENT_RACK_SET_TEMP`  | (unknown)  | Set rack temperature            |
| `SET_COOL_TEMP`           | (unknown)  | Set cooling temperature         |

---

## Auto Address Commands

| Command            | Parameters | Description                     |
|--------------------|------------|---------------------------------|
| `PRINT_ADDR_TABLE` | (none)     | Print RS-485 address table      |

---

## Usage from REPL

```python
import threading

def run_gcode(cmd, timeout=10):
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
    done.wait(timeout=timeout)
    return result[0]

# Examples
run_gcode("GET_BOX_STATE")
run_gcode("PRINT_ADDR_TABLE")
run_gcode("T2A")  # Load slot T2A
```

---

## Notes

1. Many parameters are marked as "(unknown)" - need testing to determine
2. Commands that take `gcmd` parameter must be invoked via gcode, not directly
3. Some commands may cause physical movement - use caution
4. Full slot load (T2A etc.) takes ~2 minutes to complete
