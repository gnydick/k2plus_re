# Klipper REPL Testing

How to connect to the Klipper REPL and run tests.

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

## Helper Functions

From `test_scripts.py`:

### run_gcode(cmd, timeout=10)
Execute a GCode command and wait for result.

```python
run_gcode("BOX_GET_BOX_STATE")
run_gcode("T2A")  # Load slot T2A (~2 minutes)
run_gcode("PRINT_ADDR_TABLE")
```

### rs.send(bytes)
Send raw RS-485 data.

```python
rs.send(bytes.fromhex("02 06 ff 10 01 00 00"))  # Init motor
```

## Example Session

```python
# Connect and setup
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

# Run commands
run_gcode("BOX_GET_BOX_STATE")
run_gcode("BOX_ERROR_CLEAR")
```
