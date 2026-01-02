# Klipper REPL - Interactive Python shell in running Klipper process
#
# Hybrid approach:
#   - Threading + InteractiveConsole for stable socket I/O
#   - Reactor callbacks for thread-safe Klipper interaction
#
# Add to printer.cfg:
#   [klipper_repl]
#   port: 9877
#
# Connect with:
#   socat readline tcp:k2plus:9877

import logging
import threading
import socket
import code
import sys
import io
import traceback


class ReactorConsole(code.InteractiveConsole):
    """Interactive console that executes code in the Klipper reactor thread."""

    def __init__(self, conn, reactor, locals=None):
        self.conn = conn
        self.reactor = reactor
        self._locals = locals or {}
        super().__init__(locals=self._locals)

    def write(self, data):
        """Write data to the socket."""
        if isinstance(data, str):
            data = data.encode('utf-8')
        try:
            self.conn.sendall(data)
        except:
            pass

    def raw_input(self, prompt=""):
        """Read a line from the socket."""
        self.write(prompt)
        data = b""
        while True:
            chunk = self.conn.recv(1)
            if not chunk:
                raise EOFError()
            data += chunk
            if chunk == b'\n':
                break
        line = data.decode('utf-8', errors='replace').rstrip('\r\n')
        return line

    def runsource(self, source, filename="<input>", symbol="single"):
        """Execute source code in the reactor thread."""
        # Check for incomplete input (multi-line)
        try:
            code_obj = code.compile_command(source, filename, symbol)
        except (OverflowError, SyntaxError, ValueError):
            # Syntax error - show it
            self.showsyntaxerror(filename)
            return False

        if code_obj is None:
            # Incomplete input - need more
            return True

        # Execute in reactor thread
        self._runcode_in_reactor(code_obj)
        return False

    def _runcode_in_reactor(self, code_obj):
        """Run compiled code in the reactor thread and capture output."""
        result = {'output': '', 'error': None}
        done = threading.Event()

        def _execute(eventtime):
            old_stdout = sys.stdout
            old_stderr = sys.stderr
            capture = io.StringIO()
            try:
                sys.stdout = capture
                sys.stderr = capture
                exec(code_obj, self._locals)
            except SystemExit:
                raise
            except:
                result['error'] = traceback.format_exc()
            finally:
                sys.stdout = old_stdout
                sys.stderr = old_stderr
                result['output'] = capture.getvalue()
                done.set()

        self.reactor.register_callback(_execute)

        # Wait for completion with timeout
        if not done.wait(timeout=60):
            self.write("Error: Command timed out (60s)\n")
            return

        # Write captured output
        if result['output']:
            self.write(result['output'])
        if result['error']:
            self.write(result['error'])


class KlipperRepl:
    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.config = config

        self.port = config.getint('port', 9877)

        self.server_socket = None
        self.server_thread = None
        self.clients = []
        self.running = False

        self.printer.register_event_handler('klippy:ready', self._handle_ready)
        self.printer.register_event_handler('klippy:shutdown', self._handle_shutdown)

        self.gcode.register_command('REPL_STATUS', self.cmd_REPL_STATUS,
                                    desc="Show REPL server status")

        logging.info(f"[klipper_repl] Initialized, will listen on port {self.port}")

    def _handle_ready(self):
        self._start_server()

    def _handle_shutdown(self):
        self._stop_server()

    def _start_server(self):
        if self.running:
            return

        try:
            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            try:
                self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
            except:
                pass
            self.server_socket.bind(('0.0.0.0', self.port))
            self.server_socket.listen(2)
            self.server_socket.settimeout(1.0)

            self.running = True
            self.server_thread = threading.Thread(target=self._accept_loop, daemon=True)
            self.server_thread.start()

            logging.info(f"[klipper_repl] Server started on port {self.port}")
        except Exception as e:
            logging.error(f"[klipper_repl] Failed to start server: {e}")

    def _stop_server(self):
        self.running = False

        for client in self.clients[:]:
            try:
                client.close()
            except:
                pass
        self.clients.clear()

        if self.server_socket:
            try:
                self.server_socket.close()
            except:
                pass
            self.server_socket = None

        logging.info("[klipper_repl] Server stopped")

    def _accept_loop(self):
        while self.running:
            try:
                conn, addr = self.server_socket.accept()
                logging.info(f"[klipper_repl] Client connected from {addr}")
                self.clients.append(conn)

                client_thread = threading.Thread(
                    target=self._handle_client,
                    args=(conn, addr),
                    daemon=True
                )
                client_thread.start()
            except socket.timeout:
                continue
            except Exception as e:
                if self.running:
                    logging.error(f"[klipper_repl] Accept error: {e}")
                break

    def _handle_client(self, conn, addr):
        try:
            # Build namespace with useful objects
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
                'rs': lambda: self.printer.lookup_object('serial_485 serial485'),
                'auto_addr': lambda: self.printer.lookup_object('auto_addr'),
                # Helper to run gcode safely
                'run_gcode': self._make_run_gcode(),
            }

            console = ReactorConsole(conn, self.reactor, locals=namespace)

            banner = """
Klipper REPL - Interactive Python Shell
========================================
Commands execute in the reactor thread for safety.

Available objects:
  printer, reactor, gcode, config
  lookup(name) - Lookup any printer object

Shortcuts (call as functions):
  toolhead(), extruder(), heaters()
  box(), filament_rack(), rs(), auto_addr()

Helpers:
  run_gcode("GCODE_CMD") - Run gcode and wait for completion

Type 'exit()' or Ctrl-D to disconnect.
"""
            console.interact(banner=banner, exitmsg="Goodbye!\n")

        except Exception as e:
            logging.error(f"[klipper_repl] Client error: {e}")
        finally:
            try:
                conn.close()
            except:
                pass
            if conn in self.clients:
                self.clients.remove(conn)
            logging.info(f"[klipper_repl] Client {addr} disconnected")

    def _make_run_gcode(self):
        """Create a helper function to run gcode commands."""
        def run_gcode(cmd, timeout=30):
            result = [None]
            error = [None]
            done = threading.Event()

            def _run(eventtime):
                try:
                    self.gcode.run_script(cmd)
                    result[0] = "OK"
                except Exception as e:
                    error[0] = str(e)
                done.set()

            self.reactor.register_callback(_run)
            if not done.wait(timeout=timeout):
                return "TIMEOUT"
            if error[0]:
                return f"ERROR: {error[0]}"
            return result[0]

        return run_gcode

    def cmd_REPL_STATUS(self, gcmd):
        if self.running:
            gcmd.respond_info(f"REPL server running on port {self.port}, "
                            f"{len(self.clients)} clients connected")
        else:
            gcmd.respond_info("REPL server not running")


def load_config(config):
    return KlipperRepl(config)
