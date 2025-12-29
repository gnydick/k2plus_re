# Reconstructed from serial_485_wrapper.cpython-39.so
# Original: klippy/extras/serial_485_wrapper.py
# Creality K2 Series - RS-485 Serial Communication
#
# Copyright (C) Creality
# Reverse engineered by Claude Code
#
# This file may be distributed under the terms of the GNU GPLv3 license.

import logging
import threading
import os
import time
import serial
from serial import SerialException

# Constants from binary analysis
PACK_HEAD = 0xF7
TIMEOUT_MAX = 5.0
ADDR_POS = 1


class Serialhdl_485:
    """Low-level RS-485 serial handler with background receive thread."""
    
    def __init__(self, reactor, serialport, baud):
        self.reactor = reactor
        self.serialport = serialport
        self.baud = baud
        self.serial_dev = None
        self.is_connected = False
        self.lock = threading.Lock()
        self.response_callbacks = {}
        self.read_buffer = bytearray()
        self.bg_thread = None
        self.running = False
        
    def connect_uart(self):
        """Open the serial port connection."""
        logging.info("Starting serial connect")
        try:
            self.serial_dev = serial.Serial(
                port=self.serialport,
                baudrate=self.baud,
                timeout=0.1,
                write_timeout=0.1
            )
            self.is_connected = True
            self.running = True
            self._start_session()
            return True
        except (OSError, IOError) as e:
            logging.error("Unable to open serial port: %s", e)
            return False
    
    def disconnect(self):
        """Close the serial port connection."""
        self.running = False
        if self.bg_thread:
            self.bg_thread.join(timeout=1.0)
        if self.serial_dev:
            self.serial_dev.close()
            self.serial_dev = None
        self.is_connected = False
        
    def _start_session(self):
        """Start the background receive thread."""
        self.bg_thread = threading.Thread(target=self._bg_thread)
        self.bg_thread.daemon = True
        self.bg_thread.start()
        
    def _bg_thread(self):
        """Background thread for receiving serial data."""
        while self.running:
            try:
                if self.serial_dev and self.serial_dev.in_waiting:
                    data = self.serial_dev.read(self.serial_dev.in_waiting)
                    if data:
                        self._process_received(data)
                else:
                    time.sleep(0.001)
            except Exception as e:
                logging.error("Exception in serial callback: %s", e)
                time.sleep(0.1)
    
    def _process_received(self, data):
        """Process received serial data."""
        self.read_buffer.extend(data)
        # Look for complete packets (HEAD + ADDR + LEN + ... + CRC)
        while len(self.read_buffer) >= 6:
            if self.read_buffer[0] != PACK_HEAD:
                # Discard bytes until next HEAD found
                try:
                    idx = self.read_buffer.index(PACK_HEAD)
                    self.read_buffer = self.read_buffer[idx:]
                except ValueError:
                    self.read_buffer.clear()
                    break
                continue
            
            if len(self.read_buffer) < 3:
                break
                
            msg_len = self.read_buffer[2]
            packet_len = msg_len + 3  # HEAD + ADDR + LEN + data + CRC
            
            if len(self.read_buffer) < packet_len:
                break
                
            packet = bytes(self.read_buffer[:packet_len])
            self.read_buffer = self.read_buffer[packet_len:]
            
            # Call registered handler
            self.handle_default(packet)
    
    def handle_default(self, response):
        """Default response handler - dispatch to registered callbacks."""
        with self.lock:
            for callback in self.response_callbacks.values():
                try:
                    callback(response)
                except Exception as e:
                    logging.error("Exception in response callback: %s", e)
    
    def register_response(self, name, callback):
        """Register a response callback handler."""
        with self.lock:
            self.response_callbacks[name] = callback
    
    def raw_send(self, data):
        """Send data without waiting for response."""
        if not self.is_connected or not self.serial_dev:
            return False
        try:
            self.serial_dev.write(data)
            return True
        except Exception as e:
            logging.error("Send failed: %s", e)
            return False
    
    def raw_send_wait_ack(self, data, timeout=1.0):
        """Send data and wait for acknowledgment."""
        response_event = threading.Event()
        response_data = [None]
        
        def ack_handler(resp):
            response_data[0] = resp
            response_event.set()
        
        self.register_response('_temp_ack', ack_handler)
        
        if not self.raw_send(data):
            return None
            
        response_event.wait(timeout=timeout)
        
        with self.lock:
            self.response_callbacks.pop('_temp_ack', None)
            
        return response_data[0]
    
    def get_response(self, timeout=1.0):
        """Wait for and return a response."""
        response_event = threading.Event()
        response_data = [None]
        
        def resp_handler(resp):
            response_data[0] = resp
            response_event.set()
        
        self.register_response('_get_resp', resp_handler)
        response_event.wait(timeout=timeout)
        
        with self.lock:
            self.response_callbacks.pop('_get_resp', None)
            
        return response_data[0]
    
    def stats(self):
        """Return connection statistics."""
        return {
            'connected': self.is_connected,
            'port': self.serialport,
            'baud': self.baud
        }


class Serial_485_Wrapper:
    """High-level Klipper interface for RS-485 communication."""
    
    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.name = config.get_name().split()[-1]
        self.gcode = self.printer.lookup_object('gcode')
        
        # Configuration
        self.serialport = config.get('serial')
        self.baud = config.getint('baud', default=115200)
        
        logging.info("serial_485: self.name: %s", self.name)
        
        # Serial handler
        self._serial = Serialhdl_485(self.reactor, self.serialport, self.baud)
        
        # Send queue
        self.send_list = []
        self.send_list_lock = threading.Lock()
        self.response_handlers = {}
        
        # Register commands
        self.gcode.register_command(
            '485_SEND_DATA', 
            self.cmd_485_send_data,
            desc="Send raw data over RS-485"
        )
        
        # Register event handlers
        self.printer.register_event_handler('klippy:connect', self._connect)
        self.printer.register_event_handler('klippy:disconnect', self._disconnect)
        self.printer.register_event_handler('klippy:shutdown', self._shutdown)
        self.printer.register_event_handler('klippy:firmware_restart', self._firmware_restart)
    
    def _connect(self):
        """Handle Klipper connect event."""
        self._serial.connect_uart()
        self._serial.register_response('main', self.handle_callback)
    
    def _disconnect(self):
        """Handle Klipper disconnect event."""
        self._serial.disconnect()
    
    def _shutdown(self):
        """Handle Klipper shutdown event."""
        self._serial.disconnect()
    
    def _firmware_restart(self):
        """Handle firmware restart event."""
        self._disconnect()
        time.sleep(0.5)
        self._connect()
    
    def cmd_485_send_data(self, gcmd):
        """G-code command to send raw RS-485 data."""
        data_str = gcmd.get('DATA', '')
        logging.info("gcmd = %s", gcmd.get_commandline())
        
        if not data_str:
            gcmd.respond_info("No data specified")
            return
            
        try:
            # Parse hex string
            data = bytes.fromhex(data_str.replace(' ', ''))
            self._serial.raw_send(data)
            gcmd.respond_info("Sent %d bytes" % len(data))
        except Exception as e:
            gcmd.respond_info("Send error: %s" % str(e))
    
    def cmd_send_data_with_response(self, data, timeout=1.0, retry=True):
        """Send data and wait for response with optional retry."""
        logging.info("cmd_485_send_data_with_response params: %s", data.hex())
        
        max_retries = 3 if retry else 1
        for retries in range(max_retries):
            response = self._serial.raw_send_wait_ack(data, timeout)
            if response:
                logging.info("cmd[%s] get response or timeout", data.hex())
                return response
            if retries < max_retries - 1:
                logging.warning("do not get response, retries = %d, cmd = %s", 
                               retries, data.hex())
        
        logging.info("cmd_485_send_data_with_response timeout")
        return None
    
    def add_send_data(self, data):
        """Add data to the send queue."""
        with self.send_list_lock:
            self.send_list.append(data)
    
    def remove_send_data(self, data):
        """Remove data from the send queue."""
        with self.send_list_lock:
            if data in self.send_list:
                self.send_list.remove(data)
    
    def is_exist_in_send_list(self, data):
        """Check if data exists in the send queue."""
        with self.send_list_lock:
            return data in self.send_list
    
    def send_queue_process(self):
        """Process the send queue."""
        with self.send_list_lock:
            send_list_copy = self.send_list.copy()
        
        for data in send_list_copy:
            self._serial.raw_send(data)
            
    def register_response(self, name, callback):
        """Register a response handler."""
        self.response_handlers[name] = callback
    
    def handle_callback(self, response):
        """Handle received response data."""
        for handler in self.response_handlers.values():
            try:
                handler(response)
            except Exception as e:
                logging.error("Exception in handler: %s", e)


def load_config_prefix(config):
    return Serial_485_Wrapper(config)
