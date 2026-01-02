# Claude Code Project Memory

## K2 Plus Printer Commands

### File Transfer
- **No scp on the printer** - use `rsync` instead:
  ```bash
  rsync -avz file.py root@k2plus:/path/to/destination/
  ```
- Alternative: pipe through ssh:
  ```bash
  cat file.py | ssh root@k2plus "cat > /path/to/file.py"
  ```

### Firmware Control (via Moonraker API)
- **Restart firmware**:
  ```bash
  curl -s "http://k2plus:7125/printer/firmware_restart" -X POST
  ```
- **Emergency stop**:
  ```bash
  curl -s "http://k2plus:7125/printer/emergency_stop" -X POST
  ```
- **Send GCode**:
  ```bash
  curl -s "http://k2plus:7125/printer/gcode/script?script=G28" -X POST
  ```

### Klipper Paths on Printer
- Klipper extras: `/usr/share/klipper/klippy/extras/`
- Printer config: `/mnt/UDISK/printer_data/config/printer.cfg`
- Klipper log: `/mnt/UDISK/printer_data/logs/klippy.log`

### printer.cfg Rules
- **CRITICAL**: Never add config sections below the `#*#` auto-generated section at the bottom of printer.cfg
- The `#*# <---------------------- SAVE_CONFIG ---------------------->` section and everything below it is auto-generated
- All custom config sections must be placed BEFORE this line

### Active Klipper Modules
- `[trace_hooks]` - Stream port 9876 for protocol tracing
- `[klipper_repl]` - REPL port 9877 for interactive Python access

---

## Trace Session Rules

### Directory Structure
Each session lives in `tracing/YYYYMMDD_HHMMSS_<description>/`:
```
tracing/20260101_202225_filament_ops/
├── session.log                    # Human-readable session documentation
├── sequence_diagrams.puml         # PlantUML diagrams for all flows
└── captures/                      # Raw trace data (auto-generated)
    ├── serial_485_serial485_*.jsonl
    ├── box_*.jsonl
    ├── filament_rack_*.jsonl
    └── _system_*.jsonl
```

### session.log Format
Use plain text with fixed-width ASCII tables (no markdown tables). Sections:

1. **Header** - Date, status, objectives
2. **Setup and Givens** - Capture files, REPL setup, helper functions, reference info
3. **Test Plan** - Commands to execute (manual REPL and GCode)
4. **Request/Response Pairs** - Actual test outputs with physical observations
5. **Observations** - Key discoveries, command reference tables, status codes, sequences

### Table Format (ASCII, not markdown)
```
  Column1     Column2       Column3
  ----------  ------------  -----------------------------------------
  value1      value2        description here
  value1      value2        description here
```

### PlantUML Diagrams (sequence_diagrams.puml)
Create diagrams for:
- Sequence diagrams showing layer interactions (GCode -> wrapper -> serial -> hardware)
- State machines for command subcodes
- Wire protocol format
- Architecture/component diagrams

### Starting a New Session
```bash
# Create session directory
SESSION=tracing/$(date +%Y%m%d_%H%M%S)_<description>
mkdir -p $SESSION

# Start trace capture FROM SESSION DIRECTORY (creates captures/ subdir)
cd $SESSION && python3 ../scripts/trace_capture.py k2plus 9876

# Connect to REPL
socat readline tcp:k2plus:9877
```

### Session Workflow
1. Create session directory and session.log with objectives
2. Start trace capture
3. Document test plan in session.log
4. Execute tests (manual REPL and/or GCode)
5. Record request/response pairs with physical observations
6. Analyze traces and document observations
7. Create PlantUML diagrams for discovered flows
8. Commit session files
