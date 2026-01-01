# Klipper REPL - Interactive Python shell in running Klipper process
#
# Add to printer.cfg:
#   [klipper_repl]
#   port: 9877  # optional, default is 9877 (one above trace streaming port)
#
# Connect with:
#   socat readline tcp:k2plus:9877
#   # or
#   nc k2plus 9877
#
# Available objects in REPL:
#   printer - the main Klipper printer object
#   reactor - the Klipper reactor
#   gcode   - gcode dispatch object
#   config  - printer config

import logging
import threading
import socket
import code
import sys
import io


class SocketFile:
    """File-like object that reads/writes over a socket."""

    def __init__(self, conn, mode='rw'):
        self.conn = conn
        self.mode = mode
        self.buffer = b""

    def write(self, data):
        if isinstance(data, str):
            data = data.encode('utf-8')
        try:
            self.conn.sendall(data)
        except:
            pass
        return len(data)

    def read(self, size=-1):
        if size == -1:
            return self.readline()
        data = self.conn.recv(size)
        return data.decode('utf-8') if data else ''

    def readline(self):
        data = b""
        while True:
            chunk = self.conn.recv(1)
            if not chunk:
                return ''
            data += chunk
            if chunk == b'\n':
                break
        # Strip \r if present
        if data.endswith(b'\r\n'):
            data = data[:-2] + b'\n'
        return data.decode('utf-8')

    def flush(self):
        pass

    def isatty(self):
        return True


class SocketConsole(code.InteractiveConsole):
    """Interactive console that reads/writes over a socket."""

    def __init__(self, conn, locals=None):
        self.conn = conn
        self.sockfile = SocketFile(conn)
        super().__init__(locals=locals)

    def raw_input(self, prompt=""):
        self.sockfile.write(prompt)
        line = self.sockfile.readline()
        if not line:
            raise EOFError()
        return line.rstrip('\n\r')

    def write(self, data):
        self.sockfile.write(data)


class KlipperRepl:
    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.config = config

        # Port is one higher than trace streaming default (9876)
        self.port = config.getint('port', 9877)

        self.server_socket = None
        self.server_thread = None
        self.clients = []
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
        """Start the TCP server for REPL connections."""
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
        """Stop the REPL server."""
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
        """Accept incoming connections."""
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
        """Handle a single client connection with an interactive console."""
        # Save original stdout/stderr
        old_stdout = sys.stdout
        old_stderr = sys.stderr

        try:
            # Build the namespace with useful objects
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

            console = SocketConsole(conn, locals=namespace)

            # Redirect stdout/stderr to socket for this thread
            sys.stdout = console.sockfile
            sys.stderr = console.sockfile

            banner = """
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
"""
            console.interact(banner=banner, exitmsg="Goodbye!\n")

        except Exception as e:
            logging.error(f"[klipper_repl] Client error: {e}")
        finally:
            # Restore stdout/stderr
            sys.stdout = old_stdout
            sys.stderr = old_stderr
            try:
                conn.close()
            except:
                pass
            if conn in self.clients:
                self.clients.remove(conn)
            logging.info(f"[klipper_repl] Client {addr} disconnected")

    def cmd_REPL_STATUS(self, gcmd):
        """Report REPL server status."""
        if self.running:
            gcmd.respond_info(f"REPL server running on port {self.port}, "
                            f"{len(self.clients)} clients connected")
        else:
            gcmd.respond_info("REPL server not running")


def load_config(config):
    return KlipperRepl(config)
