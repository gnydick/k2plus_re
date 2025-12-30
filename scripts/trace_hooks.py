# Klipper extra module for runtime method tracing
# Deploy to: /usr/share/klipper/klippy/extras/trace_hooks.py
# Add to printer.cfg: [trace_hooks]
#
# G-code commands:
#   TRACE_ENABLE MODULE=<module> CLASS=<class> [METHOD=<method>]
#   TRACE_DISABLE MODULE=<module> CLASS=<class> [METHOD=<method>]
#   TRACE_LIST - Show all active traces
#   TRACE_DUMP - Dump captured call log to file
#   TRACE_CLEAR - Clear captured call log

import functools
import time
import json
import os
import traceback
import inspect

class TraceHooks:
    def __init__(self, config):
        self.printer = config.get_printer()
        self.gcode = self.printer.lookup_object('gcode')
        self.reactor = self.printer.get_reactor()

        # Storage for traces
        self.active_traces = {}  # (module, class, method) -> original_method
        self.call_log = []
        self.max_log_entries = 10000
        self.log_to_console = True
        self.log_file = config.get('log_file', '/tmp/trace_hooks.log')

        # Target modules to trace
        self.target_modules = {}

        # Register commands
        self.gcode.register_command('TRACE_ENABLE', self.cmd_TRACE_ENABLE,
            desc="Enable tracing for a method")
        self.gcode.register_command('TRACE_DISABLE', self.cmd_TRACE_DISABLE,
            desc="Disable tracing for a method")
        self.gcode.register_command('TRACE_LIST', self.cmd_TRACE_LIST,
            desc="List active traces")
        self.gcode.register_command('TRACE_DUMP', self.cmd_TRACE_DUMP,
            desc="Dump call log to file")
        self.gcode.register_command('TRACE_CLEAR', self.cmd_TRACE_CLEAR,
            desc="Clear call log")
        self.gcode.register_command('TRACE_MODULE_INFO', self.cmd_TRACE_MODULE_INFO,
            desc="Show module classes and methods")
        self.gcode.register_command('TRACE_ALL', self.cmd_TRACE_ALL,
            desc="Trace all methods of a class")

        # Register event handlers
        self.printer.register_event_handler("klippy:ready", self._handle_ready)

    def _handle_ready(self):
        """Called when Klipper is ready - discover available modules."""
        self._discover_modules()
        self._log_msg("TraceHooks ready. Use TRACE_MODULE_INFO to see available targets.")

    def _discover_modules(self):
        """Find all loaded extras modules we can trace."""
        import sys

        # Modules we're interested in tracing
        target_names = [
            'box_wrapper', 'serial_485_wrapper', 'motor_control_wrapper',
            'filament_rack_wrapper', 'prtouch_v1_wrapper', 'prtouch_v2_wrapper',
            'prtouch_v3_wrapper', 'mymovie'
        ]

        for name in target_names:
            # Try to find module in sys.modules
            for key in sys.modules:
                if name in key:
                    self.target_modules[name] = sys.modules[key]
                    break

            # Also try extras namespace
            try:
                if f'extras.{name}' in sys.modules:
                    self.target_modules[name] = sys.modules[f'extras.{name}']
            except:
                pass

    def _log_msg(self, msg):
        """Log message to console and/or file."""
        timestamp = time.strftime("%H:%M:%S")
        full_msg = f"[TRACE {timestamp}] {msg}"

        if self.log_to_console:
            self.gcode.respond_info(full_msg)

        try:
            with open(self.log_file, 'a') as f:
                f.write(full_msg + '\n')
        except:
            pass

    def _create_wrapper(self, module_name, class_name, method_name, original_method):
        """Create a tracing wrapper for a method."""
        trace_hooks = self

        @functools.wraps(original_method)
        def wrapper(*args, **kwargs):
            call_id = len(trace_hooks.call_log)
            start_time = time.time()

            # Format arguments (skip self)
            try:
                arg_strs = []
                for i, arg in enumerate(args[1:], 1):  # Skip self
                    arg_strs.append(trace_hooks._format_arg(arg))
                for k, v in kwargs.items():
                    arg_strs.append(f"{k}={trace_hooks._format_arg(v)}")
                args_formatted = ", ".join(arg_strs)
            except Exception as e:
                args_formatted = f"<error formatting args: {e}>"

            trace_hooks._log_msg(f"CALL #{call_id}: {class_name}.{method_name}({args_formatted})")

            # Capture call info
            call_info = {
                'id': call_id,
                'time': start_time,
                'module': module_name,
                'class': class_name,
                'method': method_name,
                'args': args_formatted,
                'result': None,
                'error': None,
                'duration': None
            }

            try:
                result = original_method(*args, **kwargs)
                call_info['result'] = trace_hooks._format_arg(result)
                call_info['duration'] = time.time() - start_time

                trace_hooks._log_msg(f"RETURN #{call_id}: {trace_hooks._format_arg(result)} ({call_info['duration']*1000:.2f}ms)")

                return result
            except Exception as e:
                call_info['error'] = str(e)
                call_info['traceback'] = traceback.format_exc()
                call_info['duration'] = time.time() - start_time

                trace_hooks._log_msg(f"ERROR #{call_id}: {e}")
                raise
            finally:
                if len(trace_hooks.call_log) < trace_hooks.max_log_entries:
                    trace_hooks.call_log.append(call_info)

        return wrapper

    def _format_arg(self, arg, max_len=200):
        """Format an argument for logging."""
        try:
            if arg is None:
                return "None"
            elif isinstance(arg, (int, float, bool)):
                return str(arg)
            elif isinstance(arg, str):
                if len(arg) > max_len:
                    return f"'{arg[:max_len]}...'"
                return f"'{arg}'"
            elif isinstance(arg, bytes):
                if len(arg) > 50:
                    return f"<bytes len={len(arg)} {arg[:50].hex()}...>"
                return f"<bytes {arg.hex()}>"
            elif isinstance(arg, (list, tuple)):
                if len(arg) > 10:
                    return f"<{type(arg).__name__} len={len(arg)}>"
                return str(arg)[:max_len]
            elif isinstance(arg, dict):
                if len(arg) > 10:
                    return f"<dict len={len(arg)}>"
                return str(arg)[:max_len]
            else:
                return f"<{type(arg).__name__}>"
        except:
            return "<unformattable>"

    def _get_class_from_module(self, module, class_name):
        """Get a class object from a module."""
        if hasattr(module, class_name):
            return getattr(module, class_name)
        return None

    def _enable_trace(self, module_name, class_name, method_name):
        """Enable tracing for a specific method."""
        key = (module_name, class_name, method_name)

        if key in self.active_traces:
            return False, "Already tracing"

        if module_name not in self.target_modules:
            self._discover_modules()
            if module_name not in self.target_modules:
                return False, f"Module '{module_name}' not found"

        module = self.target_modules[module_name]
        cls = self._get_class_from_module(module, class_name)

        if cls is None:
            return False, f"Class '{class_name}' not found in {module_name}"

        if not hasattr(cls, method_name):
            return False, f"Method '{method_name}' not found in {class_name}"

        original = getattr(cls, method_name)
        wrapper = self._create_wrapper(module_name, class_name, method_name, original)

        self.active_traces[key] = original
        setattr(cls, method_name, wrapper)

        return True, f"Tracing {class_name}.{method_name}"

    def _disable_trace(self, module_name, class_name, method_name):
        """Disable tracing for a specific method."""
        key = (module_name, class_name, method_name)

        if key not in self.active_traces:
            return False, "Not currently tracing"

        module = self.target_modules[module_name]
        cls = self._get_class_from_module(module, class_name)

        original = self.active_traces.pop(key)
        setattr(cls, method_name, original)

        return True, f"Stopped tracing {class_name}.{method_name}"

    def cmd_TRACE_ENABLE(self, gcmd):
        """Enable tracing: TRACE_ENABLE MODULE=box_wrapper CLASS=BoxAction METHOD=send"""
        module_name = gcmd.get('MODULE')
        class_name = gcmd.get('CLASS')
        method_name = gcmd.get('METHOD', None)

        if method_name:
            success, msg = self._enable_trace(module_name, class_name, method_name)
            gcmd.respond_info(msg)
        else:
            gcmd.respond_info("METHOD parameter required. Use TRACE_ALL to trace all methods.")

    def cmd_TRACE_DISABLE(self, gcmd):
        """Disable tracing: TRACE_DISABLE MODULE=box_wrapper CLASS=BoxAction METHOD=send"""
        module_name = gcmd.get('MODULE')
        class_name = gcmd.get('CLASS')
        method_name = gcmd.get('METHOD', None)

        if method_name:
            success, msg = self._disable_trace(module_name, class_name, method_name)
            gcmd.respond_info(msg)
        else:
            # Disable all traces for this class
            disabled = []
            for key in list(self.active_traces.keys()):
                if key[0] == module_name and key[1] == class_name:
                    self._disable_trace(*key)
                    disabled.append(key[2])
            gcmd.respond_info(f"Disabled {len(disabled)} traces: {disabled}")

    def cmd_TRACE_ALL(self, gcmd):
        """Trace all methods of a class: TRACE_ALL MODULE=box_wrapper CLASS=BoxAction"""
        module_name = gcmd.get('MODULE')
        class_name = gcmd.get('CLASS')

        if module_name not in self.target_modules:
            self._discover_modules()
            if module_name not in self.target_modules:
                gcmd.respond_info(f"Module '{module_name}' not found")
                return

        module = self.target_modules[module_name]
        cls = self._get_class_from_module(module, class_name)

        if cls is None:
            gcmd.respond_info(f"Class '{class_name}' not found")
            return

        enabled = []
        for name in dir(cls):
            if name.startswith('_'):
                continue
            attr = getattr(cls, name, None)
            if callable(attr):
                success, _ = self._enable_trace(module_name, class_name, name)
                if success:
                    enabled.append(name)

        gcmd.respond_info(f"Enabled tracing for {len(enabled)} methods: {enabled}")

    def cmd_TRACE_LIST(self, gcmd):
        """List active traces."""
        if not self.active_traces:
            gcmd.respond_info("No active traces")
            return

        lines = ["Active traces:"]
        for module, cls, method in self.active_traces.keys():
            lines.append(f"  {module}.{cls}.{method}")
        gcmd.respond_info("\n".join(lines))

    def cmd_TRACE_DUMP(self, gcmd):
        """Dump call log to JSON file."""
        filename = gcmd.get('FILE', '/tmp/trace_dump.json')

        with open(filename, 'w') as f:
            json.dump(self.call_log, f, indent=2, default=str)

        gcmd.respond_info(f"Dumped {len(self.call_log)} calls to {filename}")

    def cmd_TRACE_CLEAR(self, gcmd):
        """Clear call log."""
        count = len(self.call_log)
        self.call_log = []
        gcmd.respond_info(f"Cleared {count} log entries")

    def cmd_TRACE_MODULE_INFO(self, gcmd):
        """Show module classes and methods."""
        module_name = gcmd.get('MODULE', None)

        if module_name is None:
            # List all available modules
            self._discover_modules()
            gcmd.respond_info(f"Available modules: {list(self.target_modules.keys())}")
            return

        if module_name not in self.target_modules:
            self._discover_modules()
            if module_name not in self.target_modules:
                gcmd.respond_info(f"Module '{module_name}' not found")
                return

        module = self.target_modules[module_name]
        lines = [f"Module: {module_name}"]

        for name in dir(module):
            if name.startswith('_'):
                continue
            attr = getattr(module, name, None)
            if isinstance(attr, type):
                methods = [m for m in dir(attr) if not m.startswith('_') and callable(getattr(attr, m, None))]
                lines.append(f"  class {name}: {len(methods)} methods")
                for m in methods[:20]:  # Limit output
                    lines.append(f"    .{m}")
                if len(methods) > 20:
                    lines.append(f"    ... and {len(methods)-20} more")

        gcmd.respond_info("\n".join(lines))


def load_config(config):
    return TraceHooks(config)
