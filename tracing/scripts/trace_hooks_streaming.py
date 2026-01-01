# Klipper extra module for STREAMING runtime method tracing
#
# Part of the K2 Plus firmware reverse engineering toolkit.
# Wraps methods on Cython-compiled modules to capture call traces.
#
# Deploy to: /usr/share/klipper/klippy/extras/trace_hooks.py
# Add to printer.cfg: [trace_hooks]
#
# Created: 2024-12-30
# Updated: 2025-01-01 - Rewritten to use Klipper reactor (no threads)
# Project: Creality K2 Plus Klipper Firmware Reconstruction
#
# Commands:
#   TRACE_ALL OBJECT=<name>        - Trace public methods
#   TRACE_DEEP OBJECT=<name>       - Trace all methods including _private
#   TRACE_ATTRS OBJECT=<name>      - Trace attribute access
#   TRACE_EVERYTHING               - Trace all discovered objects
#
# Streams JSON traces over TCP (default port 9876) to trace_capture.py

import functools
import time
import json
import socket
import traceback
import sys

class TraceHooks:
    def __init__(self, config):
        self.printer = config.get_printer()
        self.gcode = self.printer.lookup_object('gcode')
        self.reactor = self.printer.get_reactor()

        # Streaming config
        self.stream_port = config.getint('stream_port', 9876)
        self.stream_clients = {}  # fd -> socket
        self.client_buffers = {}  # fd -> partial read buffer
        self.server_socket = None
        self.server_fd = None

        # Storage for traces
        self.active_traces = {}
        self.call_counter = 0

        # Discovered objects: name -> (object_instance, class)
        self.target_objects = {}

        # Attribute tracing: (object_name, class_name) -> original __getattribute__
        self.attr_traces = {}

        # Quiet methods - filtered out by default (noisy polling)
        self.quiet_methods = {
            'get_status',              # Status polling (~4x/sec)
            'get_connect_state',       # Connection status check
            'test_error',              # Error test polling
            'box_connect_state_check', # Box connection status
            'connect_state_check',     # Generic connection check
        }
        # Objects where quiet methods ARE traced (override)
        self.verbose_objects = set()

        # Register commands
        self.gcode.register_command('TRACE_ENABLE', self.cmd_TRACE_ENABLE,
            desc="Enable tracing for a method")
        self.gcode.register_command('TRACE_DISABLE', self.cmd_TRACE_DISABLE,
            desc="Disable tracing for a method")
        self.gcode.register_command('TRACE_ALL', self.cmd_TRACE_ALL,
            desc="Trace all methods of a class")
        self.gcode.register_command('TRACE_LIST', self.cmd_TRACE_LIST,
            desc="List active traces")
        self.gcode.register_command('TRACE_MODULE_INFO', self.cmd_TRACE_MODULE_INFO,
            desc="Show module classes and methods")
        self.gcode.register_command('TRACE_STREAM_START', self.cmd_TRACE_STREAM_START,
            desc="Start streaming server")
        self.gcode.register_command('TRACE_STREAM_STOP', self.cmd_TRACE_STREAM_STOP,
            desc="Stop streaming server")
        self.gcode.register_command('TRACE_STREAM_STATUS', self.cmd_TRACE_STREAM_STATUS,
            desc="Show streaming status")
        self.gcode.register_command('TRACE_DEBUG', self.cmd_TRACE_DEBUG,
            desc="Debug: show sys.modules and printer objects")
        self.gcode.register_command('TRACE_STATUS', self.cmd_TRACE_STATUS,
            desc="Show trace status")
        self.gcode.register_command('TRACE_EVERYTHING', self.cmd_TRACE_EVERYTHING,
            desc="Trace all methods on all discovered objects")
        self.gcode.register_command('TRACE_VERBOSE', self.cmd_TRACE_VERBOSE,
            desc="Enable/disable verbose mode (get_status) for an object")
        self.gcode.register_command('TRACE_QUIET', self.cmd_TRACE_QUIET,
            desc="Show/modify quiet methods list")
        self.gcode.register_command('TRACE_MACRO', self.cmd_TRACE_MACRO,
            desc="Trace a specific GCode macro")
        self.gcode.register_command('TRACE_DEEP', self.cmd_TRACE_DEEP,
            desc="Trace ALL methods including private (_) methods")
        self.gcode.register_command('TRACE_ATTRS', self.cmd_TRACE_ATTRS,
            desc="Trace attribute access on an object")

        # Running flag
        self.running = False

        # Register event handlers
        self.printer.register_event_handler("klippy:ready", self._handle_ready)
        self.printer.register_event_handler("klippy:disconnect", self._handle_disconnect)

    def _handle_ready(self):
        self._discover_objects()
        # Don't auto-start server - use TRACE_STREAM_START to enable when needed
        self._log_msg(f"TraceHooks ready. Use TRACE_STREAM_START to begin streaming on port {self.stream_port}")
        self._log_msg(f"Found {len(self.target_objects)} traceable objects")

    def _handle_disconnect(self):
        self._stop_stream_server()

    def _start_stream_server(self):
        """Start TCP server for streaming traces using reactor."""
        # Clean up first
        self._stop_stream_server()

        try:
            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            try:
                self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
            except:
                pass
            self.server_socket.setblocking(False)
            self.server_socket.bind(('0.0.0.0', self.stream_port))
            self.server_socket.listen(5)

            self.server_fd = self.server_socket.fileno()
            self.reactor.register_fd(self.server_fd, self._handle_server_read)
            self.running = True

            self._log_msg(f"Stream server started on port {self.stream_port}")
        except Exception as e:
            self._log_msg(f"Failed to start stream server: {e}")

    def _stop_stream_server(self):
        """Stop TCP server."""
        self.running = False

        # Unregister and close all client sockets
        for fd, client_sock in list(self.stream_clients.items()):
            try:
                self.reactor.unregister_fd(fd)
            except:
                pass
            try:
                client_sock.close()
            except:
                pass
        self.stream_clients.clear()
        self.client_buffers.clear()

        # Unregister and close server socket
        if self.server_fd is not None:
            try:
                self.reactor.unregister_fd(self.server_fd)
            except:
                pass
            self.server_fd = None

        if self.server_socket:
            try:
                self.server_socket.close()
            except:
                pass
            self.server_socket = None

    def _handle_server_read(self, eventtime):
        """Handle incoming connection on server socket (reactor callback)."""
        try:
            client_sock, addr = self.server_socket.accept()
            client_sock.setblocking(False)
            client_fd = client_sock.fileno()

            self.stream_clients[client_fd] = client_sock
            self.client_buffers[client_fd] = b""

            # Register client for read events (to detect disconnect)
            self.reactor.register_fd(client_fd, self._handle_client_read, client_fd)

            self._log_msg(f"Client connected from {addr}")
            self._send_to_client(client_sock, {
                'type': 'connected',
                'time': time.time(),
                'message': 'TraceHooks streaming connected',
                'active_traces': [list(k) for k in self.active_traces.keys()],
                'available_objects': list(self.target_objects.keys())
            })
        except BlockingIOError:
            pass  # No pending connections
        except Exception as e:
            self._log_msg(f"Accept error: {e}")

    def _handle_client_read(self, eventtime, client_fd):
        """Handle data from client (mainly to detect disconnect)."""
        if client_fd not in self.stream_clients:
            return
        client_sock = self.stream_clients[client_fd]
        try:
            data = client_sock.recv(1024)
            if not data:
                # Client disconnected
                self._disconnect_client(client_fd)
        except BlockingIOError:
            pass  # No data available
        except:
            self._disconnect_client(client_fd)

    def _disconnect_client(self, client_fd):
        """Clean up a disconnected client."""
        if client_fd in self.stream_clients:
            client_sock = self.stream_clients.pop(client_fd)
            self.client_buffers.pop(client_fd, None)
            try:
                self.reactor.unregister_fd(client_fd)
            except:
                pass
            try:
                client_sock.close()
            except:
                pass
            self._log_msg(f"Client disconnected (fd={client_fd})")

    def _send_to_client(self, client_sock, event):
        """Send event to a specific client."""
        try:
            event_json = json.dumps(event, default=str) + '\n'
            client_sock.sendall(event_json.encode('utf-8'))
        except:
            pass

    def _stream_event(self, event):
        """Send event to all connected clients."""
        if not self.stream_clients:
            return

        event_json = json.dumps(event, default=str) + '\n'
        event_bytes = event_json.encode('utf-8')

        dead_clients = []
        for client_fd, client_sock in self.stream_clients.items():
            try:
                client_sock.sendall(event_bytes)
            except:
                dead_clients.append(client_fd)

        for client_fd in dead_clients:
            self._disconnect_client(client_fd)

    def _discover_objects(self):
        """Find all loaded Klipper objects we can trace."""
        # Method 1: Look for objects via printer.lookup_object()
        # These are the object names as registered with Klipper
        object_names_to_try = [
            'box_wrapper', 'serial_485_wrapper', 'motor_control_wrapper',
            'filament_rack_wrapper', 'prtouch_v1_wrapper', 'prtouch_v2_wrapper',
            'prtouch_v3_wrapper', 'mymovie',
            # Also try without _wrapper suffix
            'box', 'serial_485', 'motor_control', 'filament_rack',
            'prtouch_v1', 'prtouch_v2', 'prtouch_v3',
            # Try common Klipper object names
            'prtouch', 'multi_material', 'filament_switch_sensor',
            # Low-level serial handler
            'serial_485 serial485', 'serialhdl_485',
        ]

        for name in object_names_to_try:
            try:
                obj = self.printer.lookup_object(name)
                if obj is not None:
                    cls = type(obj)
                    self.target_objects[name] = (obj, cls)
                    self._log_msg(f"Found object: {name} -> {cls.__name__}")
            except Exception:
                pass

        # Method 2: Search printer.objects dict directly
        try:
            printer_objects = self.printer.objects
            for name, obj in printer_objects.items():
                if obj is None:
                    continue
                cls = type(obj)
                cls_name = cls.__name__.lower()
                # Look for our target modules
                if any(target in cls_name or target in name.lower()
                       for target in ['box', 'motor', 'filament', 'prtouch', 'serial', 'movie']):
                    if name not in self.target_objects:
                        self.target_objects[name] = (obj, cls)
                        self._log_msg(f"Found object: {name} -> {cls.__name__}")
        except Exception as e:
            self._log_msg(f"Error searching printer.objects: {e}")

        # Method 3: Search sys.modules for the modules themselves
        for mod_name, module in list(sys.modules.items()):
            if module is None:
                continue
            mod_name_lower = mod_name.lower()
            if any(target in mod_name_lower
                   for target in ['box_wrapper', 'motor_control', 'filament_rack',
                                  'prtouch', 'serial_485', 'serialhdl', 'mymovie']):
                # Found a module, extract classes from it
                for attr_name in dir(module):
                    if attr_name.startswith('_'):
                        continue
                    attr = getattr(module, attr_name, None)
                    if isinstance(attr, type):
                        key = f"{mod_name}.{attr_name}"
                        if key not in self.target_objects:
                            # Store (None, class) - no instance, just class
                            self.target_objects[key] = (None, attr)

    def _log_msg(self, msg):
        """Log message to console."""
        self.gcode.respond_info(f"[TRACE] {msg}")

    def _create_wrapper(self, object_name, class_name, method_name, original_method):
        """Create a streaming trace wrapper for a method."""
        trace_hooks = self

        @functools.wraps(original_method)
        def wrapper(*args, **kwargs):
            # Check if this is a quiet method that should be filtered
            if method_name in trace_hooks.quiet_methods and object_name not in trace_hooks.verbose_objects:
                return original_method(*args, **kwargs)

            trace_hooks.call_counter += 1
            call_id = trace_hooks.call_counter
            start_time = time.time()

            # Format arguments
            try:
                arg_strs = []
                for i, arg in enumerate(args[1:], 1):
                    formatted = trace_hooks._format_arg(arg)
                    arg_strs.append(str(formatted) if not isinstance(formatted, str) else formatted)
                for k, v in kwargs.items():
                    formatted = trace_hooks._format_arg(v)
                    arg_strs.append(f"{k}={formatted}")
                args_formatted = ", ".join(arg_strs)
            except Exception as e:
                args_formatted = f"<error: {e}>"

            # Stream CALL event
            trace_hooks._stream_event({
                'type': 'call',
                'id': call_id,
                'time': start_time,
                'object': object_name,
                'class': class_name,
                'method': method_name,
                'args': args_formatted
            })

            try:
                result = original_method(*args, **kwargs)
                duration = time.time() - start_time

                # Stream RETURN event
                trace_hooks._stream_event({
                    'type': 'return',
                    'id': call_id,
                    'time': time.time(),
                    'object': object_name,
                    'class': class_name,
                    'method': method_name,
                    'result': trace_hooks._format_arg(result),
                    'duration_ms': duration * 1000
                })

                return result
            except Exception as e:
                duration = time.time() - start_time

                # Stream ERROR event
                trace_hooks._stream_event({
                    'type': 'error',
                    'id': call_id,
                    'time': time.time(),
                    'object': object_name,
                    'class': class_name,
                    'method': method_name,
                    'error': str(e),
                    'traceback': traceback.format_exc(),
                    'duration_ms': duration * 1000
                })
                raise

        return wrapper

    def _format_arg(self, arg, max_len=500):
        """Format an argument for streaming."""
        try:
            if arg is None:
                return None
            elif isinstance(arg, (int, float, bool)):
                return arg
            elif isinstance(arg, str):
                return arg[:max_len] + ('...' if len(arg) > max_len else '')
            elif isinstance(arg, bytes):
                return {'_bytes': arg.hex()[:max_len]}
            elif isinstance(arg, (list, tuple)):
                if len(arg) > 20:
                    return {'_type': type(arg).__name__, '_len': len(arg), '_preview': [self._format_arg(x) for x in arg[:5]]}
                return [self._format_arg(x) for x in arg]
            elif isinstance(arg, dict):
                if len(arg) > 20:
                    return {'_type': 'dict', '_len': len(arg)}
                return {str(k): self._format_arg(v) for k, v in list(arg.items())[:20]}
            else:
                result = {'_type': type(arg).__name__}
                if hasattr(arg, '__dict__'):
                    result['_attrs'] = list(arg.__dict__.keys())[:10]
                return result
        except:
            return {'_type': type(arg).__name__, '_error': 'unformattable'}

    def _enable_trace(self, object_name, method_name):
        """Enable tracing for a specific method on an object."""
        if object_name not in self.target_objects:
            # Try rediscovery
            self._discover_objects()
            if object_name not in self.target_objects:
                return False, f"Object '{object_name}' not found. Use TRACE_DEBUG to see available objects."

        obj, cls = self.target_objects[object_name]
        class_name = cls.__name__

        key = (object_name, class_name, method_name)
        if key in self.active_traces:
            return False, "Already tracing"

        if not hasattr(cls, method_name):
            return False, f"Method '{method_name}' not found in {class_name}"

        original = getattr(cls, method_name)
        wrapper = self._create_wrapper(object_name, class_name, method_name, original)

        self.active_traces[key] = original
        setattr(cls, method_name, wrapper)

        # Stream trace enabled event
        self._stream_event({
            'type': 'trace_enabled',
            'time': time.time(),
            'object': object_name,
            'class': class_name,
            'method': method_name
        })

        return True, f"Tracing {class_name}.{method_name}"

    def _disable_trace(self, object_name, method_name):
        """Disable tracing for a specific method."""
        if object_name not in self.target_objects:
            return False, f"Object '{object_name}' not found"

        obj, cls = self.target_objects[object_name]
        class_name = cls.__name__
        key = (object_name, class_name, method_name)

        if key not in self.active_traces:
            return False, "Not tracing"

        original = self.active_traces.pop(key)
        setattr(cls, method_name, original)

        self._stream_event({
            'type': 'trace_disabled',
            'time': time.time(),
            'object': object_name,
            'class': class_name,
            'method': method_name
        })

        return True, f"Stopped tracing {class_name}.{method_name}"

    def cmd_TRACE_ENABLE(self, gcmd):
        object_name = gcmd.get('OBJECT')
        method_name = gcmd.get('METHOD')

        success, msg = self._enable_trace(object_name, method_name)
        gcmd.respond_info(msg)

    def cmd_TRACE_DISABLE(self, gcmd):
        object_name = gcmd.get('OBJECT')
        method_name = gcmd.get('METHOD', None)

        if method_name:
            success, msg = self._disable_trace(object_name, method_name)
            gcmd.respond_info(msg)
        else:
            # Disable all traces for this object
            disabled = []
            for key in list(self.active_traces.keys()):
                if key[0] == object_name:
                    self._disable_trace(key[0], key[2])
                    disabled.append(key[2])
            gcmd.respond_info(f"Disabled {len(disabled)} traces")

    def cmd_TRACE_ALL(self, gcmd):
        """Trace all methods of an object: TRACE_ALL OBJECT=prtouch_v2"""
        object_name = gcmd.get('OBJECT')

        if object_name not in self.target_objects:
            self._discover_objects()
            if object_name not in self.target_objects:
                gcmd.respond_info(f"Object '{object_name}' not found. Use TRACE_DEBUG to see available objects.")
                return

        obj, cls = self.target_objects[object_name]

        enabled = []
        for name in dir(cls):
            if name.startswith('__'):
                continue
            attr = getattr(cls, name, None)
            if callable(attr) and not isinstance(attr, type):
                success, _ = self._enable_trace(object_name, name)
                if success:
                    enabled.append(name)

        gcmd.respond_info(f"Tracing {len(enabled)} methods on {cls.__name__}: {enabled[:10]}{'...' if len(enabled) > 10 else ''}")

    def cmd_TRACE_LIST(self, gcmd):
        if not self.active_traces:
            gcmd.respond_info("No active traces")
            return

        lines = ["Active traces:"]
        for obj_name, cls_name, method in self.active_traces.keys():
            lines.append(f"  {obj_name}: {cls_name}.{method}")
        gcmd.respond_info("\n".join(lines))

    def cmd_TRACE_MODULE_INFO(self, gcmd):
        """Show available objects and their methods."""
        object_name = gcmd.get('OBJECT', None)

        if not self.target_objects:
            self._discover_objects()

        if object_name is None:
            gcmd.respond_info(f"Available objects: {list(self.target_objects.keys())}")
            return

        if object_name not in self.target_objects:
            gcmd.respond_info(f"Object '{object_name}' not found")
            return

        obj, cls = self.target_objects[object_name]
        methods = [m for m in dir(cls) if not m.startswith('__') and callable(getattr(cls, m, None))]
        gcmd.respond_info(f"{cls.__name__} methods ({len(methods)}): {methods}")

    def cmd_TRACE_DEBUG(self, gcmd):
        """Debug command to show what's available."""
        lines = ["=== TRACE DEBUG ==="]

        # Show discovered objects
        lines.append(f"\nDiscovered objects ({len(self.target_objects)}):")
        for name, (obj, cls) in self.target_objects.items():
            lines.append(f"  {name}: {cls.__name__} (instance: {'yes' if obj else 'no'})")

        # Show printer.objects keys
        lines.append("\nPrinter objects (matching our targets):")
        try:
            for name in sorted(self.printer.objects.keys()):
                name_lower = name.lower()
                if any(t in name_lower for t in ['box', 'motor', 'filament', 'prtouch', 'serial', 'movie', 'rack']):
                    obj = self.printer.objects[name]
                    lines.append(f"  {name}: {type(obj).__name__ if obj else 'None'}")
        except Exception as e:
            lines.append(f"  Error: {e}")

        # Show relevant sys.modules
        lines.append("\nRelevant sys.modules:")
        for mod_name in sorted(sys.modules.keys()):
            mod_lower = mod_name.lower()
            if any(t in mod_lower for t in ['box', 'motor', 'filament', 'prtouch', 'serial', 'movie', 'rack', 'extras']):
                lines.append(f"  {mod_name}")

        gcmd.respond_info("\n".join(lines))

    def cmd_TRACE_STREAM_START(self, gcmd):
        if self.server_socket:
            gcmd.respond_info(f"Already streaming on port {self.stream_port}")
        else:
            self._start_stream_server()

    def cmd_TRACE_STREAM_STOP(self, gcmd):
        self._stop_stream_server()
        gcmd.respond_info("Stream server stopped")

    def cmd_TRACE_STREAM_STATUS(self, gcmd):
        if self.server_socket:
            with self.stream_lock:
                client_count = len(self.stream_clients)
            gcmd.respond_info(f"Streaming on port {self.stream_port}, {client_count} clients connected")
        else:
            gcmd.respond_info("Stream server not running")

    def cmd_TRACE_STATUS(self, gcmd):
        """Show overall trace status."""
        with self.stream_lock:
            client_count = len(self.stream_clients)
        gcmd.respond_info(
            f"Objects: {len(self.target_objects)}, "
            f"Active traces: {len(self.active_traces)}, "
            f"Clients: {client_count}, "
            f"Server: {'running' if self.server_socket else 'stopped'}"
        )

    def cmd_TRACE_EVERYTHING(self, gcmd):
        """Trace all methods on all discovered objects."""
        if not self.target_objects:
            self._discover_objects()

        total_enabled = 0
        objects_traced = []

        # Only trace objects with live instances (not class-only entries)
        for obj_name, (obj, cls) in self.target_objects.items():
            if obj is None:
                continue  # Skip class-only entries

            enabled = []
            for name in dir(cls):
                if name.startswith('_'):
                    continue
                attr = getattr(cls, name, None)
                if callable(attr) and not isinstance(attr, type):
                    success, _ = self._enable_trace(obj_name, name)
                    if success:
                        enabled.append(name)

            if enabled:
                total_enabled += len(enabled)
                objects_traced.append(f"{obj_name}({len(enabled)})")

        gcmd.respond_info(f"Enabled {total_enabled} traces on {len(objects_traced)} objects: {', '.join(objects_traced)}")

        # Notify clients
        self._stream_event({
            'type': 'traces_enabled',
            'total': total_enabled,
            'objects': objects_traced
        })

    def cmd_TRACE_VERBOSE(self, gcmd):
        """Enable/disable verbose mode for an object: TRACE_VERBOSE OBJECT=box [ENABLE=1/0]"""
        obj_name = gcmd.get('OBJECT', None)
        enable = gcmd.get_int('ENABLE', -1)

        if obj_name is None:
            # Show current verbose objects
            if self.verbose_objects:
                gcmd.respond_info(f"Verbose objects (get_status traced): {list(self.verbose_objects)}")
            else:
                gcmd.respond_info("No objects in verbose mode. get_status is filtered for all.")
            return

        if enable == -1:
            # Toggle
            if obj_name in self.verbose_objects:
                self.verbose_objects.remove(obj_name)
                gcmd.respond_info(f"Verbose OFF for {obj_name} - get_status will be filtered")
            else:
                self.verbose_objects.add(obj_name)
                gcmd.respond_info(f"Verbose ON for {obj_name} - get_status will be traced")
        elif enable:
            self.verbose_objects.add(obj_name)
            gcmd.respond_info(f"Verbose ON for {obj_name}")
        else:
            self.verbose_objects.discard(obj_name)
            gcmd.respond_info(f"Verbose OFF for {obj_name}")

    def cmd_TRACE_QUIET(self, gcmd):
        """Show/modify quiet methods: TRACE_QUIET [ADD=method] [REMOVE=method]"""
        add_method = gcmd.get('ADD', None)
        remove_method = gcmd.get('REMOVE', None)

        if add_method:
            self.quiet_methods.add(add_method)
            gcmd.respond_info(f"Added '{add_method}' to quiet methods")
        elif remove_method:
            self.quiet_methods.discard(remove_method)
            gcmd.respond_info(f"Removed '{remove_method}' from quiet methods")
        else:
            gcmd.respond_info(f"Quiet methods (filtered by default): {list(self.quiet_methods)}")

    def cmd_TRACE_MACRO(self, gcmd):
        """Trace a specific GCode macro: TRACE_MACRO NAME=BOX_CHECK_MATERIAL"""
        macro_name = gcmd.get('NAME', None)

        if macro_name is None:
            # List available macros
            macros = []
            try:
                for name in self.printer.objects.keys():
                    if name.startswith('gcode_macro '):
                        macros.append(name.replace('gcode_macro ', ''))
            except:
                pass
            gcmd.respond_info(f"Available macros: {macros[:20]}{'...' if len(macros) > 20 else ''}")
            gcmd.respond_info("Usage: TRACE_MACRO NAME=<macro_name>")
            return

        # Build the full object name
        object_name = f"gcode_macro {macro_name}"

        # Check if it exists in printer.objects
        try:
            obj = self.printer.lookup_object(object_name)
            if obj is None:
                gcmd.respond_info(f"Macro '{macro_name}' not found")
                return
        except:
            gcmd.respond_info(f"Macro '{macro_name}' not found")
            return

        # Add to target_objects if not already there
        if object_name not in self.target_objects:
            cls = type(obj)
            self.target_objects[object_name] = (obj, cls)

        # Enable tracing on all methods
        obj, cls = self.target_objects[object_name]
        enabled = []
        for name in dir(cls):
            if name.startswith('_'):
                continue
            attr = getattr(cls, name, None)
            if callable(attr) and not isinstance(attr, type):
                success, _ = self._enable_trace(object_name, name)
                if success:
                    enabled.append(name)

        gcmd.respond_info(f"Tracing macro '{macro_name}': {enabled}")

    def cmd_TRACE_DEEP(self, gcmd):
        """Trace ALL methods on an object including private (_) methods.

        TRACE_DEEP OBJECT=box  - Trace all methods including _private ones
        TRACE_DEEP             - Trace all methods on all objects deeply
        """
        object_name = gcmd.get('OBJECT', None)

        if not self.target_objects:
            self._discover_objects()

        if object_name:
            # Trace specific object deeply
            if object_name not in self.target_objects:
                gcmd.respond_info(f"Object '{object_name}' not found. Use TRACE_DEBUG to see available objects.")
                return

            obj, cls = self.target_objects[object_name]
            enabled = self._trace_object_deep(object_name, obj, cls)
            gcmd.respond_info(f"Deep tracing {len(enabled)} methods on {cls.__name__}")
        else:
            # Trace all objects deeply
            total_enabled = 0
            objects_traced = []

            for obj_name, (obj, cls) in self.target_objects.items():
                if obj is None:
                    continue  # Skip class-only entries

                enabled = self._trace_object_deep(obj_name, obj, cls)
                if enabled:
                    total_enabled += len(enabled)
                    objects_traced.append(f"{obj_name}({len(enabled)})")

            gcmd.respond_info(f"Deep tracing {total_enabled} methods on {len(objects_traced)} objects: {', '.join(objects_traced)}")

            self._stream_event({
                'type': 'deep_traces_enabled',
                'total': total_enabled,
                'objects': objects_traced
            })

    def _trace_object_deep(self, object_name, obj, cls):
        """Trace all methods on an object including private (_) methods."""
        enabled = []
        for name in dir(cls):
            # Skip dunder methods but INCLUDE single underscore methods
            if name.startswith('__'):
                continue

            attr = getattr(cls, name, None)
            if callable(attr) and not isinstance(attr, type):
                success, _ = self._enable_trace(object_name, name)
                if success:
                    enabled.append(name)
        return enabled

    def cmd_TRACE_ATTRS(self, gcmd):
        """Trace attribute access on an object to see what data is read.

        TRACE_ATTRS OBJECT=box ENABLE=1             - Enable attribute tracing
        TRACE_ATTRS OBJECT=box ENABLE=1 RECURSIVE=1 - Enable recursive tracing
        TRACE_ATTRS OBJECT=box ENABLE=0             - Disable attribute tracing
        TRACE_ATTRS                                  - Show objects with attribute tracing
        """
        object_name = gcmd.get('OBJECT', None)
        enable = gcmd.get_int('ENABLE', -1)
        recursive = gcmd.get_int('RECURSIVE', 0)

        if object_name is None:
            # Show current attribute traces
            if self.attr_traces:
                gcmd.respond_info(f"Attribute tracing enabled on: {list(self.attr_traces.keys())}")
            else:
                gcmd.respond_info("No attribute tracing active. Use: TRACE_ATTRS OBJECT=<name> ENABLE=1")
            return

        if object_name not in self.target_objects:
            self._discover_objects()
            if object_name not in self.target_objects:
                gcmd.respond_info(f"Object '{object_name}' not found")
                return

        obj, cls = self.target_objects[object_name]
        class_name = cls.__name__
        key = (object_name, class_name)

        if enable == 1 or (enable == -1 and key not in self.attr_traces):
            # Enable attribute tracing
            if key in self.attr_traces:
                gcmd.respond_info(f"Already tracing attributes on {object_name}")
                return

            if recursive:
                count = self._enable_recursive_attr_trace(object_name, obj, cls)
                gcmd.respond_info(f"Recursive attribute tracing enabled on {object_name} ({count} classes wrapped)")
            else:
                self._enable_single_attr_trace(object_name, cls)
                gcmd.respond_info(f"Attribute tracing enabled on {object_name}")

        elif enable == 0 or (enable == -1 and key in self.attr_traces):
            # Disable attribute tracing - remove all traces for this root object
            disabled = []
            for trace_key in list(self.attr_traces.keys()):
                if trace_key[0].startswith(object_name):
                    original_getattr, traced_cls = self.attr_traces.pop(trace_key)
                    traced_cls.__getattribute__ = original_getattr
                    disabled.append(trace_key)

            gcmd.respond_info(f"Attribute tracing disabled on {object_name} ({len(disabled)} classes)")

            self._stream_event({
                'type': 'attr_trace_disabled',
                'time': time.time(),
                'object': object_name,
                'class': class_name,
                'count': len(disabled)
            })

    def _enable_single_attr_trace(self, object_name, cls, path_prefix=""):
        """Enable attribute tracing on a single class."""
        class_name = cls.__name__
        key = (object_name, class_name)

        if key in self.attr_traces:
            return  # Already traced

        original_getattr = cls.__getattribute__
        self.attr_traces[key] = (original_getattr, cls)

        trace_hooks = self
        full_path = path_prefix if path_prefix else object_name

        def traced_getattribute(self_obj, name):
            # Skip internal attributes to avoid recursion
            if name.startswith('_') or name in ('__class__', '__dict__'):
                return original_getattr(self_obj, name)

            result = original_getattr(self_obj, name)

            # Only log data attributes, not methods
            if not callable(result):
                trace_hooks._stream_event({
                    'type': 'attr_read',
                    'time': time.time(),
                    'object': object_name,
                    'class': class_name,
                    'path': f"{full_path}.{name}",
                    'attr': name,
                    'value': trace_hooks._format_arg(result)
                })

            return result

        cls.__getattribute__ = traced_getattribute

        self._stream_event({
            'type': 'attr_trace_enabled',
            'time': time.time(),
            'object': object_name,
            'class': class_name,
            'path': full_path
        })

    def _enable_recursive_attr_trace(self, root_name, obj, cls, path="", depth=0, visited=None):
        """Recursively enable attribute tracing on an object and all its nested objects."""
        if visited is None:
            visited = set()

        # Avoid infinite recursion
        if depth > 5:
            return 0
        if id(cls) in visited:
            return 0

        visited.add(id(cls))

        class_name = cls.__name__
        key = (f"{root_name}:{class_name}", class_name)

        if key in self.attr_traces:
            return 0

        # Primitives and built-ins we don't trace
        skip_types = (str, int, float, bool, list, dict, tuple, set, type(None), bytes)
        skip_modules = ('builtins', 'typing', 'collections', 'abc')

        original_getattr = cls.__getattribute__
        self.attr_traces[key] = (original_getattr, cls)

        trace_hooks = self
        current_path = path if path else root_name
        count = 1

        def traced_getattribute(self_obj, name):
            # Skip internal attributes to avoid recursion
            if name.startswith('_') or name in ('__class__', '__dict__'):
                return original_getattr(self_obj, name)

            result = original_getattr(self_obj, name)
            attr_path = f"{current_path}.{name}"

            # Log the attribute access
            if not callable(result):
                trace_hooks._stream_event({
                    'type': 'attr_read',
                    'time': time.time(),
                    'object': root_name,
                    'class': class_name,
                    'path': attr_path,
                    'attr': name,
                    'value': trace_hooks._format_arg(result)
                })

            return result

        cls.__getattribute__ = traced_getattribute

        self._stream_event({
            'type': 'attr_trace_enabled',
            'time': time.time(),
            'object': root_name,
            'class': class_name,
            'path': current_path,
            'recursive': True
        })

        # Now recursively trace nested objects
        if obj is not None:
            for attr_name in dir(obj):
                if attr_name.startswith('_'):
                    continue
                try:
                    attr_value = getattr(obj, attr_name)
                    if callable(attr_value):
                        continue
                    if isinstance(attr_value, skip_types):
                        continue

                    attr_cls = type(attr_value)
                    module = getattr(attr_cls, '__module__', '')
                    if any(m in module for m in skip_modules):
                        continue

                    # Recursively trace this nested object
                    nested_path = f"{current_path}.{attr_name}"
                    count += self._enable_recursive_attr_trace(
                        root_name, attr_value, attr_cls,
                        nested_path, depth + 1, visited
                    )
                except:
                    pass

        return count


def load_config(config):
    return TraceHooks(config)
