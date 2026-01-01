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
- Printer config: `/usr/data/printer_data/config/printer.cfg`
