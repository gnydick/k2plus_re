# box_protocol.py - Clean RS-485 Driver for Creality K2 AMS Box
# Pure protocol implementation - no Klipper dependencies.

# Protocol constants
CRC_POLY = 0x07
BOX_ADDR = 0x01
TRACKING_ACTIVE_FLAG = 0x02


def crc8(data, poly=CRC_POLY, init=0x00):
    crc = init
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x80:
                crc = (crc << 1) ^ poly
            else:
                crc <<= 1
            crc &= 0xFF
    return crc


class CleanBoxDriver:
    """Driver for direct RS-485 commands."""
    
    def __init__(self, serial_485, addr=BOX_ADDR, logger=None, printer=None):
        self.serial = serial_485
        self.addr = addr
        self._logger = logger
        self._printer = printer
        self._send_fn = None  # Will be set lazily on first send
        self._send_fn_checked = False
    
    def _log(self, msg):
        if self._logger:
            self._logger(msg)

    def _send(self, *payload_bytes, timeout=1.0):
        """Send command and get response."""
        packet = bytes([self.addr] + list(payload_bytes))
        
        # Lazy lookup of sniffer's direct_send (once)
        if not self._send_fn_checked and self._printer:
            self._send_fn_checked = True
            try:
                sniffer = self._printer.lookup_object("rs485_sniffer")
                if sniffer.original_send:
                    self._send_fn = sniffer.direct_send
                    self._log("Using sniffer's direct_send (bypasses .so filter)")
            except:
                pass  # No sniffer, use regular send
        
        # Use direct send function if available (bypasses .so filter)
        if self._send_fn:
            response = self._send_fn(packet, timeout)
        else:
            self._log(f"CLEAN TX: {packet.hex()}")
            response = self.serial.cmd_send_data_with_response(packet, timeout)
            if response:
                self._log(f"CLEAN RX: {response.hex()}")
            else:
                self._log(f"CLEAN RX: None")
        return response
    
    def _slot_to_byte(self, slot):
        """Convert slot (0-3) to protocol byte (bitmask: 1,2,4,8)."""
        return 1 << slot
    
    def _byte_to_slot(self, byte):
        """Convert protocol byte to slot. Returns -1 if none, None if invalid."""
        if byte == 0:
            return -1
        for i in range(4):
            if byte == (1 << i):
                return i
        return None
    
    def begin_session(self):
        """Begin command session with box."""
        return self._send(0x05, 0xff, 0x04, 0x00, 0x01)
    
    def finalize_session(self, slot=0):
        """Finalize session and activate tracking for slot.
        
        Packet: 0105ff04[SLOT_BYTE]00 where SLOT_BYTE = 1<<slot
        This clears error state AND activates position tracking for the specified slot.
        """
        return self._send(0x05, 0xff, 0x04, self._slot_to_byte(slot), 0x00)
    
    def set_mode_load(self):
        """Set load mode (for loading filament)."""
        return self._send(0x04, 0xff, 0x0f, 0x01)
    
    def set_mode_unload(self):
        """Set unload mode (for unloading filament)."""
        return self._send(0x04, 0xff, 0x08, 0x01)
    
    def clear_mode(self):
        """Clear mode."""
        return self._send(0x04, 0xff, 0x0f, 0x00)
    
    def get_state(self):
        """Get current state."""
        return self._send(0x04, 0xff, 0x08, 0x00)
    
    def load_stage(self, slot, stage, timeout=1.0):
        """Send load stage command.
        
        Packet format: 0x06 0xff 0x10 [SLOT_BYTE] [stage] 0x00
        - Slot 0 = 0x01, Slot 1 = 0x02, Slot 2 = 0x04, Slot 3 = 0x08 (bitmask!)
        - Stage 7 uses 0x03 as final byte instead of 0x00
        
        Note: Stages 0/4 may take longer if box is auto-unloading another slot.
        """
        slot_byte = self._slot_to_byte(slot)
        if stage == 7:
            return self._send(0x06, 0xff, 0x10, slot_byte, stage, 0x03, timeout=timeout)
        else:
            return self._send(0x06, 0xff, 0x10, slot_byte, stage, 0x00, timeout=timeout)
    
    def unload_slot(self, slot, slot_motor=False, timeout=1.0):
        """Unload/retract filament from slot.
        
        Packet: 0105ff11[SLOT_BYTE][MOTOR] where SLOT_BYTE = 1<<slot
        MOTOR byte:
          0x00 = Hub motor - gives buffer slack (so extruder can retract into it)
          0x01 = Slot motor - full retraction back into slot
        
        Typical sequence: hub motor (0x00) while extruder retracts, then slot motor (0x01).
        Note: Slot motor has 40s internal timeout, use timeout=45.0.
        """
        motor_byte = 0x01 if slot_motor else 0x00
        return self._send(0x05, 0xff, 0x11, self._slot_to_byte(slot), motor_byte, timeout=timeout)
    
    def get_buffer_state(self):
        """Get buffer state - required after stage 7."""
        return self._send(0x03, 0xff, 0x05)
    
    def query_tracking(self):
        """Query tracking status - 0x0a command. May indicate if tracking is active."""
        return self._send(0x03, 0xff, 0x0a)
    
    def query_encoder(self, slot=0):
        """Query measuring wheel encoder - 0x0e command.
        
        Returns 4-byte float with encoder position in mm.
        Packet: 0104ff0e[SLOT_BYTE] where SLOT_BYTE = 1<<slot
        """
        return self._send(0x04, 0xff, 0x0e, self._slot_to_byte(slot))
    
    def query_status(self):
        """Query box status - 010300a2."""
        return self._send(0x03, 0x00, 0xa2)
    
    def query_loaded_slot(self):
        """Query which slot is currently loaded.
        
        Sends: 0104ff0801 (set_mode_unload)
        Response: f70104000804xx where 04 = slot 2 bitmask, 00 = no slot
        Returns: (slot_number, raw_response) where slot=-1 if none loaded
        """
        r = self._send(0x04, 0xff, 0x08, 0x01)  # set_mode_unload
        if r and len(r) >= 6:
            # Response byte 5 (0-indexed) is slot bitmask (1,2,4,8), or 0x00 if none
            slot_byte = r[5]
            slot = self._byte_to_slot(slot_byte)
            return (slot, r)
        return (None, r)
    
    def parse_stage5_state(self, response):
        """Parse Stage 5 response to detect box state.
        
        Returns: 'FEEDING', 'STALL', or 'ERROR'
        
        Response format: f7 01 07 [STATUS] 10 [encoder float 4 bytes] [CRC]
        
        Status byte (byte 3):
        - 0x00: Normal/feeding
        - 0x0a: Timeout (motor ran 40s without stall)
        - 0x0c: Stall (motor stopped from resistance)
        """
        if not response or len(response) < 6:
            return "ERROR"
        
        status = response[3]
        
        # Check status byte (definitive stall/timeout signal)
        if status in (0x0a, 0x0c):
            return "STALL"
        
        # Normal feeding (status 0x00)
        return "FEEDING"
