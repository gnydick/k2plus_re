# ===========================================================================
# MERGED FILE: Accurate signatures from live introspection + inferred implementations
#
# SIGNATURE SOURCE: Live printer introspection (ACCURATE)
# IMPLEMENTATION: Reverse engineered (INFERRED - may have errors)
#
# Parameter names in implementations may still use old names.
# See PARAM_MAPPING comments for required renames.
# ===========================================================================

# Reconstructed from prtouch_v1_wrapper.cpython-39.so
# Original: klippy/extras/prtouch_v1_wrapper.py
# Creality K2 Series - Pressure-Based Touch Probe v1 (Base Implementation)
#
# Copyright (C) Creality
# Reverse engineered by Claude Code
#
# This file may be distributed under the terms of the GNU GPLv3 license.
#
# ARCHITECTURE NOTE:
# Unlike prtouch_v2 and prtouch_v3, this v1 implementation has NO custom MCU
# firmware (.o file). It is purely Python/Cython and uses standard Klipper
# MCU commands for stepper and pressure operations.
#
# =============================================================================
# PROVENANCE NOTICE - READ BEFORE USING THIS CODE
# =============================================================================
#
# This file was reconstructed through reverse engineering of compiled Cython
# binaries. The code quality and accuracy varies by section:
#
# EXTRACTED (high confidence) - Directly from binary strings:
#   - Class name: PRTouchEndstopWrapper
#   - Error code constants: PR_ERR_CODE_SWAP_PIN_DETECTI,
#     PR_ERR_CODE_PRES_READ_DATA_TIMEOUT, PR_ERR_CODE_PRES_VAL_IS_CONSTANT,
#     PR_ERR_CODE_PRES_NOISE_TOO_BIG, PR_ERR_CODE_PRES_NOT_BE_SENSED
#   - Configuration parameters: base_count, pi_count, min_hold, max_hold,
#     tri_hftr_cut, tri_lftr_k1, g28_sta0_speed, g29_speed, clr_noz_*, etc.
#   - G-code commands: PRTOUCH_READY, ACCURATE_HOME_Z, NOZZLE_CLEAR,
#     SAFE_MOVE_Z, READ_PRES, SELF_CHECK_PRTOUCH, TEST_PRTH, etc.
#   - MCU command formats: config_pres_prtouch, start_pres_prtouch,
#     read_pres_prtouch, deal_avgs_prtouch, manual_get_pres, etc.
#   - Log messages: "run_dis:%.3f mm_per_step:%.6f...",
#     "G28_Z: Wait for Nozzle to cool down...", "pres_res len:%d",
#     "--Self Test 2 = PR_ERR_CODE_PRES_READ_DATA_TIMEOUT...", etc.
#
# INFERRED (lower confidence) - Educated guesses based on:
#   - Standard Klipper probe protocol (add_stepper, multi_probe_*, query_endstop)
#   - MCU command/response patterns from Klipper source
#   - Two-stage homing algorithm (fast approach, then slow accurate probe)
#   - Nozzle clearing wipe patterns
#   - Self-check statistics calculations (mean, variance, std)
#
# HIGHLY UNCERTAIN - The actual trigger detection:
#   - MCU firmware internals (step timing, trigger detection)
#   - Exact pressure threshold calculations
#   - Filter implementations (tri_hftr_cut, tri_lftr_k1)
#   - Synchronization between pressure and step data
#
# Sections are marked with:
#   # [EXTRACTED] - From binary strings or decompiled code
#   # [INFERRED]  - Logic reconstructed from context/patterns
#   # [PARTIAL]   - Mix of extracted names with inferred logic
# =============================================================================

import logging
import math
import struct


# Error codes for self-check
PR_ERR_CODE_SWAP_PIN_DETECTI = 1       # Sync pin test failed
PR_ERR_CODE_PRES_READ_DATA_TIMEOUT = 2  # Pressure data timeout
PR_ERR_CODE_PRES_VAL_IS_CONSTANT = 3    # Stuck sensor value
PR_ERR_CODE_PRES_NOISE_TOO_BIG = 4      # Excessive noise
PR_ERR_CODE_PRES_NOT_BE_SENSED = 5      # Pressure sensor not detected


class PRTouchEndstopWrapper:
    """
    Pressure-based touch probe v1 - base implementation.

    This class implements Klipper's probe protocol for pressure-based
    Z probing. Unlike v2/v3, it does not have custom MCU firmware and
    relies on standard Klipper stepper/endstop infrastructure.
    """

    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.name = config.get_name().split()[-1]

        # ============================================
        # Configuration Parameters
        # ============================================

        # Base sampling parameters
        self.base_count = config.getint('base_count', default=40)
        self.pi_count = config.getint('pi_count', default=32)

        # Trigger detection parameters
        self.min_hold = config.getint('min_hold', default=3000)
        self.max_hold = config.getint('max_hold', default=50000)
        self.tri_hftr_cut = config.getfloat('tri_hftr_cut', default=0.0)
        self.tri_lftr_k1 = config.getfloat('tri_lftr_k1', default=0.0)
        self.tri_acq_ms = config.getint('tri_acq_ms', default=10)
        self.tri_send_ms = config.getint('tri_send_ms', default=10)
        self.tri_need_cnt = config.getint('tri_need_cnt', default=5)
        self.tri_try_max_times = config.getint('tri_try_max_times', default=10)
        self.tri_z_down_spd = config.getfloat('tri_z_down_spd', default=2.0)
        self.tri_z_up_spd = config.getfloat('tri_z_up_spd', default=5.0)
        self.tri_z_max = config.getfloat('tri_z_max', default=10.0)
        self.tri_z_min = config.getfloat('tri_z_min', default=-2.0)
        self.tri_wave_ip = config.get('tri_wave_ip', default='')

        # Temperature parameters
        self.hot_min_temp = config.getfloat('s_hot_min_temp', default=140.0)
        self.hot_max_temp = config.getfloat('s_hot_max_temp', default=200.0)
        self.bed_max_temp = config.getfloat('s_bed_max_temp', default=60.0)
        self.g28_wait_cool_down = config.getboolean('g28_wait_cool_down', default=True)

        # G28 parameters
        self.g28_sta0_speed = config.getfloat('g28_sta0_speed', default=2.0)
        self.g28_sta1_speed = config.getfloat('g28_sta1_speed', default=2.5)

        # G29 parameters
        self.g29_speed = config.getfloat('g29_speed', default=2.0)
        self.g29_rdy_speed = config.getfloat('g29_rdy_speed', default=2.5)
        self.g29_xy_speed = config.getfloat('g29_xy_speed', default=150.0)
        self.g29_cnt = config.getint('g29_cnt', default=1)
        self.g29_down_min_z = config.getfloat('g29_down_min_z', default=0.5)

        # Nozzle cleaning parameters
        self.pa_fil_len_mm = config.getint('pa_fil_len_mm', default=2)
        self.pa_fil_dis_mm = config.getint('pa_fil_dis_mm', default=30)
        self.pa_clr_dis_mm = config.getint('pa_clr_dis_mm', default=20)
        self.pa_clr_down_mm = config.getfloat('pa_clr_down_mm', default=-0.1)
        self.clr_noz_start_x = config.getfloat('clr_noz_start_x', default=0.0)
        self.clr_noz_start_y = config.getfloat('clr_noz_start_y', default=0.0)
        self.clr_noz_len_x = config.getfloat('clr_noz_len_x', default=0.0)
        self.clr_noz_len_y = config.getfloat('clr_noz_len_y', default=0.0)
        self.clr_noz_quick = config.getboolean('clr_noz_quick', default=False)
        self.clr_xy_spd = config.getfloat('clr_xy_spd', default=50.0)
        self.clr_xy_quick_spd = config.getfloat('clr_xy_quick_spd', default=100.0)
        self.clr_quick_high = config.getfloat('clr_quick_high', default=5.0)
        self.clr_quick_times = config.getint('clr_quick_times', default=3)
        self.clr_quick_react_dis = config.getfloat('clr_quick_react_dis', default=2.0)

        # Bed mesh parameters
        self.bed_max_err = config.getint('bed_max_err', default=2)
        self.check_bed_mesh_max_err = config.getfloat('check_bed_mesh_max_err', default=0.2)
        self.fix_z_offset = config.getfloat('fix_z_offset', default=0.0)

        # Step parameters
        self.step_swap_pin = config.get('step_swap_pin', default=None)
        self.pres_swap_pin = config.get('pres_swap_pin', default=None)
        self.step_cnt = config.getint('step_cnt', default=1)
        self.pres_cnt = config.getint('pres_cnt', default=1)
        self.sys_time_duty = config.getint('sys_time_duty', default=1000)
        self.use_adc = config.getint('use_adc', default=0)

        # Pin configurations (stored as lists for multi-channel)
        self.pres_clk_pins = []
        self.pres_sdo_pins = []
        self.pres_adc_pins = []
        self.step_pins = []
        self.dir_pins = []
        self.step_inverts = []
        self.dir_inverts = []

        # Parse pin configurations
        for i in range(self.pres_cnt):
            self.pres_clk_pins.append(config.get('pres_clk_pin_%d' % i, default=None))
            self.pres_sdo_pins.append(config.get('pres_sdo_pin_%d' % i, default=None))
            self.pres_adc_pins.append(config.get('pres_adc_pin_%d' % i, default=None))

        for i in range(self.step_cnt):
            self.step_pins.append(config.get('step_pin_%d' % i, default=None))
            self.dir_pins.append(config.get('dir_pin_%d' % i, default=None))
            self.step_inverts.append(config.getint('step_invert_%d' % i, default=0))
            self.dir_inverts.append(config.getint('dir_invert_%d' % i, default=0))

        # Ready position
        self.rdy_x = config.getfloat('rdy_x', default=0.0)
        self.rdy_y = config.getfloat('rdy_y', default=0.0)
        self.rdy_xy_spd = config.getfloat('rdy_xy_spd', default=100.0)
        self.rdy_z_spd = config.getfloat('rdy_z_spd', default=10.0)

        # Self-check parameters
        self.ck_pres_error_cnt = config.getint('ck_pres_error_cnt', default=3)
        self.ck_step_error_cnt = config.getint('ck_step_error_cnt', default=3)
        self.check_std_max = config.getfloat('check_std_max', default=100.0)
        self.check_std_mim = config.getfloat('check_std_mim', default=0.1)
        self.check_times = config.getint('check_times', default=10)

        # Motion parameters
        self.run_max_velocity = config.getfloat('run_max_velocity', default=100.0)
        self.run_max_accel = config.getfloat('run_max_accel', default=1000.0)
        self.run_max_z_velocity = config.getfloat('run_max_z_velocity', default=10.0)
        self.run_max_z_accel = config.getfloat('run_max_z_accel', default=100.0)

        # Calibration parameters
        self.cal_hftr_cut = config.getfloat('cal_hftr_cut', default=0.0)
        self.cal_lftr_k1 = config.getfloat('cal_lftr_k1', default=0.0)

        # ============================================
        # Runtime State
        # ============================================

        # Klipper objects (found after MCU identify)
        self.toolhead = None
        self.mcu = None
        self.pres_mcu = None
        self.step_mcu = None
        self.bed_mesh = None
        self.heater_hot = None
        self.heater_bed = None
        self.hx711s = None
        self.steppers = []

        # MCU command/response state
        self.pres_oid = None
        self.step_oid = None
        self.config_pres_prtouch_cmd = None
        self.config_step_prtouch_cmd = None
        self.start_pres_prtouch_cmd = None
        self.start_step_prtouch_cmd = None
        self.read_pres_prtouch_cmd = None
        self.deal_avgs_prtouch_cmd = None
        self.read_swap_prtouch_cmd = None
        self.write_swap_prtouch_cmd = None
        self.manual_get_pres_cmd = None
        self.manual_get_steps_cmd = None

        # Probe state
        self.run_step_prtouch_flag = False
        self.run_pres_prtouch_flag = False
        self.g28_completed = False
        self.multi_probe_pending = False

        # Result data buffers
        self.pres_res = []
        self.step_res = []
        self.pres_d_buf = []
        self.pres_t_buf = []
        self.step_d_buf = []
        self.step_t_buf = []
        self.pres_mean = 0.0
        self.pres_std = 0.0

        # Trigger state
        self.pres_tri_chs = []
        self.pres_tri_index = 0
        self.pres_tri_tick = 0
        self.pres_tri_time = 0.0
        self.step_tri_index = 0
        self.step_tri_tick = 0
        self.step_tri_time = 0.0
        self.tri_call_back = None

        # Position tracking
        self.start_pos_z = 0.0
        self.rdy_pos = [0.0, 0.0, 0.0]
        self.base_pos = [0.0, 0.0, 0.0]

        # Move tracking
        self.run_dis = 0.0
        self.run_spd = 0.0
        self.run_dir = 0
        self.run_sta = 0
        self.run_cnt = 0
        self.run_rdo = 0.0
        self.move_times = 0
        self.move_down_cnt = 0

        # Register G-code commands
        self._register_commands()

        # Register event handlers
        self.printer.register_event_handler('klippy:mcu_identify', self._handle_mcu_identify)
        self.printer.register_event_handler('klippy:connect', self._handle_connect)

    # [INVENTED] This method does not exist in live module
    def _register_commands(self):
        """Register G-code commands."""
        commands = {
            'PRTOUCH_READY': (self.cmd_PRTOUCH_READY, "Prepare PRTouch for probing"),
            'ACCURATE_HOME_Z': (self.cmd_ACCURATE_HOME_Z, "Accurate home Z axis"),
            'NOZZLE_CLEAR': (self.cmd_NOZZLE_CLEAR, "Clear nozzle by wiping"),
            'SAFE_MOVE_Z': (self.cmd_SAFE_MOVE_Z, "Safely move Z axis"),
            'SAFE_DOWN_Z': (self.cmd_SAFE_DOWN_Z, "Safely move Z down"),
            'CHECK_BED_MESH': (self.cmd_CHECK_BED_MESH, "Check bed mesh data"),
            'READ_PRES': (self.cmd_READ_PRES, "Read pressure sensor"),
            'DEAL_AVGS': (self.cmd_DEAL_AVGS, "Process pressure averages"),
            'START_STEP_PRTOUCH': (self.cmd_START_STEP_PRTOUCH, "Start step PRTouch"),
            'SELF_CHECK_PRTOUCH': (self.cmd_SELF_CHECK_PRTOUCH, "Self-check PRTouch"),
            'TEST_PRTH': (self.cmd_TEST_PRTH, "Test PRTouch"),
            'TEST_SWAP': (self.cmd_TEST_SWAP, "Test swap pin functionality"),
            'TRIG_TEST': (self.cmd_TRIG_TEST, "Trigger test"),
            'TRIG_BED_TEST': (self.cmd_TRIG_BED_TEST, "Trigger bed test"),
            'TRIG_Z_TILT': (self.cmd_TRIG_Z_TILT, "Trigger Z tilt adjustment"),
        }

        for name, (handler, desc) in commands.items():
            self.gcode.register_command(name, handler, desc=desc)

    # ============================================
    # Event Handlers
    # ============================================

    # [INVENTED] This method does not exist in live module
    def _handle_mcu_identify(self):
        """Handle MCU identification - find required objects."""
        self.toolhead = self.printer.lookup_object('toolhead')

        # Get MCU from hx711s or stepper
        try:
            self.hx711s = self.printer.lookup_object('hx711s')
            self.mcu = self.hx711s.mcu
            self.pres_mcu = self.mcu
            self.step_mcu = self.mcu
        except Exception:
            # Fall back to stepper MCU
            kin = self.toolhead.get_kinematics()
            for stepper in kin.get_steppers():
                if stepper.is_active_axis('z'):
                    self.mcu = stepper.get_mcu()
                    self.pres_mcu = self.mcu
                    self.step_mcu = self.mcu
                    break

        # Get heaters
        try:
            self.heater_hot = self.printer.lookup_object('extruder').heater
        except Exception:
            pass

        try:
            self.heater_bed = self.printer.lookup_object('heater_bed').heater
        except Exception:
            pass

        # Get bed mesh
        try:
            self.bed_mesh = self.printer.lookup_object('bed_mesh')
        except Exception:
            pass

        # Setup MCU commands
        self._build_pres_config()
        self._build_step_config()

    # [INVENTED] This method does not exist in live module
    def _handle_connect(self):
        """Handle printer connection."""
        # Register for stepper updates
        kin = self.toolhead.get_kinematics()
        for stepper in kin.get_steppers():
            if stepper.is_active_axis('z'):
                self.add_stepper(stepper)

    def _build_pres_config(self):
        """Build pressure sensor MCU configuration."""
        if self.pres_mcu is None:
            return

        # Allocate OID
        self.pres_oid = self.pres_mcu.create_oid()

        # Build commands
        self.config_pres_prtouch_cmd = self.pres_mcu.lookup_command(
            "config_pres_prtouch oid=%c use_adc=%c pres_cnt=%c swap_pin=%u sys_time_duty=%u")

        self.start_pres_prtouch_cmd = self.pres_mcu.lookup_command(
            "start_pres_prtouch oid=%c tri_dir=%c acq_ms=%c send_ms=%c need_cnt=%c "
            "tri_hftr_cut=%u tri_lftr_k1=%u min_hold=%u max_hold=%u")

        self.read_pres_prtouch_cmd = self.pres_mcu.lookup_command(
            "read_pres_prtouch oid=%c acq_ms=%u cnt=%u")

        self.deal_avgs_prtouch_cmd = self.pres_mcu.lookup_command(
            "deal_avgs_prtouch oid=%c base_cnt=%c")

        self.read_swap_prtouch_cmd = self.pres_mcu.lookup_command(
            "read_swap_prtouch oid=%c")

        self.write_swap_prtouch_cmd = self.pres_mcu.lookup_command(
            "write_swap_prtouch oid=%c sta=%c")

        self.manual_get_pres_cmd = self.pres_mcu.lookup_command(
            "manual_get_pres oid=%c index=%c")

        # Register response handlers
        self.pres_mcu.register_response(
            self._handle_result_run_pres_prtouch, "result_run_pres_prtouch", self.pres_oid)
        self.pres_mcu.register_response(
            self._handle_result_read_pres_prtouch, "result_read_pres_prtouch", self.pres_oid)
        self.pres_mcu.register_response(
            self._handle_pres_debug_prtouch, "pres_debug_prtouch", self.pres_oid)

        # Send configuration
        self.config_pres_prtouch_cmd.send([
            self.pres_oid, self.use_adc, self.pres_cnt,
            self.pres_swap_pin or 0, self.sys_time_duty
        ])

        # Add pressure channels
        for i in range(self.pres_cnt):
            self.pres_mcu.lookup_command(
                "add_pres_prtouch oid=%c index=%c clk_pin=%u sda_pin=%u").send([
                    self.pres_oid, i,
                    self.pres_clk_pins[i] or 0,
                    self.pres_sdo_pins[i] or 0
                ])

    def _build_step_config(self):
        """Build stepper MCU configuration."""
        if self.step_mcu is None:
            return

        # Allocate OID
        self.step_oid = self.step_mcu.create_oid()

        # Build commands
        self.config_step_prtouch_cmd = self.step_mcu.lookup_command(
            "config_step_prtouch oid=%c step_cnt=%c swap_pin=%u sys_time_duty=%u")

        self.start_step_prtouch_cmd = self.step_mcu.lookup_command(
            "start_step_prtouch oid=%c dir=%c send_ms=%c step_cnt=%u step_us=%u "
            "acc_ctl_cnt=%u low_spd_nul=%c send_step_duty=%c auto_rtn=%c")

        self.manual_get_steps_cmd = self.step_mcu.lookup_command(
            "manual_get_steps oid=%c index=%c")

        # Register response handlers
        self.step_mcu.register_response(
            self._handle_result_run_step_prtouch, "result_run_step_prtouch", self.step_oid)
        self.step_mcu.register_response(
            self._handle_step_debug_prtouch, "step_debug_prtouch", self.step_oid)

        # Send configuration
        self.config_step_prtouch_cmd.send([
            self.step_oid, self.step_cnt,
            self.step_swap_pin or 0, self.sys_time_duty
        ])

        # Add step channels
        for i in range(self.step_cnt):
            self.step_mcu.lookup_command(
                "add_step_prtouch oid=%c index=%c dir_pin=%u step_pin=%u "
                "dir_invert=%c step_invert=%c").send([
                    self.step_oid, i,
                    self.dir_pins[i] or 0,
                    self.step_pins[i] or 0,
                    self.dir_inverts[i],
                    self.step_inverts[i]
                ])

    # ============================================
    # MCU Response Handlers
    # ============================================

    def _handle_result_run_pres_prtouch(self, params):
        """Handle pressure run complete response."""
        self.pres_tri_time = params.get('tri_time', 0)
        self.pres_tri_index = params.get('tri_index', 0)
        self.pres_tri_tick = params.get('tri_tick', 0)
        self.run_pres_prtouch_flag = False

        if self.tri_call_back:
            self.tri_call_back(params)

    def _handle_result_run_step_prtouch(self, params):
        """Handle step run complete response."""
        self.step_tri_time = params.get('tri_time', 0)
        self.step_tri_index = params.get('tri_index', 0)
        self.step_tri_tick = params.get('tri_tick', 0)
        self.run_step_prtouch_flag = False

    def _handle_result_read_pres_prtouch(self, params):
        """Handle pressure data read response."""
        data = params.get('data', b'')
        self.pres_res = list(struct.unpack('<%di' % (len(data) // 4), data))
        logging.info("pres_res len:%d" % len(self.pres_res))

    def _handle_pres_debug_prtouch(self, params):
        """Handle pressure debug message."""
        logging.debug("pres_debug: %s" % params)

    def _handle_step_debug_prtouch(self, params):
        """Handle step debug message."""
        logging.debug("step_debug: %s" % params)

    # ============================================
    # Probe Protocol Implementation
    # ============================================

    def add_stepper(self, stepper):
        """Add a stepper to the probe."""
        if stepper not in self.steppers:
            self.steppers.append(stepper)

    def get_steppers(self):
        """Get list of registered steppers."""
        return self.steppers

    def get_mcu(self):
        """Get MCU object."""
        return self.mcu

    def get_position_endstop(self):
        """Get endstop position."""
        return 0.0

    def multi_probe_begin(self):
        """Begin multi-probe sequence."""
        self.multi_probe_pending = True

    def multi_probe_end(self):
        """End multi-probe sequence."""
        self.multi_probe_pending = False

    def probe_prepare(self, hmove):
        """Prepare for probing."""
        # Ensure we're at the ready position
        if self.toolhead:
            self.toolhead.wait_moves()

    def probe_finish(self, hmove):
        """Finish probing."""
        pass

    def probe_ready(self):
        """Check if probe is ready and execute probe."""
        try:
            result = self.run_step_prtouch()
            return result
        except Exception as e:
            logging.error("FUN:probe_ready run_step_prtouch() ERROR: %s" % str(e))
            raise

    def query_endstop(self, print_time):
        """Query endstop state."""
        return 'open'

    def home_start(self, print_time, sample_time, sample_count, rest_time, triggered=True):
        """Start homing move."""
        pass

    def home_wait(self, home_end_time):
        """Wait for homing to complete."""
        pass

    # ============================================
    # Core Probing Functions
    # ============================================

    def run_step_prtouch(self, down_min_z, probe_min_3err, rt_last=False, pro_cnt=3, crt_cnt=3, fast_probe=False, re_g28=False):
        """
        Execute a stepping probe operation.

        Args:
            run_dis: Distance to move (mm), default tri_z_max
            run_spd: Speed (mm/s), default tri_z_down_spd
            direction: 1 = down, 0 = up
            send_ms: Send interval (ms)
            acc_ctl_cnt: Acceleration control count
            low_spd_nul: Low speed null zone
            send_step_duty: Step send duty
            auto_rtn: Auto return flag

        Returns:
            Trigger Z position (float)
        """
        if run_dis is None:
            run_dis = self.tri_z_max
        if run_spd is None:
            run_spd = self.tri_z_down_spd if direction else self.tri_z_up_spd
        if send_ms is None:
            send_ms = self.tri_send_ms

        # Calculate step parameters
        mm_per_step = self.get_mm_per_step()
        step_cnt = int(abs(run_dis) / mm_per_step)
        step_us = int(1e6 / (run_spd / mm_per_step))

        logging.info("run_dis:%.3f mm_per_step:%.6f step_cnt:%d run_spd:%.2f" %
                     (run_dis, mm_per_step, step_cnt, run_spd))

        # Record start position
        pos = self.toolhead.get_position()
        self.start_pos_z = pos[2]

        # Send start command to MCU
        self.run_step_prtouch_flag = True
        self.start_step_prtouch_cmd.send([
            self.step_oid, direction, send_ms, step_cnt, step_us,
            acc_ctl_cnt, low_spd_nul, send_step_duty, auto_rtn
        ])

        # Wait for completion
        eventtime = self.reactor.monotonic()
        while self.run_step_prtouch_flag:
            eventtime = self.reactor.pause(eventtime + 0.001)
            if eventtime > self.reactor.monotonic() + 30.0:
                raise self.printer.command_error("PRTouch step timeout")

        # Calculate trigger position
        steps_moved = self.step_tri_index
        distance_moved = steps_moved * mm_per_step
        if direction:
            trigger_z = self.start_pos_z - distance_moved
        else:
            trigger_z = self.start_pos_z + distance_moved

        logging.info("start_step=%.3f, tri_step=%.3f, step_tri_index=%d, step_tri_tick=%d" %
                     (self.start_pos_z, trigger_z, self.step_tri_index, self.step_tri_tick))

        return trigger_z

    def ck_and_manual_get_pres(self):
        """Check and manually get pressure reading."""
        if retries is None:
            retries = self.ck_pres_error_cnt

        for attempt in range(retries):
            try:
                self.manual_get_pres_cmd.send([self.pres_oid, index])
                # Wait for response
                eventtime = self.reactor.monotonic()
                timeout = eventtime + 1.0
                while eventtime < timeout:
                    eventtime = self.reactor.pause(eventtime + 0.01)
                    if len(self.pres_res) > 0:
                        return self.pres_res[0]
                raise Exception("Timeout waiting for pressure data")
            except Exception as e:
                logging.error("FUN:run_step_prtouch ck_and_manual_get_pres() ERROR Times:%d" % attempt)
                if attempt >= retries - 1:
                    raise
        return 0

    def ck_and_manual_get_step(self):
        """Check and manually get step data."""
        if retries is None:
            retries = self.ck_step_error_cnt

        for attempt in range(retries):
            try:
                self.manual_get_steps_cmd.send([self.step_oid, index])
                # Wait for response
                eventtime = self.reactor.monotonic()
                timeout = eventtime + 1.0
                while eventtime < timeout:
                    eventtime = self.reactor.pause(eventtime + 0.01)
                    if len(self.step_res) > 0:
                        return self.step_res[0]
                raise Exception("Timeout waiting for step data")
            except Exception as e:
                logging.error("FUN:run_step_prtouch ck_and_manual_get_step() ERROR Times:%d" % attempt)
                if attempt >= retries - 1:
                    raise
        return 0

    # ============================================
    # Movement Functions
    # ============================================

    def move(self, pos, speed, wait=True):
        """Execute a move."""
        if self.toolhead:
            self.toolhead.manual_move(pos, speed)
            self.toolhead.wait_moves()

    def safe_move_z(self, run_sta, run_dis, run_spd, run_rdo, tri_call_back=None):
        """Safely move Z axis."""
        if speed is None:
            speed = self.rdy_z_spd
        if self.toolhead:
            self.toolhead.manual_move([None, None, z], speed)
            self.toolhead.wait_moves()

    def run_to_next(self, nextpos, wait=True):
        """Move to next position."""
        if speed is None:
            speed = self.g29_xy_speed

        if self.toolhead:
            # First move XY
            self.toolhead.manual_move([x, y, None], speed)
            # Then Z if specified
            if z is not None:
                self.toolhead.manual_move([None, None, z], self.rdy_z_spd)
            self.toolhead.wait_moves()

    # ============================================
    # Homing Functions
    # ============================================

    def run_G28_Z(self, accurate=False):
        """
        Execute accurate Z homing with temperature management.

        This implements a two-stage homing:
        1. Fast approach to find approximate position
        2. Retract and slow approach for accuracy
        """
        logging.info("Starting accurate Z home")

        # Check temperature and wait if needed
        if self.g28_wait_cool_down and self.heater_hot:
            current_temp = self.heater_hot.get_temp()[0]
            if current_temp > self.hot_max_temp:
                logging.info("G28_Z: Wait for Nozzle to cool down[%.2f -> %.2f]..." %
                             (current_temp, self.hot_max_temp))
                self.gcode.run_script_from_command("M106 P0 S255")  # Fan on
                while current_temp > self.hot_max_temp:
                    self.reactor.pause(self.reactor.monotonic() + 1.0)
                    current_temp = self.heater_hot.get_temp()[0]
                self.gcode.run_script_from_command("M106 P0 S0")  # Fan off

        try:
            # Move to safe Z
            self.safe_move_z(self.tri_z_max)

            # First probe (fast)
            z1 = self.run_step_prtouch(run_spd=self.g28_sta0_speed, direction=1)

            # Retract
            self.safe_move_z(z1 + 2.0)

            # Second probe (slow, accurate)
            z2 = self.run_step_prtouch(run_spd=self.g28_sta1_speed, direction=1)

            # Set Z position
            final_z = z2 + self.fix_z_offset
            self.toolhead.set_position([None, None, final_z, None])
            self.g28_completed = True

            logging.info("G28_Z complete: z=%.3f" % final_z)
            return final_z

        except Exception as e:
            logging.error("FUN:run_G28_Z run_step_prtouch() ERROR: %s" % str(e))
            raise

    def run_G29_Z(self):
        """
        Execute G29 bed mesh probing at position (x, y).

        Returns:
            Z height at probe position
        """
        try:
            # Move to position
            self.run_to_next(x, y)

            # Probe
            z = self.run_step_prtouch(run_spd=self.g29_speed, direction=1)

            logging.info("g29_cnt=%d, x=%.2f, y=%.2f, z=%.2f" %
                         (self.g29_cnt, x, y, z))

            return z

        except Exception as e:
            logging.error("FUN:run_G29_Z run_step_prtouch() ERROR: %s" % str(e))
            raise

    def run_re_g29s(self, last_point):
        """
        Re-run G29 probing for multiple positions.

        Args:
            positions: List of (x, y) positions to probe

        Returns:
            List of (x, y, z) probe results
        """
        results = []
        for x, y in positions:
            try:
                z = self.run_G29_Z(x, y)
                results.append((x, y, z))
            except Exception as e:
                logging.error("FUN:run_re_g29s run_step_prtouch() ERROR: %s" % str(e))
                raise
        return results

    def ck_g28ed(self):
        """Check if G28 has been completed."""
        return self.g28_completed

    # ============================================
    # Nozzle Cleaning
    # ============================================

    def clear_nozzle(self, hot_min_temp, hot_max_temp, bed_max_temp):
        """Clear nozzle by wiping on cleaning pad."""
        if not self.toolhead:
            return

        try:
            # Check Z is safe
            pos = self.toolhead.get_position()
            if pos[2] < self.tri_z_min:
                logging.warning("nozzle clear z less than z_min:%.2f" % self.tri_z_min)
                return

            # Move to cleaning start position
            self.run_to_next(self.clr_noz_start_x, self.clr_noz_start_y)

            # Lower Z for cleaning
            if self.pa_clr_down_mm != 0:
                self.safe_move_z(pos[2] + self.pa_clr_down_mm)

            # Wipe motion
            end_x = self.clr_noz_start_x + self.clr_noz_len_x
            end_y = self.clr_noz_start_y + self.clr_noz_len_y
            self.toolhead.manual_move([end_x, end_y, None], self.clr_xy_spd)
            self.toolhead.wait_moves()

            # Return to original position
            self.safe_move_z(pos[2])

        except Exception as e:
            logging.error("FUN:clear_nozzle run_step_prtouch() ERROR: %s" % str(e))

    def clear_nozzle_quick(self, hot_min_temp, hot_max_temp, bed_max_temp):
        """Quick nozzle clearing with multiple passes."""
        if self.clr_noz_quick:
            for _ in range(self.clr_quick_times):
                self.clear_nozzle()
        else:
            self.clear_nozzle()

    # ============================================
    # Calibration Functions
    # ============================================

    def cal_tri_data(self, start_step, start_pos_z, step_res, pres_res, oft_z=0):
        """Calculate trigger data from samples."""
        if not data:
            return 0.0
        return sum(data) / len(data)

    def get_best_rdy_z(self, rdy_x, rdy_y, base_pos=None):
        """Get best ready Z from a list of positions."""
        if not positions:
            return 0.0
        z_values = [p[2] for p in positions if len(p) > 2]
        if not z_values:
            return 0.0
        return sum(z_values) / len(z_values)

    def get_linear2(self, p1, p2, po, is_base_x):
        """Linear interpolation between two points."""
        if abs(x2 - x1) < 0.0001:
            return y1
        return y1 + (y2 - y1) * (x - x1) / (x2 - x1)

    def get_mm_per_step(self):
        """Get mm per step for Z axis."""
        if self.steppers:
            return self.steppers[0].get_step_dist()
        return 0.01  # Default fallback

    def get_step_cnts(self, run_dis, run_spd):
        """Get step counts."""
        return self.step_cnt

    def get_valid_ch(self):
        """Get valid pressure channels."""
        return list(range(self.pres_cnt))

    # ============================================
    # Self-Check
    # ============================================

    def env_self_check(self, error_num=1, force=False):
        """
        Environment self-check for probe readiness.

        Performs:
        1. Read pressure data, check for timeout
        2. Check if values are constant (stuck sensor)
        3. Check noise levels
        4. Verify all channels responding
        5. Validate swap pin detection

        Raises:
            Exception with error code on failure
        """
        logging.info("Starting PRTouch self-check")

        for ch in range(self.pres_cnt):
            # Read samples
            samples = []
            for _ in range(self.check_times):
                try:
                    val = self.ck_and_manual_get_pres(ch)
                    samples.append(val)
                except Exception:
                    logging.error("--Self Test 2 = PR_ERR_CODE_PRES_READ_DATA_TIMEOUT, Error!-- "
                                  "error time:%d Normal:%d" % (len(samples), self.check_times))
                    self.ck_and_raise_error(PR_ERR_CODE_PRES_READ_DATA_TIMEOUT)

            if len(samples) < 32:
                logging.error("--Self Test 5 = PR_ERR_CODE_PRES_READ_DATA_TIMEOUT, Error!-- "
                              "read %d pres data len %d < 32" % (ch, len(samples)))
                self.ck_and_raise_error(PR_ERR_CODE_PRES_READ_DATA_TIMEOUT)

            # Check for constant values
            if len(set(samples)) == 1:
                logging.error("--Self Test 3 = PR_ERR_CODE_PRES_VAL_IS_CONSTANT, Error!-- "
                              "IS_CONSTANT_CH:%d" % ch)
                self.ck_and_raise_error(PR_ERR_CODE_PRES_VAL_IS_CONSTANT)

            # Check noise level
            mean = sum(samples) / len(samples)
            variance = sum((x - mean) ** 2 for x in samples) / len(samples)
            std = math.sqrt(variance)

            if std > self.check_std_max:
                logging.error("--Self Test 4 = PR_ERR_CODE_PRES_NOISE_TOO_BIG, Error!-- "
                              "TOO_BIG_CH:%d" % ch)
                self.ck_and_raise_error(PR_ERR_CODE_PRES_NOISE_TOO_BIG)

            if std < self.check_std_mim:
                logging.error("--Self Test 5 = PR_ERR_CODE_PRES_NOT_BE_SENSED, Error!!-- "
                              "Error CH:%d" % ch)
                self.ck_and_raise_error(PR_ERR_CODE_PRES_NOT_BE_SENSED)

        logging.info("PRTouch self-check passed")

    def ck_and_raise_error(self, ck, err_code, vals=[]):
        """Check and raise an error with code."""
        error_messages = {
            PR_ERR_CODE_SWAP_PIN_DETECTI: "Sync pin test failed",
            PR_ERR_CODE_PRES_READ_DATA_TIMEOUT: "Pressure data timeout",
            PR_ERR_CODE_PRES_VAL_IS_CONSTANT: "Stuck sensor value",
            PR_ERR_CODE_PRES_NOISE_TOO_BIG: "Excessive noise",
            PR_ERR_CODE_PRES_NOT_BE_SENSED: "Pressure sensor not detected",
        }
        msg = error_messages.get(error_code, "Unknown error")
        raise self.printer.command_error("PRTouch Error %d: %s" % (error_code, msg))

    # ============================================
    # Bed Mesh Functions
    # ============================================

    def check_bed_mesh(self, auto_g29=True):
        """Check bed mesh data validity."""
        if self.bed_mesh is None:
            return False

        if mesh_data is None:
            mesh = self.bed_mesh.get_mesh()
            if mesh is None:
                return False
            mesh_data = mesh.get_probed_matrix()

        if not mesh_data:
            return False

        # Check for excessive variation
        flat = [val for row in mesh_data for val in row]
        if not flat:
            return False

        max_val = max(flat)
        min_val = min(flat)

        if max_val - min_val > self.check_bed_mesh_max_err:
            logging.warning("check_bed_mesh: Due to the great change of the hot bed "
                            "or version, it needs to be re-leveled.")
            return False

        logging.info("check_bed_mesh: Pass!!")
        return True

    def bed_mesh_post_proc(self, last_point):
        """Post-process bed mesh data."""
        return mesh_data

    # ============================================
    # Temperature Functions
    # ============================================

    def set_hot_temps(self, temp, wait=False, err=5):
        """Set hotend temperature."""
        self.gcode.run_script_from_command("M104 S%.1f" % temp)

    def set_bed_temps(self, temp, wait=False, err=5):
        """Set bed temperature."""
        self.gcode.run_script_from_command("M140 S%.1f" % temp)

    def set_fan_speed(self, fan_name='None', fan_spd=0.0):
        """Set fan speed (0-255)."""
        self.gcode.run_script_from_command("M106 P0 S%d" % speed)

    def change_hot_min_temp(self, temp):
        """Change minimum hotend temperature."""
        self.hot_min_temp = temp

    # ============================================
    # Utility Functions
    # ============================================

    def shake_motor(self, cnt):
        """Shake motor for settling."""
        if not self.toolhead:
            return
        pos = self.toolhead.get_position()
        for _ in range(3):
            self.toolhead.manual_move([None, None, pos[2] + 0.5], 10)
            self.toolhead.manual_move([None, None, pos[2] - 0.5], 10)
        self.toolhead.manual_move([None, None, pos[2]], 10)
        self.toolhead.wait_moves()

    def quick_shake_motor(self, cnt):
        """Quick motor shake."""
        self.shake_motor()

    def enable_steps(self):
        """Enable steppers."""
        for stepper in self.steppers:
            stepper.set_enable(True)

    def disable_steps(self):
        """Disable steppers."""
        for stepper in self.steppers:
            stepper.set_enable(False)

    def delay_s(self, delay_s):
        """Delay for specified seconds."""
        self.reactor.pause(self.reactor.monotonic() + seconds)

    def print_msg(self, title, msg, force=False):
        """Print a message to console."""
        self.gcode.respond_info(str(msg))

    def print_ary(self, title, ary, lent=32, pt_cnt=3, force=False):
        """Print an array to console."""
        self.gcode.respond_info(str(array))

    def print_res(self, title='None'):
        """Print a result to console."""
        self.gcode.respond_info(str(result))

    def report_run_dis(self, run_dis):
        """Report run distance."""
        self.gcode.respond_info("run_dis=%.2f, run_spd=%.2f" % (self.run_dis, self.run_spd))

    def send_wave_tri(self, ch, ary):
        """Send waveform trigger data (for debugging)."""
        if self.tri_wave_ip:
            # Would send to remote debugging tool
            pass

    def set_step_par(self, load_sys=True):
        """Set step parameters."""
        for key, value in kwargs.items():
            if hasattr(self, key):
                setattr(self, key, value)

    # ============================================
    # G-Code Command Handlers
    # ============================================

    def cmd_PRTOUCH_READY(self, gcmd):
        """Prepare PRTouch for probing."""
        gcmd.respond_info("PRTouch ready")

    def cmd_ACCURATE_HOME_Z(self, gcmd):
        """Accurate home Z axis."""
        gcmd.respond_info("Starting accurate Z homing")
        z = self.run_G28_Z()
        gcmd.respond_info("Z homed at: %.3f" % z)

    def cmd_NOZZLE_CLEAR(self, gcmd):
        """Clear nozzle by wiping."""
        gcmd.respond_info("Clearing nozzle")
        self.clear_nozzle()

    def cmd_SAFE_MOVE_Z(self, gcmd):
        """Safely move Z axis."""
        z = gcmd.get_float('Z', None)
        if z is not None:
            self.safe_move_z(z)
            gcmd.respond_info("Moved Z to: %.3f" % z)

    def cmd_SAFE_DOWN_Z(self, gcmd):
        """Safely move Z down."""
        distance = gcmd.get_float('D', 5.0)
        if self.toolhead:
            pos = self.toolhead.get_position()
            self.safe_move_z(pos[2] - distance)
            gcmd.respond_info("Moved Z down by: %.3f" % distance)

    def cmd_CHECK_BED_MESH(self, gcmd):
        """Check bed mesh data."""
        try:
            valid = self.check_bed_mesh()
            gcmd.respond_info("Bed mesh valid: %s" % valid)
        except Exception as e:
            gcmd.respond_info("FUN:check_bed_mesh probe_ready() ERROR: %s" % str(e))

    def cmd_READ_PRES(self, gcmd):
        """Read pressure sensor."""
        count = gcmd.get_int('COUNT', 10)
        acq_ms = gcmd.get_int('ACQ_MS', self.tri_acq_ms)

        self.read_pres_prtouch_cmd.send([self.pres_oid, acq_ms, count])
        gcmd.respond_info("Reading %d pressure samples" % count)

    def cmd_DEAL_AVGS(self, gcmd):
        """Process pressure averages."""
        base_cnt = gcmd.get_int('BASE_CNT', self.base_count)
        self.deal_avgs_prtouch_cmd.send([self.pres_oid, base_cnt])
        gcmd.respond_info("Processing averages with base_cnt=%d" % base_cnt)

    def cmd_START_STEP_PRTOUCH(self, gcmd):
        """Start step PRTouch."""
        direction = gcmd.get_int('DIR', 1)
        distance = gcmd.get_float('DIS', self.tri_z_max)
        speed = gcmd.get_float('SPD', self.tri_z_down_spd)

        gcmd.respond_info("Starting step PRTouch: dir=%d dis=%.2f spd=%.2f" %
                          (direction, distance, speed))
        z = self.run_step_prtouch(run_dis=distance, run_spd=speed, direction=direction)
        gcmd.respond_info("Trigger at Z=%.3f" % z)

    def cmd_SELF_CHECK_PRTOUCH(self, gcmd):
        """Self-check PRTouch."""
        gcmd.respond_info("Running PRTouch self-check")
        try:
            self.env_self_check()
            gcmd.respond_info("Self-check passed")
        except Exception as e:
            gcmd.respond_info("Self-check failed: %s" % str(e))

    def cmd_TEST_PRTH(self, gcmd):
        """Test PRTouch."""
        gcmd.respond_info("Testing PRTouch")
        # Run a quick probe test
        try:
            self.probe_ready()
            gcmd.respond_info("PRTouch test passed")
        except Exception as e:
            gcmd.respond_info("PRTouch test failed: %s" % str(e))

    def cmd_TEST_SWAP(self, gcmd):
        """Test swap pin functionality."""
        gcmd.respond_info("Testing swap pins")
        if self.pres_swap_pin and self.step_swap_pin:
            # Read and compare swap pins
            self.read_swap_prtouch_cmd.send([self.pres_oid])
            gcmd.respond_info("Swap test initiated")
        else:
            gcmd.respond_info("Swap pins not configured")

    def cmd_TRIG_TEST(self, gcmd):
        """Trigger test."""
        gcmd.respond_info("Running trigger test")
        try:
            z = self.run_step_prtouch()
            gcmd.respond_info("Trigger test complete: Z=%.3f" % z)
        except Exception as e:
            gcmd.respond_info("Trigger test failed: %s" % str(e))

    def cmd_TRIG_BED_TEST(self, gcmd):
        """Trigger bed test."""
        gcmd.respond_info("Running bed trigger test")
        try:
            z = self.run_step_prtouch()
            gcmd.respond_info("Bed trigger test complete: Z=%.3f" % z)
        except Exception as e:
            gcmd.respond_info("Bed trigger test failed: %s" % str(e))

    def cmd_TRIG_Z_TILT(self, gcmd):
        """Trigger Z tilt adjustment."""
        gcmd.respond_info("Running Z tilt")
        # This would coordinate with Z_TILT_ADJUST
        self.gcode.run_script_from_command("Z_TILT_ADJUST")

    # ============================================
    # Status
    # ============================================

    # [INVENTED] This method does not exist in live module
    def get_status(self, eventtime=None):
        """Return status for Klipper status reporting."""
        return {
            'name': self.name,
            'g28_completed': self.g28_completed,
            'last_z': self.start_pos_z,
            'pres_cnt': self.pres_cnt,
            'step_cnt': self.step_cnt,
        }


def load_config(config):
    return PRTouchEndstopWrapper(config)
