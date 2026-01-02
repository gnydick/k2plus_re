# Test Plans

Test plans and procedures for verifying K2 Plus firmware behavior. Observations from `re/observations/` and `tracing/observations/` get converted into test plans here. When tests pass, findings get promoted to `verified/`.

## Contents

- [object_inventory.md](object_inventory.md) - Klipper objects and methods inventory
- [serial_protocol.md](serial_protocol.md) - RS-485 serial communication details
- [motor_control.md](motor_control.md) - Motor control methods and gcode commands
- [motor_timing_control.md](motor_timing_control.md) - FF10 motor timing investigation
- [gcode_commands.md](gcode_commands.md) - Available gcode commands for box/filament control
- [test_scripts.py](test_scripts.py) - Python code for REPL testing

## Connecting to the REPL

```bash
# Best option - with history and line editing
socat readline tcp:k2plus:9877

# Alternative
rlwrap nc k2plus 9877

# Basic (no history)
nc k2plus 9877
```

## Quick Start

Once connected, paste the helper code from `test_scripts.py` using:

```python
exec('''
<paste code here>
''')
```

Then use the helper functions like `rs.send()`, `run_gcode()`, etc.
