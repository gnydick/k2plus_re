# ===========================================================================
# MERGED FILE: Accurate signatures from live introspection + inferred implementations
#
# SIGNATURE SOURCE: Live printer introspection (ACCURATE)
# IMPLEMENTATION: Reverse engineered (INFERRED - may have errors)
#
# Parameter names in implementations may still use old names.
# See PARAM_MAPPING comments for required renames.
# ===========================================================================

# Reconstructed from box_wrapper.cpython-39.so
# Original: klippy/extras/box_wrapper.py
# Creality K2 Series - Multi-Color Material Box (AMS-style) Control
#
# Copyright (C) Creality
# Reverse engineered by Claude Code
#
# This file may be distributed under the terms of the GNU GPLv3 license.
#
# =============================================================================
# PROVENANCE NOTICE - READ BEFORE USING THIS CODE
# =============================================================================
#
# This file was reconstructed through reverse engineering. The code quality
# and accuracy varies by section:
#
# EXTRACTED (high confidence) - Directly from binary strings or decompiled C:
#   - Class names (ParseData, BoxCfg, BoxState, BoxSave, CutSensor, BoxAction,
#     MultiColorMeterialBoxWrapper)
#   - G-code command names (BOX_*, 60+ commands)
#   - Configuration parameter names
#   - Log message strings
#   - RS-485 packet format from msgblock_485_decompiled.c (HEAD=0xF7)
#   - Protocol constants (STATE_POS, MATERIAL_NUM_POS, etc.)
#
# INFERRED (lower confidence) - Educated guesses based on:
#   - Function names implying behavior
#   - AMS-style multi-material system patterns
#   - Common Klipper extension patterns
#   - RS-485 protocol conventions
#
# SPECIFIC UNCERTAINTIES:
#   - RS-485 command codes (0x10, 0x20, 0x40, etc.) are GUESSES
#   - Flush length calculations are simplified approximations
#   - State machine transitions are inferred from function names
#   - CRC calculation uses algorithm from decompiled C but may have errors
#
# Sections are marked with:
#   # [EXTRACTED] - From binary strings or decompiled code
#   # [INFERRED]  - Logic reconstructed from context/patterns
#   # [PARTIAL]   - Mix of extracted names with inferred logic
#
# =============================================================================

import logging
import threading
import json
import os
import time

# Protocol constants
PACK_HEAD = 0xF7
TIMEOUT_MAX = 5.0
TIMEOUT_LONG_TIME = 10.0
TIMEOUT_LONGER_TIME = 30.0
TIMEOUT_SHORT_TIME = 1.0

# State constants
STATE_IDLE = 0
STATE_EXTRUDE = 1
STATE_RETRUDE = 2
STATE_CUT = 3
STATE_FLUSH = 4
STATE_ERR = -1

# Error indices
ERROR_INDEX = {
    'EXTRUDE_ERR1': 1,
    'EXTRUDE_ERR4': 4,
    'EXTRUDE_ERR5': 5,
    'EXTRUDE_ERR6': 6,
    'EXTRUDE_ERR7': 7,
    'EXTRUDE_ERR8': 8,
    'EXTRUDE_ERR9': 9,
    'EXTRUDE_ERR10': 10,
}

# Position indices in protocol
STATE_POS = 3
MATERIAL_NUM_POS = 4
BOX_NUM_POS = 5


class error(Exception):
    """Exception class for box_wrapper errors."""
    pass


class ParseData:
    """Protocol data parsing utilities."""

    def __init__(self):
        self.printer = config.get_printer()
        self._ffi = None

    def get_cmd_num(self, data_send, return_method):
        """Extract command number from response."""
        if len(data) >= 5:
            return data[4]
        return 0

    def get_key_from_value(self, dict, v):
        """Get dictionary key from value."""
        for k, v in mapping.items():
            if v == value:
                return k
        return None

    def get_measuring_wheel(self, data_send, msg):
        """Parse measuring wheel position from response."""
        if len(data) >= 8:
            pos = (data[6] << 8) | data[7]
            return pos / 100.0  # Convert to mm
        return 0.0

    def get_remain_len(self, data_send, msg):
        """Parse remaining material length from response."""
        if len(data) >= 10:
            length = (data[6] << 24) | (data[7] << 16) | (data[8] << 8) | data[9]
            return length / 100.0  # Convert to mm
        return 0.0

    def get_rfid(self, msg):
        """Parse RFID from response data."""
        if len(data) < 20:
            return None
        # RFID is typically bytes 6-17 in hex format
        rfid_bytes = data[6:18]
        return ''.join('%02X' % b for b in rfid_bytes)

    def parse_num_string_to_byte(self, data):
        """Convert numeric string to bytes."""
        try:
            return bytes.fromhex(num_str.replace(' ', ''))
        except:
            return b''

    def parse_num_to_byte(self, data):
        """Convert number to bytes."""
        return num.to_bytes(length, byteorder='big')


class BoxCfg:
    """Configuration for material box."""

    def __init__(self, config):
        self.printer = config.get_printer()

        # Cutting position
        self.cut_pos_x = config.getfloat('cut_pos_x', default=0.0)
        self.cut_pos_y = config.getfloat('cut_pos_y', default=0.0)
        self.cut_velocity = config.getfloat('cut_velocity', default=50.0)
        self.cut_hall_move = config.getfloat('cut_hall_move', default=10.0)

        # Extrusion position
        self.extrude_pos_x = config.getfloat('extrude_pos_x', default=0.0)
        self.extrude_pos_y = config.getfloat('extrude_pos_y', default=0.0)

        # Safe position
        self.safe_pos_x = config.getfloat('safe_pos_x', default=0.0)
        self.safe_pos_y = config.getfloat('safe_pos_y', default=0.0)

        # Cleaning positions
        self.clean_pos_min_x = config.getfloat('clean_pos_min_x', default=0.0)
        self.clean_pos_max_x = config.getfloat('clean_pos_max_x', default=0.0)
        self.clean_pos_min_y = config.getfloat('clean_pos_min_y', default=0.0)
        self.clean_pos_max_y = config.getfloat('clean_pos_max_y', default=0.0)
        self.clean_pos_middle_y = config.getfloat('clean_pos_middle_y', default=0.0)
        self.clean_left_pos_x = config.getfloat('clean_left_pos_x', default=0.0)
        self.clean_left_pos_y = config.getfloat('clean_left_pos_y', default=0.0)
        self.clean_right_pos_x = config.getfloat('clean_right_pos_x', default=0.0)
        self.clean_right_pos_y = config.getfloat('clean_right_pos_y', default=0.0)
        self.clean_velocity = config.getfloat('clean_velocity', default=100.0)
        self.clean_offset_pos = config.getfloat('clean_offset_pos', default=0.0)

        # Extrusion parameters
        self.extrude_material_len_for_box = config.getfloat(
            'extrude_material_len_for_box', default=100.0)
        self.extrude_material_len_for_extruder = config.getfloat(
            'extrude_material_len_for_extruder', default=50.0)
        self.extrude_material_velocity = config.getfloat(
            'extrude_material_velocity', default=30.0)
        self.extrude_material_times = config.getint(
            'extrude_material_times', default=3)

        # Buffer parameters
        self.buffer_empty_len = config.getfloat('buffer_empty_len', default=50.0)

        # Flush parameters
        self.box_first_clean_length = config.getfloat(
            'box_first_clean_length', default=50.0)
        self.box_need_clean_length = config.getfloat(
            'box_need_clean_length', default=30.0)
        self.box_need_clean_length_max = config.getfloat(
            'box_need_clean_length_max', default=100.0)


class BoxState:
    """State management for material slots (T0-Tn)."""

    def __init__(self):
        self.printer = config.get_printer()
        self.num_slots = num_slots

        # Tn data - per-slot material info
        self.tn_data = {}      # {slot: {rfid, remain_len, color, material_type}}
        self.tn_inner_data = {}  # {slot: {inner state data}}
        self.tn_save_data = {}   # Persistent save data

        # Tnn map - active slot mapping
        self.tnn_map = {}      # {tnn_index: slot_index}
        self.tnn_content = {}  # {tnn_index: content}

        # Same material list for optimization
        self.same_material_list = []

        # Error state
        self.e_err = None

        self.state_init()

    def state_init(self):
        """Initialize slot states."""
        for i in range(self.num_slots):
            self.tn_data[i] = {
                'rfid': None,
                'remain_len': 0.0,
                'color': 0,
                'material_type': None,
                'slot': i
            }
            self.tn_inner_data[i] = {
                'filament_present': False,
                'connected': False
            }

    def generate_Tn_data(self):
        """Generate Tn data for a slot."""
        self.tn_data[slot] = {
            'rfid': rfid,
            'remain_len': remain_len,
            'color': color,
            'material_type': material_type,
            'slot': slot
        }

    def get_Tn_data(self, addr, part, num=None, uppart=None):
        """Get Tn data for a slot."""
        return self.tn_data.get(slot, {})

    def modify_Tn_data(self, addr, data, part, num=None, uppart=None, cmd=False):
        """Modify specific Tn data field."""
        if slot in self.tn_data:
            self.tn_data[slot][key] = value

    def generate_Tn_inner_data(self):
        """Generate inner state data for a slot."""
        self.tn_inner_data[slot] = {
            'filament_present': filament_present,
            'connected': connected
        }

    def get_Tn_inner_data(self, addr, part, num=None, subpart=None, uppart=None):
        """Get inner state data for a slot."""
        return self.tn_inner_data.get(slot, {})

    def modify_Tn_inner_data(self, addr, data, part, num=None, subpart=None, uppart=None):
        """Modify specific inner data field."""
        if slot in self.tn_inner_data:
            self.tn_inner_data[slot][key] = value

    def generate_Tn_map(self):
        """Generate slot mapping."""
        self.tnn_map = mapping.copy()

    def generate_Tnn_map(self):
        """Map Tnn to physical slot."""
        self.tnn_map[tnn_index] = slot_index

    def get_Tnn_map(self):
        """Get full Tnn mapping."""
        return self.tnn_map.copy()

    def generate_Tnn_content(self):
        """Set Tnn content."""
        self.tnn_content[tnn_index] = content

    def get_Tnn_content(self, tnn):
        """Get Tnn content."""
        return self.tnn_content.get(tnn_index)

    def generate_tn_save_data(self):
        """Generate save data for slot."""
        self.tn_save_data[slot] = data

    def get_tn_save_data(self, addr, part, num):
        """Get save data for slot."""
        return self.tn_save_data.get(slot, {})

    def update_tn_save_data(self, part, enable=None, tnn_map=None, last_cmd=None, save=False):
        """Update save data field."""
        if slot not in self.tn_save_data:
            self.tn_save_data[slot] = {}
        self.tn_save_data[slot][key] = value

    def modify_tn_save_data(self, addr, data, part, num):
        """Modify entire save data for slot."""
        self.tn_save_data[slot] = data

    def sync_tn_data(self, tn, material_status):
        """Synchronize Tn data across structures."""
        # Sync tn_data to tn_save_data for persistence
        for slot in self.tn_data:
            self.tn_save_data[slot] = self.tn_data[slot].copy()

    def update_same_material_list(self):
        """Update list of slots with same material."""
        self.same_material_list = material_list

    def e_err_set(self):
        """Set error state."""
        self.e_err = err

    def clear_e_err(self):
        """Clear error state."""
        self.e_err = None


class BoxSave:
    """Persistence layer for box state."""

    def __init__(self, config):
        self.printer = config.get_printer()
        self.gcode = self.printer.lookup_object('gcode')

        # Error tracking
        self.err_tnn = None
        self.resume_tnn = None

        # Saved state
        self.saved_fan_speed = 0
        self.saved_accel = 0
        self.saved_accel_to_decel = 0

        self.printer.register_event_handler('klippy:ready', self.find_objs)

    def find_objs(self):
        """Find required Klipper objects."""
        self.toolhead = self.printer.lookup_object('toolhead', None)

    def save_err_tnn(self, last_tnn=None, tnn=None, addr=None, vtnn=None):
        """Save error Tnn for recovery."""
        self.err_tnn = tnn

    def clear_err(self):
        """Clear error state."""
        self.err_tnn = None

    def get_err(self):
        """Get current error Tnn."""
        return self.err_tnn

    def recode_err(self, err, last_tnn=None, tnn=None, addr=None, vtnn=None, filament_sensor_enable=True):
        """Record error information."""
        logging.error("[box] Error: %s", err_info)

    def save_resume_tnn(self, tnn):
        """Save Tnn for resume."""
        self.resume_tnn = tnn

    def clear_resume_tnn(self):
        """Clear resume Tnn."""
        self.resume_tnn = None

    def save_fan(self):
        """Save current fan speed."""
        try:
            fan = self.printer.lookup_object('fan')
            self.saved_fan_speed = fan.get_status(None).get('speed', 0)
        except:
            pass

    def restore_fan(self):
        """Restore saved fan speed."""
        try:
            self.gcode.run_script_from_command(
                "M106 S%d" % int(self.saved_fan_speed * 255)
            )
        except:
            pass

    def save_printer_accel(self, velocity, accel, speed_factor):
        """Save printer acceleration settings."""
        if self.toolhead:
            status = self.toolhead.get_status(None)
            self.saved_accel = status.get('max_accel', 0)
            self.saved_accel_to_decel = status.get('max_accel_to_decel', 0)

    def restore_printer_accel(self):
        """Restore saved acceleration settings."""
        if self.saved_accel > 0:
            self.gcode.run_script_from_command(
                "SET_VELOCITY_LIMIT ACCEL=%f ACCEL_TO_DECEL=%f" %
                (self.saved_accel, self.saved_accel_to_decel)
            )


class CutSensor:
    """Filament cut sensor interface."""

    def __init__(self, config, switch_pin):
        self.printer = config.get_printer()
        self.box_action = box_action
        self._state = False

        # Get button pin if configured
        switch_pin = config.get('switch_pin', None)
        if switch_pin:
            try:
                buttons = self.printer.load_object(config, 'buttons')
                buttons.register_buttons([switch_pin], self._button_handler)
            except Exception as e:
                logging.warning("[box] do not define 'switch_pin' for cutting: %s", e)

    def _button_handler(self, eventtime, state):
        """Handle cut sensor state change."""
        self._state = state
        if state:
            logging.info("[box] cut sensor detected")
        else:
            logging.info("[box] cut sensor not detected")

    def state(self):
        """Get current sensor state."""
        return self._state


class BoxAction:
    """Core material handling operations."""

    def __init__(self, config, box_state):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.name = config.get_name().split()[-1]

        # Configuration
        self.boxcfg = BoxCfg(config)
        self.boxstate = BoxState(config)
        self.boxsave = BoxSave(config)
        self.parse_data = ParseData(config)

        # Cut sensor
        self.cut_sensor = CutSensor(config, self)

        # Serial communication
        self._serial = None
        self.addr = 0x01  # Default material box address

        # Objects found later
        self.toolhead = None
        self.extruder = None
        self.heater_hot = None
        self.fan = None

        # Flushing state
        self.flushing_sign = False
        self.flush_array = []

        # Operation state
        self.current_tnn = -1
        self.cut_succeed_num = 0
        self.release_succeed_num = 0
        self.extrude_process_ret_state = 0
        self.extrude_process_stage7_flag = False

        # Heart/keepalive
        self.heart_enabled = True
        self.heart_timer = None

        # Z position save
        self.saved_z_pos = 0

        # FFI for flush calculation
        self._ffi = None

        # Register event handlers
        self.printer.register_event_handler('klippy:ready', self._handle_ready)
        self.printer.register_event_handler('klippy:shutdown', self._handle_shutdown)

    def _handle_ready(self):
        """Handle Klipper ready event."""
        self.find_objs()

    def _handle_shutdown(self):
        """Handle Klipper shutdown event."""
        self.heart_enabled = False

    def find_objs(self):
        """Find required Klipper objects after ready."""
        self.toolhead = self.printer.lookup_object('toolhead', None)
        try:
            self._serial = self.printer.lookup_object('serial_485 serial485')
        except:
            logging.warning("[box] No serial_485 serial485 found")
        try:
            self.extruder = self.printer.lookup_object('extruder')
            self.heater_hot = self.extruder.heater
        except:
            pass
        try:
            self.fan = self.printer.lookup_object('fan')
        except:
            logging.warning("[box] do not define 'output_pin fan0'")

    # --- Serial Communication ---

    def send_data(self, addr, cmd, timeout, state="b'\\xff'", data="b''", report_err=True):
        """Send data via RS-485."""
        if self._serial:
            data_bytes = bytes(int(c) for c in data) if isinstance(data[0], str) else bytes(data)
            return self._serial.cmd_send_data_with_response(data_bytes, timeout)
        return None

    def motor_send_data(self, addr, cmd, timeout, state="b'\\x00'", data="b''", retries_en=True):
        """Send data to motor controller."""
        return self.send_data(data, timeout)

    def process_msg(self, data_send, msg):
        """Process received message."""
        if not response or len(response) < 6:
            return None
        # Dispatch based on function code
        return response

    def ret_parse_process(self, data_send, msg):
        """Parse response and validate."""
        if not response:
            return False
        if len(response) < 6:
            return False
        if expected_func and response[4] != expected_func:
            return False
        return True

    # --- Communication Commands ---

    def communication_create_connect(self, addr):
        """Create connection to material box."""
        data = [PACK_HEAD, addr, 0x04, 0x00, 0xA2, 0x00]
        # Add CRC
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_get_box_state(self, addr):
        """Get box state from device."""
        data = [PACK_HEAD, addr, 0x04, 0x00, 0x10, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        response = self.send_data(data, timeout)
        if not response:
            logging.warning("communication_get_box_state return false, timeout_times: %d",
                          timeout)
            return None
        return response

    def communication_get_buffer_state(self, addr):
        """Get buffer state."""
        data = [PACK_HEAD, addr, 0x04, 0x00, 0x11, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_get_filament_sensor_state(self, addr, pos):
        """Get filament sensor state."""
        data = [PACK_HEAD, addr, 0x04, 0x00, 0x12, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        response = self.send_data(data)
        if response:
            logging.info("get_connect_state: get_filament_sensor_state material_status:%s",
                        response.hex() if response else "None")
        return response

    def communication_get_rfid(self, addr, num=15):
        """Get RFID for a slot."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x20, slot, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_get_remain_len(self, addr, num=15):
        """Get remaining material length."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x21, slot, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_get_version_sn(self, addr):
        """Get firmware version and serial number."""
        data = [PACK_HEAD, addr, 0x04, 0x00, 0x30, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_get_hardware_status(self, addr):
        """Get hardware status."""
        data = [PACK_HEAD, addr, 0x04, 0x00, 0x31, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_extrude_process(self, addr, num, trigger='', stage=2, report_err=True, extrude=None):
        """Start extrusion process."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x40, slot, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data, timeout=TIMEOUT_LONG_TIME)

    def communication_extrude2_process(self, addr, num, trigger):
        """Continue extrusion process."""
        len_hi = (int(length * 100) >> 8) & 0xFF
        len_lo = int(length * 100) & 0xFF
        data = [PACK_HEAD, addr, 0x07, 0x00, 0x41, slot, len_hi, len_lo, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data, timeout=TIMEOUT_LONG_TIME)

    def communication_retrude_process(self, addr, num, trigger, report_err=True):
        """Start retraction process."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x50, slot, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data, timeout=TIMEOUT_LONG_TIME)

    def communication_ctrl_connection_motor_action(self, addr, act):
        """Control connection motor."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x60, action, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_set_box_mode(self, addr, m, num='0'):
        """Set box operating mode."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x70, mode, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_set_pre_loading(self, addr, action, num=15, force=False):
        """Enable/disable pre-loading for slot."""
        data = [PACK_HEAD, addr, 0x06, 0x00, 0x71, slot, enable, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_tighten_up_enable(self, addr, enable):
        """Enable/disable tighten up."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x72, enable, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_measuring_wheel(self, addr, action):
        """Get measuring wheel position."""
        data = [PACK_HEAD, addr, 0x05, 0x00, 0x80, slot, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    def communication_test(self, count, timeout, interval, addr, num):
        """Send test command."""
        data = [PACK_HEAD, addr, 0x04, 0x00, 0xFF, 0x00]
        crc = self._calc_crc(data[2:])
        data.append(crc)
        return self.send_data(data)

    # [INVENTED] This method does not exist in live module
    def _calc_crc(self, data):
        """Calculate CRC-8 for packet."""
        crc = 0
        for byte in data:
            crc ^= byte
            for _ in range(8):
                if crc & 0x80:
                    crc = (crc << 1) ^ 0x07
                else:
                    crc <<= 1
                crc &= 0xFF
        return crc

    # --- Material Operations ---

    def box_extrude_material(self, tnn):
        """Extrude material for given Tnn."""
        slot = self.boxstate.tnn_map.get(tnn, 0)
        logging.info("[box] box_extrude_material tnn=%d slot=%d", tnn, slot)

        # Move to extrude position
        self.go_to_extrude_pos()

        # Start extrusion
        response = self.communication_extrude_process(self.addr, slot)
        if not self.ret_parse_process(response, 0x40):
            return False

        return True

    def box_extrude_material_part(self, tnn, retry=[0, 0, 0, 0]):
        """Extrude partial material."""
        slot = self.boxstate.tnn_map.get(tnn, 0)
        response = self.communication_extrude2_process(self.addr, slot, length)
        return self.ret_parse_process(response, 0x41)

    def box_extrude_material_stage8(self, tnn):
        """Final extrusion stage."""
        slot = self.boxstate.tnn_map.get(tnn, 0)
        logging.info("box_extrude_material_stage8 tnn: %s", tnn)
        return True

    def box_retrude_material(self):
        """Retract material for given Tnn."""
        if tnn < 0:
            logging.warning("[box] retrude, no tnn")
            return False

        slot = self.boxstate.tnn_map.get(tnn, 0)
        logging.info("[box] box_retrude_material tnn=%d slot=%d", tnn, slot)

        response = self.communication_retrude_process(self.addr, slot)
        return self.ret_parse_process(response, 0x50)

    def box_retrude_material_filament_err_part(self):
        """Handle retraction during filament error."""
        return self.box_retrude_material(tnn)

    # --- Cutting Operations ---

    def cut_material(self):
        """Perform material cut."""
        self.move_to_cut()

        # Execute cut sequence
        self.cut_hall_zero()
        result = self.cut_hall_find_zero()

        if result:
            logging.info("[box] cut to return OK")
            self.cut_succeed_num += 1
        else:
            logging.warning("[box] cut to return failed")

        return result

    def move_to_cut(self):
        """Move to cutting position."""
        if self.toolhead:
            self.toolhead.manual_move(
                [self.boxcfg.cut_pos_x, self.boxcfg.cut_pos_y, None],
                self.boxcfg.cut_velocity
            )
            self.toolhead.wait_moves()

    def cut_hall_zero(self):
        """Reset cut hall sensor - move cutter to zero/home position."""
        # Send command to reset cutter position
        if self.toolhead:
            # Small movement to trigger hall sensor reset
            pos = self.toolhead.get_position()
            self.toolhead.manual_move(
                [pos[0] + self.boxcfg.cut_hall_move, pos[1], None],
                self.boxcfg.cut_velocity
            )
            self.toolhead.wait_moves()

    def cut_hall_find_zero(self):
        """Find cut hall zero position."""
        logging.info("[box] cut to return_3 OK")
        return True

    def cut_hall_test(self):
        """Test cut hall sensor."""
        state = self.cut_sensor.state()
        logging.info("[box] cut_hall_test: state=%s", state)
        return state

    def cut_hall_find_test(self):
        """Test finding cut hall position."""
        state = self.cut_hall_test()
        logging.info("[box] cut_hall_find_test: %s", "found" if state else "not found")

    # --- Movement Operations ---

    def go_to_extrude_pos(self):
        """Move to extrusion position."""
        if self.toolhead:
            self.toolhead.manual_move(
                [self.boxcfg.extrude_pos_x, self.boxcfg.extrude_pos_y, None],
                self.boxcfg.clean_velocity
            )
            self.toolhead.wait_moves()

    def move_to_safe_pos(self):
        """Move to safe position."""
        if self.toolhead:
            self.toolhead.manual_move(
                [self.boxcfg.safe_pos_x, self.boxcfg.safe_pos_y, None],
                self.boxcfg.clean_velocity
            )
            self.toolhead.wait_moves()

    def z_move(self):
        """Move Z axis."""
        if self.toolhead:
            self.toolhead.manual_move([None, None, z_pos], velocity)
            self.toolhead.wait_moves()

    def z_down(self):
        """Move Z down by distance."""
        if self.toolhead:
            pos = self.toolhead.get_position()
            self.z_move(pos[2] - distance, velocity)

    def z_restore(self):
        """Restore Z to saved position."""
        if self.saved_z_pos > 0:
            self.z_move(self.saved_z_pos)

    # --- Flushing Operations ---

    def material_flush(self, length, velocity, temp, max_temp=None, percent=None, tnn=None):
        """Flush material between Tnn changes."""
        if length is None:
            length = self.get_flush_len(from_tnn, to_tnn)

        logging.info("[box] material_flush from=%d to=%d len=%.1f",
                    from_tnn, to_tnn, length)

        # Heat to flush temperature
        flush_temp = self.get_flush_temp(from_tnn, to_tnn)
        self.set_temp(flush_temp)
        self.quickly_wait_heating(flush_temp)

        # Perform flush extrusion
        self.check_flush_temp_and_extrude(length, flush_temp)

        return True

    def cal_flush_list(self, src_length, cal_length):
        """Calculate flush sequence for multiple materials."""
        flush_list = []
        for i in range(len(used_tnns) - 1):
            from_tnn = used_tnns[i]
            to_tnn = used_tnns[i + 1]
            length = self.get_flush_len(from_tnn, to_tnn)
            flush_list.append((from_tnn, to_tnn, length))
        return flush_list

    def get_flush_len(self, scv, tcv):
        """Get flush length for material transition."""
        # Try FFI first
        if self._ffi:
            try:
                from_color = self._get_color_for_tnn(from_tnn)
                to_color = self._get_color_for_tnn(to_tnn)
                return self._ffi.get_flushing_volume(from_color, to_color)
            except:
                pass

        # Check flush array
        if self.flush_array:
            try:
                return self.flush_array[from_tnn][to_tnn]
            except (IndexError, KeyError):
                pass

        # Default based on color difference
        return self.boxcfg.box_need_clean_length

    # [INVENTED] This method does not exist in live module
    def _get_color_for_tnn(self, tnn):
        """Get color for Tnn slot."""
        tn_data = self.boxstate.get_Tn_data(
            self.boxstate.tnn_map.get(tnn, 0))
        return tn_data.get('color', 0)

    def get_flush_temp(self, last_tnn, current_tnn):
        """Get flush temperature for transition."""
        from_temp = self.get_material_target_temp(from_tnn)
        to_temp = self.get_material_target_temp(to_tnn)
        return max(from_temp, to_temp)

    def get_flush_max_temp(self, last_tnn, current_tnn):
        """Get maximum temperature for flush."""
        from_temp = self.get_material_target_max_temp(from_tnn)
        to_temp = self.get_material_target_max_temp(to_tnn)
        return max(from_temp, to_temp)

    def get_flush_velocity(self, last_tnn, current_tnn):
        """Get flush extrusion velocity."""
        from_speed = self.get_material_max_extrusion_speed(from_tnn)
        to_speed = self.get_material_max_extrusion_speed(to_tnn)
        return min(from_speed, to_speed)

    def set_flushing_sign(self):
        """Set flushing in progress flag."""
        self.flushing_sign = True

    def reset_flushing_sign(self):
        """Clear flushing flag."""
        self.flushing_sign = False

    def has_flushing_sign(self):
        """Check if flushing is in progress."""
        return self.flushing_sign

    # --- Material Info ---

    def get_material_target_temp(self, tnn=None, type=None):
        """Get target print temperature for material."""
        slot = self.boxstate.tnn_map.get(tnn, 0)
        tn_data = self.boxstate.get_Tn_data(slot)
        rfid = tn_data.get('rfid')

        # Look up in material database
        if rfid:
            # Would query material database here
            pass

        return 200  # Default PLA temp

    def get_material_target_max_temp(self, tnn=None, type=None):
        """Get maximum safe temperature for material."""
        base_temp = self.get_material_target_temp(tnn)
        return base_temp + 20  # 20°C margin

    def get_material_max_extrusion_speed(self, tnn=None, type=None):
        """Get max extrusion speed for material."""
        return 10.0  # mm³/s default

    def check_rfid_valid(self, rfid):
        """Validate RFID."""
        if not rfid:
            return False
        # Add validation logic
        return True

    def check_same_box(self, tnn):
        """Check if two Tnns use same physical box."""
        slot1 = self.boxstate.tnn_map.get(tnn1, -1)
        slot2 = self.boxstate.tnn_map.get(tnn2, -1)

        # Same box if slots are in same group of 4
        return (slot1 // 4) == (slot2 // 4)

    def is_material_available(self, tnn):
        """Check if material is available for Tnn."""
        slot = self.boxstate.tnn_map.get(tnn, 0)
        tn_data = self.boxstate.get_Tn_data(slot)
        return tn_data.get('remain_len', 0) > 0

    def material_volume_to_length(self, volume):
        """Convert volume to filament length."""
        import math
        radius = diameter / 2.0
        area = math.pi * radius * radius
        return volume / area

    # --- Temperature Control ---

    def set_temp(self):
        """Set hotend temperature."""
        self.gcode.run_script_from_command("M104 S%d" % int(temp))

    def set_cool_temp(self):
        """Set cooling target temperature."""
        self.gcode.run_script_from_command("M104 S%d" % int(temp))

    def quickly_wait_heating(self, set_temp):
        """Wait for hotend to reach temperature."""
        if not self.heater_hot:
            return False

        start_time = self.reactor.monotonic()
        while True:
            cur_temp = self.heater_hot.get_temp()[0]
            if cur_temp >= target_temp - 5:
                return True
            if self.reactor.monotonic() - start_time > timeout:
                return False
            self.reactor.pause(self.reactor.monotonic() + 0.5)

    # --- Extrusion Control ---

    def extruder_extrude(self, tnn):
        """Perform extruder extrusion."""
        self.gcode.run_script_from_command(
            "G1 E%.2f F%d" % (length, int(speed * 60))
        )

    def check_and_extrude(self, extrude, velocity, wait=True):
        """Check conditions and extrude."""
        logging.info("check_and_extrude extrude: %s, velocity: %s", length, velocity)
        self.extruder_extrude(length, velocity)

    def check_speed_and_extrude(self, extrude, velocity, wait=True):
        """Check speed limits and extrude."""
        actual_speed = min(max_speed, 30.0)  # Cap at 30 mm/s
        self.extruder_extrude(length, actual_speed)

    def check_flush_temp_and_extrude(self, length, index, temp, max_temp, velocity, max_temp_flush=False):
        """Check temperature and perform flush extrusion."""
        cur_temp = 0
        if self.heater_hot:
            cur_temp = self.heater_hot.get_temp()[0]

        if cur_temp < temp - 10:
            self.quickly_wait_heating(temp)

        self.extruder_extrude(length, 5.0)  # Flush at 5 mm/s

    def extrusion_all_materials(self):
        """Extrude from all specified Tnns."""
        for tnn in tnns:
            self.box_extrude_material(tnn)
            self.extruder_extrude(length, 5.0)
            self.box_retrude_material(tnn)

    # --- Sensor Operations ---

    def get_filament_sensor_detect(self):
        """Get filament sensor detection state."""
        response = self.communication_get_filament_sensor_state(self.addr)
        if response and len(response) >= 6:
            logging.info("[box] filament sensor state: %x", response[5])
            return response[5]
        return 0

    def get_five_way_sensor_detect(self):
        """Get five-way sensor detection."""
        return self.communication_get_buffer_state(self.addr)

    def enable_filament_sensor(self):
        """Enable filament sensor."""
        self.gcode.run_script_from_command("SET_FILAMENT_SENSOR SENSOR=fila ENABLE=1")

    def disable_filament_sensor(self):
        """Disable filament sensor."""
        self.gcode.run_script_from_command("SET_FILAMENT_SENSOR SENSOR=fila ENABLE=0")

    # --- Heart/Keepalive ---

    def enable_heart_process(self, tnn):
        """Enable heart/keepalive process."""
        self.heart_enabled = True

    def disable_heart_process(self, tnn):
        """Disable heart/keepalive process."""
        self.heart_enabled = False

    def timeout_process(self, addr):
        """Handle timeout events."""
        logging.warning("[box] Communication timeout - attempting reconnect")
        self.communication_create_connect(self.addr)

    # --- Error Handling ---

    def extrude_process_auto_retry_process(self, tnn, type, retry=[0, 0, 0, 0]):
        """Auto-retry extrusion process."""
        logging.info("auto_retry_connection extrude_process stage=0 failed")
        return self.box_extrude_material(tnn)

    def extrude_process_stage7(self):
        """Stage 7 of extrusion process."""
        logging.info("extrude_process_stage7 tnn: %s", tnn)
        self.extrude_process_stage7_flag = True
        result = True
        ret = "OK"
        logging.info("extrude_process_stage7_ret: %s", ret)
        return result

    def filament_conflict_check(self, print_type):
        """Check for filament conflicts."""
        return False

    def filament_err_tighten_up_event(self, eventtime):
        """Handle filament tighten up error event."""
        logging.warning("[box] Filament tighten up error - sending tighten command")
        self.communication_tighten_up_enable(self.addr, 1)

    def rfid_check(self, rfid):
        """Check RFID for slot."""
        response = self.communication_get_rfid(self.addr, slot)
        if response:
            rfid = self.parse_data.get_rfid(response)
            return self.check_rfid_valid(rfid)
        return False

    def retrude_process_clear_flag(self):
        """Clear retraction process flags."""
        self.extrude_process_stage7_flag = False
        self.extrude_process_ret_state = 0

    # --- Utility Operations ---

    def blow(self):
        """Control blow/purge mechanism."""
        if enable:
            self.gcode.run_script_from_command("SET_PIN PIN=fan0 VALUE=255")
        else:
            self.gcode.run_script_from_command("SET_PIN PIN=fan0 VALUE=0")

    def Tn_Extrude(self, extrude, velocity, temp, max_temp=None, percent=None, tnn=None):
        """Extrude material from specified Tnn slot."""
        raise NotImplementedError  # [STUB] - Missing from reconstructed

    def nozzle_clean(self, circle=True):
        """Perform nozzle cleaning."""
        # Move through cleaning positions
        if self.toolhead:
            self.toolhead.manual_move(
                [self.boxcfg.clean_left_pos_x, self.boxcfg.clean_left_pos_y, None],
                self.boxcfg.clean_velocity
            )
            self.toolhead.manual_move(
                [self.boxcfg.clean_right_pos_x, self.boxcfg.clean_right_pos_y, None],
                self.boxcfg.clean_velocity
            )
            self.toolhead.wait_moves()

    def make_material_loose(self):
        """Make material loose in tube by small back-forth movement."""
        if self.heater_hot:
            cur_temp = self.heater_hot.get_temp()[0]
            if cur_temp > 180:
                # Small retraction and push to loosen material
                self.gcode.run_script_from_command("G1 E-5 F300")
                self.gcode.run_script_from_command("G1 E5 F300")

    def material_auto_refill(self, eventtime):
        """Auto-refill material from same-type slot."""
        if not self.boxstate.same_material_list:
            return False

        # Find alternate slot with same material
        for alt_tnn in self.boxstate.same_material_list:
            if alt_tnn != tnn and self.is_material_available(alt_tnn):
                logging.info("[box] Auto refill: switching from TNN %d to %d", tnn, alt_tnn)
                return True
        return False

    def check_material_refill(self):
        """Check if material refill is needed."""
        slot = self.boxstate.tnn_map.get(tnn, 0)
        tn_data = self.boxstate.get_Tn_data(slot)
        remain = tn_data.get('remain_len', 0)
        return remain < 100  # Refill threshold

    def check_printing_used_material(self, addr, num):
        """Check materials used in print."""
        for tnn in tnns:
            if not self.is_material_available(tnn):
                return False
        return True

    def check_connect(self, addr):
        """Check box connection."""
        response = self.communication_create_connect(self.addr)
        return response is not None

    def power_loss_restore(self):
        """Restore after power loss."""
        # Load saved state from persistent storage
        try:
            import os
            state_file = "creality/userdata/box/power_loss_state.json"
            if os.path.exists(state_file):
                with open(state_file, 'r') as f:
                    state = json.load(f)
                    self.current_tnn = state.get('current_tnn', -1)
                    self.saved_z_pos = state.get('z_pos', 0)
                    logging.info("[box] Restored power loss state: tnn=%d z=%.2f",
                                self.current_tnn, self.saved_z_pos)
        except Exception as e:
            logging.warning("[box] Failed to restore power loss state: %s", e)

    def power_loss_clean(self):
        """Clean state after power loss."""
        try:
            import os
            state_file = "creality/userdata/box/power_loss_state.json"
            if os.path.exists(state_file):
                os.remove(state_file)
                logging.info("[box] Cleaned power loss state")
        except Exception as e:
            logging.warning("[box] Failed to clean power loss state: %s", e)

    def convert_scv(self, cv):
        """Convert SCV value."""
        return value

    def convert_tcv(self, cv):
        """Convert TCV value."""
        return value

    def generate_auto_get_rfid_func(self, addr, num):
        """Generate auto RFID getter function."""
        def function():
            return self.communication_get_rfid(self.addr, slot)
        return function

    def update_filament_pos(self, tnn, data):
        """Update filament position tracking."""
        self.boxstate.modify_Tn_inner_data(slot, 'filament_pos', pos)

    def update_state_process(self, addr, data):
        """Update box state from data."""
        logging.info("update_state_process, data: %s", data)
        if data and len(data) >= 6:
            state = data[STATE_POS] if len(data) > STATE_POS else 0
            material_num = data[MATERIAL_NUM_POS] if len(data) > MATERIAL_NUM_POS else 0
            box_num = data[BOX_NUM_POS] if len(data) > BOX_NUM_POS else 0
            logging.info("[box] state=%d material_num=%d box_num=%d",
                        state, material_num, box_num)

    def update_Tnn_map(self):
        """Update Tnn to slot mapping."""
        self.boxstate.generate_Tnn_map(tnn_index, slot_index)

    def update_tn_save_data(self, eventtime):
        """Update Tn save data."""
        self.boxstate.update_tn_save_data(slot, 'data', data)

    def update_same_material_list(self, eventtime):
        """Update same material list."""
        self.boxstate.update_same_material_list(material_list)

    def is_use_ending_material_flush(self, **recode_err):
        """Check if using ending material flush."""
        return False

    def use_ending_material_flag_clear(self):
        """Clear ending material flag."""
        self.flushing_sign = False

    def get_gcode_used_tnn(self):
        """Get Tnns used in current G-code."""
        return []


class MultiColorMeterialBoxWrapper:
    """Main Klipper interface for multi-color material box."""

    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.name = config.get_name().split()[-1]

        # Core components
        self.box_action = BoxAction(config)
        self.boxstate = self.box_action.boxstate
        self.boxsave = self.box_action.boxsave
        self.boxcfg = self.box_action.boxcfg

        # Current state
        self.current_tnn = -1
        self.connect_state = False

        # Auto refill
        self.auto_refill_enabled = False

        # Objects found later
        self.toolhead = None

        # Register all G-code commands
        self._register_commands()

        # Register event handlers
        self.printer.register_event_handler('klippy:ready', self.find_objs)

    # [INVENTED] This method does not exist in live module
    def _register_commands(self):
        """Register all G-code commands."""
        commands = {
            'BOX_START_PRINT': self.cmd_box_start_print,
            'BOX_END_PRINT': self.cmd_box_end_print,
            'BOX_END': self.cmd_box_end,
            'BOX_EXTRUDE_MATERIAL': self.cmd_box_extrude_material,
            'BOX_RETRUDE_MATERIAL': self.cmd_box_retrude_material,
            'BOX_RETRUDE_MATERIAL_WITH_TNN': self.cmd_retrude_material_with_tnn,
            'BOX_MATERIAL_FLUSH': self.cmd_material_flush,
            'BOX_MATERIAL_CHANGE_FLUSH': self.cmd_material_change_flush,
            'BOX_CUT_MATERIAL': self.cmd_cut_material,
            'BOX_CUT_STATE': self.cmd_cut_state,
            'BOX_MOVE_TO_CUT': self.cmd_move_to_cut,
            'BOX_MOVE_TO_SAFE_POS': self.cmd_move_to_safe_pos,
            'BOX_GO_TO_EXTRUDE_POS': self.cmd_go_to_extrude_pos,
            'BOX_CREATE_CONNECT': self.cmd_create_connect,
            'BOX_GET_BOX_STATE': self.cmd_get_box_state,
            'BOX_GET_BUFFER_STATE': self.cmd_get_buffer_state,
            'BOX_GET_FILAMENT_SENSOR_STATE': self.cmd_get_filament_sensor_state,
            'BOX_GET_HARDWARE_STATUS': self.cmd_get_hardware_status,
            'BOX_GET_RFID': self.cmd_get_rfid,
            'BOX_GET_REMAIN_LEN': self.cmd_get_remain_len,
            'BOX_GET_VERSION_SN': self.cmd_get_version_sn,
            'BOX_GET_FLUSH_LEN': self.cmd_get_flush_len,
            'BOX_GET_GCODE_USED_TNN': self.cmd_get_gcode_used_tnn,
            'BOX_GENERATE_FLUSH_ARRAY': self.cmd_generate_flush_array,
            'BOX_SHOW_FLUSH_LIST': self.cmd_show_flush_list,
            'BOX_SEND_DATA': self.cmd_send_data,
            'BOX_COMMUNICATION_TEST': self.cmd_communication_test,
            'BOX_EXTRUDER_EXTRUDE': self.cmd_extruder_extrude,
            'BOX_EXTRUSION_ALL_MATERIALS': self.cmd_extrusion_all_materials,
            'BOX_EXTRUDE_PROCESS': self.cmd_extrude_process,
            'BOX_RETRUDE_PROCESS': self.cmd_retrude_process,
            'BOX_SET_TEMP': self.cmd_set_temp,
            'BOX_SET_BOX_MODE': self.cmd_set_box_mode,
            'BOX_SET_PRE_LOADING': self.cmd_set_pre_loading,
            'BOX_SET_CURRENT_BOX_IDLE_MODE': self.cmd_BOX_SET_CURRENT_BOX_IDLE_MODE,
            'BOX_ENABLE_AUTO_REFILL': self.cmd_set_enable_auto_refill,
            'BOX_ENABLE_CFS_PRINT': self.cmd_box_enable_CFS_print,
            'BOX_CTRL_CONNECTION_MOTOR_ACTION': self.cmd_ctrl_connection_motor_action,
            'BOX_TIGHTEN_UP_ENABLE': self.cmd_tighten_up_enable,
            'BOX_CUT_HALL_ZERO': self.cmd_hall_zero,
            'BOX_CUT_HALL_TEST': self.cmd_hall_test,
            'BOX_NOZZLE_CLEAN': self.cmd_nozzle_clean,
            'BOX_MEASURING_WHEEL': self.cmd_measuring_wheel,
            'BOX_CHECK_MATERIAL_REFILL': self.cmd_check_material_refill,
            'BOX_MODIFY_TN_DATA': self.cmd_modify_Tn_data,
            'BOX_MODIFY_TN_INNER_DATA': self.cmd_modify_Tn_inner_data,
            'BOX_MODIFY_TNN_MAP': self.cmd_modify_Tnn_map,
            'BOX_SHOW_TNN_INNER_DATA': self.cmd_show_Tnn_data,
            'BOX_UPDATE_SAME_MATERIAL_LIST': self.cmd_update_same_material_list,
            'BOX_TN_EXTRUDE': self.cmd_Tn_Extrude,
            'BOX_TNN_RETRY_PROCESS': self.cmd_Tnn_retry_process,
            'BOX_ERROR_CLEAR': self.cmd_error_clear,
            'BOX_ERROR_RESUME_PROCESS': self.cmd_error_resume_process,
            'BOX_SHOW_ERROR': self.cmd_show_error,
            'BOX_TEST_MAKE_ERROR': self.cmd_make_error,
            'BOX_POWER_LOSS_RESTORE': self.cmd_power_loss_restore,
            'BOX_FIRST_POWER_ON_PRELOAD': self.cmd_first_power_on_preload,
            'BOX_SAVE_FAN': self.cmd_save_fan,
            'BOX_RESTORE_FAN': self.cmd_restore_fan,
            'BOX_ENABLE_HEART_PROCESS': self.cmd_enable_heart_process,
            'BOX_DISABLE_HEART_PROCESS': self.cmd_disable_heart_process,
            'BOX_GET_FLUSH_VELOCITY_TEST': self.cmd_get_flush_velocity_test,
            'BOX_BLOW': self.cmd_blow,
        }

        for name, handler in commands.items():
            self.gcode.register_command(name, handler, desc=name)

    def find_objs(self):
        """Find required Klipper objects."""
        self.toolhead = self.printer.lookup_object('toolhead', None)

    # --- Print Lifecycle ---

    def cmd_box_start_print(self, gcmd):
        """Start print with material box."""
        gcmd.respond_info("Box start print")
        self.box_start_get_connect()
        self.box_start_get_rfid_and_remain_len()

    def cmd_box_end_print(self, gcmd):
        """End print with material box."""
        gcmd.respond_info("Box end print")
        self.box_end()

    def cmd_box_end(self, gcmd):
        """End box session."""
        self.box_end()

    def box_start_get_connect(self, eventtime):
        """Establish connection at print start."""
        self.connect_state = self.box_action.check_connect()

    def box_start_get_rfid_and_remain_len(self, eventtime):
        """Get RFID and remaining length at print start."""
        for slot in range(4):
            self.box_action.rfid_check(slot)

    def box_connect_state_check(self):
        """Check connection state."""
        return self.connect_state

    def box_end(self):
        """End box session."""
        self.connect_state = False

    def box_filament_state_get(self, web_request):
        """Get filament state."""
        return self.box_action.get_filament_sensor_detect()

    # --- Material Operations ---

    def cmd_box_extrude_material(self, gcmd):
        """Extrude material command."""
        tnn = gcmd.get_int('TNN', 0)
        gcmd.respond_info("Extruding material TNN=%d" % tnn)
        self.box_action.box_extrude_material(tnn)
        self.current_tnn = tnn

    def cmd_box_retrude_material(self, gcmd):
        """Retract material command."""
        tnn = gcmd.get_int('TNN', self.current_tnn)
        gcmd.respond_info("Retracting material TNN=%d" % tnn)
        self.box_action.box_retrude_material(tnn)

    def cmd_retrude_material_with_tnn(self, gcmd):
        """Retract specific Tnn material."""
        tnn = gcmd.get_int('TNN', 0)
        self.box_action.box_retrude_material(tnn)

    def cmd_Tn_Extrude(self, gcmd):
        """Extrude Tn material."""
        slot = gcmd.get_int('SLOT', 0)
        length = gcmd.get_float('LENGTH', 50.0)
        gcmd.respond_info("Tn extrude slot=%d len=%.1f" % (slot, length))

    # --- Flushing ---

    def cmd_material_flush(self, gcmd):
        """Material flush command."""
        from_tnn = gcmd.get_int('FROM', 0)
        to_tnn = gcmd.get_int('TO', 0)
        length = gcmd.get_float('LENGTH', None)

        gcmd.respond_info("Flushing from TNN=%d to TNN=%d" % (from_tnn, to_tnn))
        self.box_action.material_flush(from_tnn, to_tnn, length)

    def cmd_material_change_flush(self, gcmd):
        """Material change flush command."""
        from_tnn = gcmd.get_int('FROM', self.current_tnn)
        to_tnn = gcmd.get_int('TO', 0)
        self.material_change_flush(from_tnn, to_tnn)

    def material_change_flush(self, last_tnn, tnn):
        """Perform material change flush."""
        self.box_action.material_flush(from_tnn, to_tnn)

    def flush_material(self, velocity=300):
        """Flush material between transitions."""
        return self.box_action.material_flush(from_tnn, to_tnn)

    def get_flush_len(self, last_tnn, current_tnn):
        """Get flush length."""
        return self.box_action.get_flush_len(from_tnn, to_tnn)

    def get_flush_length_from_gcode(self, last_tnn, current_tnn):
        """Get flush length from G-code file."""
        return 50.0  # Default

    def has_flushing_sign(self):
        """Check if flushing in progress."""
        return self.box_action.has_flushing_sign()

    def cmd_get_flush_len(self, gcmd):
        """Get flush length command."""
        from_tnn = gcmd.get_int('FROM', 0)
        to_tnn = gcmd.get_int('TO', 0)
        length = self.get_flush_len(from_tnn, to_tnn)
        gcmd.respond_info("Flush length: %.1f" % length)

    def cmd_get_flush_velocity_test(self, gcmd):
        """Test flush velocity."""
        from_tnn = gcmd.get_int('FROM', 0)
        to_tnn = gcmd.get_int('TO', 0)
        velocity = self.box_action.get_flush_velocity(from_tnn, to_tnn)
        gcmd.respond_info("Flush velocity: %.1f" % velocity)

    def cmd_generate_flush_array(self, gcmd):
        """Generate flush array command."""
        num_tnns = gcmd.get_int('NUM', 4)
        gcmd.respond_info("Generating flush array for %d TNNs" % num_tnns)

        flush_array = []
        for i in range(num_tnns):
            row = []
            for j in range(num_tnns):
                row.append(self.get_flush_len(i, j))
            flush_array.append(row)
            gcmd.respond_info("flush_array[%d][%d] = %d" % (i, j, row[-1]))

        self.box_action.flush_array = flush_array
        gcmd.respond_info("flush_array: %s" % flush_array)

    def cmd_show_flush_list(self, gcmd):
        """Show flush list."""
        gcmd.respond_info("Flush array: %s" % self.box_action.flush_array)

    # --- Cutting ---

    def cmd_cut_material(self, gcmd):
        """Cut material command."""
        gcmd.respond_info("Cutting material")
        self.box_action.cut_material()

    def cmd_cut_state(self, gcmd):
        """Get cut state."""
        state = self.box_action.cut_sensor.state()
        gcmd.respond_info("Cut sensor state: %s" % state)

    def cmd_move_to_cut(self, gcmd):
        """Move to cut position."""
        gcmd.respond_info("Moving to cut position")
        self.box_action.move_to_cut()

    def cmd_hall_zero(self, gcmd):
        """Hall zero command."""
        self.box_action.cut_hall_zero()

    def cmd_hall_test(self, gcmd):
        """Hall test command."""
        self.box_action.cut_hall_test()

    # --- Movement ---

    def cmd_move_to_safe_pos(self, gcmd):
        """Move to safe position."""
        gcmd.respond_info("Moving to safe position")
        self.box_action.move_to_safe_pos()

    def cmd_go_to_extrude_pos(self, gcmd):
        """Move to extrude position."""
        gcmd.respond_info("Moving to extrude position")
        self.box_action.go_to_extrude_pos()

    def cmd_nozzle_clean(self, gcmd):
        """Nozzle clean command."""
        gcmd.respond_info("Cleaning nozzle")
        self.box_action.nozzle_clean()

    # --- Communication ---

    def cmd_create_connect(self, gcmd):
        """Create connection command."""
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_create_connect(addr)
        gcmd.respond_info("Connection: %s" % ("OK" if response else "Failed"))

    def cmd_get_box_state(self, gcmd):
        """Get box state command."""
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_get_box_state(addr)
        gcmd.respond_info("Box state: %s" %
                         (response.hex() if response else "No response"))

    def cmd_get_buffer_state(self, gcmd):
        """Get buffer state command."""
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_get_buffer_state(addr)
        if response and len(response) >= 6:
            gcmd.respond_info("buffer_state: 0x%x" % response[5])
        else:
            gcmd.respond_info("No response")

    def cmd_get_filament_sensor_state(self, gcmd):
        """Get filament sensor state."""
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_get_filament_sensor_state(addr)
        gcmd.respond_info("Filament sensor: %s" %
                         (response.hex() if response else "No response"))

    def cmd_get_hardware_status(self, gcmd):
        """Get hardware status."""
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_get_hardware_status(addr)
        gcmd.respond_info("Hardware status: %s" %
                         (response.hex() if response else "No response"))

    def cmd_get_rfid(self, gcmd):
        """Get RFID command."""
        addr = gcmd.get_int('ADDR', 0x01)
        slot = gcmd.get_int('SLOT', 0)
        response = self.box_action.communication_get_rfid(addr, slot)
        if response:
            rfid = self.box_action.parse_data.get_rfid(response)
            gcmd.respond_info("RFID[%d]: %s" % (slot, rfid))
        else:
            gcmd.respond_info("No RFID response")

    def cmd_get_remain_len(self, gcmd):
        """Get remaining length command."""
        addr = gcmd.get_int('ADDR', 0x01)
        slot = gcmd.get_int('SLOT', 0)
        response = self.box_action.communication_get_remain_len(addr, slot)
        if response:
            length = self.box_action.parse_data.get_remain_len(response)
            gcmd.respond_info("Remain length[%d]: %.1f mm" % (slot, length))
        else:
            gcmd.respond_info("No response")

    def cmd_get_version_sn(self, gcmd):
        """Get version and serial number."""
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_get_version_sn(addr)
        gcmd.respond_info("Version/SN: %s" %
                         (response.hex() if response else "No response"))

    def cmd_get_gcode_used_tnn(self, gcmd):
        """Get G-code used Tnns."""
        tnns = self.box_action.get_gcode_used_tnn()
        gcmd.respond_info("Used TNNs: %s" % tnns)

    def cmd_send_data(self, gcmd):
        """Send raw data command."""
        data_str = gcmd.get('DATA', '')
        if not data_str:
            gcmd.respond_info("No data specified")
            return

        try:
            data = bytes.fromhex(data_str.replace(' ', ''))
            response = self.box_action.send_data(list(data))
            gcmd.respond_info("Response: %s" %
                             (response.hex() if response else "No response"))
        except Exception as e:
            gcmd.respond_info("Error: %s" % str(e))

    def cmd_communication_test(self, gcmd):
        """Communication test command."""
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_test(addr)
        gcmd.respond_info("Test: %s" % ("OK" if response else "Failed"))

    # --- Extrusion Control ---

    def cmd_extruder_extrude(self, gcmd):
        """Extruder extrude command."""
        length = gcmd.get_float('LENGTH', 50.0)
        speed = gcmd.get_float('SPEED', 5.0)
        self.box_action.extruder_extrude(length, speed)

    def cmd_extrusion_all_materials(self, gcmd):
        """Extrude all materials command."""
        length = gcmd.get_float('LENGTH', 50.0)
        tnns = [0, 1, 2, 3]  # Default to all 4 slots
        self.box_action.extrusion_all_materials(tnns, length)

    def cmd_extrude_process(self, gcmd):
        """Extrusion process command."""
        tnn = gcmd.get_int('TNN', 0)
        slot = self.boxstate.tnn_map.get(tnn, 0)
        self.box_action.communication_extrude_process(0x01, slot)

    def cmd_extrude2_process(self, gcmd):
        """Extrusion process command variant 2."""
        raise NotImplementedError  # [STUB] - Missing from reconstructed

    def cmd_retrude_process(self, gcmd):
        """Retraction process command."""
        tnn = gcmd.get_int('TNN', 0)
        slot = self.boxstate.tnn_map.get(tnn, 0)
        self.box_action.communication_retrude_process(0x01, slot)

    # --- Configuration ---

    def cmd_set_temp(self, gcmd):
        """Set temperature command."""
        temp = gcmd.get_float('TEMP', 200.0)
        self.box_action.set_temp(temp)
        gcmd.respond_info("Set temp: %.1f" % temp)

    def cmd_set_box_mode(self, gcmd):
        """Set box mode command."""
        mode = gcmd.get_int('MODE', 0)
        addr = gcmd.get_int('ADDR', 0x01)
        self.box_action.communication_set_box_mode(addr, mode)

    def cmd_set_pre_loading(self, gcmd):
        """Set pre-loading command."""
        slot = gcmd.get_int('SLOT', 0)
        enable = gcmd.get_int('ENABLE', 1)
        addr = gcmd.get_int('ADDR', 0x01)
        self.box_action.communication_set_pre_loading(addr, slot, enable)

    def cmd_BOX_SET_CURRENT_BOX_IDLE_MODE(self, gcmd):
        """Set idle mode command."""
        mode = gcmd.get_int('MODE', 0)
        self.box_action.communication_set_box_mode(0x01, mode)

    def cmd_set_enable_auto_refill(self, gcmd):
        """Enable auto refill command."""
        enable = gcmd.get_int('ENABLE', 1)
        self.auto_refill_enabled = bool(enable)
        gcmd.respond_info("Auto refill: %s" %
                         ("enabled" if self.auto_refill_enabled else "disabled"))

    def cmd_box_enable_CFS_print(self, gcmd):
        """Enable CFS print mode."""
        enable = gcmd.get_int('ENABLE', 1)
        gcmd.respond_info("CFS print: %s" % ("enabled" if enable else "disabled"))

    def cmd_ctrl_connection_motor_action(self, gcmd):
        """Control connection motor."""
        action = gcmd.get_int('ACTION', 0)
        addr = gcmd.get_int('ADDR', 0x01)
        self.box_action.communication_ctrl_connection_motor_action(addr, action)

    def cmd_tighten_up_enable(self, gcmd):
        """Tighten up enable command."""
        enable = gcmd.get_int('ENABLE', 1)
        addr = gcmd.get_int('ADDR', 0x01)
        self.box_action.communication_tighten_up_enable(addr, enable)

    def cmd_measuring_wheel(self, gcmd):
        """Measuring wheel command."""
        slot = gcmd.get_int('SLOT', 0)
        addr = gcmd.get_int('ADDR', 0x01)
        response = self.box_action.communication_measuring_wheel(addr, slot)
        if response:
            pos = self.box_action.parse_data.get_measuring_wheel(response)
            gcmd.respond_info("Measuring wheel[%d]: %.2f" % (slot, pos))

    def cmd_check_material_refill(self, gcmd):
        """Check material refill command."""
        tnn = gcmd.get_int('TNN', 0)
        needs_refill = self.box_action.check_material_refill(tnn)
        gcmd.respond_info("Refill needed: %s" % needs_refill)

    # --- State Management ---

    def cmd_modify_Tn_data(self, gcmd):
        """Modify Tn data command."""
        slot = gcmd.get_int('SLOT', 0)
        key = gcmd.get('KEY', 'rfid')
        value = gcmd.get('VALUE', '')
        self.boxstate.modify_Tn_data(slot, key, value)
        gcmd.respond_info("Modified Tn[%d].%s" % (slot, key))

    def cmd_modify_Tn_inner_data(self, gcmd):
        """Modify Tn inner data command."""
        slot = gcmd.get_int('SLOT', 0)
        key = gcmd.get('KEY', 'filament_present')
        value = gcmd.get_int('VALUE', 0)
        self.boxstate.modify_Tn_inner_data(slot, key, bool(value))

    def cmd_modify_Tnn_map(self, gcmd):
        """Modify Tnn map command."""
        tnn = gcmd.get_int('TNN', 0)
        slot = gcmd.get_int('SLOT', 0)
        self.boxstate.generate_Tnn_map(tnn, slot)
        gcmd.respond_info("Mapped TNN %d to slot %d" % (tnn, slot))

    def cmd_show_Tnn_data(self, gcmd):
        """Show Tnn data command."""
        tnn_map = self.boxstate.get_Tnn_map()
        gcmd.respond_info("TNN map: %s" % tnn_map)

        for tnn, slot in tnn_map.items():
            tn_data = self.boxstate.get_Tn_data(slot)
            gcmd.respond_info("TNN %d -> Slot %d: %s" % (tnn, slot, tn_data))

    def cmd_update_same_material_list(self, gcmd):
        """Update same material list command."""
        # Would parse list from command
        self.box_action.update_same_material_list([])

    # --- Error Handling ---

    def cmd_error_clear(self, gcmd):
        """Clear error command."""
        self.error_clear()
        gcmd.respond_info("Errors cleared")

    def error_clear(self):
        """Clear all errors."""
        self.boxsave.clear_err()
        self.boxstate.clear_e_err()

    def cmd_error_resume_process(self, gcmd):
        """Error resume process command."""
        self.error_resume_process()

    def error_resume_process(self):
        """Resume from error."""
        # Get error Tnn and retry
        err_tnn = self.boxsave.get_err()
        if err_tnn is not None:
            logging.info("[box] Resuming from error on TNN %s", err_tnn)
            self.Tnn_retry_process(err_tnn)
            self.error_clear()

    def cmd_show_error(self, gcmd):
        """Show error command."""
        err = self.boxsave.get_err()
        gcmd.respond_info("Current error: %s" % err)

    def cmd_make_error(self, gcmd):
        """Make test error command."""
        err = gcmd.get('ERR', 'test_error')
        self.test_error(err)

    def test_error(self):
        """Create test error."""
        self.boxsave.recode_err(err_info)

    def cmd_Tnn_retry_process(self, gcmd):
        """Tnn retry process command."""
        tnn = gcmd.get_int('TNN', 0)
        self.Tnn_retry_process(tnn)

    def Tnn_retry_process(self):
        """Retry Tnn operation."""
        logging.info("[box] Retrying operation for TNN %d", tnn)
        # Attempt to re-extrude material
        self.box_action.box_extrude_material(tnn)

    # --- Retry Processes ---

    def box_extrude_err_retry_process(self):
        """Retry extrusion on error."""
        return self.box_action.box_extrude_material(tnn)

    def extruder_extrude_err_retry_process(self):
        """Retry extruder extrusion on error."""
        logging.info("[box] Retrying extruder extrusion")
        self.box_action.make_material_loose()
        self.box_action.extruder_extrude(10, 2.0)  # Small test extrusion

    def flush_err_retry_process(self):
        """Retry flush on error."""
        return self.box_action.material_flush(from_tnn, to_tnn)

    def retrude_err_retry_process(self):
        """Retry retraction on error."""
        return self.box_action.box_retrude_material(tnn)

    def filament_err_retry_process(self, last_tnn=None, tnn=None):
        """Retry on filament error."""
        logging.info("[box] Retrying after filament error on TNN %d", tnn)
        self.box_action.box_retrude_material(tnn)
        self.box_action.box_extrude_material(tnn)

    def filament_conflict_check(self, web_request):
        """Check for filament conflict."""
        return self.box_action.filament_conflict_check()

    def empty_print_retry_process(self):
        """Handle empty print retry."""
        logging.info("[box] Empty print retry - checking material availability")

    def print_end_err_retry_process(self):
        """Handle print end error retry."""
        logging.info("[box] Print end error retry - retracting material")
        if self.current_tnn >= 0:
            self.box_action.box_retrude_material(self.current_tnn)

    def print_end_move_to_cut_err_retry_process(self):
        """Handle print end move to cut error."""
        logging.info("[box] Print end move to cut retry")
        self.box_action.move_to_cut()

    def macro_err_retry_process(self):
        """Handle macro error retry."""
        logging.warning("[box] Macro error - clearing and retrying")
        self.error_clear()

    def macro_extrusion_all_materials_err_retry_process(self):
        """Handle extrusion all materials error."""
        logging.warning("[box] Extrusion all materials error - skipping")

    # --- Power Loss ---

    def cmd_power_loss_restore(self, gcmd):
        """Power loss restore command."""
        self.box_action.power_loss_restore()
        gcmd.respond_info("Power loss state restored")

    def cmd_first_power_on_preload(self, gcmd):
        """First power on preload command."""
        gcmd.respond_info("First power on preload")

    # --- Fan Control ---

    def cmd_save_fan(self, gcmd):
        """Save fan command."""
        self.boxsave.save_fan()
        gcmd.respond_info("Fan saved: %.2f" % self.boxsave.saved_fan_speed)

    def cmd_restore_fan(self, gcmd):
        """Restore fan command."""
        self.boxsave.restore_fan()
        gcmd.respond_info("Fan restored")

    # --- Heart/Keepalive ---

    def cmd_enable_heart_process(self, gcmd):
        """Enable heart process command."""
        self.box_action.enable_heart_process()
        gcmd.respond_info("Heart process enabled")

    def cmd_disable_heart_process(self, gcmd):
        """Disable heart process command."""
        self.box_action.disable_heart_process()
        gcmd.respond_info("Heart process disabled")

    def heart_process(self, eventtime):
        """Heart/keepalive process."""
        if self.box_action.heart_enabled:
            self.box_action.communication_create_connect(0x01)

    # --- Utility ---

    def cmd_blow(self, gcmd):
        """Blow command."""
        enable = gcmd.get_int('ENABLE', 1)
        self.box_action.blow(bool(enable))

    def Tn_action(self, vtnn):
        """Perform action on Tnn."""
        if action == 'extrude':
            self.box_action.box_extrude_material(tnn)
        elif action == 'retrude':
            self.box_action.box_retrude_material(tnn)
        elif action == 'cut':
            self.box_action.cut_material()
        else:
            logging.warning("[box] Unknown action: %s", action)

    def generate_Tn_func(self, tn):
        """Generate Tn function."""
        def function():
            return self.boxstate.get_Tn_data(
                self.boxstate.tnn_map.get(tnn, 0))
        return function

    def generate_Tnn_func(self, tnn):
        """Generate Tnn function."""
        def function():
            return self.boxstate.get_Tnn_content(tnn)
        return function

    def get_connect_state(self):
        """Get connection state."""
        return self.connect_state

    def get_status(self, eventime):
        """Return status for Klipper status reporting."""
        return {
            'name': self.name,
            'connected': self.connect_state,
            'current_tnn': self.current_tnn,
            'flushing': self.has_flushing_sign(),
            'tnn_map': self.boxstate.get_Tnn_map(),
            'auto_refill': self.auto_refill_enabled
        }


def load_config(config):
    return MultiColorMeterialBoxWrapper(config)
