# rs485_sniffer.py - RS-485 traffic logger for debugging
# Logs all box-related serial traffic to /tmp/box_driver_test.log
# Enable by adding [rs485_sniffer] to printer.cfg

import time
from datetime import datetime, timezone, timedelta

_log_file = "/tmp/box_driver.log"
_tz_pst = timezone(timedelta(hours=-8))

def _log(msg):
    try:
        with open(_log_file, 'a') as f:
            f.write(f"[{datetime.now(_tz_pst).strftime('%H:%M:%S.%f')[:-3]}] {msg}\n")
    except:
        pass


class RS485Sniffer:
    def __init__(self, config):
        self.printer = config.get_printer()
        self.printer.register_event_handler("klippy:ready", self._handle_ready)
        self.original_send = None  # Will hold unfiltered send method
        _log("=" * 60)
        _log("RS485 SNIFFER - Initialized")
        _log("=" * 60)

    def _handle_ready(self):
        self._hook_serial()
        self._hook_box_methods()

    # Commands to suppress from .so polling (reduce log spam and bus contention)
    SO_POLL_COMMANDS = [
        bytes.fromhex('010300a2'),      # Hardware status query (~2s)
        bytes.fromhex('fe0500a1fefe'),  # Broadcast tracking query (~2s)
        bytes.fromhex('0103ff0a'),      # Direct tracking query (~4s)
        # Note: 0104ff0e01 (encoder) is NOT filtered - useful for debugging
    ]
    
    def direct_send(self, data, timeout=1.0):
        """Send without filtering, but still log. Used by clean driver."""
        if not self.original_send:
            _log("WARNING: direct_send called before hook, using fallback")
            return None
        data_hex = data.hex() if hasattr(data, 'hex') else str(data)
        _log(f"TX: {data_hex}")
        result = self.original_send(data, timeout)
        if result:
            _log(f"RX: {result.hex()}")
        return result
    
    def _hook_serial(self):
        """Hook RS-485 serial to log box traffic and filter .so spam."""
        try:
            serial = self.printer.lookup_object("serial_485 serial485")
            self.original_send = serial.cmd_send_data_with_response  # Save original!
            sniffer = self  # Capture for closure
            
            def logged_send(data, timeout=1.0, *args, **kwargs):
                # Filter .so polling commands
                for cmd in sniffer.SO_POLL_COMMANDS:
                    if data == cmd:
                        # Silently drop - return None (pretend no response)
                        return None
                
                data_hex = data.hex() if hasattr(data, 'hex') else str(data)
                # Only log box traffic (01, 8x, FE addresses)
                first_byte = int(data_hex[0:2], 16) if len(data_hex) >= 2 else 0
                is_box = first_byte in (0x01, 0x02, 0xFE) or (0x81 <= first_byte <= 0x88)
                if is_box:
                    _log(f"TX: {data_hex}")
                result = sniffer.original_send(data, timeout, *args, **kwargs)
                if is_box and result:
                    _log(f"RX: {result.hex()}")
                return result
            
            serial.cmd_send_data_with_response = logged_send
            _log("RS-485 serial hooked (filtering .so polls)")
        except Exception as e:
            _log(f"Failed to hook serial: {e}")

    def _hook_box_methods(self):
        """Hook box .so methods to log control flow."""
        try:
            box = self.printer.lookup_object("box", None)
            if not box:
                _log("Box object not found, skipping method hooks")
                return
            
            hooked_count = 0
            for method_name in dir(box):
                if method_name.startswith('_'):
                    continue
                if method_name in ('printer', 'gcode', 'config'):
                    continue
                try:
                    # Only hook methods from the original .so wrapper
                    from .box_wrapper import MultiColorMeterialBoxWrapper as OrigWrapper
                    attr = getattr(OrigWrapper, method_name, None)
                    if attr and callable(attr):
                        original = getattr(box, method_name)
                        def make_hook(name, orig):
                            def hooked(*args, **kwargs):
                                _log(f">>> {name}({str(args[:2])[:50]}...)")
                                result = orig(*args, **kwargs)
                                _log(f"<<< {name} done")
                                return result
                            return hooked
                        setattr(box, method_name, make_hook(method_name, original))
                        hooked_count += 1
                except:
                    pass
            _log(f"Hooked {hooked_count} .so methods")
        except Exception as e:
            _log(f"Failed to hook box methods: {e}")


def load_config(config):
    return RS485Sniffer(config)
