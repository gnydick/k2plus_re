# Klipper REPL Test Scripts
#
# Usage: Connect to REPL and paste code using exec('''...''')
#
# Connect with: socat readline tcp:k2plus:9877

# =============================================================================
# HELPER CLASS - Paste this first
# =============================================================================

HELPER_CODE = '''
import threading
import time

class RS485Helper:
    """Helper class for RS-485 communication from REPL."""

    def __init__(self, printer, reactor):
        self.printer = printer
        self.reactor = reactor
        self._serial = None
        self._box = None
        self._rack = None
        self._auto_addr = None

    @property
    def serial(self):
        if self._serial is None:
            self._serial = self.printer.lookup_object("serial_485 serial485")
        return self._serial

    @property
    def box(self):
        if self._box is None:
            self._box = self.printer.lookup_object("box")
        return self._box

    @property
    def rack(self):
        if self._rack is None:
            self._rack = self.printer.lookup_object("filament_rack")
        return self._rack

    @property
    def auto_addr(self):
        if self._auto_addr is None:
            self._auto_addr = self.printer.lookup_object("auto_addr")
        return self._auto_addr

    def send(self, data, timeout=0.1):
        """Send RS-485 data and get response."""
        result = [None]
        done = threading.Event()
        serial = self.serial

        def _send(eventtime):
            result[0] = serial.cmd_send_data_with_response(bytes(data), timeout, False)
            done.set()

        self.reactor.register_callback(_send)
        done.wait(timeout=timeout + 1)
        return result[0]

    def send_hex(self, hex_string, timeout=0.1):
        """Send RS-485 data from hex string like '02 04 00 08 01'."""
        data = bytes.fromhex(hex_string.replace(' ', ''))
        return self.send(list(data), timeout)

    # Convenience methods
    def online_check(self, addr):
        return self.send([addr, 0x03, 0x00, 0xA2])

    def sensor_read(self, addr):
        return self.send([addr, 0x03, 0x00, 0x0A])

    def motor_enable(self, addr, enable=True):
        return self.send([addr, 0x04, 0x00, 0x08, 0x01 if enable else 0x00])

    def motor_disable(self, addr):
        return self.motor_enable(addr, False)

    def motor_cmd(self, addr, variant, subcmd, param=0x00):
        return self.send([addr, 0x06, 0x00, 0x10, variant, subcmd, param])

    def feed_start(self, addr, variant=0x01):
        """Start feeding sequence."""
        results = []
        results.append(("enable", self.motor_enable(addr)))
        results.append(("init", self.motor_cmd(addr, variant, 0x00, 0x00)))
        results.append(("pre-feed", self.motor_cmd(addr, variant, 0x04, 0x00)))
        results.append(("start", self.motor_cmd(addr, variant, 0x05, 0x00)))
        return results

    def feed_stop(self, addr, variant=0x01):
        """Stop feeding sequence."""
        results = []
        results.append(("stop", self.motor_cmd(addr, variant, 0x07, 0x00)))
        results.append(("disable", self.motor_disable(addr)))
        return results


def run_gcode(cmd, timeout=10):
    """Run gcode command safely from REPL."""
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


def run_on_reactor(func, timeout=5):
    """Run any function on the reactor thread."""
    result = [None]
    done = threading.Event()

    def _run(eventtime):
        result[0] = func()
        done.set()

    reactor.register_callback(_run)
    done.wait(timeout=timeout)
    return result[0]


# Create global helper instance
rs = RS485Helper(printer, reactor)

print("Helpers loaded!")
print("  rs.send([addr, ...])  - Send RS-485 command")
print("  rs.online_check(addr) - Check device online")
print("  rs.sensor_read(addr)  - Read sensor")
print("  rs.feed_start(addr)   - Start feeding")
print("  rs.feed_stop(addr)    - Stop feeding")
print("  run_gcode('CMD')      - Run gcode command")
print("  run_on_reactor(func)  - Run function on reactor")
'''

# To use: exec(HELPER_CODE) in the REPL

# =============================================================================
# TEST SCRIPTS
# =============================================================================

# Test 1: Communication Check
TEST_COMMUNICATION = '''
print("=== Communication Test ===")
for addr in [0x01, 0x02, 0x03, 0x04, 0x81, 0x82, 0x83, 0x84]:
    resp = rs.online_check(addr)
    status = resp.hex() if resp else "No response"
    print(f"Address 0x{addr:02X}: {status}")
'''

# Test 2: Sensor Read
TEST_SENSORS = '''
print("=== Sensor Read Test ===")
for addr in [0x01, 0x02, 0x03, 0x04]:
    resp = rs.sensor_read(addr)
    status = resp.hex() if resp else "No response"
    print(f"Box {addr} sensor: {status}")
'''

# Test 3: Box State
TEST_BOX_STATE = '''
print("=== Box State ===")
print(run_gcode("GET_BOX_STATE"))
print(run_gcode("GET_BUFFER_STATE"))
print(run_gcode("GET_FILAMENT_SENSOR_STATE"))
'''

# Test 4: Motor Test (CAREFUL!)
TEST_MOTOR = '''
print("=== Motor Test (Box 2) ===")
addr = 0x02  # Box 2

print("Starting feed...")
for name, resp in rs.feed_start(addr):
    print(f"  {name}: {resp.hex() if resp else 'None'}")

import time
time.sleep(1.0)  # Run for 1 second

print("Stopping feed...")
for name, resp in rs.feed_stop(addr):
    print(f"  {name}: {resp.hex() if resp else 'None'}")

print("Done!")
'''

# Test 5: Gcode Motor Control
TEST_GCODE_MOTOR = '''
print("=== Gcode Motor Test ===")
# Try different ACTION values
for action in ["1", "forward", "0", "stop"]:
    print(f"ACTION={action}: {run_gcode(f'CTRL_CONNECTION_MOTOR_ACTION Tnn=T2A ACTION={action}')}")
    import time
    time.sleep(0.5)
'''

# Test 6: Inspect Box Methods
TEST_INSPECT_BOX = '''
print("=== Box Object Inspection ===")
b = rs.box

print("\\nBoxCfg parameters:")
for attr in ['Tn_extrude', 'Tn_extrude_velocity', 'extrude_material_velocity']:
    print(f"  {attr}: {getattr(b.boxcfg, attr, 'N/A')}")

print("\\nBox state Tnn_map:")
print(f"  {b.box_state.get_Tnn_map()}")
'''

# Test 7: Filament Rack
TEST_FILAMENT_RACK = '''
print("=== Filament Rack ===")
fr = rs.rack

print(f"Address: 0x{fr.addr:02X} ({fr.addr})")
print(f"Velocity: {fr.velocity}")
print(f"Extrude: {fr.extrude}")

# Try enable_get_filament
def try_enable():
    return fr.enable_get_filament()

result = run_on_reactor(try_enable)
print(f"enable_get_filament result: {result}")
'''

# Test 8: Auto Address Table
TEST_ADDR_TABLE = '''
print("=== Address Table ===")
print(run_gcode("PRINT_ADDR_TABLE"))
'''

# =============================================================================
# USAGE INSTRUCTIONS
# =============================================================================

USAGE = """
# Connect to REPL:
socat readline tcp:k2plus:9877

# Load helpers (paste this):
exec('''
<paste HELPER_CODE content here>
''')

# Then run tests:
exec('''
<paste TEST_COMMUNICATION content here>
''')

# etc.
"""
