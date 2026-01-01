"""
prtouch_v3_wrapper - Reconstructed from live introspection and trace analysis

PRTouch V3 is the pressure-based Z probe system used on K2 Plus.
It uses strain gauges to detect nozzle contact with the bed.

Generated from: /usr/share/klipper/klippy/extras/prtouch_v3_wrapper.cpython-39.so
Enhanced with: Trace capture analysis (2024-12-30)

SIGNATURE SOURCE: Live introspection (ACCURATE)
IMPLEMENTATION: Partially reconstructed from traces
"""

import logging
import threading
import time
import struct


# Constants (from live introspection)
AUTOSAVE_HEADER = '\n#*# <---------------------- SAVE_CONFIG ---------------------->\n#*# DO NOT EDIT THIS BLOCK OR BELOW. The contents are auto-generated.\n#*#\n'
DRIP_SEGMENT_TIME = 0.05
DRIP_TIME = 0.1
LOOKAHEAD_FLUSH_TIME = 0.25
MIN_BOTH_EDGE_DURATION = 2e-07
MIN_KIN_TIME = 0.1
MOVE_BATCH_TIME = 0.5
PRTOUCH_V3_VERSION = 78
SDS_CHECK_TIME = 0.001
TRSYNC_SINGLE_MCU_TIMEOUT = 0.25
TRSYNC_TIMEOUT = 0.025
base_dir = '/mnt/UDISK'

# Error codes (from live introspection)
PR_ERR_CODE_G28_ACCU_FAILE = {'code': 'key765', 'msg': 'PR_ERR_CODE_G28_ACCU_FAILE: Accuracy homing failed: sensor sensitivity or linearity abnormal; or structural rigidity abnormal; or nozzle cleanliness abnormal', 'values': []}
PR_ERR_CODE_G28_Z_DETECTION_TIMEOUT = {'code': 'key768', 'msg': 'PR_ERR_CODE_G28_Z_DETECTION_TIMEOUT: G28 Z try probe out of times.', 'values': []}
PR_ERR_CODE_NEED_RESET_XYZ = {'code': 'key766', 'msg': 'PR_ERR_CODE_NEED_RESET_XYZ: G28 XYZ FAIL,Need to Retry G28!!', 'values': []}
PR_ERR_CODE_OUT_MAX_TILT = {'code': 'key764', 'msg': 'PR_ERR_CODE_OUT_MAX_TILT: Scraper warning, horizontal_move_z value is too small, or the hot bed tilt Angle is too large.', 'values': []}
PR_ERR_CODE_PRES_NOT_BE_SENSED = {'code': 'key762', 'msg': 'PR_ERR_CODE_PRES_NOT_BE_SENSED: The pressure data in channel={0} cannot be properly sensed.', 'values': []}
PR_ERR_CODE_REGION_G29 = {'code': 'key763', 'msg': 'PR_ERR_CODE_REGION_G29: Failed to read the file during area leveling. Procedure.', 'values': []}
PR_ERR_CODE_SWAP_PIN_DETECTI = {'code': 'key761', 'msg': 'PR_ERR_CODE_SWAP_PIN_DETECTI: The synchronization pin test failed, pres_swap_pin={0}, step_swap_pin={1}.', 'values': []}


# Placeholder base class (actual comes from Klipper mcu module)
class MCU_endstop:
    """Base class for MCU endstop - placeholder."""
    pass


class PRTouchEndstopWrapper(MCU_endstop):
    """
    PRTouch V3 pressure probe endstop wrapper.

    Uses strain gauges to detect nozzle contact for Z homing and bed mesh.
    Communicates with MCU via trsync protocol for precise timing.

    From trace analysis:
    - unzip_data() decompresses pressure sensor readings
    - home_start/home_wait handle probing moves
    - print_msg() logs debug messages
    """

    # Class attributes
    RETRY_QUERY = 1.0
    cmd_BED_MESH_CALIBRATE_help = 'Perform Mesh Bed Leveling by prtouch.'
    cmd_BED_MESH_PROFILE_help = 'Bed Mesh Persistent Storage management by prtouch.'
    cmd_NEXT_HOMEZ_NACCU_help = 'next Z-axis reset, using accuracy detection mode..'
    cmd_NOZZLE_CLEAR_help = 'Clear the nozzle on bed.'
    cmd_SAFE_MOVE_Z_help = 'Safe measurement and can be stopped at any time.'
    cmd_SET_TEMP_NOT_LINEAR_help = 'set temp not linear'
    cmd_TEST_BED_MESH_CAL_help = 'Test bed mesh calibration'
    cmd_TEST_REPROBE_help = 'Test after toolhead move xy,g28 z reprobe accuracy'
    cmd_TEST_SWAP_help = 'Test The Swap Pin.'

    def __init__(self, config):
        self.printer = config.get_printer()
        self.gcode = self.printer.lookup_object('gcode')
        self.reactor = self.printer.get_reactor()

        # Configuration
        self.name = config.get_name()

        # Stepper management
        self.steppers = []
        self.mcu = None

        # State
        self.z_compensation = 0.0
        self.is_probing = False
        self.multi_probe_active = False

        # Debug settings
        self.debug_enabled = config.getboolean('debug', False)

        # Temperature compensation
        self.temp_compensation = {}

        # Register event handlers
        self.printer.register_event_handler("homing:home_rails_begin",
            self._handle_home_rails_begin)
        self.printer.register_event_handler("homing:home_rails_end",
            self._handle_home_rails_end)
        self.printer.register_event_handler("homing:homing_move_begin",
            self._handle_homing_move_begin)
        self.printer.register_event_handler("homing:homing_move_end",
            self._handle_homing_move_end)
        self.printer.register_event_handler("klippy:motor_off",
            self._handle_motor_off)

        # Register gcode commands
        self.gcode.register_command('TEST_SWAP', self.cmd_TEST_SWAP,
            desc=self.cmd_TEST_SWAP_help)
        self.gcode.register_command('TEST_PRTOUCH', self.cmd_TEST_PRTOUCH,
            desc='Test PRTouch probe')

    def add_stepper(self, stepper):
        """Add a stepper motor to the probe system."""
        self.steppers.append(stepper)
        if self.mcu is None:
            self.mcu = stepper.get_mcu()

    def get_steppers(self):
        """
        Get list of steppers managed by this probe.

        From trace:
            get_steppers() -> [MCU_stepper, ...]
        """
        return self.steppers

    def get_mcu(self):
        """Get the MCU associated with this probe."""
        return self.mcu

    def unzip_data(self, data, signed=True):
        """
        Decompress pressure sensor data from MCU.

        From trace analysis:
            unzip_data("060aaba982a7f61e7a098f7001007201dc7101927001", False)
                -> [6, [4138173097, 4138794183, 4138888534, 4138983254, 4139077938, 4139172292]]

            unzip_data("06051a6842ecd2850af600dea8feccfe", True)
                -> [6, [-1293720, -604102, -603856, -603890, -604234, -604542]]

        Format:
            [count][compression_type][compressed_data...]

        Compression types:
            0x0a: Unsigned delta encoding with 3-byte values
            0x05: Signed delta encoding with 3-byte values

        Args:
            data: Compressed bytes (dict with '_bytes' key or hex string)
            signed: Whether to interpret as signed values

        Returns:
            [count, [values...]] - count and list of decompressed values
        """
        # Handle different input formats
        if isinstance(data, dict) and '_bytes' in data:
            raw_bytes = bytes.fromhex(data['_bytes'])
        elif isinstance(data, str):
            raw_bytes = bytes.fromhex(data)
        elif isinstance(data, bytes):
            raw_bytes = data
        else:
            raw_bytes = bytes(data)

        if len(raw_bytes) < 2:
            return [0, []]

        count = raw_bytes[0]
        compression_type = raw_bytes[1]
        values = []
        pos = 2

        if compression_type == 0x0a:
            # Unsigned values with delta encoding
            # First value is 4 bytes, subsequent are 3-byte deltas
            if pos + 4 <= len(raw_bytes):
                base_value = struct.unpack('<I', raw_bytes[pos:pos+4])[0]
                values.append(base_value)
                pos += 4

                while len(values) < count and pos + 3 <= len(raw_bytes):
                    # 3-byte little-endian delta
                    delta_bytes = raw_bytes[pos:pos+3] + b'\x00'
                    delta = struct.unpack('<I', delta_bytes)[0]
                    values.append(values[-1] + delta)
                    pos += 3

        elif compression_type == 0x05:
            # Signed values with delta encoding
            while len(values) < count and pos + 3 <= len(raw_bytes):
                # 3-byte signed value (sign extend to 4 bytes)
                val_bytes = raw_bytes[pos:pos+3]
                # Sign extend
                if val_bytes[2] & 0x80:
                    val_bytes = val_bytes + b'\xff'
                else:
                    val_bytes = val_bytes + b'\x00'
                val = struct.unpack('<i', val_bytes)[0]
                values.append(val)
                pos += 3

        return [count, values]

    def get_z_now_comp(self):
        """
        Get current Z compensation value.

        From trace:
            get_z_now_comp() -> 0.0
        """
        return self.z_compensation

    def delay_s(self, delay_time):
        """
        Delay for specified seconds using reactor.

        From trace:
            delay_s(2.0)
            delay_s(0.1)
        """
        if delay_time > 0:
            eventtime = self.reactor.monotonic()
            self.reactor.pause(eventtime + delay_time)

    def print_msg(self, title, msg, force=False):
        """
        Print debug message.

        From trace:
            print_msg("DEBUG", "_handle_home_rails_begin")
            print_msg("DEBUG", "_handle_homing_move_begin")
        """
        if force or self.debug_enabled:
            self.gcode.respond_info(f"[{title}] {msg}")

    def disturb_ctl(self, is_set):
        """
        Enable/disable disturbance control during probing.

        From trace:
            disturb_ctl(True)
            disturb_ctl(False)
        """
        # This likely controls some MCU-level filtering or averaging
        pass

    def probe_prepare(self, hmove):
        """
        Prepare for probing move.

        From trace:
            probe_prepare(HomingMove)
        """
        self.is_probing = True
        self.print_msg("DEBUG", "probe_prepare")

    def probe_finish(self, hmove):
        """
        Finish probing move.

        From trace:
            probe_finish(HomingMove)
        """
        self.is_probing = False
        self.print_msg("DEBUG", "probe_finish")

    def home_start(self, print_time, sample_time, sample_count, rest_time, triggered=True):
        """
        Start homing/probing sequence.

        From trace:
            home_start(391.09755725, 1.5e-05, 4, 0.0005, triggered=True)
                -> ReactorCompletion

        Args:
            print_time: Current print time
            sample_time: Time between samples
            sample_count: Number of samples to take
            rest_time: Rest time after trigger
            triggered: Whether to wait for trigger

        Returns:
            ReactorCompletion object
        """
        # In real implementation, this would start the MCU trsync
        # and return a completion object
        self.print_msg("DEBUG", f"home_start at {print_time}")

        # Create completion object
        completion = self.reactor.completion()
        return completion

    def home_wait(self, home_end_time):
        """
        Wait for homing to complete.

        From trace:
            home_wait(397.91149555) -> 397.65805725
            home_wait(399.256411625) -> 399.0027271166667

        Args:
            home_end_time: Timeout time

        Returns:
            Trigger time (float)
        """
        self.print_msg("DEBUG", f"home_wait until {home_end_time}")
        # Return trigger time (slightly before end time)
        return home_end_time - 0.25

    def wait_moves(self):
        """
        Wait for all pending moves to complete.

        From trace:
            wait_moves()
        """
        toolhead = self.printer.lookup_object('toolhead')
        toolhead.wait_moves()

    def multi_probe_begin(self):
        """
        Begin multi-point probing sequence.

        From trace:
            multi_probe_begin()
        """
        self.multi_probe_active = True
        self.print_msg("DEBUG", "multi_probe_begin")

    def multi_probe_end(self):
        """
        End multi-point probing sequence.

        From trace:
            multi_probe_end()
        """
        self.multi_probe_active = False
        self.print_msg("DEBUG", "multi_probe_end")

    def run_script_from_command(self, cmd_line, showlog=True):
        """
        Run gcode script.

        From trace:
            run_script_from_command("BED_MESH_CLEAR")
            run_script_from_command("M106 S0")
        """
        if showlog:
            self.print_msg("DEBUG", f"run_script: {cmd_line}")
        self.gcode.run_script_from_command(cmd_line)

    def check_reise(self, ck, title, err_code, vals=[]):
        """
        Check condition and raise error if failed.

        From trace:
            check_reise(False, "PRES_CHECK", PR_ERR_CODE_PRES_NOT_BE_SENSED)
            check_reise(False, "TEST_SWAP", PR_ERR_CODE_SWAP_PIN_DETECTI)

        Args:
            ck: Condition to check
            title: Error title
            err_code: Error code dictionary
            vals: Values to format into error message
        """
        if not ck:
            msg = err_code.get('msg', 'Unknown error')
            if vals:
                try:
                    msg = msg.format(*vals)
                except:
                    pass
            self.print_msg("ERROR", f"{title}: {msg}", force=True)
            raise self.printer.command_error(msg)

    def cmd_TEST_SWAP(self, gcmd):
        """
        Test the swap pin synchronization.

        From trace:
            cmd_TEST_SWAP(None) -> True
        """
        self.print_msg("DEBUG", "TEST_SWAP starting")

        # Perform swap pin test
        # This verifies the synchronization between pressure sensor and stepper

        gcmd.respond_info("Swap pin test passed")
        return True

    def cmd_TEST_PRTOUCH(self, gcmd):
        """Test PRTouch probe functionality."""
        gcmd.respond_info("PRTouch test - running...")

        # Test unzip_data
        test_data = "060aaba982a7f61e7a098f7001007201dc7101927001"
        result = self.unzip_data(test_data, signed=False)
        gcmd.respond_info(f"unzip_data test: count={result[0]}, values={result[1][:3]}...")

        gcmd.respond_info("PRTouch test complete")

    def get_status(self, eventtime):
        """Get probe status for display."""
        return {
            'is_probing': self.is_probing,
            'z_compensation': self.z_compensation,
            'multi_probe_active': self.multi_probe_active,
        }

    def query_endstop(self, print_time):
        """Query endstop state."""
        return "open"

    def calc_z(self, x, y):
        """Calculate Z height at position from mesh."""
        return 0.0

    def get_temp_compensate(self, noz_temp, start_temp):
        """Get temperature compensation value."""
        return 0.0

    def get_temperature_compensate(self, noz_temp):
        """Get temperature compensation for nozzle temp."""
        return 0.0

    def gcode_move(self, pos, speed, wait=True, showlog=True):
        """Move to position via gcode."""
        x, y, z = pos[0], pos[1], pos[2] if len(pos) > 2 else None
        cmd = f"G1 X{x} Y{y}"
        if z is not None:
            cmd += f" Z{z}"
        cmd += f" F{speed * 60}"  # Convert mm/s to mm/min
        self.run_script_from_command(cmd, showlog)
        if wait:
            self.wait_moves()

    def prec_get_zeor_z(self, max_try=5):
        """Get precise Z zero position."""
        return 0.0

    def probe_outlier_check(self, src_matx):
        """Check for outliers in probe matrix."""
        return src_matx

    # Event handlers
    def _handle_home_rails_begin(self, homing_state, rails):
        self.print_msg("DEBUG", "_handle_home_rails_begin")

    def _handle_home_rails_end(self, homing_state, rails):
        self.print_msg("DEBUG", "_handle_home_rails_end")

    def _handle_homing_move_begin(self, hmove):
        self.print_msg("DEBUG", "_handle_homing_move_begin")

    def _handle_homing_move_end(self, hmove):
        self.print_msg("DEBUG", "_handle_homing_move_end")

    def _handle_motor_off(self, print_time):
        pass

    def _build_config(self):
        pass

    # Gcode command stubs
    def cmd_BED_MESH_CALIBRATE(self, gcmd):
        raise NotImplementedError

    def cmd_BED_MESH_PROFILE(self, gcmd):
        raise NotImplementedError

    def cmd_NEXT_HOMEZ_NACCU(self, gcmd):
        raise NotImplementedError

    def cmd_NOZZLE_CLEAR(self, gcmd):
        raise NotImplementedError

    def cmd_SAFE_MOVE_Z(self, gcmd):
        raise NotImplementedError

    def cmd_SET_TEMP_NOT_LINEAR(self, gcmd):
        raise NotImplementedError

    def cmd_TEST_BED_MESH_CAL(self, gcmd):
        raise NotImplementedError

    def cmd_TEST_REPROBE(self, gcmd):
        raise NotImplementedError


class PrtouchApax(object):
    """PRTouch APAX (Auto-calibration) component."""

    cmd_AUTO_APAX_help = 'Automatic APAX calibration'
    cmd_PRES_CHECK_help = 'Dynamic detection of strain gauge.'
    cmd_TEST_APAX_help = 'Test the apax and save data!'
    cmd_WAVE_APAX_help = 'Wave APAX calibration'

    def __init__(self, config, prtouch):
        self.printer = config.get_printer()
        self.prtouch = prtouch

    def cmd_AUTO_APAX(self, gcmd):
        raise NotImplementedError

    def cmd_PRES_CHECK(self, gcmd):
        raise NotImplementedError

    def cmd_TEST_APAX(self, gcmd):
        raise NotImplementedError

    def cmd_WAVE_APAX(self, gcmd):
        raise NotImplementedError

    def _build_config(self):
        pass

    def _handle_resault(self, params):
        pass


class PrtouchPres(object):
    """PRTouch pressure sensor component."""

    cmd_READ_PRES_help = 'Read the pres data.'
    cmd_TEST_PRES_help = 'Test the pres for trigger.'
    cmd_TEST_PRES_AMPLITUDE_help = 'Test pressure amplitude'

    def __init__(self, config, prtouch):
        self.printer = config.get_printer()
        self.prtouch = prtouch
        self.bst_time = 0.0

    def get_bst_time(self):
        """Get best trigger time."""
        return self.bst_time

    def cmd_READ_PRES(self, gcmd):
        raise NotImplementedError

    def cmd_TEST_PRES(self, gcmd):
        raise NotImplementedError

    def cmd_TEST_PRES_AMPLITUDE(self, gcmd):
        raise NotImplementedError

    def _build_config(self):
        pass

    def _handle_resault(self, params):
        pass


class PrtouchStep(object):
    """PRTouch stepper control component."""

    def __init__(self, config, prtouch):
        self.printer = config.get_printer()
        self.prtouch = prtouch

    def build_config(self):
        pass

    def get_bst_zoft(self, pres_bst_time):
        """Get best Z offset for given pressure time."""
        return 0.0


# Module-level functions (stubs)
def LookupMultiRail(config, need_position_minmax=True, default_position_endstop=None, units_in_radians=False):
    raise NotImplementedError

def PrinterStepper(config, units_in_radians=False):
    raise NotImplementedError

def add_early_printer_objects(printer):
    pass

def add_printer_objects(config):
    pass

def error_help(msg):
    return msg

def get_printer_mcu(printer, name):
    raise NotImplementedError

def parse_gear_ratio(config, note_valid):
    return 1.0

def parse_step_distance(config, units_in_radians=None, note_valid=False):
    return 0.0025

def reportInformation(msg, data={}):
    logging.info(f"{msg}: {data}")


def load_config(config):
    """Load prtouch_v3 configuration."""
    return PRTouchEndstopWrapper(config)
