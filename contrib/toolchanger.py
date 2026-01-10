
#
# Commands:
#   PARSE_FLUSH_VOLUMES          - Parse flush matrix from loaded gcode file
#   TOOL_FLUSH TO_TNN= [FROM_TNN=] - Prime tool and optionally flush based on matrix
#   SET_TOOL_STATE TNN= [SAVE=1] - Set current tool, optionally persist as last_tnn
#   CLEAR_TOOL_STATE             - Clear current tool (filament unloaded)
#   CALC_TNN I=                  - Convert slot index to TNN string
#   PREHEAT_FOR_CHANGE [FROM_TNN=] [TO_TNN=] - Preheat for tool change
#   RETRACT_AND_CUT              - Retract filament and cut
#   CR_BOX_EXTRUDE_SAFE TNN=     - Safe extrude with verification (auto-sets tool state)
#   CR_BOX_RETRUDE_SAFE [LENGTH=] - Safe retrude with error handling
#
# Config:
#   [toolchanger]
#   flush_speed: 20              # mm³/s volumetric flow rate (optional, default 20)
#   pre_flush_speed: 10          # mm³/s for pre-flush extrusion (optional, default 10)
#   pre_flush_length: 50         # mm to extrude before flush (optional, default 50)
#   default_temp: 220            # fallback temp when no gcode data (optional, default 220)
#   retract_length: 40           # mm to retract before cutting (optional, default 40)
#   spoolman_integration: false  # enable spoolman spool tracking (optional, default false)
#   spoolman_url: http://localhost:7125/server/database/item?namespace=fluidd&key=filamentBox.slots

import re
import math
import logging


class ToolChanger:
    def __init__(self, config):
        self.printer = config.get_printer()
        self.gcode = self.printer.lookup_object("gcode")

        # Config
        self.flush_speed = config.getfloat("flush_speed", 20.0)  # mm³/s
        self.pre_flush_speed = config.getfloat("pre_flush_speed", 10.0)  # mm³/s
        self.pre_flush_length = config.getfloat("pre_flush_length", 50.0)
        self.default_temp = config.getint("default_temp", 220)
        self.retract_length = config.getfloat("retract_length", 40.0)
        self.spoolman_integration = config.getboolean("spoolman_integration", False)
        self.spoolman_url = config.get("spoolman_url", "http://localhost:7125/server/database/item?namespace=fluidd&key=filamentBox.slots")
        
        # Filament cross-section area: π × (1.75/2)² ≈ 2.405 mm²
        self.filament_area = 2.405

        # Flush matrix (parsed from gcode)
        self.matrix = None
        self.last_flush_length = 0.0

        # Temperature ranges (parsed from gcode)
        self.temp_range_high = None  # List of max temps per tool
        self.temp_range_low = None   # List of min temps per tool
        self.temp_initial_layer = None  # List of initial layer temps per tool

        # Cached flush temperatures (calculated once in PREHEAT_FOR_CHANGE, reused in TOOL_FLUSH)
        self.cached_target_temp = None
        self.cached_wait_min = None

        # Tool name to index mapping
        self.tnn_to_idx = {"T1A": 0, "T1B": 1, "T1C": 2, "T1D": 3}

        # Pending tool change goal (set on failure, cleared on success or explicit clear)
        # Format: {'target_slot': int, 'target_tnn': str, 'do_flush': bool, 'from_tnn': str|None}
        self.pending_tool_change = None



        # Register commands
        self.gcode.register_command(
            "PARSE_FLUSH_VOLUMES",
            self.cmd_PARSE_FLUSH_VOLUMES,
            desc="Parse flush_volumes_matrix from current gcode file",
        )
        self.gcode.register_command(
            "TOOL_FLUSH",
            self.cmd_TOOL_FLUSH,
            desc="Prime tool and optionally flush based on slicer matrix",
        )

        self.gcode.register_command(
            "CALC_TNN",
            self.cmd_CALC_TNN,
            desc="Calculate TNN from slot index I parameter",
        )

        self.gcode.register_command(
            "PREHEAT_FOR_CHANGE",
            self.cmd_PREHEAT_FOR_CHANGE,
            desc="Preheat for tool change (set target, wait for min)",
        )
        self.gcode.register_command(
            "RETRACT_AND_CUT",
            self.cmd_RETRACT_AND_CUT,
            desc="Retract filament and cut at cutting position",
        )
        self.gcode.register_command(
            "BOX_EXTRUDE",
            self.cmd_BOX_EXTRUDE,
            desc="Load filament via clean driver",
        )
        self.gcode.register_command(
            "BOX_RETRUDE",
            self.cmd_BOX_RETRUDE,
            desc="Unload filament via clean driver",
        )
        self.gcode.register_command(
            "TOOL_CHANGE",
            self.cmd_TOOL_CHANGE,
            desc="Full tool change sequence (Python)",
        )
        # T0-T3 shortcuts (Python to avoid Jinja2 param issues)
        # Must unregister first since .so wrapper already registers them
        for i in range(4):
            cmd_name = "T%d" % i
            # Unregister existing command (returns old handler, which we discard)
            self.gcode.register_command(cmd_name, None)
            # Register our handler
            self.gcode.register_command(
                cmd_name,
                lambda gcmd, slot=i: self._cmd_Tn(gcmd, slot),
                desc="Tool change to slot %d" % i,
            )
        
        # Retry mechanism for failed tool changes
        self.gcode.register_command(
            "RETRY_TOOL_CHANGE",
            self.cmd_RETRY_TOOL_CHANGE,
            desc="Retry failed tool change - assesses current state and completes goal",
        )
        self.gcode.register_command(
            "CLEAR_PENDING_TOOL_CHANGE",
            self.cmd_CLEAR_PENDING_TOOL_CHANGE,
            desc="Clear any pending tool change retry state",
        )


    def get_status(self, eventtime):
        # Get persistent last_tnn from save_variables
        last_tnn = None
        save_vars = self.printer.lookup_object("save_variables", None)
        if save_vars:
            last_tnn = save_vars.allVariables.get("last_loaded_tnn")

        return {
            "last_tnn": last_tnn,
            "matrix": self.matrix,
            "last_flush_length": self.last_flush_length,
            "flush_speed": self.flush_speed,
            "pre_flush_length": self.pre_flush_length,
            "temp_range_high": self.temp_range_high,
            "temp_range_low": self.temp_range_low,
            "temp_initial_layer": self.temp_initial_layer,
            "default_temp": self.default_temp,
            "retract_length": self.retract_length,
        }

    # =========================================================================
    # Box Commands (Clean Driver)
    # =========================================================================

    def cmd_BOX_EXTRUDE(self, gcmd):
        """Load filament via clean driver - calls Python directly."""
        tnn = self._get_param(gcmd, "TNN")
        if tnn is None:
            raise gcmd.error("BOX_EXTRUDE requires TNN parameter")
        
        slot = self.tnn_to_idx.get(tnn)
        if slot is None:
            raise gcmd.error("Invalid TNN: %s" % tnn)
        
        gcmd.respond_info("Loading slot %d (%s)" % (slot, tnn))
        
        box = self.printer.lookup_object('box')
        result = box.load_filament(slot)
        
        if not result.success:
            raise gcmd.error("BOX_EXTRUDE failed: %s" % result.error)
        
        # Save as last_tnn for flush volume calculation
        self._save_last_tnn(tnn)
        self._set_active_spool_for_tnn(tnn)
        gcmd.respond_info("Saved last_tnn=%s" % tnn)

    def cmd_BOX_RETRUDE(self, gcmd):
        """Unload filament via clean driver - calls Python directly."""
        gcmd.respond_info("Unloading via clean driver")
        
        box = self.printer.lookup_object('box')
        result = box.auto_unload(gcode=self.gcode)
        
        if not result.success:
            raise gcmd.error("BOX_RETRUDE failed: %s" % result.error)
        
        gcmd.respond_info("Unload successful")
        
        if self.spoolman_integration:
            self.gcode.run_script_from_command("CLEAR_ACTIVE_SPOOL")



    # =========================================================================
    # TOOL_CHANGE - Full Python-controlled tool change
    # =========================================================================

    def _get_param(self, gcmd, name, default=None, parser=str):
        """Robust parameter getting that handles Creality's broken parsing (leading =)."""
        params = gcmd.get_command_parameters()
        val = params.get(name, default)
        
        if val is None:
            return default
            
        # Strip leading = if present (Creality bug)
        if isinstance(val, str) and val.startswith("="):
            val = val[1:]
            
        try:
            return parser(val)
        except ValueError:
            raise gcmd.error("Unable to parse parameter '%s' value '%s'" % (name, val))

    def cmd_TOOL_CHANGE(self, gcmd):
        """Full tool change sequence in Python for synchronous control.
        
        Usage: TOOL_CHANGE SLOT=0 [FLUSH=1]
        """
        slot = self._get_param(gcmd, "SLOT", parser=int)
        if slot is None:
            raise gcmd.error("TOOL_CHANGE requires SLOT parameter")
        
        do_flush = self._get_param(gcmd, "FLUSH", default=1, parser=int) == 1
        
        tnn = self._calc_tnn_from_index(slot)
        gcmd.respond_info("TOOL_CHANGE: slot=%d (%s) flush=%s" % (slot, tnn, do_flush))
        
        # 1. Get fresh box status
        box = self.printer.lookup_object('box', None)
        if not box:
            raise gcmd.error("Box not available")
        
        box.refresh_box_status()
        loaded_slot = box._cached_loaded_slot
        gcmd.respond_info("Box status: loaded_slot=%d" % loaded_slot)
        
        # Determine "from" for temperature/flush calculation
        last_tnn = self._get_last_tnn()
        if loaded_slot >= 0:
            from_tnn = self._calc_tnn_from_index(loaded_slot)
        else:
            from_tnn = last_tnn
        
        # Build goal for potential retry
        goal = {
            'target_slot': slot,
            'target_tnn': tnn,
            'do_flush': do_flush,
            'from_tnn': from_tnn,
        }
        
        # Clear any previous pending retry since we're starting fresh
        self.pending_tool_change = None
        
        # 2. Check if already loaded (box reports this slot in buffer)
        # Note: This doesn't mean filament is at printhead - load_filament handles that
        if loaded_slot == slot:
            gcmd.respond_info("Slot %d in buffer, checking sensor..." % slot)
            # load_filament will either activate tracking (if at sensor) or feed to printhead
            if not self._do_box_extrude(gcmd, tnn, goal=goal):
                return  # Failed - already paused or error raised
            if do_flush:
                self._set_temp(gcmd, from_tnn, tnn)  # Set temp before flush (was missing!)
                self._do_flush(gcmd, tnn)
                self._wait_for_initial_layer_temp(gcmd, tnn)
            gcmd.respond_info("TOOL_CHANGE complete: %s" % tnn)
            return
        
        # 3. Set temp (no wait - wait happens before flush)
        if do_flush:
            self._set_temp(gcmd, from_tnn, tnn)
        
        # 4. Unload if something is loaded
        if loaded_slot >= 0:
            gcmd.respond_info("Unloading slot %d before loading %s" % (loaded_slot, tnn))
            self._do_home_if_needed()
            self._do_retract_and_cut(gcmd)
            if not self._do_box_retrude(gcmd, goal=goal):
                return  # Failed - already paused or error raised
        
        # 5. Load new filament
        gcmd.respond_info("Loading %s" % tnn)
        if not self._do_box_extrude(gcmd, tnn, goal=goal):
            return  # Failed - already paused or error raised
        
        # 6. Flush (waits for temp, then extrudes)
        if do_flush:
            self._do_flush(gcmd, tnn)
            self._wait_for_initial_layer_temp(gcmd, tnn)
        
        gcmd.respond_info("TOOL_CHANGE complete: %s" % tnn)

    def _cmd_Tn(self, gcmd, slot):
        """Handler for T0-T3 commands."""
        do_flush = self._get_param(gcmd, "FLUSH", default=1, parser=int) == 1
        self.gcode.run_script_from_command("TOOL_CHANGE SLOT=%d FLUSH=%d" % (slot, 1 if do_flush else 0))

    def cmd_RETRY_TOOL_CHANGE(self, gcmd):
        """Retry a failed tool change by assessing current state and completing the goal.
        
        Queries fresh state from box/sensor, determines what steps remain,
        and executes only those. Resumes print on success.
        """
        goal = self.pending_tool_change
        if not goal:
            raise gcmd.error("No pending tool change to retry. Use TOOL_CHANGE SLOT=X instead.")
        
        target_slot = goal['target_slot']
        target_tnn = goal['target_tnn']
        do_flush = goal['do_flush']
        from_tnn = goal.get('from_tnn')
        
        gcmd.respond_info("RETRY_TOOL_CHANGE: target=%s flush=%s" % (target_tnn, do_flush))
        
        # Query current state fresh
        box = self.printer.lookup_object('box')
        box.refresh_box_status()
        loaded_slot = box._cached_loaded_slot
        filament_detected, _ = box._get_filament_detected()
        
        gcmd.respond_info("Current state: loaded_slot=%d, filament_detected=%s" % (loaded_slot, filament_detected))
        
        # Case 1: Wrong slot loaded - need to unload first
        if loaded_slot >= 0 and loaded_slot != target_slot:
            gcmd.respond_info("Wrong slot (%d) loaded, unloading first..." % loaded_slot)
            if filament_detected:
                # Filament at printhead - need retract and cut
                self._do_home_if_needed()
                self._do_retract_and_cut(gcmd)
            if not self._do_box_retrude(gcmd, goal=goal):
                return  # Failed again - stays paused, goal still pending
            # Refresh state after unload
            box.refresh_box_status()
            loaded_slot = box._cached_loaded_slot
            filament_detected, _ = box._get_filament_detected()
        
        # Set temp early (before load) so extruder heats while loading
        if do_flush:
            if from_tnn:
                self._set_temp(gcmd, from_tnn, target_tnn)
            else:
                self._set_temp(gcmd, None, target_tnn)
        
        # Case 2: Target slot not loaded OR loaded but not at sensor
        if loaded_slot != target_slot or not filament_detected:
            gcmd.respond_info("Loading %s..." % target_tnn)
            if not self._do_box_extrude(gcmd, target_tnn, goal=goal):
                return  # Failed again - stays paused, goal still pending
            # Refresh state after load
            filament_detected, _ = box._get_filament_detected()
        
        # Case 3: Verify we're ready for flush
        if not filament_detected:
            self._handle_box_error(gcmd, "Filament still not at sensor after load", goal=goal)
            return
        
        # Case 4: Flush if needed (temp wait happens inside _do_flush)
        if do_flush:
            self._do_flush(gcmd, target_tnn)
        
        # Success! Clear pending and resume
        self.pending_tool_change = None
        gcmd.respond_info("Tool change recovered successfully!")
        self.gcode.run_script_from_command("RESUME")

    def cmd_CLEAR_PENDING_TOOL_CHANGE(self, gcmd):
        """Clear any pending tool change retry state."""
        if self.pending_tool_change:
            tnn = self.pending_tool_change.get('target_tnn', 'unknown')
            gcmd.respond_info("Cleared pending retry for %s" % tnn)
            self.pending_tool_change = None
        else:
            gcmd.respond_info("No pending tool change to clear")

    def _get_last_tnn(self):
        """Get last_tnn from persistent storage."""
        save_vars = self.printer.lookup_object("save_variables", None)
        if save_vars:
            return save_vars.allVariables.get("last_loaded_tnn")
        return None

    def _set_temp(self, gcmd, from_tnn, to_tnn):
        """Set temperature based on from/to TNNs (no wait)."""
        has_from = from_tnn is not None and from_tnn in self.tnn_to_idx
        has_to = to_tnn is not None and to_tnn in self.tnn_to_idx
        
        # Fallback if no temp data
        if not self.temp_range_high or not self.temp_range_low:
            gcmd.respond_info("Setting temp to 240°C (default)")
            self.cached_target_temp = 240
            self.cached_wait_min = 220
            self.gcode.run_script_from_command("M104 S240")
            return
        
        from_idx = self.tnn_to_idx[from_tnn] if has_from else None
        to_idx = self.tnn_to_idx[to_tnn] if has_to else None
        
        target_temp, wait_min = self._calculate_transition_temps(from_idx, to_idx)
        self.cached_target_temp = target_temp
        self.cached_wait_min = wait_min
        
        if target_temp:
            gcmd.respond_info("Setting temp to %d°C" % target_temp)
            self.gcode.run_script_from_command("M104 S%d" % target_temp)

    def _do_home_if_needed(self):
        """Home axes if needed."""
        self.gcode.run_script_from_command("HOME_IF_NEEDED")

    def _do_retract_and_cut(self, gcmd):
        """Retract filament and cut."""
        gcmd.respond_info("Retracting and cutting")
        self.gcode.run_script_from_command("SAVE_GCODE_STATE NAME=_retract_cut_state")
        self.gcode.run_script_from_command("M83")
        
        # Ensure we are hot enough before retracting
        wait_min = self.cached_wait_min
        if wait_min:
             gcmd.respond_info("Waiting for temp >=%d°C before retract" % wait_min)
             self.gcode.run_script_from_command("TEMPERATURE_WAIT SENSOR=extruder MINIMUM=%d" % wait_min)
        else:
             # Fallback safety
             gcmd.respond_info("Waiting for temp >=200°C before retract (safety fallback)")
             self.gcode.run_script_from_command("TEMPERATURE_WAIT SENSOR=extruder MINIMUM=200")

        self.gcode.run_script_from_command("SET_VELOCITY_LIMIT VELOCITY=500 ACCEL_TO_DECEL=10000 ACCEL=10000")
        self.gcode.run_script_from_command("G0 X10 Y200 F18000")
        self.gcode.run_script_from_command("G1 E-%.4f F1000" % self.retract_length)
        self.gcode.run_script_from_command("BOX_CUT_MATERIAL")
        self.gcode.run_script_from_command("BOX_GO_TO_EXTRUDE_POS")
        self.gcode.run_script_from_command("RESTORE_GCODE_STATE NAME=_retract_cut_state MOVE=0")

    def _handle_box_error(self, gcmd, error_msg, goal=None):
        """Handle box operation failure - PAUSE if printing, else raise.
        
        If goal is provided and we're printing, stores it for RETRY_TOOL_CHANGE.
        """
        # Store goal for retry
        if goal:
            self.pending_tool_change = goal
        
        # Check if we're printing
        sd = self.printer.lookup_object('virtual_sdcard', None)
        if sd and sd.is_active():
            # Show error-style message (!! prefix) without aborting
            self.gcode.respond_raw("!! %s" % error_msg)
            if goal:
                gcmd.respond_info("Use RETRY_TOOL_CHANGE to retry after fixing the issue")
            gcmd.respond_info("Pausing print for recovery...")
            self.gcode.run_script_from_command("PAUSE")
        else:
            # Not printing - raise error to stop execution
            raise gcmd.error(error_msg)

    def _do_box_retrude(self, gcmd, goal=None):
        """Unload filament via box - calls Python directly."""
        gcmd.respond_info("Box retrude")
        
        box = self.printer.lookup_object('box')
        result = box.auto_unload(gcode=self.gcode)
        
        if not result.success:
            self._handle_box_error(gcmd, "Unload failed: %s" % result.error, goal=goal)
            return False
        
        if self.spoolman_integration:
            self.gcode.run_script_from_command("CLEAR_ACTIVE_SPOOL")
        return True

    def _do_box_extrude(self, gcmd, tnn, goal=None):
        """Load filament via box - calls Python directly."""
        slot = self.tnn_to_idx.get(tnn)
        if slot is None:
            raise gcmd.error("Invalid TNN: %s" % tnn)
        
        gcmd.respond_info("Loading slot %d (%s)" % (slot, tnn))
        
        box = self.printer.lookup_object('box')
        result = box.load_filament(slot)
        
        if not result.success:
            self._handle_box_error(gcmd, "Load failed: %s" % result.error, goal=goal)
            return False
        
        # Save as last_tnn for flush calculation
        self._save_last_tnn(tnn)
        self._set_active_spool_for_tnn(tnn)
        return True

    def _do_flush(self, gcmd, to_tnn):
        """Wait for temp and flush."""
        target_temp = self.cached_target_temp
        wait_min = self.cached_wait_min
        
        # Move to extrude position first
        self.gcode.run_script_from_command("BOX_GO_TO_EXTRUDE_POS")
        
        if target_temp and wait_min:
            gcmd.respond_info("Waiting for temp >=%d°C before flush" % wait_min)
            self.gcode.run_script_from_command("M104 S%d" % target_temp)
            self.gcode.run_script_from_command("TEMPERATURE_WAIT SENSOR=extruder MINIMUM=%d" % wait_min)
        else:
            gcmd.respond_info("Waiting for temp >=220°C before flush (default)")
            self.gcode.run_script_from_command("M104 S240")
            self.gcode.run_script_from_command("TEMPERATURE_WAIT SENSOR=extruder MINIMUM=220")
        
        # Call existing flush logic
        self.gcode.run_script_from_command("TOOL_FLUSH TO_TNN=%s" % to_tnn)

    # =========================================================================
    # Tool State Commands
    # =========================================================================

    def cmd_CALC_TNN(self, gcmd):
        i_param = self._get_param(gcmd, "I", parser=int)
        if i_param is None:
            raise gcmd.error("CALC_TNN requires I parameter")

        tnn = self._calc_tnn_from_index(i_param)
        gcmd.respond_info("CALC_TNN: I=%d -> %s" % (i_param, tnn))


    def _calc_tnn_from_index(self, i_param):
        """Convert slot index to TNN string (e.g., 0->T1A, 1->T1B, 5->T2B)"""
        addr = int(i_param / 4) + 1
        num_map = ["A", "B", "C", "D"]
        num = i_param % 4
        return "T%d%s" % (addr, num_map[num])

    def _save_last_tnn(self, tnn):
        """Save TNN to persistent storage via save_variables"""
        cmd = "SAVE_VARIABLE VARIABLE=last_loaded_tnn VALUE=\"'%s'\"" % tnn
        self.gcode.run_script_from_command(cmd)

    def _set_active_spool_for_tnn(self, tnn):
        """Fetch spool ID from Moonraker database and set active spool via spoolman"""
        if not self.spoolman_integration:
            return
        
        # Convert TNN to slot index (T1A=0, T1B=1, T1C=2, T1D=3, etc.)
        if tnn not in self.tnn_to_idx:
            logging.warning("Spoolman: invalid TNN %s, skipping", tnn)
            return
        
        slot_idx = self.tnn_to_idx[tnn]
        
        try:
            # Python 2/3 compatible URL fetch
            try:
                from urllib.request import urlopen
            except ImportError:
                from urllib2 import urlopen
            
            import json
            
            response = urlopen(self.spoolman_url, timeout=5)
            data = json.loads(response.read().decode('utf-8'))
            
            # Response format: {"result": {"value": [id1, id2, null, id4]}}
            slots = data.get("result", {}).get("value", [])
            
            if slot_idx >= len(slots):
                logging.warning("Spoolman: slot index %d out of range (only %d slots)", slot_idx, len(slots))
                return
            
            spool_id = slots[slot_idx]
            
            if spool_id is None:
                logging.warning("Spoolman: no spool ID configured for slot %d (%s)", slot_idx, tnn)
                return
            
            # Set active spool
            self.gcode.run_script_from_command("SET_ACTIVE_SPOOL ID=%s" % spool_id)
            logging.info("Spoolman: set active spool ID=%s for %s", spool_id, tnn)
            
        except Exception as e:
            logging.warning("Spoolman: failed to set active spool for %s: %s", tnn, str(e))

    def _snap_and_clean(self):
        """Fan blast, retract to snap, clean nozzle"""
        self.gcode.run_script_from_command("_FLUSH_CLEAN_SNAP")

    def _wait_for_initial_layer_temp(self, gcmd, to_tnn):
        """Wait for exact initial layer temp at extrude pos, clean if wait > 5s.
        
        After flush, we may be at a different temp than initial_layer requires.
        This ensures we reach the exact print temp before leaving extrude pos.
        If wait exceeds 5 seconds, nozzle clean is called to remove drool.
        Always ends in-bounds (Y=350).
        """
        to_idx = self.tnn_to_idx.get(to_tnn)
        if to_idx is None:
            gcmd.respond_info("No valid tool index, skipping initial layer temp wait")
            return
        
        # Get initial layer temp for this tool
        if not self.temp_initial_layer or to_idx >= len(self.temp_initial_layer):
            gcmd.respond_info("No initial layer temp data, skipping")
            return
        
        target_temp = self.temp_initial_layer[to_idx]
        temp_min = target_temp - 2
        temp_max = target_temp + 2
        
        # Check current temp to see if we need to wait
        heater = self.printer.lookup_object('heaters').lookup_heater('extruder')
        current_temp, _ = heater.get_temp(self.printer.get_reactor().monotonic())
        
        if temp_min <= current_temp <= temp_max:
            gcmd.respond_info("Already at initial layer temp (%.1f°C), moving in-bounds" % current_temp)
            self.gcode.run_script_from_command("G1 Y350 F12000")
            return
        
        # Move to extrude pos for temp wait (drool goes in waste)
        self.gcode.run_script_from_command("BOX_GO_TO_EXTRUDE_POS")
        
        # Set target and record start time
        gcmd.respond_info("Waiting for initial layer temp %d°C (±2)" % target_temp)
        self.gcode.run_script_from_command("M104 S%d" % target_temp)
        
        reactor = self.printer.get_reactor()
        start_time = reactor.monotonic()
        
        # Wait for temp with polling (so we can track time)
        while True:
            current_temp, _ = heater.get_temp(reactor.monotonic())
            if temp_min <= current_temp <= temp_max:
                break
            # Check every 0.5s
            reactor.pause(reactor.monotonic() + 0.5)
        
        wait_duration = reactor.monotonic() - start_time
        gcmd.respond_info("Initial layer temp reached in %.1fs" % wait_duration)
        
        # If we waited > 5 seconds, clean nozzle (drool accumulated)
        if wait_duration > 5.0:
            gcmd.respond_info("Long wait - cleaning nozzle")
            self.gcode.run_script_from_command("_NOZZLE_CLEAN")
        else:
            # Just move in-bounds
            self.gcode.run_script_from_command("G1 Y350 F12000")

    # =========================================================================
    # Temperature Management
    # =========================================================================

    def _parse_temp_array(self, text, key, expected_len):
        """Parse a comma-separated temp array from gcode comments"""
        pattern = r";\s*" + re.escape(key) + r"\s*=\s*([0-9,]+)"
        match = re.search(pattern, text)
        if not match:
            return None

        values = []
        for v in match.group(1).split(","):
            v = v.strip()
            if v:
                values.append(int(v))

        # Only return if we have enough values for the tool count
        if len(values) >= expected_len:
            return values[:expected_len]
        return None


    def cmd_PREHEAT_FOR_CHANGE(self, gcmd):
        """
        Preheat for tool change calculates temps, caches them, sets target and waits for minimum.
        Cached temps are reused by TOOL_FLUSH to guard against external temp changes.
        
        Usage:
        - PREHEAT_FOR_CHANGE FROM_TNN=X TO_TNN=Y  (transition: use overlap logic with initial_layer override)
        - PREHEAT_FOR_CHANGE FROM_TNN=X           (retract only: use from tool's midpoint)
        - PREHEAT_FOR_CHANGE TO_TNN=Y             (first load: use to tool's range with initial_layer override)
        """
        from_tnn = self._get_param(gcmd, "FROM_TNN")
        to_tnn = self._get_param(gcmd, "TO_TNN")

        has_from = from_tnn is not None and from_tnn in self.tnn_to_idx
        has_to = to_tnn is not None and to_tnn in self.tnn_to_idx

        if not has_from and not has_to:
            gcmd.respond_info("PREHEAT_FOR_CHANGE: no valid TNN provided, skipping")
            self.cached_target_temp = None
            self.cached_wait_min = None
            return

        # Fallback to default if no temp data
        if not self.temp_range_high or not self.temp_range_low:
            gcmd.respond_info("Setting temp to 240°C (default, no gcode data)")
            self.cached_target_temp = 240
            self.cached_wait_min = 220
            self.gcode.run_script_from_command("M104 S240")
            # No wait here - wait happens in TOOL_FLUSH before extrusion
            return

        from_idx = self.tnn_to_idx[from_tnn] if has_from else None
        to_idx = self.tnn_to_idx[to_tnn] if has_to else None

        # Calculate temps based on scenario
        target_temp, wait_min = self._calculate_transition_temps(from_idx, to_idx)

        # Cache calculated temps for TOOL_FLUSH to reuse
        self.cached_target_temp = target_temp
        self.cached_wait_min = wait_min

        if target_temp is None:
            gcmd.respond_info("Preheat: could not determine temps, skipping")
            return

        gcmd.respond_info("Setting temp to %d°C" % target_temp)
        self.gcode.run_script_from_command("M104 S%d" % target_temp)
        # No wait here - wait happens in TOOL_FLUSH before extrusion

    def _calculate_transition_temps(self, from_idx, to_idx):
        """Calculate target and wait temperatures based on tool indices."""
        target_temp = None
        wait_min = None
        
        has_from = from_idx is not None
        has_to = to_idx is not None

        if has_from and has_to:
            # Full transition - use overlap logic with initial_layer override
            if from_idx < len(self.temp_range_high) and to_idx < len(self.temp_range_high):
                prev_high = self.temp_range_high[from_idx]
                prev_low = self.temp_range_low[from_idx]
                new_high = self.temp_range_high[to_idx]
                new_low = self.temp_range_low[to_idx]

                target_temp = min(prev_high, new_high)
                wait_min = max(prev_low, new_low)

                # No overlap - prioritize new filament to avoid clogs
                if wait_min > target_temp:
                    target_temp = new_high
                    wait_min = new_low

                # Override with initial_layer temp if it's within safe range
                if self.temp_initial_layer and to_idx < len(self.temp_initial_layer):
                    initial_temp = self.temp_initial_layer[to_idx]
                    if wait_min <= initial_temp <= target_temp:
                        target_temp = initial_temp
        
        elif has_from:
            # Retract only - target midpoint for quality, wait for low (safe minimum)
            if from_idx < len(self.temp_range_low) and from_idx < len(self.temp_range_high):
                low_temp = self.temp_range_low[from_idx]
                high_temp = self.temp_range_high[from_idx]
                target_temp = (low_temp + high_temp) // 2
                wait_min = low_temp

        elif has_to:
            # First load - use to tool's range with initial_layer override
            if to_idx < len(self.temp_range_high):
                target_temp = self.temp_range_high[to_idx]
                wait_min = self.temp_range_low[to_idx]
                # Apply initial_layer override if available and within range
                if self.temp_initial_layer and to_idx < len(self.temp_initial_layer):
                    initial_temp = self.temp_initial_layer[to_idx]
                    if wait_min <= initial_temp <= target_temp:
                        target_temp = initial_temp

        return target_temp, wait_min

    # =========================================================================
    # Retract and Cut
    # =========================================================================

    def cmd_RETRACT_AND_CUT(self, gcmd):
        """
        Retract filament and cut at cutting position.
        Assumes temp is already set by PREHEAT_FOR_CHANGE.
        """
        self._do_home_if_needed()
        self._do_retract_and_cut(gcmd)

    # =========================================================================
    # Flush Volume Commands
    # =========================================================================

    def cmd_PARSE_FLUSH_VOLUMES(self, gcmd):
        sd = self.printer.lookup_object("virtual_sdcard", None)
        if sd is None:
            raise gcmd.error("virtual_sdcard not configured")

        filepath = sd.file_path()
        if not filepath:
            raise gcmd.error("No file currently loaded")

        # Read last 50KB of file (matrix comment is near end)
        try:
            with open(filepath, "rb") as f:
                f.seek(0, 2)
                size = f.tell()
                f.seek(max(0, size - 50000))
                tail = f.read().decode("utf-8", errors="ignore")
        except Exception as e:
            raise gcmd.error("Failed to read gcode file: %s" % str(e))

        # Parse flush_volumes_matrix
        match = re.search(r";\s*flush_volumes_matrix\s*=\s*([0-9.,]+)", tail)
        if not match:
            gcmd.respond_info("flush_volumes_matrix not found in gcode")
            self.matrix = None
            return

        # Parse values
        raw_values = match.group(1).split(",")
        values = []
        for v in raw_values:
            v = v.strip()
            if not v:
                continue
            values.append(float(v))

        # Determine matrix dimensions (n x n)
        n_sq = len(values)
        n = int(math.sqrt(n_sq))
        if n * n != n_sq:
            raise gcmd.error(
                "flush_volumes_matrix size %d is not a perfect square" % n_sq
            )

        # Build 2D matrix
        self.matrix = []
        for i in range(n):
            row = values[i * n : (i + 1) * n]
            self.matrix.append(row)

        gcmd.respond_info("Flush volumes: parsed %dx%d matrix" % (n, n))

        # Parse temperature ranges
        self.temp_range_high = self._parse_temp_array(tail, "nozzle_temperature_range_high", n)
        self.temp_range_low = self._parse_temp_array(tail, "nozzle_temperature_range_low", n)

        # Parse initial layer temps
        self.temp_initial_layer = self._parse_temp_array(tail, "nozzle_temperature_initial_layer", n)

        if self.temp_range_high and self.temp_range_low:
            gcmd.respond_info("Temp ranges: high=%s low=%s" % (self.temp_range_high, self.temp_range_low))
            if self.temp_initial_layer:
                gcmd.respond_info("Initial layer temps: %s" % self.temp_initial_layer)
        else:
            gcmd.respond_info("Temp ranges: not found or incomplete, temp management disabled")

    def cmd_TOOL_FLUSH(self, gcmd):
        from_tnn = self._get_param(gcmd, "FROM_TNN")
        to_tnn = self._get_param(gcmd, "TO_TNN")

        # TO_TNN is required
        if to_tnn is None or to_tnn not in self.tnn_to_idx:
            gcmd.respond_info("TOOL_FLUSH: invalid or missing TO_TNN (%s)" % to_tnn)
            return

        to_idx = self.tnn_to_idx[to_tnn]

        # Determine FROM for flush volume calculation:
        # 1. If FROM_TNN provided explicitly, use it
        # 2. Else query box status - if slot loaded, convert to TNN
        # 3. Else use last_tnn (persistent fallback when box is empty)
        # 4. Else no from - pre-flush only
        if from_tnn is not None and from_tnn in self.tnn_to_idx:
            from_idx = self.tnn_to_idx[from_tnn]
        else:
            # Try box status
            try:
                box = self.printer.lookup_object('box', None)
                if box:
                    box_status = box.get_status(self.printer.get_reactor().monotonic())
                    loaded_slot = box_status.get('loaded_slot', -1)
                    if loaded_slot >= 0:
                        from_tnn = self._calc_tnn_from_index(loaded_slot)
                        from_idx = loaded_slot
                        gcmd.respond_info("Flush from: %s (from box status)" % from_tnn)
                    else:
                        # Box empty - use last_tnn
                        save_vars = self.printer.lookup_object("save_variables", None)
                        if save_vars:
                            from_tnn = save_vars.allVariables.get("last_loaded_tnn")
                            if from_tnn and from_tnn in self.tnn_to_idx:
                                from_idx = self.tnn_to_idx[from_tnn]
                                gcmd.respond_info("Flush from: %s (from last_tnn)" % from_tnn)
                            else:
                                from_tnn = None
                                from_idx = None
                        else:
                            from_tnn = None
                            from_idx = None
                else:
                    from_tnn = None
                    from_idx = None
            except Exception:
                from_tnn = None
                from_idx = None

        # Re-apply cached temperatures and WAIT before extrusion
        target_temp = self.cached_target_temp
        wait_min = self.cached_wait_min

        if target_temp is not None and wait_min is not None:
            self.gcode.run_script_from_command("M104 S%d" % target_temp)
            gcmd.respond_info("Waiting for temp >=%d°C before flush" % wait_min)
            self.gcode.run_script_from_command(
                "TEMPERATURE_WAIT SENSOR=extruder MINIMUM=%d" % wait_min
            )
        else:
            # Fallback
            self.gcode.run_script_from_command("M104 S240")
            gcmd.respond_info("Waiting for temp >=220°C before flush (default)")
            self.gcode.run_script_from_command(
                "TEMPERATURE_WAIT SENSOR=extruder MINIMUM=220"
            )

        # Convert mm³/s to mm/min for gcode: (mm³/s / area) * 60
        feed_rate = (self.flush_speed / self.filament_area) * 60.0
        pre_feed_rate = (self.pre_flush_speed / self.filament_area) * 60.0

        # Determine flush length from matrix
        # If from == to, or no from, or no matrix: pre-flush only
        length = 0.0
        volume = 0.0
        if from_idx is not None and from_tnn != to_tnn and self.matrix is not None:
            if from_idx < len(self.matrix) and to_idx < len(self.matrix[0]):
                volume = self.matrix[from_idx][to_idx]
                if volume > 0:
                    length = volume / self.filament_area

        self.last_flush_length = length

        # Log what we're doing
        if length > 0:
            gcmd.respond_info(
                "Extruding %.0fmm (pre flush) + %.1fmm (flush %.0fmm³ %s→%s)"
                % (self.pre_flush_length, length, volume, from_tnn, to_tnn)
            )
        else:
            gcmd.respond_info("Extruding %.0fmm (pre flush only)" % self.pre_flush_length)

        # Flush in 100mm chunks with snap/clean between each (not after last)
        # Pre-flush at slower speed, then flush at full speed
        # _snap_and_clean retracts 1.2mm, so we add that back to remaining after each snap
        self.gcode.run_script_from_command("SAVE_GCODE_STATE NAME=tool_flush_state")
        self.gcode.run_script_from_command("M83")  # Relative E mode
        
        chunk_size = 100.0
        remaining = length + self.pre_flush_length
        pre_flush_remaining = self.pre_flush_length

        while remaining > 0:
            chunk = min(chunk_size, remaining)
            remaining -= chunk
            # Pre-flush portion at slower speed
            if pre_flush_remaining > 0:
                pre_chunk = min(pre_flush_remaining, chunk)
                self.gcode.run_script_from_command(
                    "G1 E%.4f F%.1f" % (pre_chunk, pre_feed_rate)
                )
                pre_flush_remaining -= pre_chunk
                chunk -= pre_chunk
            # Remaining chunk at full speed
            if chunk > 0:
                self.gcode.run_script_from_command(
                    "G1 E%.4f F%.1f" % (chunk, feed_rate)
                )
            # Snap/clean after each chunk, compensate for 1.2mm retract (except last)
            self._snap_and_clean()
            if remaining > 0:
                remaining += 1.2  # Compensate for retract in _snap_and_clean
        
        self.gcode.run_script_from_command("RESTORE_GCODE_STATE NAME=tool_flush_state MOVE=0")


def load_config(config):
    return ToolChanger(config)
