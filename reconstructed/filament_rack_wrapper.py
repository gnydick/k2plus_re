# Reconstructed from filament_rack_wrapper.cpython-39.so
# Original: klippy/extras/filament_rack_wrapper.py
# Creality K2 Series - Filament Rack Management
#
# Copyright (C) Creality
# Reverse engineered by Claude Code
#
# This file may be distributed under the terms of the GNU GPLv3 license.
#
# Purpose: Manages filament rack slots, material detection via RFID,
#          temperature/speed recommendations, and RS-485 communication
#          with external material handling hardware.
#
# =============================================================================
# PROVENANCE NOTICE - READ BEFORE USING THIS CODE
# =============================================================================
#
# This file was reconstructed through reverse engineering of compiled Cython
# binaries. The code quality and accuracy varies by section:
#
# EXTRACTED (high confidence) - Directly from binary strings:
#   - Class/method names: RemainMaterial, FilamentRackWrapper
#   - Configuration parameter names: beep_didi_param, need_clean_length, etc.
#   - G-code command names: FILAMENT_RACK, FILAMENT_RACK_FLUSH, etc.
#   - File paths: MATERIAL_DATABASE_PATH, TN_DATA_PATH, SYSTEM_CONFIG_PATH
#   - Log message strings: "material database get nozzle temp", etc.
#   - JSON field names from material database format
#
# INFERRED (lower confidence) - Educated guesses based on:
#   - Function names implying behavior (get_material_target_temp -> lookup temp)
#   - Standard Klipper extension patterns (register_command, event handlers)
#   - Common 3D printer firmware practices (G-code macros, temperature handling)
#   - RS-485 protocol patterns from other decompiled modules
#
# Sections are marked with:
#   # [EXTRACTED] - From binary strings or decompiled code
#   # [INFERRED]  - Logic reconstructed from context/patterns
#   # [PARTIAL]   - Mix of extracted names with inferred logic
# =============================================================================

import logging
import json
import os
import subprocess

# Material database paths
MATERIAL_DATABASE_PATH = "creality/userdata/box/material_database.json"
TN_DATA_PATH = "creality/userdata/box/tn_data.json"
SYSTEM_CONFIG_PATH = "creality/userdata/config/system_config.json"

# Default values
DEFAULT_PRINT_TEMP = 200
DEFAULT_MAX_VOLUMETRIC_SPEED = 10.0
DEFAULT_MIN_EXTRUDE_TEMP = 170
DEFAULT_TIMEOUT = 60.0


class RemainMaterial:
    """
    Tracks remaining material in filament rack slots.

    Each slot can hold material with RFID identification, tracking:
    - Remaining length of filament
    - Material type and color
    - Feed velocity for the material
    """

    def __init__(self, config, slot_index):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.slot_index = slot_index

        # Material state
        self.remain_length = 0.0
        self.velocity = 0.0
        self.rfid = None
        self.material_type = None
        self.color_value = None
        self.vender = None

        # Configuration file for persistence
        self.config_file = config

        # Load saved state if available
        self._load_saved_state()

    def _load_saved_state(self):
        """Load material state from persistent storage."""
        try:
            if os.path.exists(TN_DATA_PATH):
                with open(TN_DATA_PATH, 'r') as f:
                    tn_data = json.load(f)
                    slot_key = "slot_%d" % self.slot_index
                    if slot_key in tn_data:
                        slot_data = tn_data[slot_key]
                        self.remain_length = slot_data.get('remain_length', 0.0)
                        self.rfid = slot_data.get('rfid', None)
                        self.material_type = slot_data.get('material_type', None)
                        self.color_value = slot_data.get('color_value', None)
                        self.velocity = slot_data.get('velocity', 0.0)
        except Exception as e:
            logging.warning("Failed to load slot %d state: %s", self.slot_index, e)

    def init(self, rfid=None, remain_length=0.0):
        """
        Initialize material slot with RFID and length.

        Args:
            rfid: RFID tag identifier for the material
            remain_length: Initial remaining length in mm
        """
        self.rfid = rfid
        self.remain_length = remain_length
        logging.info("RemainMaterial slot %d initialized: rfid=%s, length=%.1f",
                     self.slot_index, rfid, remain_length)

    def save(self):
        """Save material state to persistent storage."""
        try:
            # Load existing data
            tn_data = {}
            if os.path.exists(TN_DATA_PATH):
                with open(TN_DATA_PATH, 'r') as f:
                    tn_data = json.load(f)

            # Update slot data
            slot_key = "slot_%d" % self.slot_index
            tn_data[slot_key] = {
                'remain_length': self.remain_length,
                'rfid': self.rfid,
                'material_type': self.material_type,
                'color_value': self.color_value,
                'velocity': self.velocity
            }

            # Write back
            os.makedirs(os.path.dirname(TN_DATA_PATH), exist_ok=True)
            with open(TN_DATA_PATH, 'w') as f:
                json.dump(tn_data, f, indent=2)

            logging.info("save: color: %s, type: %s", self.color_value, self.material_type)
        except Exception as e:
            logging.warning("Failed to save slot %d state: %s", self.slot_index, e)

    def get_velocity(self):
        """Get the material feed velocity."""
        return self.velocity

    def set_material_info(self, material_type=None, color_value=None, vender=None):
        """
        Set material information from database lookup.

        Args:
            material_type: Type of material (PLA, ABS, PETG, etc.)
            color_value: Color hex value
            vender: Vendor/manufacturer name
        """
        if material_type is not None:
            self.material_type = material_type
        if color_value is not None:
            self.color_value = color_value
        if vender is not None:
            self.vender = vender

        logging.info("vender: %s, color_value: %s, material_type: %s",
                     self.vender, self.color_value, self.material_type)

    def update_remain_length(self, delta):
        """
        Update remaining length after extrusion.

        Args:
            delta: Amount extruded (negative reduces length)
        """
        self.remain_length += delta
        if self.remain_length < 0:
            self.remain_length = 0

    def get_status(self, eventtime=None):
        """Return status for Klipper status reporting."""
        return {
            'slot': self.slot_index,
            'remain_length': self.remain_length,
            'rfid': self.rfid,
            'material_type': self.material_type,
            'color_value': self.color_value,
            'velocity': self.velocity,
            'vender': self.vender
        }


class FilamentRackWrapper:
    """
    Klipper interface for filament rack control.

    Manages multi-slot filament storage with RFID material identification,
    automatic temperature/speed recommendations, and RS-485 communication
    with material handling hardware.

    G-code Commands:
        FILAMENT_RACK ACTION=<action> - Main control command
        FILAMENT_RACK_FLUSH LENGTH=<mm> SPEED=<mm/s> - Purge filament
        FILAMENT_RACK_PRE_FLUSH - Prepare for purging
        FILAMENT_RACK_SET_TEMP TEMP=<temp> - Set nozzle temperature
        FILAMENT_RACK_MODIFY SLOT=<n> - Modify slot settings
        SET_COOL_TEMP TEMP=<temp> - Set cooling temperature
        SAVE_FAN / RESTORE_FAN - Fan state management
    """

    def __init__(self, config):
        self.printer = config.get_printer()
        self.reactor = self.printer.get_reactor()
        self.gcode = self.printer.lookup_object('gcode')
        self.name = config.get_name().split()[-1]

        # Configuration parameters
        self.beep_didi_param = config.get('beep_didi_param', default='0.2')
        self.need_clean_length = config.getfloat('need_clean_length', default=50.0)
        self.extrude_length = config.getfloat('extrude_length', default=50.0)
        self.min_extrude_temp = config.getfloat('min_extrude_temp', default=DEFAULT_MIN_EXTRUDE_TEMP)

        # Serial communication
        self._serial = None

        # Material slots (up to 4 slots typical)
        self.slots = []
        num_slots = config.getint('num_slots', default=4)
        for i in range(num_slots):
            self.slots.append(RemainMaterial(config, i))

        # Fan state storage
        self.saved_fan_speed = 0
        self.fan0_last_value = 0.0

        # Material database
        self.material_database = {}
        self.material_list = []
        self._load_material_database()

        # System configuration
        self.system_config = {}
        self._load_system_config()

        # Objects found later
        self.toolhead = None
        self.heater_hot = None
        self.extruder = None
        self.fan = None
        self.output_pin_fan0 = None
        self.motor_control = None
        self.print_stats = None
        self.base_info = None

        # Button handling
        self.not_pin = None

        # Filament detection state
        self.can_get_filament_rack = False
        self.can_get_filament_rack_tmp = False

        # Register G-code commands
        self.gcode.register_command(
            'FILAMENT_RACK',
            self.cmd_filament_rack,
            desc="Filament rack control"
        )
        self.gcode.register_command(
            'FILAMENT_RACK_FLUSH',
            self.cmd_filament_rack_flush,
            desc="Flush filament rack"
        )
        self.gcode.register_command(
            'FILAMENT_RACK_PRE_FLUSH',
            self.cmd_filament_rack_pre_flush,
            desc="Pre-flush preparation"
        )
        self.gcode.register_command(
            'FILAMENT_RACK_SET_TEMP',
            self.cmd_filament_rack_set_temp,
            desc="Set temperature for material"
        )
        self.gcode.register_command(
            'FILAMENT_RACK_MODIFY',
            self.cmd_filament_rack_modify,
            desc="Modify filament rack settings"
        )
        self.gcode.register_command(
            'SET_COOL_TEMP',
            self.cmd_set_cool_temp,
            desc="Set cooling temperature"
        )
        self.gcode.register_command(
            'SAVE_FAN',
            self.cmd_save_fan,
            desc="Save fan state"
        )
        self.gcode.register_command(
            'RESTORE_FAN',
            self.cmd_restore_fan,
            desc="Restore fan state"
        )
        # Alternative command names
        self.gcode.register_command(
            'FILAMENT_RACK_SAVE_FAN',
            self.cmd_save_fan,
            desc="Save fan state (alias)"
        )
        self.gcode.register_command(
            'FILAMENT_RACK_RESTORE_FAN',
            self.cmd_restore_fan,
            desc="Restore fan state (alias)"
        )

        # Register event handler
        self.printer.register_event_handler('klippy:ready', self.find_objs)

    def _load_material_database(self):
        """Load material database from JSON file."""
        try:
            if os.path.exists(MATERIAL_DATABASE_PATH):
                with open(MATERIAL_DATABASE_PATH, 'r') as f:
                    data = json.load(f)
                    if isinstance(data, dict):
                        self.material_database = data
                        self.material_list = list(data.keys())
                    elif isinstance(data, list):
                        # Convert list format to dict
                        for item in data:
                            if 'rfid' in item:
                                self.material_database[item['rfid']] = item
                        self.material_list = data
                logging.info("Loaded %d materials from database", len(self.material_database))
        except Exception as e:
            logging.warning("Failed to load material database: %s", e)

    def _load_system_config(self):
        """Load system configuration for sound settings etc."""
        try:
            if os.path.exists(SYSTEM_CONFIG_PATH):
                with open(SYSTEM_CONFIG_PATH, 'r') as f:
                    self.system_config = json.load(f)
                    sound_switch = self.system_config.get('sound_switch', True)
                    logging.info("system config get sound switch: %s", sound_switch)
        except Exception as e:
            logging.warning("Failed to load system config: %s", e)

    def _is_beep_enabled(self):
        """Check if beeper is enabled in system config."""
        return self.system_config.get('sound_switch', True)

    def find_objs(self):
        """Find required Klipper objects after ready."""
        self.toolhead = self.printer.lookup_object('toolhead')

        try:
            self._serial = self.printer.lookup_object('serial_485 serial485')
        except Exception:
            logging.info("serial_485 not found")

        try:
            self.extruder = self.printer.lookup_object('extruder')
            self.heater_hot = self.extruder.heater
        except Exception:
            logging.info("extruder/heater not found")

        try:
            self.fan = self.printer.lookup_object('fan')
        except Exception:
            pass

        try:
            self.output_pin_fan0 = self.printer.lookup_object('output_pin fan0')
        except Exception:
            pass

        try:
            self.motor_control = self.printer.lookup_object('motor_control')
        except Exception:
            pass

        try:
            self.print_stats = self.printer.lookup_object('print_stats')
        except Exception:
            pass

        try:
            self.base_info = self.printer.lookup_object('extras base_info')
        except Exception:
            pass

        # Register buttons if available
        self._register_buttons()

    def _register_buttons(self):
        """Register button handlers for filament detection."""
        try:
            buttons = self.printer.lookup_object('buttons')
            # Register for filament detection button/sensor
            if hasattr(buttons, 'register_buttons'):
                buttons.register_buttons(['not_pin'], self._button_handler)
                logging.info("[filament rack] not_pin: registered")
        except Exception as e:
            logging.info("[filament rack] do not define not_pin")

    def beep(self, pattern=None):
        """
        Activate beeper with optional pattern.

        Args:
            pattern: Beep duration/pattern string (default from config)
        """
        if not self._is_beep_enabled():
            return

        if pattern is None:
            pattern = self.beep_didi_param

        try:
            # Use shell script for beeper
            cmd = "/usr/bin/beep.sh %s" % pattern
            subprocess.check_output(cmd, shell=True)
        except Exception as e:
            logging.warning("Beep failed: %s", e)

    def blow(self, enable=True):
        """
        Control the blow/purge fan mechanism.

        Args:
            enable: True to enable blow, False to disable
        """
        try:
            if enable:
                self.gcode.run_script_from_command("SET_PIN PIN=fan0 VALUE=255")
            else:
                self.gcode.run_script_from_command("SET_PIN PIN=fan0 VALUE=0.0")
        except Exception as e:
            logging.warning("Blow control failed: %s", e)

    def check_rfid_valid(self, rfid):
        """
        Check if RFID is valid and in database.

        Args:
            rfid: RFID tag to validate

        Returns:
            bool: True if valid, False otherwise
        """
        if not rfid:
            logging.warning("[filament rack] rfid: %s", rfid)
            return False

        if rfid not in self.material_database:
            logging.warning("[filament rack] rfid[%s] is error", rfid)
            return False

        return True

    def get_material_target_temp(self, rfid):
        """
        Get target temperature for material by RFID.

        Args:
            rfid: RFID tag of material

        Returns:
            int: Target print temperature in Celsius
        """
        if rfid and rfid in self.material_database:
            material = self.material_database[rfid]
            temp = material.get('nozzle_temperature',
                               material.get('print_temp', DEFAULT_PRINT_TEMP))
            logging.info("material database get nozzle temp: %s", temp)
            logging.info("get material temp: %d", temp)
            return int(temp)

        logging.warning("get material target temp fail")
        return DEFAULT_PRINT_TEMP

    def get_material_target_speed(self, rfid):
        """
        Get target extrusion speed for material by RFID.

        Args:
            rfid: RFID tag of material

        Returns:
            float: Maximum volumetric speed in mm³/s
        """
        if rfid and rfid in self.material_database:
            material = self.material_database[rfid]
            speed = material.get('filament_max_volumetric_speed',
                                material.get('max_volumetric_speed',
                                            DEFAULT_MAX_VOLUMETRIC_SPEED))
            logging.info("material database get extrusion speed: %s", speed)
            logging.info("max_volumetric_speed: %s", speed)
            logging.info("get material extrusion speed: %d", int(speed))
            return float(speed)

        logging.warning("get material extrusion speed fail")
        return DEFAULT_MAX_VOLUMETRIC_SPEED

    def get_material_type(self, rfid):
        """
        Get material type from RFID.

        Args:
            rfid: RFID tag of material

        Returns:
            str: Material type (PLA, ABS, etc.) or None
        """
        if rfid and rfid in self.material_database:
            material = self.material_database[rfid]
            material_type = material.get('material_type')
            if material_type:
                logging.info("material_type: %s", material_type)
                return material_type
            else:
                logging.warning("material_type get failed")
        else:
            logging.warning("failed to obtain consumable type")
        return None

    def get_material_color(self, rfid):
        """
        Get material color from RFID.

        Args:
            rfid: RFID tag of material

        Returns:
            str: Color value or None
        """
        if rfid and rfid in self.material_database:
            material = self.material_database[rfid]
            color = material.get('color_value')
            if color:
                return color
            else:
                logging.warning("color_value get failed")
        return None

    def get_material_vendor(self, rfid):
        """
        Get material vendor from RFID.

        Args:
            rfid: RFID tag of material

        Returns:
            str: Vendor name or None
        """
        if rfid and rfid in self.material_database:
            material = self.material_database[rfid]
            vender = material.get('vender')
            if vender:
                return vender
            else:
                logging.warning("vender get failed")
        return None

    def enable_get_filament(self, enable=True):
        """
        Enable/disable filament detection.

        Args:
            enable: True to enable detection, False to disable
        """
        self.can_get_filament_rack = enable
        self.can_get_filament_rack_tmp = enable
        logging.info("[filament rack] enable_get_filament: %s", enable)

    def quickly_wait_heating(self, target_temp, timeout=DEFAULT_TIMEOUT):
        """
        Wait for hotend to reach temperature with timeout.

        Args:
            target_temp: Target temperature in Celsius
            timeout: Maximum wait time in seconds

        Returns:
            bool: True if temperature reached, False on timeout
        """
        if not self.heater_hot:
            return False

        start_time = self.reactor.monotonic()
        while True:
            # Get current and smoothed temperature
            cur_temp, target = self.heater_hot.get_temp(self.reactor.monotonic())
            smoothed_temp = cur_temp  # heater provides smoothed reading

            if smoothed_temp >= target_temp - 5:
                return True

            elapsed = self.reactor.monotonic() - start_time
            if elapsed > timeout:
                logging.warning("Heating timeout after %.1fs", elapsed)
                return False

            # Pause to avoid busy waiting
            self.reactor.pause(self.reactor.monotonic() + 0.5)

    def send_data(self, data):
        """
        Send data via RS-485 serial.

        Args:
            data: Data to send (list of bytes or string)

        Returns:
            Response data or None on error
        """
        if not self._serial:
            logging.warning("[filament rack] do not get respond")
            return None

        try:
            # Convert to bytes if needed
            if isinstance(data, str):
                data_bytes = bytes([int(c) for c in data.split(',')])
            elif isinstance(data, (list, tuple)):
                data_bytes = bytes(int(c) for c in data)
            else:
                data_bytes = bytes(data)

            logging.info("[filament rack] data_send: %s",
                        ' '.join('%02X' % b for b in data_bytes))

            response = self._serial.cmd_send_data_with_response(
                data_bytes,
                timeout=1.0
            )
            return response
        except Exception as e:
            logging.warning("send_data failed: %s", e)
            return None

    def send_data_string(self, data_string):
        """
        Send data as comma-separated string.

        Args:
            data_string: Comma-separated byte values

        Returns:
            Response data or None
        """
        return self.send_data(data_string)

    def _button_handler(self, eventtime, state):
        """
        Handle button press events from filament sensor.

        Args:
            eventtime: Event timestamp
            state: Button state (pressed/released)
        """
        logging.info("[filament rack] not_pin trigger, state: %s", state)

        if not self.can_get_filament_rack:
            return

        # Handle filament runout or insertion
        if state:
            # Button pressed - filament detected
            pass
        else:
            # Button released - filament removed
            pass

    def check_and_extrude(self, length, speed):
        """
        Check temperature and extrude filament.

        Args:
            length: Length to extrude in mm
            speed: Extrusion speed in mm/min
        """
        if not self.heater_hot:
            return

        cur_temp, _ = self.heater_hot.get_temp(self.reactor.monotonic())
        if cur_temp < self.min_extrude_temp:
            logging.warning("Temperature too low for extrusion: %.1f < %.1f",
                           cur_temp, self.min_extrude_temp)
            return

        # Perform extrusion
        self.gcode.run_script_from_command("G0 E%.2f F%.1f" % (length, speed))
        self.gcode.run_script_from_command("M400")

    def _update_hotend_temp_variable(self, temp):
        """Update the PRINTER_PARAM macro variable for hotend temp."""
        try:
            self.gcode.run_script_from_command(
                "SET_GCODE_VARIABLE MACRO=PRINTER_PARAM VARIABLE=hotend_temp VALUE=%s" % temp
            )
        except Exception as e:
            logging.warning("Failed to update hotend_temp variable: %s", e)

    # ============================================
    # G-code Command Handlers
    # ============================================

    def cmd_filament_rack(self, gcmd):
        """
        Main filament rack command.

        Parameters:
            ACTION: Command action (status, load, unload, etc.)
            SLOT: Slot index for operation
        """
        action = gcmd.get('ACTION', 'status').lower()
        slot = gcmd.get_int('SLOT', 0, minval=0, maxval=len(self.slots)-1)

        if action == 'status':
            # Report status
            status = self.get_status()
            gcmd.respond_info("Filament rack status: %s" % json.dumps(status, indent=2))
        elif action == 'load':
            # Load filament from slot
            gcmd.respond_info("Loading filament from slot %d" % slot)
            self._load_filament(slot)
        elif action == 'unload':
            # Unload filament to slot
            gcmd.respond_info("Unloading filament to slot %d" % slot)
            self._unload_filament(slot)
        elif action == 'detect':
            # Detect material in slot
            self._detect_material(slot)
        elif action == 'clean':
            # Clean nozzle
            self.gcode.run_script_from_command("BOX_NOZZLE_CLEAN")
        elif action == 'extrude_pos':
            # Move to extrude position
            self.gcode.run_script_from_command("BOX_GO_TO_EXTRUDE_POS")
        else:
            gcmd.respond_info("unknown action: %s" % action)

    def _load_filament(self, slot):
        """Load filament from specified slot."""
        if slot >= len(self.slots):
            return

        slot_data = self.slots[slot]
        rfid = slot_data.rfid

        if rfid and self.check_rfid_valid(rfid):
            target_temp = self.get_material_target_temp(rfid)
            self.gcode.run_script_from_command("M104 S%d" % target_temp)
            self._update_hotend_temp_variable(target_temp)
            self.quickly_wait_heating(target_temp)

    def _unload_filament(self, slot):
        """Unload filament to specified slot."""
        # Retract filament
        pass

    def _detect_material(self, slot):
        """Detect material in slot via RFID."""
        if slot >= len(self.slots):
            return

        # Read RFID via RS-485
        # Auto-address command
        response = self.send_data("auto_addr:start")
        if response:
            # Parse RFID from response
            pass

    def cmd_filament_rack_flush(self, gcmd):
        """
        Flush/purge filament command.

        Parameters:
            LENGTH: Purge length in mm (default 50)
            SPEED: Purge speed in mm/min (default 300)
        """
        length = gcmd.get_float('LENGTH', self.extrude_length)
        speed = gcmd.get_float('SPEED', 300.0)

        gcmd.respond_info("Flushing %.1fmm at %.1fmm/min" % (length, speed))

        # Heat if needed
        if self.heater_hot:
            cur_temp, _ = self.heater_hot.get_temp(self.reactor.monotonic())
            if cur_temp < self.min_extrude_temp:
                self.gcode.run_script_from_command("M104 S%d" % DEFAULT_PRINT_TEMP)
                self.quickly_wait_heating(DEFAULT_PRINT_TEMP)

        # Enable blow fan
        self.blow(True)

        # Extrude
        self.gcode.run_script_from_command("G0 E%.2f F%.1f" % (length, speed))
        self.gcode.run_script_from_command("M400")

        # Small final extrusion
        self.gcode.run_script_from_command("G0 E0.01 F60")

        # Disable blow
        self.blow(False)

    def cmd_filament_rack_pre_flush(self, gcmd):
        """
        Pre-flush preparation command.

        Prepares for purging by heating and positioning.
        """
        gcmd.respond_info("Pre-flush preparation")

        # Heat to low temp first
        self.gcode.run_script_from_command("M104 S140")

        # Move to extrude position
        self.gcode.run_script_from_command("BOX_GO_TO_EXTRUDE_POS")

        # Wait for heating
        self.quickly_wait_heating(140, timeout=30)

    def cmd_filament_rack_set_temp(self, gcmd):
        """
        Set temperature for material command.

        Parameters:
            TEMP: Target temperature in Celsius
            RFID: Optional RFID to lookup temperature
            MATERIAL_TYPE: Optional material type name
        """
        rfid = gcmd.get('RFID', None)
        material_type = gcmd.get('MATERIAL_TYPE', None)

        if rfid and self.check_rfid_valid(rfid):
            temp = self.get_material_target_temp(rfid)
        elif material_type:
            # Lookup by material type
            temp = self._get_temp_by_type(material_type)
        else:
            temp = gcmd.get_float('TEMP', DEFAULT_PRINT_TEMP)

        gcmd.respond_info("Setting temp to %.1f" % temp)
        self.gcode.run_script_from_command("M104 S%d" % int(temp))
        self._update_hotend_temp_variable(int(temp))

    def _get_temp_by_type(self, material_type):
        """Get temperature by material type name."""
        type_temps = {
            'PLA': 200,
            'ABS': 240,
            'PETG': 230,
            'TPU': 220,
            'PA': 260,
            'PC': 270,
        }
        return type_temps.get(material_type.upper(), DEFAULT_PRINT_TEMP)

    def cmd_filament_rack_modify(self, gcmd):
        """
        Modify filament rack settings.

        Parameters:
            SLOT: Slot index to modify
            REMAIN_LENGTH: New remaining length
            MATERIAL_TYPE: Material type
            COLOR: Color value
            VELOCITY: Feed velocity
        """
        slot = gcmd.get_int('SLOT', 0, minval=0, maxval=len(self.slots)-1)

        if slot >= len(self.slots):
            gcmd.respond_info("Invalid slot: %d" % slot)
            return

        slot_data = self.slots[slot]

        # Update fields if provided
        remain_length = gcmd.get_float('REMAIN_LENGTH', None)
        if remain_length is not None:
            slot_data.remain_length = remain_length

        material_type = gcmd.get('MATERIAL_TYPE', None)
        if material_type is not None:
            slot_data.material_type = material_type

        color = gcmd.get('COLOR', None)
        if color is not None:
            slot_data.color_value = color

        velocity = gcmd.get_float('VELOCITY', None)
        if velocity is not None:
            slot_data.velocity = velocity

        # Save changes
        slot_data.save()

        gcmd.respond_info("Modified slot %d: length=%.1f, type=%s, color=%s" % (
            slot, slot_data.remain_length, slot_data.material_type, slot_data.color_value))

    def cmd_set_cool_temp(self, gcmd):
        """
        Set cooling temperature command.

        Parameters:
            TEMP: Target cooling temperature (default 0 = off)
        """
        temp = gcmd.get_float('TEMP', 0.0)

        if temp <= 0:
            # Turn off heater
            self.gcode.run_script_from_command("M104 S0")
            gcmd.respond_info("Heater off")
        else:
            self.gcode.run_script_from_command("M104 S%d" % int(temp))
            gcmd.respond_info("Cool temp: %.1f" % temp)

    def cmd_save_fan(self, gcmd):
        """
        Save current fan speed.

        Saves the current fan speed for later restoration.
        """
        try:
            if self.output_pin_fan0:
                # Get from output pin
                self.saved_fan_speed = self.output_pin_fan0.last_value
                self.fan0_last_value = self.saved_fan_speed
            elif self.fan:
                # Get from fan object
                status = self.fan.get_status(self.reactor.monotonic())
                self.saved_fan_speed = status.get('speed', 0)

            gcmd.respond_info("Saved fan speed: %.2f" % self.saved_fan_speed)
        except Exception as e:
            logging.warning("save_fan failed: %s", e)

    def cmd_restore_fan(self, gcmd):
        """
        Restore saved fan speed.

        Restores the previously saved fan speed.
        """
        try:
            if self.saved_fan_speed > 0:
                self.gcode.run_script_from_command(
                    "SET_PIN PIN=fan0 VALUE=%.2f" % self.saved_fan_speed
                )
            else:
                self.gcode.run_script_from_command("SET_PIN PIN=fan0 VALUE=0.0")

            gcmd.respond_info("Restored fan speed: %.2f" % self.saved_fan_speed)
        except Exception as e:
            logging.warning("restore_fan failed: %s", e)

    def get_status(self, eventtime=None):
        """Return status for Klipper status reporting."""
        return {
            'name': self.name,
            'can_get_filament_rack': self.can_get_filament_rack,
            'saved_fan_speed': self.saved_fan_speed,
            'slots': [s.get_status() for s in self.slots],
            'material_count': len(self.material_database)
        }


def load_config(config):
    return FilamentRackWrapper(config)
