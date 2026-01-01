# Klipper REPL Test Plan

This directory contains documentation and test plans for exploring the Creality K2 Plus Klipper firmware via the interactive REPL.

## Contents

- [object_inventory.md](object_inventory.md) - Complete inventory of Klipper objects and their methods
- [serial_protocol.md](serial_protocol.md) - RS-485 serial communication details
- [motor_control.md](motor_control.md) - Motor control methods and gcode commands
- [test_scripts.py](test_scripts.py) - Python code for REPL testing
- [gcode_commands.md](gcode_commands.md) - Available gcode commands for box/filament control

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
