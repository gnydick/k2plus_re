"""
serial_485_wrapper - Reconstructed from live introspection and trace analysis

Protocol reconstructed from trace captures showing RS-485 communication.

Request format:  [addr][len][cmd][data...]
Response format: [0xF7][addr][len_lo][len_hi][cmd][data...][checksum]

Generated from: /usr/share/klipper/klippy/extras/serial_485_wrapper.cpython-39.so
Enhanced with: Trace capture analysis (2024-12-30)

SIGNATURE SOURCE: Live introspection (ACCURATE)
IMPLEMENTATION: Partially reconstructed from traces
"""

import logging
import threading
import time
import struct


# Protocol constants (verified from traces)
PACKET_HEADER = 0xF7
ADDR_POS = 1
LEN_POS = 2
STATE_POS = 3
CMD_POS = 4
DATA_POS = 5
HEAD_POS = 0
TIMEOUT_MAX = 3600

# Default message templates
DefaultMessages_485 = {'#addr': 0}


class Serial_485_Wrapper(object):
    """
    RS-485 serial communication wrapper for K2 Plus printer.

    Handles communication with external peripherals (motors, box, etc.)
    via RS-485 serial bus.

    Protocol (from trace analysis):
    - Request: [addr][len][cmd][data...]
    - Response: [0xF7][addr][len_lo][len_hi][cmd][data...][checksum]

    Example exchange:
    - Send: 0203ff0a (addr=2, len=3, cmd=0xFF, data=0x0A)
    - Recv: f70207000a182700004c (header, addr=2, len=7, cmd=0x0A, data..., checksum)
    """

    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')

        # Serial handler
        self.serial = None
        self.serialport = config.get('serial', '/dev/ttyS1')
        self.baud = config.getint('baud', 115200)

        # Send queue management
        self.send_queue = []
        self.send_queue_lock = threading.Lock()

        # Response callbacks
        self.response_callbacks = {}

        # State
        self.is_connected = False

        # Register event handlers
        self.printer.register_event_handler("klippy:connect", self._connect)
        self.printer.register_event_handler("klippy:disconnect", self._disconnect)
        self.printer.register_event_handler("klippy:shutdown", self._shutdown)
        self.printer.register_event_handler("klippy:firmware_restart", self._firmware_restart)

        # Register gcode command
        self.gcode.register_command('485_SEND_DATA', self.cmd_485_send_data,
            desc="Send data over RS-485 bus")

    def add_send_data(self, data, timeout, addr_marker, cmd_marker, wait_response=True):
        """
        Add data to the send queue.

        From trace:
            add_send_data({'_bytes': '0203ff0a'}, 3600, #addr_2, #cmd_10, True)

        Args:
            data: Bytes to send (dict with '_bytes' key or bytes)
            timeout: Timeout in seconds
            addr_marker: Address marker string (e.g., '#addr_2')
            cmd_marker: Command marker string (e.g., '#cmd_10')
            wait_response: Whether to wait for response
        """
        with self.send_queue_lock:
            entry = [data, timeout, addr_marker, cmd_marker, wait_response]
            self.send_queue.append(entry)

    def remove_send_data(self, args):
        """
        Remove data from the send queue.

        From trace:
            remove_send_data([{'_bytes': '0203ff0a'}, 3600, '#addr_2', '#cmd_10', True])

        Args:
            args: List matching the entry to remove
        """
        with self.send_queue_lock:
            # Find and remove matching entry
            for i, entry in enumerate(self.send_queue):
                if self._entries_match(entry, args):
                    self.send_queue.pop(i)
                    return

    def _entries_match(self, entry, args):
        """Check if queue entry matches args."""
        if len(entry) != len(args):
            return False
        # Compare data bytes
        if isinstance(entry[0], dict) and isinstance(args[0], dict):
            if entry[0].get('_bytes') != args[0].get('_bytes'):
                return False
        elif entry[0] != args[0]:
            return False
        # Compare timeout and markers
        return entry[1:] == args[1:]

    def cmd_send_data_with_response(self, data, timeout, retries_en=True):
        """
        Send data and wait for response.

        From trace:
            cmd_send_data_with_response({'_bytes': '0203ff0a'}, 3600)
            -> {'_bytes': 'f70207000a182700004c'}

        Args:
            data: Bytes to send (dict with '_bytes' key or bytes)
            timeout: Timeout in seconds
            retries_en: Enable retries on failure

        Returns:
            Response bytes as dict {'_bytes': 'hex_string'}
        """
        # Extract bytes from data
        if isinstance(data, dict) and '_bytes' in data:
            send_bytes = bytes.fromhex(data['_bytes'])
        elif isinstance(data, bytes):
            send_bytes = data
        else:
            send_bytes = bytes(data)

        # Parse address and command from send data
        if len(send_bytes) >= 3:
            addr = send_bytes[0]
            cmd = send_bytes[2] if len(send_bytes) > 2 else 0
            addr_marker = f'#addr_{addr}'
            cmd_marker = f'#cmd_{cmd}'
        else:
            addr_marker = '#addr_0'
            cmd_marker = '#cmd_0'

        # Add to queue
        self.add_send_data(data, timeout, addr_marker, cmd_marker, True)

        try:
            # Send via serial handler
            if self.serial:
                response = self.serial.get_response(
                    send_bytes, timeout,
                    addr_marker, cmd_marker,
                    retries_en
                )
                if response:
                    return {'_bytes': response.hex()}
        finally:
            # Remove from queue
            self.remove_send_data([data, timeout, addr_marker, cmd_marker, True])

        return None

    def cmd_485_send_data(self, gcmd):
        """GCode command to send RS-485 data."""
        data_hex = gcmd.get('DATA', '')
        timeout = gcmd.get_float('TIMEOUT', 1.0)

        if not data_hex:
            gcmd.respond_info("Usage: 485_SEND_DATA DATA=<hex> [TIMEOUT=<seconds>]")
            return

        try:
            response = self.cmd_send_data_with_response(
                {'_bytes': data_hex}, timeout
            )
            if response:
                gcmd.respond_info(f"Response: {response['_bytes']}")
            else:
                gcmd.respond_info("No response")
        except Exception as e:
            gcmd.respond_info(f"Error: {e}")

    def handle_callback(self, params):
        """Handle incoming data callback from serial."""
        # Parse response
        if not params or len(params) < 5:
            return

        addr = params[ADDR_POS]
        cmd = params[CMD_POS]

        # Look up registered callback
        key = (addr, cmd)
        if key in self.response_callbacks:
            callback = self.response_callbacks[key]
            callback(params)

    def is_exist_in_send_list(self, data, timeout):
        """Check if data is already in send queue."""
        with self.send_queue_lock:
            for entry in self.send_queue:
                if isinstance(entry[0], dict) and isinstance(data, dict):
                    if entry[0].get('_bytes') == data.get('_bytes'):
                        return True
                elif entry[0] == data:
                    return True
        return False

    def register_response(self, cb, notifications_addr, notifications_cmd):
        """
        Register callback for specific address/command responses.

        Args:
            cb: Callback function
            notifications_addr: Address to listen for
            notifications_cmd: Command to listen for
        """
        key = (notifications_addr, notifications_cmd)
        self.response_callbacks[key] = cb

    def send_queue_process(self, eventtime):
        """Process pending items in send queue."""
        with self.send_queue_lock:
            if not self.send_queue:
                return eventtime + 0.1

            # Process first item
            entry = self.send_queue[0]
            data, timeout, addr_marker, cmd_marker, wait = entry

            # Send data
            if self.serial:
                if isinstance(data, dict) and '_bytes' in data:
                    send_bytes = bytes.fromhex(data['_bytes'])
                else:
                    send_bytes = bytes(data)

                self.serial.raw_send(send_bytes)

        return eventtime + 0.01

    def _connect(self):
        """Initialize serial connection."""
        self.serial = Serialhdl_485(self.reactor)
        self.serial.connect_uart(self.serialport, self.baud)
        self.serial.register_response(self.handle_callback, None, None)
        self.is_connected = True

        # Start queue processor
        self.reactor.register_timer(self.send_queue_process, self.reactor.NOW)

    def _disconnect(self):
        """Disconnect serial."""
        self.is_connected = False
        if self.serial:
            self.serial.disconnect()
            self.serial = None

    def _firmware_restart(self):
        """Handle firmware restart."""
        self._disconnect()

    def _shutdown(self):
        """Handle shutdown."""
        self._disconnect()


class Serialhdl_485(object):
    """
    Low-level RS-485 serial handler.

    Manages the actual serial port communication in a background thread.
    """

    def __init__(self, reactor, warn_prefix=''):
        self.reactor = reactor
        self.warn_prefix = warn_prefix

        self.serial_dev = None
        self.serial_fd = None
        self.is_connected = False

        # Response handling
        self.pending_responses = {}
        self.response_callbacks = {}
        self.response_lock = threading.Lock()
        self.response_condition = threading.Condition(self.response_lock)

        # Background thread
        self.bg_thread = None
        self.running = False

        # Buffer for incoming data
        self.read_buffer = bytearray()

    def connect_uart(self, serialport, baud, rts=True):
        """
        Connect to UART serial port.

        Args:
            serialport: Path to serial device (e.g., '/dev/ttyS1')
            baud: Baud rate
            rts: Enable RTS flow control
        """
        import serial

        self.serial_dev = serial.Serial(
            port=serialport,
            baudrate=baud,
            timeout=0.1,
            rtscts=rts
        )
        self.is_connected = True

        # Start background reader thread
        self.running = True
        self.bg_thread = threading.Thread(target=self._bg_thread, daemon=True)
        self.bg_thread.start()

    def disconnect(self):
        """Disconnect from serial port."""
        self.running = False
        self.is_connected = False

        if self.bg_thread:
            self.bg_thread.join(timeout=1.0)
            self.bg_thread = None

        if self.serial_dev:
            self.serial_dev.close()
            self.serial_dev = None

    def raw_send(self, cmd):
        """
        Send raw bytes over serial.

        Args:
            cmd: Bytes to send
        """
        if self.serial_dev and self.is_connected:
            self.serial_dev.write(cmd)
            self.serial_dev.flush()

    def raw_send_wait_ack(self, cmd, notifications, timeout):
        """Send data and wait for acknowledgment."""
        self.raw_send(cmd)
        # Wait for response matching notifications
        return self._wait_response(notifications, timeout)

    def get_response(self, cmd, timeout, notifications_addr, notifications_cmd, retries_en=True):
        """
        Send command and get response.

        Args:
            cmd: Command bytes to send
            timeout: Timeout in seconds
            notifications_addr: Expected response address
            notifications_cmd: Expected response command
            retries_en: Enable retries

        Returns:
            Response bytes or None
        """
        max_retries = 3 if retries_en else 1

        for attempt in range(max_retries):
            self.raw_send(cmd)

            response = self._wait_response(
                (notifications_addr, notifications_cmd),
                timeout
            )

            if response:
                return response

        return None

    def _wait_response(self, notifications, timeout):
        """Wait for response matching notifications."""
        deadline = time.time() + timeout

        with self.response_condition:
            while time.time() < deadline:
                # Check if we have a matching response
                if notifications in self.pending_responses:
                    return self.pending_responses.pop(notifications)

                # Wait for new data
                remaining = deadline - time.time()
                if remaining > 0:
                    self.response_condition.wait(timeout=min(remaining, 0.1))

        return None

    def register_response(self, callback, notifications_addr, notifications_cmd):
        """Register callback for responses."""
        key = (notifications_addr, notifications_cmd)
        self.response_callbacks[key] = callback

    def handle_default(self, params):
        """Default handler for incoming data."""
        pass

    def stats(self, eventtime):
        """Return statistics."""
        return False, ''

    def _bg_thread(self):
        """Background thread for reading serial data."""
        while self.running:
            try:
                if self.serial_dev and self.serial_dev.in_waiting:
                    data = self.serial_dev.read(self.serial_dev.in_waiting)
                    self._process_incoming(data)
                else:
                    time.sleep(0.001)
            except Exception as e:
                if self.running:
                    logging.error(f"Serial read error: {e}")
                    time.sleep(0.1)

    def _process_incoming(self, data):
        """
        Process incoming serial data.

        Response format: [0xF7][addr][len_lo][len_hi][cmd][data...][checksum]
        """
        self.read_buffer.extend(data)

        # Look for complete packets
        while len(self.read_buffer) >= 5:
            # Look for header
            if self.read_buffer[0] != PACKET_HEADER:
                self.read_buffer.pop(0)
                continue

            # Parse length
            if len(self.read_buffer) < 4:
                break

            length = self.read_buffer[LEN_POS] | (self.read_buffer[LEN_POS + 1] << 8)

            # Calculate total packet size (header + addr + len(2) + payload + checksum)
            total_len = 1 + 1 + 2 + length + 1

            if len(self.read_buffer) < total_len:
                break

            # Extract packet
            packet = bytes(self.read_buffer[:total_len])
            self.read_buffer = self.read_buffer[total_len:]

            # Parse packet
            addr = packet[ADDR_POS]
            cmd = packet[CMD_POS] if len(packet) > CMD_POS else 0

            # Notify waiting threads
            with self.response_condition:
                key = (f'#addr_{addr}', f'#cmd_{cmd}')
                self.pending_responses[key] = packet
                self.response_condition.notify_all()

            # Call registered callbacks
            if (addr, cmd) in self.response_callbacks:
                self.response_callbacks[(addr, cmd)](packet)
            elif (None, None) in self.response_callbacks:
                self.response_callbacks[(None, None)](packet)

    def _start_session(self, serial_dev, serial_fd_type="b'u'"):
        """Start a new serial session."""
        self.serial_dev = serial_dev


class error(Exception):
    """Exception class for module errors."""
    pass


def load_config_prefix(config):
    """Load serial_485 with config prefix (e.g., [serial_485 serial485])."""
    return Serial_485_Wrapper(config)
