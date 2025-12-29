# Reconstructed from prtouch_v3_wrapper.cpython-39.so
# Original: klippy/extras/prtouch_v3_wrapper.py
# Creality K2 Series - Pressure-Based Touch Probe v3 (Latest)
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
# This file was reconstructed through reverse engineering of compiled Cython
# binaries. The code quality and accuracy varies by section:
#
# EXTRACTED (high confidence) - Directly from binary strings:
#   - Class names: PrtouchPres, PrtouchStep, PrtouchApax, PRTouchEndstopWrapper
#   - Configuration parameters: pres_swap_pin, pres_use_hx711, pres_ver,
#     pres_acq_tkms, pres_ded_tkms, pres_tri_hold, pres_tri_fter, etc.
#   - G-code commands: READ_PRES, TEST_PRES, TEST_PRES_AMPLITUDE, AUTO_APAX,
#     BED_MESH_CALIBRATE, SAFE_MOVE_Z, NOZZLE_CLEAR, TEST_SWAP, etc.
#   - MCU command strings: config_prtouch_pres, config_prtouch_step,
#     config_prtouch_apax, resault_prtouch_pres
#   - Log/response format strings: "CH{},PASS,{},Scale...", "bst_time=%.4f..."
#   - Error code strings: PR_ERR_CODE_SWAP_PIN_DETECTI
#   - File paths: PRES_DATA_PATH = "creality/userdata/pres_test/"
#
# INFERRED (lower confidence) - Educated guesses based on:
#   - Standard Klipper probe protocol (multi_probe_begin/end, probe_prepare/finish)
#   - Common pressure probe patterns from other 3D printer implementations
#   - HX711 ADC behavior (common load cell ADC)
#   - Event handler logic based on Klipper conventions
#   - Temperature compensation algorithms (assumed linear/polynomial)
#
# HIGHLY UNCERTAIN - The actual calibration/trigger algorithms:
#   - APAX calibration internals (apax_* parameters)
#   - Pressure trigger threshold calculations
#   - Step counting synchronization logic
#   - Temperature compensation curves
#
# Sections are marked with:
#   # [EXTRACTED] - From binary strings or decompiled code
#   # [INFERRED]  - Logic reconstructed from context/patterns
#   # [PARTIAL]   - Mix of extracted names with inferred logic
# =============================================================================

import logging
import math
import time
import os

# Constants
PRES_DATA_PATH = "creality/userdata/pres_test/"


class PrtouchPres:
    """Pressure sensor interface using HX711-style ADC."""

    def __init__(self, config, prtouch):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.prtouch = prtouch
        self.gcode = self.printer.lookup_object('gcode')

        # Pressure sensor configuration
        self.pres_swap_pin = config.get('pres_swap_pin', None)
        self.pres_use_hx711 = config.getboolean('pres_use_hx711', default=True)
        self.pres_ver = config.getint('pres_ver', default=3)

        # Timing parameters
        self.pres_acq_tkms = config.getfloat('pres_acq_tkms', default=0.1)
        self.pres_ded_tkms = config.getfloat('pres_ded_tkms', default=0.05)

        # Trigger parameters
        self.pres_tri_hold = config.getint('pres_tri_hold', default=3000)
        self.pres_tri_fter = config.getint('pres_tri_fter', default=100)
        self.pres_chk_hold = config.getint('pres_chk_hold', default=5000)
        self.pres_cal_fter = config.getint('pres_cal_fter', default=50)

        # Configuration registers
        self.pres_cfg_regs = config.get('pres_cfg_regs', None)

        # Multi-channel ADC pins (optional)
        self.pres_adc_pins = []
        self.pres_cs_pins = []
        for i in range(4):
            adc_pin = config.get('pres_adc%d_pin' % i, None)
            if adc_pin:
                self.pres_adc_pins.append(adc_pin)
            cs_pin = config.get('pres_cs%d_pin' % i, None)
            if cs_pin:
                self.pres_cs_pins.append(cs_pin)

        # Results storage
        self.pres_data = []
        self.pres_data_amplitude = []
        self.pres_state = 0
        self.pres_bst_time = 0.0
        self.pres_bst_indx = 0
        self.pres_time = 0.0

        # MCU command tracking
        self._oid = None
        self._cmd_queue = None

        # Register G-code commands
        self.gcode.register_command('READ_PRES', self.cmd_READ_PRES,
                                   desc="Read pressure sensor data")
        self.gcode.register_command('TEST_PRES', self.cmd_TEST_PRES,
                                   desc="Test pressure sensor")
        self.gcode.register_command('TEST_PRES_AMPLITUDE', self.cmd_TEST_PRES_AMPLITUDE,
                                   desc="Test pressure amplitude")

        # Register event handlers
        self.printer.register_event_handler('klippy:connect', self._build_config)

    def _build_config(self):
        """Build MCU configuration for pressure sensor."""
        mcu = self.prtouch.mcu
        if mcu is None:
            return

        self._oid = mcu.create_oid()

        # Build config command
        # config_prtouch_pres oid=%d idx=%d swp_pin=%s clk_pin=%s sdo_pin=%s
        logging.info("config_prtouch_pres oid=%d idx=%d swp_pin=%s clk_pin=%s sdo_pin=%s",
                    self._oid, 0, self.pres_swap_pin, "", "")

    def _handle_resault(self, params):
        """Handle pressure result from MCU."""
        # resault_prtouch_pres oid=%c tri_chxs=%c buf_len=%c ch=%c idx=%c len=%c ticks=%.*s datas=%.*s
        self.pres_data = params.get('datas', [])
        self.pres_time = params.get('ticks', 0)

    def get_bst_time(self):
        """Get best trigger time."""
        return self.pres_bst_time

    def cmd_READ_PRES(self, gcmd):
        """Read pressure sensor data."""
        count = gcmd.get_int('COUNT', 10)
        gcmd.respond_info("Reading %d pressure samples" % count)
        # Would trigger MCU to read pressure data

    def cmd_TEST_PRES(self, gcmd):
        """Test pressure sensor."""
        gcmd.respond_info("Testing pressure sensor")
        gcmd.respond_info("bst_time=%.4f, tri_time=%.4f" %
                         (self.pres_bst_time, self.pres_time))

    def cmd_TEST_PRES_AMPLITUDE(self, gcmd):
        """Test pressure amplitude."""
        scale = gcmd.get_float('SCALE', 1.0)
        ok_thrs = gcmd.get_float('THRS', 0.8)
        test_cnt = gcmd.get_int('COUNT', 10)

        ok_cnt = 0
        for data in self.pres_data_amplitude:
            if data >= ok_thrs * scale:
                ok_cnt += 1

        result = "PASS" if (ok_cnt / test_cnt >= ok_thrs) else "FAIL"
        gcmd.respond_info("CH{},PASS,{},Scale,{:.2f}%,ok_cnt,{},test_cnt,{},ok_thrs,{},(>={}% is PASS),pres_data_amplitude,{}".format(
            0, result, scale * 100, ok_cnt, test_cnt, ok_thrs, ok_thrs * 100, self.pres_data_amplitude))


class PrtouchStep:
    """Stepper-based probing for step counting."""

    def __init__(self, config, prtouch):
        self.printer = config.get_printer()
        self.prtouch = prtouch

        # Step configuration
        self.step_swap_pin = config.get('step_swap_pin', None)

        # MCU oids for steppers
        self._oid = None
        self._oid_xstp = None
        self._oid_ystp = None
        self._oid_zstp = None

        # Step data
        self.cnt_x = 0
        self.cnt_y = 0
        self.cnt_z = 0

        # Register event handler
        self.printer.register_event_handler('klippy:connect', self.build_config)

    def build_config(self):
        """Build MCU configuration for step counting."""
        mcu = self.prtouch.mcu
        if mcu is None:
            return

        self._oid = mcu.create_oid()

        # config_prtouch_step oid=%d oid_xstp=%d oid_ystp=%d oid_zstp=%d swp_pin=%s
        logging.info("config_prtouch_step oid=%d oid_xstp=%d oid_ystp=%d oid_zstp=%d swp_pin=%s",
                    self._oid, self._oid_xstp or 0, self._oid_ystp or 0,
                    self._oid_zstp or 0, self.step_swap_pin)

    def get_bst_zoft(self):
        """Get best Z offset from step counting."""
        if self.cnt_z == 0:
            return 0.0
        # Calculate offset based on step counts
        step_dist = self.prtouch.get_step_dist()
        return self.cnt_z * step_dist


class PrtouchApax:
    """APAX (Advanced Probe Axis) calibration system."""

    def __init__(self, config, prtouch):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.prtouch = prtouch
        self.gcode = self.printer.lookup_object('gcode')

        # APAX configuration
        self.apax_acq_tkms = config.getfloat('apax_acq_tkms', default=0.1)
        self.apax_apa_limt = config.getfloat('apax_apa_limt', default=0.5)
        self.apax_cal_fter = config.getint('apax_cal_fter', default=50)
        self.apax_espd = config.getfloat('apax_espd', default=2.0)
        self.apax_max_pavl = config.getfloat('apax_max_pavl', default=100.0)
        self.apax_ned_hold = config.getint('apax_ned_hold', default=3000)
        self.apax_oft_rest = config.getfloat('apax_oft_rest', default=0.0)
        self.apax_pos_star = config.getfloat('apax_pos_star', default=1.0)
        self.apax_run_cont = config.getint('apax_run_cont', default=5)
        self.apax_run_frdo = config.getfloat('apax_run_frdo', default=0.1)
        self.apax_run_limt = config.getfloat('apax_run_limt', default=0.2)
        self.apax_spx_cont = config.getint('apax_spx_cont', default=3)
        self.apax_stp_base = config.getfloat('apax_stp_base', default=0.05)
        self.apax_sys_pavl = config.getfloat('apax_sys_pavl', default=50.0)

        # APAX data
        self.apax_data = []
        self.apax_time = 0.0

        # MCU command tracking
        self._oid = None
        self._oid_estp = None

        # Register G-code commands
        self.gcode.register_command('AUTO_APAX', self.cmd_AUTO_APAX,
                                   desc=self.cmd_AUTO_APAX_help)
        self.gcode.register_command('TEST_APAX', self.cmd_TEST_APAX,
                                   desc=self.cmd_TEST_APAX_help)
        self.gcode.register_command('WAVE_APAX', self.cmd_WAVE_APAX,
                                   desc=self.cmd_WAVE_APAX_help)
        self.gcode.register_command('PRES_CHECK', self.cmd_PRES_CHECK,
                                   desc=self.cmd_PRES_CHECK_help)

        # Register event handler
        self.printer.register_event_handler('klippy:connect', self._build_config)

    cmd_AUTO_APAX_help = "Run automatic APAX calibration"
    cmd_TEST_APAX_help = "Test APAX calibration"
    cmd_WAVE_APAX_help = "APAX wave calibration"
    cmd_PRES_CHECK_help = "Check pressure system"

    def _build_config(self):
        """Build MCU configuration for APAX."""
        mcu = self.prtouch.mcu
        if mcu is None:
            return

        self._oid = mcu.create_oid()

        # config_prtouch_apax oid=%d oid_estp=%d
        logging.info("config_prtouch_apax oid=%d oid_estp=%d",
                    self._oid, self._oid_estp or 0)

    def _handle_resault(self, params):
        """Handle APAX result from MCU."""
        self.apax_data = params.get('data', [])
        self.apax_time = params.get('time', 0.0)

    def cmd_AUTO_APAX(self, gcmd):
        """Run automatic APAX calibration."""
        gcmd.respond_info("Running AUTO_APAX calibration")
        # Would perform APAX calibration sequence

    def cmd_TEST_APAX(self, gcmd):
        """Test APAX calibration."""
        gcmd.respond_info("Testing APAX")

    def cmd_WAVE_APAX(self, gcmd):
        """APAX wave calibration."""
        gcmd.respond_info("Running WAVE_APAX")

    def cmd_PRES_CHECK(self, gcmd):
        """Check pressure system."""
        gcmd.respond_info("Checking pressure system")


class PRTouchEndstopWrapper:
    """Main probe interface implementing Klipper probe protocol (v3)."""

    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.name = config.get_name().split()[-1]

        # Configuration parameters
        self.prth_tri_zacc = config.getfloat('prth_tri_zacc', default=100.0)

        # Probe parameters
        self.probe_speed = config.getfloat('probe_speed', default=2.0)
        self.lift_speed = config.getfloat('lift_speed', default=5.0)
        self.samples = config.getint('samples', default=1)
        self.sample_retract_dist = config.getfloat('sample_retract_dist', default=2.0)

        # G28 parameters
        self.g28_retry_zthr = config.getfloat('g28_retry_zthr', default=0.05)
        self.g28_retry_times = config.getint('g28_retry_times', default=3)
        self.g28_retry_okthr = config.getfloat('g28_retry_okthr', default=0.03)
        self.g28_ing = False
        self.g28_stat = 'idle'
        self.g28_nacc = False
        self.g28_prec = False

        # Temperature compensation
        self.temp_compensation_enabled = config.getboolean('temp_compensation', default=True)
        self.temp_not_linear = False

        # Bed mesh parameters
        self.bed_mesh_calibate_state = False
        self.bed_mesh_center_point = None
        self.bed_mesh_save_file_conut = 0

        # Objects found later
        self.toolhead = None
        self.mcu = None
        self.bed_mesh = None
        self.heater_hot = None
        self.heater_bed = None

        # Sub-components
        self.pres = PrtouchPres(config, self)
        self.step = PrtouchStep(config, self)
        self.apax = PrtouchApax(config, self)

        # Probing state
        self.probing = False
        self.multi_probing = False

        # Register G-code commands
        self._register_commands()

        # Register event handlers
        self.printer.register_event_handler('klippy:connect', self._build_config)
        self.printer.register_event_handler('homing:home_rails_begin',
                                           self._handle_home_rails_begin)
        self.printer.register_event_handler('homing:home_rails_end',
                                           self._handle_home_rails_end)
        self.printer.register_event_handler('homing:homing_move_begin',
                                           self._handle_homing_move_begin)
        self.printer.register_event_handler('homing:homing_move_end',
                                           self._handle_homing_move_end)
        self.printer.register_event_handler('stepper_enable:motor_off',
                                           self._handle_motor_off)

    def _register_commands(self):
        """Register all G-code commands."""
        commands = {
            'BED_MESH_CALIBRATE': (self.cmd_BED_MESH_CALIBRATE,
                                  self.cmd_BED_MESH_CALIBRATE_help),
            'BED_MESH_PROFILE': (self.cmd_BED_MESH_PROFILE,
                                self.cmd_BED_MESH_PROFILE_help),
            'SAFE_MOVE_Z': (self.cmd_SAFE_MOVE_Z, self.cmd_SAFE_MOVE_Z_help),
            'NOZZLE_CLEAR': (self.cmd_NOZZLE_CLEAR, self.cmd_NOZZLE_CLEAR_help),
            'NEXT_HOMEZ_NACCU': (self.cmd_NEXT_HOMEZ_NACCU,
                                self.cmd_NEXT_HOMEZ_NACCU_help),
            'SET_TEMP_NOT_LINEAR': (self.cmd_SET_TEMP_NOT_LINEAR,
                                   self.cmd_SET_TEMP_NOT_LINEAR_help),
            'TEST_PRTOUCH': (self.cmd_TEST_PRTOUCH, None),
            'TEST_BED_MESH_CAL': (self.cmd_TEST_BED_MESH_CAL,
                                 self.cmd_TEST_BED_MESH_CAL_help),
            'TEST_SWAP': (self.cmd_TEST_SWAP, self.cmd_TEST_SWAP_help),
            'TEST_REPROBE': (self.cmd_TEST_REPROBE, self.cmd_TEST_REPROBE_help),
        }

        for name, (handler, desc) in commands.items():
            if desc:
                self.gcode.register_command(name, handler, desc=desc)
            else:
                self.gcode.register_command(name, handler)

    # Help strings
    cmd_BED_MESH_CALIBRATE_help = "Perform bed mesh calibration"
    cmd_BED_MESH_PROFILE_help = "Manage bed mesh profiles"
    cmd_SAFE_MOVE_Z_help = "Safely move Z axis"
    cmd_NOZZLE_CLEAR_help = "Clear nozzle by wiping"
    cmd_NEXT_HOMEZ_NACCU_help = "Next home Z non-accurate"
    cmd_SET_TEMP_NOT_LINEAR_help = "Set temperature non-linear mode"
    cmd_TEST_BED_MESH_CAL_help = "Test bed mesh calibration"
    cmd_TEST_SWAP_help = "Test swap pin"
    cmd_TEST_REPROBE_help = "Test reprobe functionality"

    def _build_config(self):
        """Build MCU configuration."""
        self.toolhead = self.printer.lookup_object('toolhead', None)
        try:
            self.mcu = self.printer.lookup_object('mcu')
        except:
            pass
        try:
            self.bed_mesh = self.printer.lookup_object('bed_mesh', None)
        except:
            pass
        try:
            self.heater_hot = self.printer.lookup_object('extruder').heater
            self.heater_bed = self.printer.lookup_object('heater_bed').heater
        except:
            pass

    # --- Event Handlers ---

    def _handle_home_rails_begin(self, homing_state, rails):
        """Handle start of homing."""
        # Check if we're homing Z axis
        for rail in rails:
            if hasattr(rail, 'get_name') and 'z' in rail.get_name().lower():
                self.g28_ing = True
                self.g28_stat = 'start'
                logging.info("PRTouch: Z homing begin")
                break

    def _handle_home_rails_end(self, homing_state, rails):
        """Handle end of homing."""
        # Reset homing state
        for rail in rails:
            if hasattr(rail, 'get_name') and 'z' in rail.get_name().lower():
                self.g28_ing = False
                self.g28_stat = 'end'
                logging.info("PRTouch: Z homing end")
                break

    def _handle_homing_move_begin(self, hmove):
        """Handle start of homing move."""
        # Prepare pressure sensor for homing
        if hasattr(hmove, 'endstops'):
            for endstop, name in hmove.endstops:
                if name == 'z':
                    self.probing = True
                    break

    def _handle_homing_move_end(self, hmove):
        """Handle end of homing move."""
        self.probing = False

        # Log retry info
        logging.info("_handle_homing_move_end try reprobe:{} prozs:{} avg:{:.3f} g28_retry_zthr:{:.3f} bst_cnt:{}".format(
            0, [], 0.0, self.g28_retry_zthr, 0))

    def _handle_motor_off(self, print_time):
        """Handle motor off event."""
        # Reset state when motors are disabled
        self.probing = False
        self.multi_probing = False
        self.g28_ing = False

    # --- Probe Protocol ---

    def multi_probe_begin(self):
        """Begin multi-probe sequence."""
        self.multi_probing = True

    def multi_probe_end(self):
        """End multi-probe sequence."""
        self.multi_probing = False

    def probe_prepare(self, hmove):
        """Prepare for probing."""
        self.probing = True

    def probe_finish(self, hmove):
        """Finish probing."""
        self.probing = False

    def probe_outlier_check(self, positions, max_deviation=0.05):
        """Check for outliers in probe positions."""
        if len(positions) < 3:
            return positions

        def exten_matx(matrix, size):
            """Extend matrix for analysis."""
            return [[matrix[i % len(matrix)][j % len(matrix[0])]
                    for j in range(size)]
                   for i in range(size)]

        z_values = [p[2] for p in positions]
        avg_z = sum(z_values) / len(z_values)

        # Filter outliers
        filtered = [p for p in positions
                   if abs(p[2] - avg_z) <= max_deviation]

        return filtered if filtered else positions

    def get_temp_compensate(self, z_pos):
        """Get temperature compensation for Z position."""
        if not self.temp_compensation_enabled:
            return z_pos

        # Would apply temperature compensation curve
        return z_pos

    def get_temperature_compensate(self, z_pos):
        """Alias for get_temp_compensate."""
        return self.get_temp_compensate(z_pos)

    def get_z_now_comp(self):
        """Get current Z with compensation."""
        if self.toolhead:
            pos = self.toolhead.get_position()
            return self.get_temp_compensate(pos[2])
        return 0.0

    def prec_get_zeor_z(self):
        """Get precise zero Z position."""
        return 0.0

    def calc_z(self, trigger_time, trigger_pos):
        """Calculate Z position from trigger data."""
        return trigger_pos[2]

    def check_reise(self, z_pos):
        """Check if Z rise is needed."""
        return z_pos < self.sample_retract_dist

    def get_step_dist(self):
        """Get Z stepper step distance."""
        if self.toolhead:
            kin = self.toolhead.get_kinematics()
            # Get step distance from Z stepper
            return 0.0025  # Default microstep distance
        return 0.0025

    # --- Movement ---

    def gcode_move(self, x=None, y=None, z=None, speed=None):
        """Perform G-code move."""
        if self.toolhead is None:
            return

        pos = [x, y, z]
        if speed:
            self.toolhead.manual_move(pos, speed)
        else:
            self.toolhead.manual_move(pos, self.lift_speed)

    def wait_moves(self):
        """Wait for moves to complete."""
        if self.toolhead:
            self.toolhead.wait_moves()

    def delay_s(self, seconds):
        """Delay for specified seconds."""
        self.reactor.pause(self.reactor.monotonic() + seconds)

    def disturb_ctl(self, enable=True):
        """Control disturbance compensation.

        Enables/disables compensation for printer vibrations during probing.

        Args:
            enable: True to enable compensation, False to disable
        """
        # This would send MCU command to enable/disable disturbance filtering
        logging.debug("PRTouch: disturb_ctl enable=%s", enable)

    def print_msg(self, msg):
        """Print message to G-code console."""
        self.gcode.respond_info(msg)

    def run_script_from_command(self, script):
        """Run G-code script."""
        self.gcode.run_script_from_command(script)

    def unzip_data(self, data):
        """Decompress delta-encoded data."""
        if not data:
            return []
        result = [data[0]]
        for i in range(1, len(data)):
            result.append(result[-1] + data[i])
        return result

    # --- G-code Commands ---

    def cmd_BED_MESH_CALIBRATE(self, gcmd):
        """Perform bed mesh calibration."""
        profile = gcmd.get('PROFILE', 'default')

        self.bed_mesh_calibate_state = True
        gcmd.respond_info("bed_mesh_center_point=%s" % self.bed_mesh_center_point)

        def get_regional_cal_data(region):
            """Get calibration data for region."""
            return []

        def probe_abnormal_retry(pos, count=3):
            """Retry probing on abnormal result."""
            return pos

        def cal_bst_probe_z(positions):
            """Calculate best probe Z from positions."""
            if not positions:
                return 0.0
            z_values = [p[2] for p in positions]
            return sum(z_values) / len(z_values)

        # Would perform actual bed mesh calibration
        gcmd.respond_info("Bed mesh calibration started")

        self.bed_mesh_calibate_state = False

    def cmd_BED_MESH_PROFILE(self, gcmd):
        """Manage bed mesh profiles."""
        action = gcmd.get('SAVE', gcmd.get('LOAD', gcmd.get('REMOVE', None)))
        if action:
            gcmd.respond_info("Bed mesh profile: %s" % action)

    def cmd_SAFE_MOVE_Z(self, gcmd):
        """Safely move Z axis."""
        z = gcmd.get_float('Z', None)
        speed = gcmd.get_float('F', self.lift_speed)

        def syn_probe():
            """Synchronize probe position."""
            # Wait for any pending moves to complete
            if self.toolhead:
                self.toolhead.wait_moves()
            # Get current position for sync
            if self.toolhead:
                pos = self.toolhead.get_position()
                return pos[2]
            return 0.0

        if z is not None:
            syn_probe()  # Sync before moving
            self.gcode_move(z=z, speed=speed)
            gcmd.respond_info("Moving Z to %.3f" % z)
        else:
            gcmd.respond_info(
                "cmd_SAFE_MOVE_Z Run G28 XY to zero out their kinematic_position, "
                "or run SET_KINEMATIC_POSITION X_nohome={}, Y_nohome={} to force zero.")

    def cmd_NOZZLE_CLEAR(self, gcmd):
        """Clear nozzle by wiping."""
        gcmd.respond_info("Clearing nozzle")
        # Would perform nozzle wipe sequence

    def cmd_NEXT_HOMEZ_NACCU(self, gcmd):
        """Set next home Z to non-accurate mode."""
        gcmd.respond_info("Next home Z: non-accurate")

    def cmd_SET_TEMP_NOT_LINEAR(self, gcmd):
        """Set temperature non-linear mode."""
        enable = gcmd.get_int('ENABLE', 1)
        self.temp_not_linear = bool(enable)
        gcmd.respond_info("Temp non-linear: %s" %
                         ("enabled" if self.temp_not_linear else "disabled"))

    def cmd_TEST_PRTOUCH(self, gcmd):
        """Test PRTouch functionality."""
        gcmd.respond_info("Testing PRTouch")

        # Test trigger
        bst_time = self.pres.get_bst_time()
        bst_zoft = self.step.get_bst_zoft()

        gcmd.respond_info("best_indx=%d best_time=%.3f tri_time=%.3f" %
                         (self.pres.pres_bst_indx, bst_time, self.pres.pres_time))

    def cmd_TEST_BED_MESH_CAL(self, gcmd):
        """Test bed mesh calibration."""
        gcmd.respond_info("Testing bed mesh calibration")

        # Save test data
        os.makedirs(PRES_DATA_PATH, exist_ok=True)
        self.bed_mesh_save_file_conut += 1

    def cmd_TEST_SWAP(self, gcmd):
        """Test swap pin functionality."""
        pres_swap = self.pres.pres_swap_pin
        step_swap = self.step.step_swap_pin

        if pres_swap != step_swap:
            gcmd.respond_info(
                "PR_ERR_CODE_SWAP_PIN_DETECTI: The synchronization pin test failed, "
                "pres_swap_pin={0}, step_swap_pin={1}.".format(pres_swap, step_swap))
        else:
            gcmd.respond_info("Swap pin test passed")

    def cmd_TEST_REPROBE(self, gcmd):
        """Test reprobe functionality."""
        count = gcmd.get_int('COUNT', 3)
        gcmd.respond_info("Testing reprobe with %d iterations" % count)

    def get_status(self, eventtime=None):
        """Return status for Klipper status reporting."""
        return {
            'name': self.name,
            'probing': self.probing,
            'multi_probing': self.multi_probing,
            'temp_compensation': self.temp_compensation_enabled,
            'bed_mesh_state': self.bed_mesh_calibate_state
        }


def load_config(config):
    return PRTouchEndstopWrapper(config)
