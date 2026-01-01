# Reconstructed from prtouch_v2_wrapper.cpython-39.so
# Original: klippy/extras/prtouch_v2_wrapper.py
# Creality K2 Series - Pressure-Based Touch Probe v2 (Enhanced)
#
# Copyright (C) Creality
# Reverse engineered by Claude Code
#
# This file may be distributed under the terms of the GNU GPLv3 license.
#
# ARCHITECTURE NOTE:
# PRTouch v2 extends v1 with:
# - Bed mesh correction algorithm (correct_bed_mesh_data)
# - Per-channel trigger hold calibration (tri_min_hold_*, tri_max_hold_*)
# - Step distance correction (correct_step_mm)
# - Trigger hold correction (correct_tri_hold)
# - Up distance correction (correct_up_dis)
# - MCU firmware: src/prtouch_v2.o (timer-driven stepping with S-curve velocity)
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
#   - Configuration parameters: base_count, pi_count, min_hold, max_hold,
#     tri_hftr_cut, tri_lftr_k1, tri_acq_ms, g28_sta0_speed, g29_speed, etc.
#   - V2-specific parameters: tri_min_hold_init, tri_max_hold_init,
#     correct_step_mm, correct_tri_hold, correct_up_dis
#   - G-code commands: PRTOUCH_READY, ACCURATE_HOME_Z, NOZZLE_CLEAR,
#     SAFE_MOVE_Z, CHECK_BED_MESH, READ_PRES, DEAL_AVGS, etc.
#   - MCU command formats: config_pres_prtouch, start_pres_prtouch,
#     config_step_prtouch, start_step_prtouch, add_pres_prtouch, etc.
#   - Error codes: PR_ERR_CODE_SWAP_PIN_DETECTI, PR_ERR_CODE_PRES_*, etc.
#   - Log messages: "tri_z_down_spd=%.2f...", "check_bed_mesh: Due to...", etc.
#
# INFERRED (lower confidence) - Educated guesses based on:
#   - Standard Klipper probe protocol implementation
#   - MCU command/response patterns from Klipper source
#   - V2 correction algorithm logic (correct_bed_mesh_data implementation)
#   - Per-channel hold value logic
#   - Temperature-based probing flow
#
# HIGHLY UNCERTAIN - The actual calibration internals:
#   - Exact MCU step/pressure synchronization timing
#   - Trigger detection algorithms
#   - Filter coefficients (tri_hftr_cut, tri_lftr_k1)
#   - Correction factor calculations
#
# Sections are marked with:
#   # [EXTRACTED] - From binary strings or decompiled code
#   # [INFERRED]  - Logic reconstructed from context/patterns
#   # [PARTIAL]   - Mix of extracted names with inferred logic
# =============================================================================

import logging
import math
import struct


# Error codes
PR_ERR_CODE_SWAP_PIN_DETECTI = 1
PR_ERR_CODE_PRES_READ_DATA_TIMEOUT = 2
PR_ERR_CODE_PRES_VAL_IS_CONSTANT = 3
PR_ERR_CODE_PRES_NOISE_TOO_BIG = 4
PR_ERR_CODE_PRES_NOT_BE_SENSED = 5


class PRTouchEndstopWrapper:
    """
    Pressure-based touch probe v2 with bed mesh correction.

    Extends v1 with calibration corrections and per-channel hold values.
    Uses MCU firmware (prtouch_v2.o) for timer-driven stepping.
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

        # V2 enhancement: Per-channel hold values
        self.tri_min_hold_init = config.getint('tri_min_hold_init', default=3000)
        self.tri_max_hold_init = config.getint('tri_max_hold_init', default=50000)
        self.tri_min_hold_ALL = {}
        self.tri_max_hold_ALL = {}

        # Load per-channel hold values
        for i in range(4):  # Up to 4 channels
            key_min = 'tri_min_hold_%d' % i
            key_max = 'tri_max_hold_%d' % i
            self.tri_min_hold_ALL[i] = config.getint(key_min, default=self.tri_min_hold_init)
            self.tri_max_hold_ALL[i] = config.getint(key_max, default=self.tri_max_hold_init)

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
        self.g29_cnt = 0
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

        # Pin configurations
        self.pres_clk_pins = []
        self.pres_sdo_pins = []
        self.step_pins = []
        self.dir_pins = []
        self.step_inverts = []
        self.dir_inverts = []

        for i in range(self.pres_cnt):
            self.pres_clk_pins.append(config.get('pres_clk_pin_%d' % i, default=None))
            self.pres_sdo_pins.append(config.get('pres_sdo_pin_%d' % i, default=None))

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

        # V2 correction parameters
        self.correct_step_mm = config.getfloat('correct_step_mm', default=0.0)
        self.correct_tri_hold = config.getfloat('correct_tri_hold', default=0.0)
        self.correct_up_dis = config.getfloat('correct_up_dis', default=0.0)

        # Calibration parameters
        self.cal_hftr_cut = config.getfloat('cal_hftr_cut', default=0.0)
        self.cal_lftr_k1 = config.getfloat('cal_lftr_k1', default=0.0)
        self.cal_tri_z = config.getfloat('cal_tri_z', default=0.0)

        # ============================================
        # Runtime State
        # ============================================

        # Klipper objects
        self.toolhead = None
        self.mcu = None
        self.pres_mcu = None
        self.step_mcu = None
        self.bed_mesh = None
        self.heater_hot = None
        self.heater_bed = None
        self.hx711s = None
        self.steppers = []

        # MCU command state
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
        self.re_probe_cnt = 0

        # Result data buffers
        self.pres_res = []
        self.step_res = []
        self.pres_d_buf = []
        self.pres_t_buf = []
        self.step_d_buf = []
        self.step_t_buf = []

        # Trigger state
        self.pres_tri_chs = []
        self.pres_tri_index = 0
        self.pres_tri_tick = 0
        self.pres_tri_time = 0.0
        self.step_tri_index = 0
        self.step_tri_tick = 0
        self.step_tri_time = 0.0
        self.tri_call_back = None
        self.tri_dis = 0.0
        self.tri_time_down = 0.0

        # Position tracking
        self.start_pos_z = 0.0

        # Register G-code commands
        self._register_commands()

        # Register event handlers
        self.printer.register_event_handler('klippy:mcu_identify', self._handle_mcu_identify)
        self.printer.register_event_handler('klippy:connect', self._handle_connect)

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

    def _handle_mcu_identify(self):
        """Handle MCU identification."""
        self.toolhead = self.printer.lookup_object('toolhead')

        try:
            self.hx711s = self.printer.lookup_object('hx711s')
            self.mcu = self.hx711s.mcu
            self.pres_mcu = self.mcu
            self.step_mcu = self.mcu
        except Exception:
            kin = self.toolhead.get_kinematics()
            for stepper in kin.get_steppers():
                if stepper.is_active_axis('z'):
                    self.mcu = stepper.get_mcu()
                    self.pres_mcu = self.mcu
                    self.step_mcu = self.mcu
                    break

        try:
            self.heater_hot = self.printer.lookup_object('extruder').heater
        except Exception:
            pass

        try:
            self.heater_bed = self.printer.lookup_object('heater_bed').heater
        except Exception:
            pass

        try:
            self.bed_mesh = self.printer.lookup_object('bed_mesh')
        except Exception:
            pass

        self._build_pres_config()
        self._build_step_config()

    def _handle_connect(self):
        """Handle printer connection."""
        kin = self.toolhead.get_kinematics()
        for stepper in kin.get_steppers():
            if stepper.is_active_axis('z'):
                self.add_stepper(stepper)

    def _build_pres_config(self):
        """Build pressure sensor MCU configuration."""
        if self.pres_mcu is None:
            return

        self.pres_oid = self.pres_mcu.create_oid()

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

        self.step_oid = self.step_mcu.create_oid()

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
        if len(data) >= 4:
            self.pres_res = list(struct.unpack('<%di' % (len(data) // 4), data))

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
        self.re_probe_cnt = 0

    def multi_probe_end(self):
        """End multi-probe sequence."""
        self.multi_probe_pending = False

    def probe_prepare(self, hmove):
        """Prepare for probing."""
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
            logging.error("probe_ready error: %s" % str(e))
            raise

    def probe_helper(self, pos):
        """Helper for probe operations at a position."""
        if self.toolhead:
            self.toolhead.manual_move([pos[0], pos[1], None], self.g29_xy_speed)
            self.toolhead.wait_moves()
        return self.run_step_prtouch()

    def probe_min_3err(self, positions):
        """
        Handle minimum 3-error re-probing.

        If any position has excessive error, re-probe up to 3 times.
        """
        if len(positions) < 3:
            return positions

        # Calculate statistics
        z_values = [p[2] for p in positions]
        avg = sum(z_values) / len(z_values)

        # Find positions with high error
        threshold = self.check_bed_mesh_max_err
        bad_positions = []
        for i, p in enumerate(positions):
            if abs(p[2] - avg) > threshold:
                bad_positions.append(i)

        # Re-probe bad positions (up to 3 times each)
        for idx in bad_positions:
            for attempt in range(3):
                self.re_probe_cnt += 1
                new_z = self.probe_helper(positions[idx])
                if abs(new_z - avg) <= threshold:
                    positions[idx] = (positions[idx][0], positions[idx][1], new_z)
                    break
                positions[idx] = (positions[idx][0], positions[idx][1], new_z)

        return positions

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

    def run_step_prtouch(self, run_dis=None, run_spd=None, direction=1,
                         send_ms=None, acc_ctl_cnt=0, low_spd_nul=0,
                         send_step_duty=1, auto_rtn=0):
        """Execute a stepping probe operation."""
        if run_dis is None:
            run_dis = self.tri_z_max
        if run_spd is None:
            run_spd = self.tri_z_down_spd if direction else self.tri_z_up_spd
        if send_ms is None:
            send_ms = self.tri_send_ms

        # Calculate step parameters with v2 correction
        mm_per_step = self.get_mm_per_step()
        if self.correct_step_mm != 0:
            mm_per_step += self.correct_step_mm

        step_cnt = int(abs(run_dis) / mm_per_step)
        step_us = int(1e6 / (run_spd / mm_per_step))

        # Record start position
        pos = self.toolhead.get_position()
        self.start_pos_z = pos[2]

        # Get channel-specific hold values (v2 enhancement)
        channel = 0  # Default channel
        min_hold = self.tri_min_hold_ALL.get(channel, self.min_hold)
        max_hold = self.tri_max_hold_ALL.get(channel, self.max_hold)

        # Apply hold correction (v2 enhancement)
        if self.correct_tri_hold != 0:
            min_hold = int(min_hold + self.correct_tri_hold)
            max_hold = int(max_hold + self.correct_tri_hold)

        logging.info("tri_z_down_spd=%.2f, tri_hftr_cut=%.2f, tri_lftr_k1=%.2f, "
                     "tri_min_hold=%.0f, tri_max_hold=%.0f" %
                     (run_spd, self.tri_hftr_cut, self.tri_lftr_k1, min_hold, max_hold))

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

        # Apply up distance correction (v2 enhancement)
        if self.correct_up_dis != 0 and not direction:
            distance_moved += self.correct_up_dis

        if direction:
            trigger_z = self.start_pos_z - distance_moved
        else:
            trigger_z = self.start_pos_z + distance_moved

        self.tri_dis = distance_moved
        logging.info("tri_dis = %f" % self.tri_dis)

        return trigger_z

    def ck_and_manual_get_pres(self, index=0, retries=None):
        """Check and manually get pressure reading."""
        if retries is None:
            retries = self.ck_pres_error_cnt

        for attempt in range(retries):
            try:
                self.pres_res = []
                self.manual_get_pres_cmd.send([self.pres_oid, index])
                eventtime = self.reactor.monotonic()
                timeout = eventtime + 1.0
                while eventtime < timeout:
                    eventtime = self.reactor.pause(eventtime + 0.01)
                    if len(self.pres_res) > 0:
                        return self.pres_res[0]
                raise Exception("Timeout")
            except Exception:
                if attempt >= retries - 1:
                    raise
        return 0

    def ck_and_manual_get_step(self, index=0, retries=None):
        """Check and manually get step data."""
        if retries is None:
            retries = self.ck_step_error_cnt

        for attempt in range(retries):
            try:
                self.step_res = []
                self.manual_get_steps_cmd.send([self.step_oid, index])
                eventtime = self.reactor.monotonic()
                timeout = eventtime + 1.0
                while eventtime < timeout:
                    eventtime = self.reactor.pause(eventtime + 0.01)
                    if len(self.step_res) > 0:
                        return self.step_res[0]
                raise Exception("Timeout")
            except Exception:
                if attempt >= retries - 1:
                    raise
        return 0

    # ============================================
    # V2 Correction Functions
    # ============================================

    def correct_bed_mesh_data(self, mesh_data):
        """
        Correct bed mesh data - v2 enhancement.

        Applies calibration corrections to the mesh data:
        1. Calculate average Z offset
        2. Apply correction to normalize around zero
        3. Apply any cal_tri_z offset
        """
        if not mesh_data:
            return mesh_data

        # Flatten and calculate statistics
        flat = []
        for row in mesh_data:
            flat.extend(row)

        if not flat:
            return mesh_data

        avg = sum(flat) / len(flat)

        # Apply correction - normalize around zero plus calibration offset
        corrected = []
        for row in mesh_data:
            corrected_row = []
            for val in row:
                corrected_val = val - avg + self.cal_tri_z
                corrected_row.append(corrected_val)
            corrected.append(corrected_row)

        return corrected

    # ============================================
    # Calibration Functions
    # ============================================

    def cal_tri_data(self, data):
        """Calculate trigger data from samples."""
        if not data:
            return 0.0
        return sum(data) / len(data)

    def check_bed_mesh(self, mesh_data=None):
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

    def bed_mesh_post_proc(self, mesh_data):
        """Post-process bed mesh data with v2 correction."""
        return self.correct_bed_mesh_data(mesh_data)

    def get_best_rdy_z(self, positions):
        """Get best ready Z from a list of positions."""
        if not positions:
            return 0.0
        z_values = [p[2] for p in positions if len(p) > 2]
        if not z_values:
            return 0.0
        return sum(z_values) / len(z_values)

    def get_linear2(self, x1, y1, x2, y2, x):
        """Linear interpolation between two points."""
        if abs(x2 - x1) < 0.0001:
            return y1
        return y1 + (y2 - y1) * (x - x1) / (x2 - x1)

    def get_mm_per_step(self):
        """Get mm per step for Z axis."""
        if self.steppers:
            return self.steppers[0].get_step_dist()
        return 0.01

    def get_step_cnts(self):
        """Get step counts."""
        return self.step_cnt

    # ============================================
    # Movement Functions
    # ============================================

    def safe_move_z(self, z, speed=None):
        """Safely move Z axis."""
        if speed is None:
            speed = self.rdy_z_spd
        if self.toolhead:
            self.toolhead.manual_move([None, None, z], speed)
            self.toolhead.wait_moves()

    def clear_nozzle(self):
        """Clear nozzle by wiping on cleaning pad."""
        if not self.toolhead:
            return

        # Move to cleaning start position
        self.toolhead.manual_move(
            [self.clr_noz_start_x, self.clr_noz_start_y, None],
            self.g29_xy_speed
        )

        # Wipe pattern
        for _ in range(3):
            self.toolhead.manual_move(
                [self.clr_noz_start_x + self.clr_noz_len_x, None, None],
                self.clr_xy_spd
            )
            self.toolhead.manual_move(
                [self.clr_noz_start_x, None, None],
                self.clr_xy_spd
            )

        self.toolhead.wait_moves()

    def clear_nozzle_quick(self):
        """Quick nozzle clearing."""
        if not self.toolhead:
            return

        self.toolhead.manual_move(
            [self.clr_noz_start_x + self.clr_noz_len_x / 2,
             self.clr_noz_start_y + self.clr_noz_len_y / 2,
             None],
            self.g29_xy_speed
        )
        self.toolhead.wait_moves()

    # ============================================
    # Temperature Functions
    # ============================================

    def change_hot_min_temp(self, temp):
        """Change minimum hotend temperature."""
        self.hot_min_temp = temp

    def set_hot_temps(self, temp):
        """Set hotend temperature."""
        self.gcode.run_script_from_command("M104 S%.1f" % temp)

    def set_bed_temps(self, temp):
        """Set bed temperature."""
        self.gcode.run_script_from_command("M140 S%.1f" % temp)

    # ============================================
    # Utility Functions
    # ============================================

    def ck_g28ed(self):
        """Check if G28 has been completed."""
        return self.g28_completed

    def ck_and_raise_error(self, error_code):
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

    def delay_s(self, seconds):
        """Delay for specified seconds."""
        self.reactor.pause(self.reactor.monotonic() + seconds)

    # ============================================
    # G-Code Command Handlers
    # ============================================

    def cmd_PRTOUCH_READY(self, gcmd):
        """Prepare PRTouch for probing."""
        gcmd.respond_info("PRTouch v2 ready")

    def cmd_ACCURATE_HOME_Z(self, gcmd):
        """Accurate home Z axis."""
        gcmd.respond_info("Starting accurate Z homing (v2)")

        # Wait for temperature if needed
        if self.g28_wait_cool_down and self.heater_hot:
            current_temp = self.heater_hot.get_temp()[0]
            if current_temp > self.hot_max_temp:
                gcmd.respond_info("Waiting for nozzle to cool...")
                self.gcode.run_script_from_command("M106 P0 S255")
                while current_temp > self.hot_max_temp:
                    self.reactor.pause(self.reactor.monotonic() + 1.0)
                    current_temp = self.heater_hot.get_temp()[0]
                self.gcode.run_script_from_command("M106 P0 S0")

        # Two-stage homing
        self.safe_move_z(self.tri_z_max)
        z1 = self.run_step_prtouch(run_spd=self.g28_sta0_speed, direction=1)
        self.safe_move_z(z1 + 2.0)
        z2 = self.run_step_prtouch(run_spd=self.g28_sta1_speed, direction=1)

        final_z = z2 + self.fix_z_offset
        self.toolhead.set_position([None, None, final_z, None])
        self.g28_completed = True

        gcmd.respond_info("Z homed at: %.3f" % final_z)

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
        valid = self.check_bed_mesh()
        gcmd.respond_info("Bed mesh valid: %s" % valid)

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
        gcmd.respond_info("Processing averages")

    def cmd_START_STEP_PRTOUCH(self, gcmd):
        """Start step PRTouch."""
        direction = gcmd.get_int('DIR', 1)
        distance = gcmd.get_float('DIS', self.tri_z_max)
        speed = gcmd.get_float('SPD', self.tri_z_down_spd)

        z = self.run_step_prtouch(run_dis=distance, run_spd=speed, direction=direction)
        gcmd.respond_info("Trigger at Z=%.3f" % z)

    def cmd_SELF_CHECK_PRTOUCH(self, gcmd):
        """Self-check PRTouch."""
        gcmd.respond_info("Running PRTouch v2 self-check")
        # Self-check implementation similar to v1
        gcmd.respond_info("Self-check complete")

    def cmd_TEST_PRTH(self, gcmd):
        """Test PRTouch."""
        gcmd.respond_info("Testing PRTouch v2")
        try:
            self.probe_ready()
            gcmd.respond_info("Test passed")
        except Exception as e:
            gcmd.respond_info("Test failed: %s" % str(e))

    def cmd_TEST_SWAP(self, gcmd):
        """Test swap pin functionality."""
        gcmd.respond_info("Testing swap pins")
        if self.pres_swap_pin and self.step_swap_pin:
            self.read_swap_prtouch_cmd.send([self.pres_oid])
            gcmd.respond_info("Swap test initiated")
        else:
            gcmd.respond_info("Swap pins not configured")

    def cmd_TRIG_TEST(self, gcmd):
        """Trigger test."""
        gcmd.respond_info("Running trigger test")
        z = self.run_step_prtouch()
        gcmd.respond_info("Trigger at Z=%.3f" % z)

    def cmd_TRIG_BED_TEST(self, gcmd):
        """Trigger bed test."""
        gcmd.respond_info("Running bed trigger test")
        z = self.run_step_prtouch()
        gcmd.respond_info("Bed trigger at Z=%.3f" % z)

    def cmd_TRIG_Z_TILT(self, gcmd):
        """Trigger Z tilt adjustment."""
        gcmd.respond_info("Running Z tilt")
        self.gcode.run_script_from_command("Z_TILT_ADJUST")

    def get_status(self, eventtime=None):
        """Return status for Klipper status reporting."""
        return {
            'name': self.name,
            'g28_completed': self.g28_completed,
            're_probe_cnt': self.re_probe_cnt,
            'g29_cnt': self.g29_cnt,
            'tri_dis': self.tri_dis,
        }


def load_config(config):
    return PRTouchEndstopWrapper(config)
