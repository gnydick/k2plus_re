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
