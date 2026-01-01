# Klipper REPL - Interactive Python shell in running Klipper process
#
# Updated: 2025-01-01 - Rewritten to use Klipper reactor (no threads)
#
# Add to printer.cfg:
#   [klipper_repl]
#   port: 9877  # optional, default is 9877 (one above trace streaming port)
#
# Connect with:
#   nc k2plus 9877
#
# Available objects in REPL:
#   printer - the main Klipper printer object
#   reactor - the Klipper reactor
#   gcode   - gcode dispatch object
#   config  - printer config
#
# Note: This REPL processes one line at a time via reactor callbacks.
#       Multi-line statements must use semicolons or backslash continuation.

import logging
import socket
import sys
import traceback

class KlipperRepl:
    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.config = config

        # Port is one higher than trace streaming default (9876)
        self.port = config.getint('port', 9877)

        self.server_socket = None
        self.server_fd = None
        self.clients = {}  # fd -> {'socket': sock, 'addr': addr, 'buffer': b'', 'namespace': {}}
        self.running = False

        # Register for ready event
        self.printer.register_event_handler('klippy:ready', self._handle_ready)
        self.printer.register_event_handler('klippy:shutdown', self._handle_shutdown)

        # Register gcode commands
        self.gcode.register_command('REPL_STATUS', self.cmd_REPL_STATUS,
                                    desc="Show REPL server status")

        logging.info(f"[klipper_repl] Initialized, will listen on port {self.port}")

    def _handle_ready(self):
        """Start the REPL server when Klipper is ready."""
        self._start_server()

    def _handle_shutdown(self):
        """Clean up on shutdown."""
        self._stop_server()

    def _start_server(self):
        """Start the TCP server for REPL connections using reactor."""
        if self.running:
            return

        try:
            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            try:
                self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
            except:
                pass
            self.server_socket.setblocking(False)
            self.server_socket.bind(('0.0.0.0', self.port))
            self.server_socket.listen(2)

            self.server_fd = self.server_socket.fileno()
            self.reactor.register_fd(self.server_fd, self._handle_server_read)
            self.running = True

            logging.info(f"[klipper_repl] Server started on port {self.port}")
        except Exception as e:
            logging.error(f"[klipper_repl] Failed to start server: {e}")

    def _stop_server(self):
        """Stop the REPL server."""
        self.running = False

        # Close all client connections
        for fd, client_info in list(self.clients.items()):
            try:
                self.reactor.unregister_fd(fd)
            except:
                pass
            try:
                client_info['socket'].close()
            except:
                pass
        self.clients.clear()

        # Close server socket
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

        logging.info("[klipper_repl] Server stopped")

    def _handle_server_read(self, eventtime):
        """Handle incoming connection on server socket."""
        try:
            conn, addr = self.server_socket.accept()
            conn.setblocking(False)
            client_fd = conn.fileno()

            # Build namespace for this client
            namespace = {
                'printer': self.printer,
                'reactor': self.reactor,
                'gcode': self.gcode,
                'config': self.config,
                'lookup': self.printer.lookup_object,
                # Convenience shortcuts
                'toolhead': lambda: self.printer.lookup_object('toolhead'),
                'extruder': lambda: self.printer.lookup_object('extruder'),
                'heaters': lambda: self.printer.lookup_object('heaters'),
                'box': lambda: self.printer.lookup_object('box'),
                'filament_rack': lambda: self.printer.lookup_object('filament_rack'),
                'serial_485': lambda: self.printer.lookup_object('serial_485 serial485'),
                'auto_addr': lambda: self.printer.lookup_object('auto_addr'),
            }

            self.clients[client_fd] = {
                'socket': conn,
                'addr': addr,
                'buffer': b'',
                'namespace': namespace
            }

            # Register for read events
            self.reactor.register_fd(client_fd, self._handle_client_read, client_fd)

            logging.info(f"[klipper_repl] Client connected from {addr}")

            # Send banner
            banner = b"""
Klipper REPL - Interactive Python Shell
========================================
Available objects:
  printer       - Main printer object
  reactor       - Klipper reactor
  gcode         - Gcode dispatch
  config        - Printer config
  lookup(name)  - Lookup any printer object

Shortcuts (call as functions):
  toolhead(), extruder(), heaters()
  box(), filament_rack(), serial_485(), auto_addr()

Type 'exit()' or Ctrl-D to disconnect.

>>> """
            try:
                conn.sendall(banner)
            except:
                pass

        except BlockingIOError:
            pass
        except Exception as e:
            logging.error(f"[klipper_repl] Accept error: {e}")

    def _handle_client_read(self, eventtime, client_fd):
        """Handle data from a REPL client."""
        if client_fd not in self.clients:
            return

        client_info = self.clients[client_fd]
        conn = client_info['socket']

        try:
            data = conn.recv(4096)
            if not data:
                self._disconnect_client(client_fd)
                return

            # Add to buffer
            client_info['buffer'] += data

            # Process complete lines
            while b'\n' in client_info['buffer']:
                line, client_info['buffer'] = client_info['buffer'].split(b'\n', 1)
                line = line.rstrip(b'\r').decode('utf-8', errors='replace')

                if line.strip() in ('exit()', 'quit()'):
                    try:
                        conn.sendall(b"Goodbye!\n")
                    except:
                        pass
                    self._disconnect_client(client_fd)
                    return

                # Execute the line
                output = self._execute_line(line, client_info['namespace'])
                if output:
                    try:
                        conn.sendall(output.encode('utf-8'))
                    except:
                        self._disconnect_client(client_fd)
                        return

                # Send prompt
                try:
                    conn.sendall(b">>> ")
                except:
                    self._disconnect_client(client_fd)
                    return

        except BlockingIOError:
            pass
        except Exception as e:
            logging.error(f"[klipper_repl] Client read error: {e}")
            self._disconnect_client(client_fd)

    def _execute_line(self, line, namespace):
        """Execute a line of Python code and return output."""
        if not line.strip():
            return ""

        # Capture output
        import io
        old_stdout = sys.stdout
        old_stderr = sys.stderr
        capture = io.StringIO()

        try:
            sys.stdout = capture
            sys.stderr = capture

            try:
                # Try eval first (for expressions)
                result = eval(line, namespace)
                if result is not None:
                    print(repr(result))
            except SyntaxError:
                # Fall back to exec (for statements)
                exec(line, namespace)

        except Exception as e:
            traceback.print_exc()
        finally:
            sys.stdout = old_stdout
            sys.stderr = old_stderr

        return capture.getvalue()

    def _disconnect_client(self, client_fd):
        """Disconnect a client."""
        if client_fd not in self.clients:
            return

        client_info = self.clients.pop(client_fd)
        try:
            self.reactor.unregister_fd(client_fd)
        except:
            pass
        try:
            client_info['socket'].close()
        except:
            pass
        logging.info(f"[klipper_repl] Client {client_info['addr']} disconnected")

    def cmd_REPL_STATUS(self, gcmd):
        """Report REPL server status."""
        if self.running:
            gcmd.respond_info(f"REPL server running on port {self.port}, "
                            f"{len(self.clients)} clients connected")
        else:
            gcmd.respond_info("REPL server not running")


def load_config(config):
    return KlipperRepl(config)
