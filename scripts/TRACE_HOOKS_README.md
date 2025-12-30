# Klipper Runtime Tracing Module (Streaming)

Trace method calls on a running Klipper instance via TCP streaming to reverse-engineer method implementations from compiled Cython modules.

## Architecture

```
[Klipper + trace_hooks.py] --TCP:9876--> [trace_capture.py] --> captures/*.jsonl
```

- **trace_hooks.py**: Klipper extra that wraps methods and streams events
- **trace_capture.py**: Client that connects and writes to per-object JSONL files
- **flush_data_collector.py**: Automation script for systematic data collection

## Deployment

1. **Copy to printer:**
   ```bash
   scp scripts/trace_hooks_streaming.py root@<printer-ip>:/usr/share/klipper/klippy/extras/trace_hooks.py
   ```

2. **Add to printer.cfg:**
   ```ini
   [trace_hooks]
   stream_port: 9876
   ```

3. **Restart Klipper:**
   ```bash
   systemctl restart klipper
   ```

## Quick Start

```bash
# Terminal 1: Start capture client
python3 scripts/trace_capture.py <printer-ip>

# Terminal 2: Enable tracing via Klipper console/Mainsail
TRACE_EVERYTHING    # Trace all public methods on all objects
# or
TRACE_DEEP          # Trace all methods including _private ones
```

## G-Code Commands

### Discovery Commands

#### TRACE_DEBUG
Show discovered objects and available modules.
```gcode
TRACE_DEBUG
```

#### TRACE_MODULE_INFO
Show available objects or methods on a specific object.
```gcode
TRACE_MODULE_INFO                    # List all objects
TRACE_MODULE_INFO OBJECT=box         # Show methods on box object
```

#### TRACE_STATUS
Show current trace status (objects, active traces, clients).
```gcode
TRACE_STATUS
```

#### TRACE_LIST
Show active traces.
```gcode
TRACE_LIST
```

### Basic Tracing

#### TRACE_ENABLE / TRACE_DISABLE
Enable/disable tracing on a specific method.
```gcode
TRACE_ENABLE OBJECT=box METHOD=Tn_action
TRACE_DISABLE OBJECT=box METHOD=Tn_action
TRACE_DISABLE OBJECT=box              # Disable all traces on object
```

#### TRACE_ALL
Trace all public methods (excludes `_private` methods).
```gcode
TRACE_ALL OBJECT=box
TRACE_ALL OBJECT=prtouch_v3
```

#### TRACE_EVERYTHING
Trace all public methods on ALL discovered objects.
```gcode
TRACE_EVERYTHING
```

### Deep Tracing

#### TRACE_DEEP
Trace ALL methods including single-underscore `_private` methods (skips `__dunder__`).
```gcode
TRACE_DEEP OBJECT=box     # Deep trace specific object
TRACE_DEEP                # Deep trace all objects
```

#### TRACE_ATTRS
Trace attribute access to see what data is read during method execution.
```gcode
TRACE_ATTRS OBJECT=box ENABLE=1              # Enable attribute tracing
TRACE_ATTRS OBJECT=box ENABLE=1 RECURSIVE=1  # Recursive (traces nested objects)
TRACE_ATTRS OBJECT=box ENABLE=0              # Disable
TRACE_ATTRS                                   # Show active attribute traces
```

This emits `attr_read` events showing every attribute accessed:
```json
{"type": "attr_read", "object": "box", "attr": "flush_multiplier", "value": 1.5}
```

### Filtering

#### TRACE_QUIET
Manage quiet methods (filtered by default to reduce noise).
```gcode
TRACE_QUIET                     # Show current quiet methods
TRACE_QUIET ADD=some_method     # Add to quiet list
TRACE_QUIET REMOVE=get_status   # Remove from quiet list
```

Default quiet methods: `get_status`, `get_connect_state`, `test_error`, `box_connect_state_check`, `connect_state_check`

#### TRACE_VERBOSE
Enable verbose mode for an object (traces quiet methods too).
```gcode
TRACE_VERBOSE OBJECT=box           # Toggle verbose for box
TRACE_VERBOSE OBJECT=box ENABLE=1  # Enable verbose
TRACE_VERBOSE OBJECT=box ENABLE=0  # Disable verbose
TRACE_VERBOSE                       # Show verbose objects
```

### Macro Tracing

#### TRACE_MACRO
Trace a specific GCode macro.
```gcode
TRACE_MACRO                        # List available macros
TRACE_MACRO NAME=BOX_CHECK_MATERIAL
```

Note: Macro tracing has limitations due to how Klipper stores method references at startup.

### Stream Control

#### TRACE_STREAM_START / TRACE_STREAM_STOP
Control the TCP streaming server.
```gcode
TRACE_STREAM_START
TRACE_STREAM_STOP
```

#### TRACE_STREAM_STATUS
Show streaming server status and connected clients.
```gcode
TRACE_STREAM_STATUS
```

## Capture Client

### Basic Usage
```bash
python3 scripts/trace_capture.py <printer-ip> [--port 9876]
```

Creates separate files per object in `captures/`:
- `captures/box_20251230_143022.jsonl`
- `captures/prtouch_v3_20251230_143022.jsonl`
- `captures/serial_485_serial485_20251230_143022.jsonl`

### Output Format

Each line is a JSON event:

**Method call:**
```json
{"type": "call", "id": 123, "time": 1703945025.123, "object": "box", "class": "MultiColorMeterialBoxWrapper", "method": "get_flush_len", "args": "None, \"T2A\""}
```

**Return value:**
```json
{"type": "return", "id": 123, "time": 1703945025.456, "object": "box", "method": "get_flush_len", "result": 160.83333333333334, "duration_ms": 333.0}
```

**Attribute read (with TRACE_ATTRS):**
```json
{"type": "attr_read", "time": 1703945025.200, "object": "box", "attr": "flush_table", "value": {"T0A": {"T1A": 140, "T2A": 150}}}
```

**Error:**
```json
{"type": "error", "id": 123, "object": "box", "method": "Tn_action", "error": "Timeout", "traceback": "..."}
```

## Data Collection Script

For systematic flush algorithm reverse-engineering:

```bash
# Dry run (see what would happen)
python3 scripts/flush_data_collector.py <printer-ip> --dry-run

# Actual collection with all tool combinations
python3 scripts/flush_data_collector.py <printer-ip>

# Specific tools only
python3 scripts/flush_data_collector.py <printer-ip> --tools T0A T1A T2A

# First-load scenarios only
python3 scripts/flush_data_collector.py <printer-ip> --first-load-only
```

## Workflow Examples

### Reverse-engineer calc_flushing_volume

```bash
# Terminal 1: Start capture
python3 scripts/trace_capture.py <printer-ip>

# Klipper console: Enable deep tracing
TRACE_DEEP OBJECT=box
TRACE_ATTRS OBJECT=box ENABLE=1

# Terminal 2: Run systematic tool changes
python3 scripts/flush_data_collector.py <printer-ip>

# Analyze captures
cat captures/box_*.jsonl | grep calc_flushing
```

### Trace a specific probing operation

```gcode
TRACE_DEEP OBJECT=prtouch_v3
G28 Z
```

Then check `captures/prtouch_v3_*.jsonl` for the full call sequence.

### Trace serial protocol

```gcode
TRACE_ALL OBJECT=serial_485_serial485
; Trigger some motor/box commands
```

Check `captures/serial_485_*.jsonl` for raw protocol data.

## Available Objects

Common objects discovered on K2 Plus:
- `box` - Multi-material box wrapper (filament changes, flushing)
- `prtouch_v3` - Pressure-based touch probe
- `serial_485_serial485` - RS-485 serial communication
- `motor_control` - Motor control protocol
- `filament_rack` - Filament rack management

Use `TRACE_DEBUG` to see all discovered objects on your printer.

## Tips

1. **Start with TRACE_DEEP on the specific module** you're investigating
2. **Enable TRACE_ATTRS** to see what data the algorithm reads
3. **Use flush_data_collector.py** for systematic input/output collection
4. **Filter noise** with TRACE_QUIET if get_status floods the logs
5. **Check captures/ directory** - each object gets its own timestamped file
6. **Bytes are hex-encoded** as `{"_bytes": "f70203..."}` in the output
