# ===========================================================================
# MERGED FILE: Accurate signatures from live introspection + inferred implementations
#
# SIGNATURE SOURCE: Live printer introspection (ACCURATE)
# IMPLEMENTATION: Reverse engineered (INFERRED - may have errors)
#
# Parameter names in implementations may still use old names.
# See PARAM_MAPPING comments for required renames.
# ===========================================================================

# Reconstructed from motor_control_wrapper.cpython-39.so
# Original: klippy/extras/motor_control_wrapper.py
# Creality K2 Series - Closed-Loop Motor Control via RS-485
#
# Copyright (C) Creality
# Reverse engineered by Claude Code
#
# This file may be distributed under the terms of the GNU GPLv3 license.
#
# Purpose: Interface for closed-loop stepper motors using RS-485 bus.
# Provides calibration, protection, and monitoring for X/Y/Z/E motors.
#
# =============================================================================
# PROVENANCE NOTICE - READ BEFORE USING THIS CODE
# =============================================================================
#
# This file was reconstructed through reverse engineering. The code quality
# and accuracy varies by section:
#
# EXTRACTED (high confidence) - Directly from binary strings or decompiled C:
#   - Function/method names
#   - Configuration parameter names (motor_x_stall, motor_closed_loop, etc.)
#   - Log message strings
#   - G-code command names (MOTOR_BOOT, MOTOR_CONTROL, etc.)
#   - RS-485 motor addresses (0x81-0x85)
#   - Error message JSON structures
#   - Packet format from msgblock_485_decompiled.c
#
# INFERRED (lower confidence) - Educated guesses based on:
#   - Function names implying behavior
#   - Common Klipper extension patterns
#   - RS-485 protocol conventions
#   - 3D printer firmware patterns
#
# Sections are marked with:
#   # [EXTRACTED] - From binary strings or decompiled code
#   # [INFERRED]  - Logic reconstructed from context/patterns
#   # [PARTIAL]   - Mix of extracted names with inferred logic
#
# =============================================================================

import logging
import time

# [EXTRACTED] Motor address mapping - from binary strings showing "motor_x 81", etc.
MOTOR_MAP = {
    'x': 0x81,
    'y': 0x82,
    'z': 0x83,
    'z1': 0x84,
    'e': 0x85
}

# [EXTRACTED] Motor identifiers - from binary strings
MOTOR_NUM = 5
MOTOR_IDS = ['x', 'y', 'z', 'z1', 'e']

# [INFERRED] Motor command function codes - these values are GUESSES
# The command NAMES are extracted, but the actual byte values (0x01, 0x02, etc.)
# are not known and were assigned sequentially as a reasonable assumption.
CMD_BOOT = 0x01
CMD_REBOOT = 0x02
CMD_CONTROL = 0x03
CMD_GET = 0x04
CMD_VERSION = 0x05
CMD_SYS_PARAM = 0x06
CMD_FLASH_PARAM = 0x07
CMD_SET_ADDR = 0x08
CMD_READ_ADDR = 0x09
CMD_ELEC_CALIBRATE = 0x0A
CMD_ENCODER_CALIBRATE = 0x0B
CMD_CLEAR_ERR = 0x0C
CMD_PROTECTION = 0x0D
CMD_READ_PIN = 0x0E
CMD_STALL_MODE = 0x0F

# [INFERRED] Error/warning codes - completely guessed based on common motor driver errors
# No evidence for these specific bit mappings
motor_error_dict = {
    0x01: "Over current",
    0x02: "Over voltage",
    0x04: "Under voltage",
    0x08: "Over temperature",
    0x10: "Motor stall",
    0x20: "Encoder error",
    0x40: "Communication error",
    0x80: "Internal error"
}

motor_warning_dict = {
    0x01: "Temperature warning",
    0x02: "Current warning",
    0x04: "Voltage warning",
    0x08: "Position warning"
}


class ParseData:
    """Protocol data parsing utilities for motor control."""

    def __init__(self):
        pass

    def get_cmd_num(self, data_send, return_method):
        """Extract command number from response."""
        raise NotImplementedError  # [STUB]

    def get_key_from_value(self, dict, v):
        """Get dictionary key from value."""
        raise NotImplementedError  # [STUB]

    def get_measuring_wheel(self, data_send, msg):
        """Get measuring wheel data."""
        raise NotImplementedError  # [STUB]

    def get_remain_len(self, data_send, msg):
        """Get remaining length data."""
        raise NotImplementedError  # [STUB]

    def get_rfid(self, msg):
        """Get RFID data from message."""
        raise NotImplementedError  # [STUB]

    def parse_num_string_to_byte(self, data):
        """Parse numeric string to bytes."""
        raise NotImplementedError  # [STUB]

    def parse_num_to_byte(self, data):
        """Parse number to bytes."""
        raise NotImplementedError  # [STUB]


# [PARTIAL] Class name extracted, but implementation is largely inferred
class Motor_Control:
    """
    Closed-loop motor control interface via RS-485.

    Manages communication with Creality's closed-loop stepper motors,
    providing calibration, protection, and monitoring functions.

    [EXTRACTED] G-code command names from binary strings:
        MOTOR_BOOT, MOTOR_CONTROL, MOTOR_GET, MOTOR_REBOOT, MOTOR_VERSION,
        MOTOR_SYS_PARAM, MOTOR_FLASH_PARAM, MOTOR_SET_ADDR, MOTOR_READ_ADDR,
        MOTOR_ELEC_OFFSET_CALIBRATE, MOTOR_ELEC_OFFSET_CALIBRATE_ALL,
        MOTOR_ENCODER_CALIBRATE_OFFICIAL, MOTOR_CLEAR_ERR_WARN_CODE,
        MOTOR_CHECK_PROTECTION_AFTER_HOME, MOTOR_AUTO_CHECK_PROTECTION,
        MOTOR_CHECK_CUT_POS, MOTOR_READ_PIN_IO, MOTOR_READ_ALL_PIN_IO,
        MOTOR_STALL_MODE

    [INFERRED] The actual implementation of each command handler is guessed
    based on command names and common motor control patterns.
    """

    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.name = config.get_name()

        # Configuration
        self.switch = config.getint('switch', default=0)
        self.motor_closed_loop = config.getint('motor_closed_loop', default=0)
        self.motor_addr_num = config.getint('motor_addr_num', default=4)

        # Motor pin configurations
        self.motor_x_step = config.get('motor_x_step', None)
        self.motor_x_dir = config.get('motor_x_dir', None)
        self.motor_y_step = config.get('motor_y_step', None)
        self.motor_y_dir = config.get('motor_y_dir', None)
        self.motor_z_step = config.get('motor_z_step', None)
        self.motor_z_dir = config.get('motor_z_dir', None)
        self.motor_z1_step = config.get('motor_z1_step', None)
        self.motor_z1_dir = config.get('motor_z1_dir', None)
        self.motor_e_step = config.get('motor_e_step', None)
        self.motor_e_dir = config.get('motor_e_dir', None)

        # Stall detection pins
        self.motor_x_stall = config.get('motor_x_stall', None)
        self.motor_y_stall = config.get('motor_y_stall', None)
        self.motor_z_stall = config.get('motor_z_stall', None)
        self.motor_z1_stall = config.get('motor_z1_stall', None)
        self.motor_e_stall = config.get('motor_e_stall', None)

        # Additional config
        self.enable_pin_pa9 = config.get('enable_pin_pa9', None)
        self.check_cut_pos_x_max = config.getfloat('check_cut_pos_x_max', default=350.0)
        self.extruder_flag = config.getboolean('extruder_flag', default=False)
        self.extruder_transparent = config.getboolean('extruder_transparent', default=False)

        # Serial communication
        self._serial = None

        # Motor state
        self.motor_status = {}
        self.motor_ready = False
        self.en_pin_state = True

        # Pin objects
        self._stall_pins = {}

        # Objects found later
        self.toolhead = None
        self.print_stats = None
        self.buttons = None

        # Register G-code commands
        self._register_commands()

        # Register event handlers
        self.printer.register_event_handler('klippy:ready', self._handle_ready)
        self.printer.register_event_handler('motor_control:extruder_motor_retry',
                                            self.extruder_motor_retry)
        self.printer.register_event_handler('motor_control:extruder_motor_err_clear',
                                            self.extruder_motor_err_clear)
        self.printer.register_event_handler('motor_control:extruder_motor_err_state',
                                            self.extruder_motor_err_state_query)

    # [INVENTED] This method does not exist in live module
    def _register_commands(self):
        """Register all G-code commands."""
        commands = [
            ('MOTOR_BOOT', self.motor_boot, 'Boot motor controller'),
            ('MOTOR_CONTROL', self.motor_control, 'Motor control command'),
            ('MOTOR_GET', self.motor_get, 'Get motor status'),
            ('MOTOR_REBOOT', self.motor_reboot, 'Reboot motor'),
            ('MOTOR_VERSION', self.motor_version, 'Get motor version'),
            ('MOTOR_SYS_PARAM', self.motor_sys_param, 'System parameters'),
            ('MOTOR_FLASH_PARAM', self.motor_flash_param, 'Flash parameters'),
            ('MOTOR_SET_ADDR', self.motor_set485_addr, 'Set RS-485 address'),
            ('MOTOR_READ_ADDR', self.motor_read485_addr, 'Read RS-485 address'),
            ('MOTOR_ELEC_OFFSET_CALIBRATE', self.motor_elec_offset_calibrate,
             'Electrical offset calibration'),
            ('MOTOR_ELEC_OFFSET_CALIBRATE_ALL', self.motor_elec_offset_calibrate_all,
             'Calibrate all motors'),
            ('MOTOR_ENCODER_CALIBRATE_OFFICIAL', self.motor_encoder_calibrate_official,
             'Official encoder calibration'),
            ('MOTOR_CLEAR_ERR_WARN_CODE', self.motor_clear_err_warn_code,
             'Clear error/warning codes'),
            ('MOTOR_CHECK_PROTECTION_AFTER_HOME', self.motor_check_protection_after_home,
             'Check protection after homing'),
            ('MOTOR_AUTO_CHECK_PROTECTION', self.motor_auto_check_protection,
             'Auto check protection'),
            ('MOTOR_CHECK_CUT_POS', self.motor_check_cut_pos, 'Check cut position'),
            ('MOTOR_READ_PIN_IO', self.motor_read_pin_io, 'Read pin IO'),
            ('MOTOR_READ_ALL_PIN_IO', self.motor_read_all_pin_io_status,
             'Read all pin IO'),
            ('MOTOR_STALL_MODE', self.motort_stall_mode, 'Set stall mode'),
            ('MOTOR_EXTRUDER_RETRY_PROCESS', self.cmd_MOTOR_EXTRUDER_RETRY_PROCESS,
             'Extruder retry process'),
            ('ZDOWN_FORCE_STOP', self.cmd_ZDOWN_FORCE_STOP, 'Force stop Z'),
            ('MOTOR_CANCEL_PRINT', self.motor_cancel_print_start, 'Cancel print'),
        ]

        for cmd_name, handler, desc in commands:
            self.gcode.register_command(cmd_name, handler, desc=desc)

    # [INVENTED] This method does not exist in live module
    def _handle_ready(self):
        """Handle klippy:ready event."""
        self.find_objs()
        if self.switch:
            self.motor_config_params_init()

    def find_objs(self):
        """Find required Klipper objects."""
        self.toolhead = self.printer.lookup_object('toolhead')
        try:
            self.print_stats = self.printer.lookup_object('print_stats')
        except Exception:
            pass
        try:
            self._serial = self.printer.lookup_object('serial_485 serial485')
        except Exception:
            logging.warning("Serial 485 not found")
        try:
            self.buttons = self.printer.lookup_object('buttons')
        except Exception:
            pass

    def motor_config_params_init(self):
        """Initialize motor configuration parameters."""
        start_time = time.time()

        # Initialize each motor axis
        self.motor_x_init()
        self.motor_y_init()
        self.motor_z_init()
        self.motor_z1_init()
        self.motor_e_init()

        # Initialize pin configuration
        self.motor_pin_init()
        self.button_stall_pin_init()

        elapsed = time.time() - start_time
        logging.info("motor_config_params_init use_time:%s", elapsed)

        self.motor_ready = True

    def motor_init(self, config):
        """Initialize motor system."""
        raise NotImplementedError  # [STUB] - Missing from reconstructed

    def _build_config(self):
        """Build motor configuration."""
        raise NotImplementedError  # [STUB] - Missing from reconstructed

    def motor_extruder_sys_param(self, gcmd):
        """Set extruder motor system parameters."""
        raise NotImplementedError  # [STUB] - Missing from reconstructed

    def motor_x_init(self, config):
        """Initialize X motor."""
        self._motor_init_axis('x', 0x81)

    def motor_y_init(self, config):
        """Initialize Y motor."""
        self._motor_init_axis('y', 0x82)

    def motor_z_init(self, config):
        """Initialize Z motor."""
        self._motor_init_axis('z', 0x83)

    def motor_z1_init(self, config):
        """Initialize Z1 motor."""
        self._motor_init_axis('z1', 0x84)

    def motor_e_init(self, config):
        """Initialize E motor (extruder)."""
        self._motor_init_axis('e', 0x85)
        if self.extruder_flag:
            self.motor_extruder_sys_param_init()

    # [INVENTED] This method does not exist in live module
    def _motor_init_axis(self, axis, addr):
        """Initialize a motor axis with default status."""
        self.motor_status[axis] = {
            'addr': addr,
            'initialized': False,
            'enabled': False,
            'error_code': 0,
            'warning_code': 0,
            'position': 0,
            'version': 'unknown'
        }
        # Send boot command
        if self._serial:
            data = self.data_pack(addr & 0x0F, CMD_BOOT, [])
            result = self.motor_send_data(data)
            if result:
                self.motor_status[axis]['initialized'] = True
                logging.info("Motor %s (0x%02X) initialized", axis, addr)

    def motor_pin_init(self):
        """Initialize motor GPIO pins for step/dir control."""
        # Set initial pin states for motor control
        pin_configs = [
            ('x', self.motor_x_step, self.motor_x_dir),
            ('y', self.motor_y_step, self.motor_y_dir),
            ('z', self.motor_z_step, self.motor_z_dir),
            ('z1', self.motor_z1_step, self.motor_z1_dir),
            ('e', self.motor_e_step, self.motor_e_dir),
        ]

        for axis, step_pin, dir_pin in pin_configs:
            if step_pin:
                logging.debug("Motor %s step pin: %s", axis, step_pin)
            if dir_pin:
                logging.debug("Motor %s dir pin: %s", axis, dir_pin)

    def button_stall_pin_init(self, config):
        """Initialize stall detection buttons/pins."""
        if not self.buttons:
            return

        stall_configs = [
            ('x', self.motor_x_stall, self._button_handler_x),
            ('y', self.motor_y_stall, self._button_handler_y),
            ('z', self.motor_z_stall, self._button_handler_z),
            ('z1', self.motor_z1_stall, self._button_handler_z1),
            ('e', self.motor_e_stall, self._button_handler_e),
        ]

        for axis, stall_pin, handler in stall_configs:
            if stall_pin:
                try:
                    self.buttons.register_buttons([stall_pin], handler)
                    logging.info("Registered stall button for motor %s", axis)
                except Exception as e:
                    logging.warning("Failed to register stall button %s: %s", axis, e)

    def _button_handler_x(self, eventtime, state):
        """Handle X motor stall button."""
        logging.info("X stall detected: state=%s", state)
        if state:
            self.motor_status['x']['error_code'] |= 0x10

    def _button_handler_y(self, eventtime, state):
        """Handle Y motor stall button."""
        logging.info("Y stall detected: state=%s", state)
        if state:
            self.motor_status['y']['error_code'] |= 0x10

    def _button_handler_z(self, eventtime, state):
        """Handle Z motor stall button."""
        logging.info("Z stall detected: state=%s", state)
        if state:
            self.motor_status['z']['error_code'] |= 0x10

    def _button_handler_z1(self, eventtime, state):
        """Handle Z1 motor stall button."""
        logging.info("Z1 stall detected: state=%s", state)
        if state:
            self.motor_status['z1']['error_code'] |= 0x10

    def _button_handler_e(self, eventtime, state):
        """Handle E motor stall button."""
        logging.info("E stall detected: state=%s", state)
        if state:
            self.motor_status['e']['error_code'] |= 0x10

    # ============================================
    # Data Packing and Communication
    # ============================================

    # [PARTIAL] Packet format from msgblock_485_decompiled.c, but byte ordering
    # and exact structure may differ from original
    def data_pack(self, addr, cmd, data):
        """
        Pack data for RS-485 transmission.

        [EXTRACTED] Format from decompiled msgblock_485.c:
            HEAD(0xF7) + ADDR + LEN + STATUS + FUNC + DATA + CRC

        [INFERRED] The exact byte positions and ordering are guesses.
        The HEAD byte is added by serial_485_queue, not here.
        """
        packet = bytearray()
        packet.append(0x80 + motor_num)  # [EXTRACTED] Address base 0x80 from strings
        packet.append(len(data_list) + 3)  # [INFERRED] Length calculation
        packet.append(0x00)  # [INFERRED] Status byte
        packet.append(cmd)  # [INFERRED] Function code position
        packet.extend(data_list)
        return bytes(packet)

    def data_pack_extruder(self, addr, cmd, data, id_params_type=''):
        """Pack data for extruder motor (address 0x85)."""
        return self.data_pack(5, cmd, data_list)

    # [INVENTED] This method does not exist in live module
    def motor_send_data(self, data, timeout=1.0):
        """Send data to motor controller via RS-485."""
        if self._serial:
            try:
                return self._serial.cmd_send_data_with_response(data, timeout)
            except Exception as e:
                logging.warning("motor_send_data failed: %s", e)
        return None

    def bytes_to_int(self, bytes_obj, is_data_obj=False):
        """Convert bytes to integer."""
        if not data:
            return 0
        return int.from_bytes(data, byteorder='big', signed=signed)

    def result_to_value(self, result, id_params_type):
        """Parse motor response to value."""
        if result and len(result) > 5:
            return result[5:]
        return None

    def validate_param(self, gcmd):
        """Validate parameter value and type."""
        if param_type == 'int':
            return isinstance(param, int)
        elif param_type == 'float':
            return isinstance(param, (int, float))
        return True

    def validate_num_params(self, gcmd):
        """Validate numeric parameter."""
        return gcmd.get_int(param_name, default=1)

    def validate_data_params(self, gcmd):
        """Validate data parameter."""
        return gcmd.get_int(param_name, default=0)

    def validate_id_params(self, gcmd):
        """Validate ID parameter."""
        return gcmd.get_int(param_name, default=0)

    def validate_param_type_params(self, gcmd):
        """Validate parameter type."""
        return gcmd.get(param_name, 'int')

    def check_and_retry(self, num, data, id, params, id_params_type, extruder=False):
        """Execute function with retry logic."""
        for i in range(max_retries):
            try:
                result = func(*args)
                if result:
                    return result
            except Exception as e:
                logging.warning("Retry %d failed: %s", i + 1, e)
        return None

    def check_protection_code(self, cur_obj, is_extruder=False):
        """Check motor protection code for axis."""
        addr = MOTOR_MAP.get(axis, 0)
        logging.info("motor_%s 8%X check_protection_code", axis, addr & 0x0F)

        # Query protection status
        data = self.data_pack(addr & 0x0F, CMD_PROTECTION, [])
        result = self.motor_send_data(data)

        if result:
            value = self.result_to_value(result)
            if value:
                error_code = value[0] if len(value) > 0 else 0
                warning_code = value[1] if len(value) > 1 else 0
                self.motor_status[axis]['error_code'] = error_code
                self.motor_status[axis]['warning_code'] = warning_code

                if error_code:
                    logging.warning("Motor %s protection error: 0x%02X", axis, error_code)
                    return False

        return True

    def check_motor_pin_io(self):
        """Check motor pin IO status."""
        def resend_set_io():
            """Resend set IO command."""
            data = self.data_pack(0, CMD_READ_PIN, [])
            return self.motor_send_data(data)

        result = self.check_and_retry(resend_set_io)
        if not result:
            logging.error('{"code":"key799", "msg":"Motor set pin init io status error", "values":["%s:%s"]}',
                         pin, "no response")
            return False
        return True

    def check_motor_pin_io_restore(self):
        """Restore motor pin IO status."""
        def resend_set_io():
            """Resend set IO restore command."""
            data = self.data_pack(0, CMD_READ_PIN, [0x01])  # Restore flag
            return self.motor_send_data(data)

        result = self.check_and_retry(resend_set_io)
        if not result:
            logging.error('{"code":"key800", "msg":"Motor set pin restore io status error", "values":["%s:%s"]}',
                         pin, "no response")
            return False
        return True

    # ============================================
    # G-code Command Handlers
    # ============================================

    def motor_boot(self, gcmd):
        """MOTOR_BOOT command - Boot motor controller."""
        num = self.validate_num_params(gcmd, 'NUM')
        logging.info("MOTOR_BOOT NUM=%d", num)

        data = self.data_pack(num, CMD_BOOT, [])
        result = self.motor_send_data(data)
        gcmd.respond_info("Motor %d boot: %s" % (num, "OK" if result else "FAIL"))

    def motor_control(self, gcmd):
        """MOTOR_CONTROL command - Enable/disable motor."""
        num = self.validate_num_params(gcmd, 'NUM')
        data = self.validate_data_params(gcmd, 'DATA')
        logging.info("MOTOR_CONTROL NUM=%d DATA=%d", num, data)

        # Check print state for pause handling
        if self.print_stats:
            state = self.print_stats.get_status(None).get('state', '')
            logging.info("motor_control print_stats.state:%s", state)

            if state == 'paused' and data == 0:
                logging.info("motor_control start PAUSE...")
                # Handle pause state
                logging.info("motor_control PAUSE END")
                return

        if data == 0:
            logging.info("motor_control disable start")
            # Disable motor
            cmd_data = self.data_pack(num, CMD_CONTROL, [0x00])
            result = self.motor_send_data(cmd_data)
            logging.info("motor_control disable end")
        else:
            # Enable motor
            cmd_data = self.data_pack(num, CMD_CONTROL, [0x01])
            result = self.motor_send_data(cmd_data)

        # Update status
        for axis, info in self.motor_status.items():
            if (info['addr'] & 0x0F) == num:
                info['enabled'] = (data != 0)
                break

    def motor_get(self, gcmd):
        """MOTOR_GET command - Get motor status."""
        num = self.validate_num_params(gcmd, 'NUM')
        data = self.validate_data_params(gcmd, 'DATA')

        cmd_data = self.data_pack(num, CMD_GET, [data])
        result = self.motor_send_data(cmd_data)
        value = self.result_to_value(result)

        gcmd.respond_info("MOTOR_GET NUM=%d DATA=%d Result=%s" % (num, data, value))

    def motor_reboot(self, gcmd):
        """MOTOR_REBOOT command - Reboot motor."""
        num = self.validate_num_params(gcmd, 'NUM')

        data = self.data_pack(num, CMD_REBOOT, [])
        result = self.motor_send_data(data)
        gcmd.respond_info("MOTOR_REBOOT NUM=%d: %s" % (num, "OK" if result else "FAIL"))

    def motor_version(self, gcmd):
        """MOTOR_VERSION command - Get motor firmware version."""
        num = self.validate_num_params(gcmd, 'NUM')

        data = self.data_pack(num, CMD_VERSION, [])
        result = self.motor_send_data(data)
        value = self.result_to_value(result)

        version_str = value.decode('ascii', errors='ignore') if value else "unknown"
        gcmd.respond_info("MOTOR_VERSION NUM=%d: %s" % (num, version_str))

    def motor_sys_param(self, gcmd):
        """MOTOR_SYS_PARAM command - Set system parameters."""
        num = self.validate_num_params(gcmd, 'NUM')
        data = self.validate_data_params(gcmd, 'DATA')
        param_id = self.validate_id_params(gcmd, 'ID')
        params = gcmd.get_float('PARAMS', 0.0)
        params_type = self.validate_param_type_params(gcmd, 'PARAMS_TYPE')

        # Pack parameter data
        if params_type == 'float':
            import struct
            param_bytes = list(struct.pack('>f', params))
        else:
            param_bytes = list(int(params).to_bytes(4, 'big', signed=True))

        cmd_data = self.data_pack(num, CMD_SYS_PARAM, [param_id] + param_bytes)
        result = self.motor_send_data(cmd_data)

        if result:
            logging.info("motor_sys_param update:%s success", param_id)
        else:
            logging.info("motor_sys_param update:%s fail", param_id)

    def motor_sys_param_init(self, num, data, id, params, id_params_type):
        """Initialize system parameters for motor."""
        # Read current params and update defaults
        logging.info("motor_sys_param_init for motor %d", num)

    def motor_extruder_sys_param_init(self, num, data, id, params, id_params_type):
        """Initialize extruder system parameters."""
        self.motor_sys_param_init(5)

    def motor_flash_param(self, gcmd):
        """MOTOR_FLASH_PARAM command - Flash parameters to motor EEPROM."""
        num = self.validate_num_params(gcmd, 'NUM')
        data = self.validate_data_params(gcmd, 'DATA')

        cmd_data = self.data_pack(num, CMD_FLASH_PARAM, [data])
        result = self.motor_send_data(cmd_data)
        gcmd.respond_info("MOTOR_FLASH_PARAM NUM=%d DATA=%d: %s" %
                         (num, data, "OK" if result else "FAIL"))

    def motor_set485_addr(self, gcmd):
        """MOTOR_SET_ADDR command - Set RS-485 address."""
        num = self.validate_num_params(gcmd, 'NUM')
        new_addr = self.validate_data_params(gcmd, 'ADDR')

        cmd_data = self.data_pack(num, CMD_SET_ADDR, [new_addr])
        result = self.motor_send_data(cmd_data)
        gcmd.respond_info("MOTOR_SET_ADDR NUM=%d: %s" % (num, "OK" if result else "FAIL"))

    def motor_read485_addr(self, gcmd):
        """MOTOR_READ_ADDR command - Read RS-485 address."""
        num = self.validate_num_params(gcmd, 'NUM')

        cmd_data = self.data_pack(num, CMD_READ_ADDR, [])
        result = self.motor_send_data(cmd_data)
        value = self.result_to_value(result)

        addr = self.bytes_to_int(value[:1]) if value else 0
        gcmd.respond_info("MOTOR_READ_ADDR NUM=%d: 0x%02X" % (num, addr))

    def motor_extruder_read485_addr(self, gcmd):
        """Read extruder RS-485 address."""
        cmd_data = self.data_pack_extruder(CMD_READ_ADDR, [])
        result = self.motor_send_data(cmd_data)
        value = self.result_to_value(result)
        return self.bytes_to_int(value[:1]) if value else 0

    def motor_extruder_set485_addr(self, gcmd):
        """Set extruder RS-485 address."""
        cmd_data = self.data_pack_extruder(CMD_SET_ADDR, [addr])
        return self.motor_send_data(cmd_data)

    def motor_elec_offset_calibrate(self, gcmd):
        """MOTOR_ELEC_OFFSET_CALIBRATE command - Electrical offset calibration."""
        num = self.validate_num_params(gcmd, 'NUM')

        cmd_data = self.data_pack(num, CMD_ELEC_CALIBRATE, [])
        result = self.motor_send_data(cmd_data, timeout=5.0)
        gcmd.respond_info("MOTOR_ELEC_OFFSET_CALIBRATE NUM=%d: %s" %
                         (num, "OK" if result else "FAIL"))

    def motor_elec_offset_calibrate_all(self, gcmd):
        """MOTOR_ELEC_OFFSET_CALIBRATE_ALL command - Calibrate all motors."""
        for num in range(1, 5):
            logging.info("MOTOR_ELEC_OFFSET_CALIBRATE NUM=%d", num)
            cmd_data = self.data_pack(num, CMD_ELEC_CALIBRATE, [])
            self.motor_send_data(cmd_data, timeout=5.0)
            self.reactor.pause(self.reactor.monotonic() + 1.0)

        gcmd.respond_info("All motors calibrated")

    def motor_extruder_elec_offset_calibrate(self, gcmd):
        """Calibrate extruder electrical offset."""
        cmd_data = self.data_pack_extruder(CMD_ELEC_CALIBRATE, [])
        return self.motor_send_data(cmd_data, timeout=5.0)

    def motor_encoder_calibrate_official(self, gcmd):
        """MOTOR_ENCODER_CALIBRATE_OFFICIAL command - Official encoder calibration."""
        num = self.validate_num_params(gcmd, 'NUM')

        cmd_data = self.data_pack(num, CMD_ENCODER_CALIBRATE, [])
        result = self.motor_send_data(cmd_data, timeout=10.0)
        gcmd.respond_info("MOTOR_ENCODER_CALIBRATE_OFFICIAL NUM=%d: %s" %
                         (num, "OK" if result else "FAIL"))

    def motor_extruder_encoder_calibrate_official(self, gcmd):
        """Official encoder calibration for extruder."""
        cmd_data = self.data_pack_extruder(CMD_ENCODER_CALIBRATE, [])
        return self.motor_send_data(cmd_data, timeout=10.0)

    def motor_clear_err_warn_code(self, gcmd):
        """MOTOR_CLEAR_ERR_WARN_CODE command - Clear error/warning codes."""
        num = self.validate_num_params(gcmd, 'NUM')
        data = self.validate_data_params(gcmd, 'DATA')

        if num == 0:
            # Clear all motors
            for motor_num in range(1, 6):
                cmd_data = self.data_pack(motor_num, CMD_CLEAR_ERR, [data])
                self.motor_send_data(cmd_data)
        else:
            cmd_data = self.data_pack(num, CMD_CLEAR_ERR, [data])
            self.motor_send_data(cmd_data)

        # Reset local status
        for axis in self.motor_status:
            self.motor_status[axis]['error_code'] = 0
            self.motor_status[axis]['warning_code'] = 0

        gcmd.respond_info("MOTOR_CLEAR_ERR_WARN_CODE NUM=%d DATA=%d" % (num, data))

    def motor_extruder_clear_err_warn_code(self):
        """Clear extruder error/warning codes."""
        cmd_data = self.data_pack_extruder(CMD_CLEAR_ERR, [0x05])
        return self.motor_send_data(cmd_data)

    def motor_check_protection_after_home(self, gcmd):
        """MOTOR_CHECK_PROTECTION_AFTER_HOME command."""
        data = self.validate_data_params(gcmd, 'DATA')
        logging.info("MOTOR_CHECK_PROTECTION_AFTER_HOME DATA=%d", data)

        # Check all motors for protection errors
        for axis in ['x', 'y', 'z', 'z1']:
            if not self.check_protection_code(axis):
                logging.warning("check_protection_code start M84")
                self.gcode.run_script_from_command("M84")
                logging.warning("check_protection_code end M84")
                return

        # Clear error codes after home
        logging.info("motor_check_protection_after_home MOTOR_CLEAR_ERR_WARN_CODE NUM=0 DATA=5")
        self.gcode.run_script_from_command("MOTOR_CLEAR_ERR_WARN_CODE NUM=0 DATA=5")

    def motor_auto_check_protection(self, gcmd):
        """MOTOR_AUTO_CHECK_PROTECTION command."""
        num = self.validate_num_params(gcmd, 'NUM')
        data = self.validate_data_params(gcmd, 'DATA')

        for axis in ['x', 'y', 'z', 'z1']:
            self.check_protection_code(axis)

        gcmd.respond_info("MOTOR_AUTO_CHECK_PROTECTION NUM=%d DATA=%d" % (num, data))

    def motor_check_cut_pos(self, gcmd):
        """MOTOR_CHECK_CUT_POS command - Check if at cut position."""
        if self.toolhead:
            pos = self.toolhead.get_position()
            at_cut_pos = pos[0] >= self.check_cut_pos_x_max
            gcmd.respond_info("At cut position: %s (X=%.2f)" % (at_cut_pos, pos[0]))
        else:
            gcmd.respond_info("Toolhead not available")

    def motor_read_pin_io(self, gcmd):
        """MOTOR_READ_PIN_IO command - Read pin IO status."""
        pin = gcmd.get('PIN', 'PB15')

        cmd_data = self.data_pack(0, CMD_READ_PIN, [])
        result = self.motor_send_data(cmd_data)
        value = self.result_to_value(result)

        gcmd.respond_info("MOTOR_READ_PIN_IO PIN=%s: %s" % (pin, value))

    def motor_read_all_pin_io_status(self, gcmd):
        """MOTOR_READ_ALL_PIN_IO command - Read all pin IO status."""
        gcmd.respond_info("Reading all pin IO status")

        for num in range(1, 6):
            cmd_data = self.data_pack(num, CMD_READ_PIN, [])
            result = self.motor_send_data(cmd_data)
            value = self.result_to_value(result)
            gcmd.respond_info("Motor %d pins: %s" % (num, value))

    def set_motor_pin(self):
        """Set motor GPIO pin value."""
        logging.debug("set_motor_pin %s = %d", pin, value)

    def set_motor_pin_dir(self, toolhead):
        """Set motor direction pin."""
        dir_pins = {
            'x': self.motor_x_dir,
            'y': self.motor_y_dir,
            'z': self.motor_z_dir,
            'z1': self.motor_z1_dir,
            'e': self.motor_e_dir,
        }
        dir_pin = dir_pins.get(motor)
        if dir_pin:
            self.set_motor_pin(dir_pin, direction)

    def set_motor_pin_normal(self, toolhead):
        """Set motor pins to normal operation."""
        self.set_motor_pin_dir(motor, 0)

    def motort_stall_mode(self, gcmd):
        """MOTOR_STALL_MODE command - Set stall detection mode."""
        data = self.validate_data_params(gcmd, 'DATA')

        # Set Z stall mode
        self.set_z_stall_mode(data)

        # Set E stall mode if extruder enabled
        if self.extruder_flag:
            self.set_e_stall_mode(data)

        gcmd.respond_info("MOTOR_STALL_MODE DATA=%d" % data)

    def set_z_stall_mode(self):
        """Set Z motor stall detection mode."""
        max_retries = 3
        for i in range(max_retries):
            cmd_data = self.data_pack(3, CMD_STALL_MODE, [mode])  # Z is motor 3
            result = self.motor_send_data(cmd_data)
            if result:
                logging.info("stall mode change motor_z: send:%d recv:%s", mode, result)
                return True

        logging.error('{"code":"key801", "msg":"Motor %s set_z_stall_mode failed, '
                     'exceeding maximum retry count", "values":["z"]}')
        return False

    def set_e_stall_mode(self):
        """Set E motor stall detection mode."""
        max_retries = 3
        for i in range(max_retries):
            cmd_data = self.data_pack_extruder(CMD_STALL_MODE, [mode])
            result = self.motor_send_data(cmd_data)
            if result:
                logging.info("stall mode change motor_e: send:%d recv:%s", mode, result)
                return True

        logging.error('{"code":"key802", "msg":"Motor e set_e_stall_mode failed, '
                     'exceeding maximum retry count", "values":["e"]}')
        return False

    # ============================================
    # Extruder Motor Functions
    # ============================================

    def motor_extruder_boot(self, gcmd):
        """Boot extruder motor."""
        cmd_data = self.data_pack_extruder(CMD_BOOT, [])
        return self.motor_send_data(cmd_data)

    def motor_extruder_reboot(self, gcmd):
        """Reboot extruder motor."""
        cmd_data = self.data_pack_extruder(CMD_REBOOT, [])
        return self.motor_send_data(cmd_data)

    def motor_extruder_control(self, gcmd):
        """Control extruder motor enable/disable."""
        cmd_data = self.data_pack_extruder(CMD_CONTROL, [0x01 if enable else 0x00])
        return self.motor_send_data(cmd_data)

    def motor_extruder_get(self, gcmd):
        """Get extruder motor parameter."""
        cmd_data = self.data_pack_extruder(CMD_GET, [param])
        result = self.motor_send_data(cmd_data)
        return self.result_to_value(result)

    def motor_extruder_protection(self, gcmd):
        """Check extruder motor protection status."""
        logging.info("motor_e 81 check_protection_code")
        return self.check_protection_code('e')

    def motor_extruder_flash_param(self, gcmd):
        """Flash extruder motor parameters."""
        cmd_data = self.data_pack_extruder(CMD_FLASH_PARAM, [0x00])
        return self.motor_send_data(cmd_data)

    def motor_extruder_version(self, gcmd):
        """Get extruder motor version."""
        cmd_data = self.data_pack_extruder(CMD_VERSION, [])
        result = self.motor_send_data(cmd_data)
        value = self.result_to_value(result)
        return value.decode('ascii', errors='ignore') if value else "unknown"

    def extruder_motor_err_state_query(self):
        """Query extruder motor error state."""
        cmd_data = self.data_pack_extruder(CMD_PROTECTION, [])
        result = self.motor_send_data(cmd_data)
        return self.result_to_value(result)

    def extruder_motor_err_clear(self):
        """Clear extruder motor errors."""
        logging.info("motor_control extruder_motor_err_clear start")
        self.motor_extruder_clear_err_warn_code()
        logging.info("motor_control extruder_motor_err_clear end")

    def extruder_motor_retry(self, eventtime):
        """Retry extruder motor operation after error."""
        logging.info("send_event motor_control:extruder_motor_retry")
        self.motor_extruder_boot()
        self.motor_extruder_clear_err_warn_code()

    def cmd_MOTOR_EXTRUDER_RETRY_PROCESS(self, gcmd):
        """MOTOR_EXTRUDER_RETRY_PROCESS command."""
        self.extruder_motor_retry()
        logging.info("hys: MOTOR_EXTRUDER_RETRY_PROCESS end")

    # ============================================
    # Force Stop and Cancel
    # ============================================

    def force_stop(self):
        """Force stop all motors."""
        for num in range(1, 6):
            cmd_data = self.data_pack(num, CMD_CONTROL, [0x00])
            self.motor_send_data(cmd_data)

        if self.toolhead:
            self.toolhead.motor_off()

    def web_force_stop(self, web_request):
        """Force stop from web interface."""
        self.force_stop()

    # [INVENTED] This method does not exist in live module
    def cmd_ZDOWN_FORCE_STOP(self, gcmd):
        """ZDOWN_FORCE_STOP command."""
        self.force_stop()
        gcmd.respond_info("Z force stop executed")

    # [INVENTED] This method does not exist in live module
    def motor_cancel_print_start(self, gcmd):
        """MOTOR_CANCEL_PRINT command - Handle cancel print."""
        logging.info("check_protection_code start CANCEL_PRINT")

        for axis in ['x', 'y', 'z', 'z1']:
            self.check_protection_code(axis)

        self.gcode.run_script_from_command("MOTOR_CLEAR_ERR_WARN_CODE NUM=0 DATA=5")
        logging.info("check_protection_code end CANCEL_PRINT")

    def transparent_send_gcmd(self, gcmd):
        """Transparent send for debugging - pass raw data."""
        data = gcmd.get('DATA', '')
        if data:
            data_bytes = bytes([int(x, 16) for x in data.split(',')])
            result = self.motor_send_data(data_bytes)
            gcmd.respond_info("Transparent send result: %s" % result)

    def get_status(self, eventime):
        """Return status for Klipper status reporting."""
        return {
            'ready': self.motor_ready,
            'switch': self.switch,
            'closed_loop': self.motor_closed_loop,
            'motors': self.motor_status
        }


def load_config(config):
    return Motor_Control(config)
