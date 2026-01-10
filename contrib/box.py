# box.py - Clean box driver
# Uses the .so for normal operation, but adds BOX commands that use our clean driver

import struct
import time
from datetime import datetime, timezone, timedelta
from dataclasses import dataclass
from typing import Optional, Dict, Any

from .box_wrapper import MultiColorMeterialBoxWrapper as _OriginalWrapper
from .box_protocol import CleanBoxDriver, crc8


# =============================================================================
# BoxResult - Structured return type for driver operations
# =============================================================================

@dataclass
class BoxResult:
    """Result from box operations. Used for clean separation between driver and gcode layer."""
    success: bool
    error: Optional[str] = None
    data: Optional[Dict[str, Any]] = None

# =============================================================================
# Configuration
# =============================================================================

_log_file = "/tmp/box_driver.log"

# Protocol constants
# CRC_POLY moved to box_protocol.py
# BOX_ADDR moved to box_protocol.py
TRACKING_ACTIVE_FLAG = 0x02

# Timeouts (seconds)
DEFAULT_TIMEOUT = 1.0
STAGE_0_TIMEOUT = 45.0    # Auto-unload may take 30s+
STAGE_4_TIMEOUT = 30.0    # Feed to printhead
SLOT_MOTOR_TIMEOUT = 45.0 # 40s internal + margin

# Stage 5 - Wait for box stall
LOAD_TIMEOUT = 45.0       # Box internal timeout is 40s, add margin
STAGE_5_POLL_INTERVAL = 0.1

# Encoder stability detection (grind jam)
ENCODER_STABLE_THRESHOLD = 5.0  # mm - delta less than this = stable
ENCODER_STABLE_POLLS = 15        # polls stable = grind (~1.0 seconds)

# Extruder retraction
RETRACT_DISTANCE_MM = 25
RETRACT_SPEED_F = 900
RETRACT_CYCLES = 2

# Background polling
POLL_INTERVAL = 1.0           # Normal poll interval (seconds)
POLL_INITIAL_DELAY = 5.0      # Delay before first poll after klippy:ready
POLL_ERROR_BACKOFF = 10.0     # Backoff after detecting error

# Clog detection thresholds
CLOG_EXTRUDER_THRESHOLD = 75.0    # mm - extruder must move this much to trigger
CLOG_ENCODER_MIN = 5.0            # mm - encoder less than this = clog
CLOG_ENCODER_RESET = 25.0         # mm - encoder movement to reset window

# =============================================================================
# Logging
# =============================================================================

_tz_pst = timezone(timedelta(hours=-8))

def _log(msg):
    try:
        with open(_log_file, 'a') as f:
            f.write(f"[{datetime.now(_tz_pst).strftime('%H:%M:%S.%f')[:-3]}] {msg}\n")
    except:
        pass

# CRC and CleanBoxDriver have been moved to box_protocol.py

# ===== Klipper wrapper =====

class MultiColorMeterialBoxWrapper(_OriginalWrapper):
    """Wrapper with BOX commands for clean driver."""
    
    def __init__(self, config):
        _log("=" * 60)
        _log("BOX DRIVER - Clean driver")
        _log("=" * 60)
        super().__init__(config)
        
        # Gcode object for console output
        self.gcode = self.printer.lookup_object('gcode')
        
        self._clean_driver = None
        # Cached state - updated when we actually query the box
        self._cached_loaded_slot = -1
        self._cached_tracking = False
        
        # Error/clog polling state
        self._poll_timer = None
        self._box_operation_in_progress = False
        self._last_runout_logged = False  # Avoid spamming runout logs
        
        # Clog detection state (rolling window)
        self._clog_extruder_baseline = None
        self._clog_encoder_baseline = None
        self._clog_window_mm = CLOG_EXTRUDER_THRESHOLD
        # Last polled values (for debug output)
        self._last_poll_extruder = None
        self._last_poll_encoder = None
        self._last_poll_mcu_success = False
        
        # CRC validation stats
        self._crc_total = 0
        self._crc_fails = 0
        self._last_crc_fail_time = None
        
        self._init_clean_driver()
        
        # Register for klippy:ready to start polling
        self.printer.register_event_handler("klippy:ready", self._start_status_polling)
    
    def _init_clean_driver(self):
        try:
            serial = self.printer.lookup_object("serial_485 serial485")
            # Pass printer so CleanBoxDriver can lazily lookup sniffer
            self._clean_driver = CleanBoxDriver(serial, logger=_log, printer=self.printer)
            _log("Clean driver initialized")
        except Exception as e:
            _log(f"Failed to init clean driver: {e}")
    
    def _respond(self, msg):
        """Log to file AND console."""
        _log(msg)
        self.gcode.respond_info(msg)
    
    # =========================================================================
    # Helper Methods
    # =========================================================================
    
    def _require_driver(self, gcmd):
        """Check if driver available. Returns False and responds with error if not."""
        if not self._clean_driver:
            gcmd.respond_info("Clean driver not available")
            return False
        return True
    
    def _fmt(self, response):
        """Format response bytes for display."""
        return response.hex() if response else 'FAIL'
    
    def _validate_crc(self, response):
        """Validate CRC of response, track stats. Returns True if valid or can't check."""
        if not response or len(response) < 4:
            return True  # Can't validate, assume OK (need at least header + 1 byte + crc)
        
        self._crc_total += 1
        
        # CRC is over bytes [2:-1] (skip header f7 01, exclude CRC byte)
        payload = bytes(response[2:-1])
        calculated = crc8(payload)
        actual = response[-1]
        
        if calculated != actual:
            self._crc_fails += 1
            self._last_crc_fail_time = time.monotonic()
            return False
        return True
    
    def _get_filament_detected(self):
        """Check filament sensor. Returns (detected: bool, error: str|None)."""
        try:
            sensor = self.printer.lookup_object('filament_switch_sensor filament_sensor')
            status = sensor.get_status(self.printer.get_reactor().monotonic())
            return status.get('filament_detected', False), None
        except Exception as e:
            return False, str(e)
    
    def _is_tracking_active(self):
        """Query tracking status. Returns True if active. Updates cache."""
        r = self._clean_driver.query_tracking()
        active = r and len(r) >= 9 and r[8] == TRACKING_ACTIVE_FLAG
        self._cached_tracking = active
        return active
    
    def _setup_load(self):
        """Setup sequence for load operations."""
        self._clean_driver.begin_session()
        self._clean_driver.set_mode_load()
    
    def _setup_unload(self):
        """Setup sequence for unload operations."""
        self._clean_driver.set_mode_unload()
        self._clean_driver.get_state()
        self._clean_driver.begin_session()
    
    def _get_loaded_slot(self):
        """Query loaded slot. Returns (slot: int|-1|None, raw_hex: str). Updates cache."""
        slot, raw = self._clean_driver.query_loaded_slot()
        self._cached_loaded_slot = slot if slot is not None else -1
        return slot, self._fmt(raw)
    
    def refresh_box_status(self):
        """Query box and update cached status. Used by toolchanger.py before reading cached values."""
        if self._clean_driver:
            self._get_loaded_slot()
            self._is_tracking_active()
    
    def get_status(self, eventtime):
        """Expose box state to Klipper macros via printer.box.*
        
        NOTE: This is called frequently by Klipper for status updates.
        We DON'T query the box here to avoid interfering with .so initialization.
        Real box queries happen on-demand in get_box_status() or during operations.
        """
        # Only return filament sensor state (doesn't require box query)
        filament, _ = self._get_filament_detected()
        return {
            'loaded_slot': self._cached_loaded_slot,
            'tracking_active': self._cached_tracking,
            'filament_detected': filament,
        }
    
    # =========================================================================
    # Background Status Polling (Error + Clog Detection)
    # =========================================================================
    
    def _start_status_polling(self):
        """Start background polling for box errors and clogs."""
        reactor = self.printer.get_reactor()
        self._poll_timer = reactor.register_timer(
            self._poll_box_status, reactor.monotonic() + POLL_INITIAL_DELAY
        )
        _log("Status polling started")
    
    def _poll_box_status(self, eventtime):
        """Poll box status for errors and check for clogs."""
        # Skip during box operations (load/unload)
        if self._box_operation_in_progress:
            return eventtime + POLL_INTERVAL
        
        # Skip if not tracking (no filament loaded or not activated)
        if not self._cached_tracking:
            # Reset clog baselines when not tracking
            self._clog_extruder_baseline = None
            self._clog_encoder_baseline = None
            self._last_runout_logged = False
            return eventtime + POLL_INTERVAL
        
        # Query tracking status
        if self._clean_driver:
            r = self._clean_driver.query_tracking()
            self._validate_crc(r)  # Track CRC stats
            if r and len(r) >= 9:
                status = r[3]
                tracking = r[8]
                
                if status == 0x50:
                    # Runout - just log once (printhead sensor handles pause)
                    if not self._last_runout_logged:
                        _log("Box runout detected (0x50)")
                        self.gcode.respond_info("Box: filament runout at spool detected")
                        self._last_runout_logged = True
                elif status in (0x51, 0x52) or tracking == 0x04:
                    # Actual error - pause print
                    self._handle_box_error(status, tracking)
                    return eventtime + POLL_ERROR_BACKOFF  # Back off after error
                else:
                    self._last_runout_logged = False
            
            # Clog detection
            self._check_for_clog()
        
        return eventtime + POLL_INTERVAL
    
    def _handle_box_error(self, status, tracking):
        """Handle box error detected during polling - pause print."""
        _log(f"BOX ERROR: status=0x{status:02x}, tracking=0x{tracking:02x}")
        self.gcode.respond_raw("!! Box error detected (status=0x%02x)" % status)
        
        sd = self.printer.lookup_object('virtual_sdcard', None)
        if sd and sd.is_active():
            self.gcode.respond_info("Pausing print for recovery...")
            self.gcode.run_script_from_command("PAUSE")
    
    def _check_for_clog(self):
        """Check for clog using rolling window approach.
        
        Compares extruder movement vs encoder movement. If extruder has moved
        significantly but encoder hasn't, we have a clog.
        
        Position tracking:
        -----------------
        Queries MCU directly for actual extruder step count. This is essential
        because other methods have issues:
        - extruder.last_position: Updated when move is QUEUED, not executed
        - motion_report.live_position.e: Returns 0 when idle
        - find_past_position: Has lookahead buffer issues (60+ seconds ahead)
        
        MCU query gives the actual physical step count - ground truth.
        
        Rolling window:
        --------------
        Encoder moves in ~30mm chunks (buffer refills). Reset baseline when
        encoder moves >CLOG_ENCODER_RESET to prevent false triggers.
        """
        if self._box_operation_in_progress:
            return
        
        # Get actual extruder position by querying MCU directly
        # This is the ground truth - actual step count, no lookahead
        try:
            toolhead = self.printer.lookup_object('toolhead')
            extruder = toolhead.get_extruder()
            extruder_stepper = extruder.extruder_stepper
            
            if extruder_stepper is None:
                return
            
            mcu_stepper = extruder_stepper.stepper
            # Query MCU for current step position
            params = mcu_stepper._get_position_cmd.send([mcu_stepper._oid])
            mcu_pos = params['pos']
            if mcu_stepper._invert_dir:
                mcu_pos = -mcu_pos
            # Convert MCU steps to position in mm
            extruder_pos = mcu_stepper.mcu_to_commanded_position(mcu_pos)
            used_mcu_query = True
        except Exception as e:
            _log(f"Clog detection: MCU query failed: {e}")
            return
        
        # Get encoder position from box
        encoder_val = self._get_encoder_value()
        if encoder_val is None:
            return
        
        # Cache values for debug output
        self._last_poll_extruder = extruder_pos
        self._last_poll_encoder = encoder_val
        self._last_poll_mcu_success = used_mcu_query
        
        # Initialize baseline on first check
        if self._clog_extruder_baseline is None:
            self._clog_extruder_baseline = extruder_pos
            self._clog_encoder_baseline = encoder_val
            return
        
        # Calculate movement deltas since baseline
        extruder_delta = extruder_pos - self._clog_extruder_baseline
        encoder_delta = abs(encoder_val - self._clog_encoder_baseline)
        
        # Rolling window: reset when encoder moves significantly (buffer refill)
        if encoder_delta > CLOG_ENCODER_RESET:
            self._clog_extruder_baseline = extruder_pos
            self._clog_encoder_baseline = encoder_val
            return
        
        # Clog check: extruder moved significantly but encoder didn't
        if extruder_delta > self._clog_window_mm and encoder_delta < CLOG_ENCODER_MIN:
            self._handle_clog_detected(extruder_delta, encoder_delta)
            self._clog_extruder_baseline = extruder_pos
            self._clog_encoder_baseline = encoder_val
    
    def _parse_encoder(self, response) -> Optional[float]:
        """Parse encoder float from response bytes 5-9."""
        if response and len(response) >= 9:
            try:
                return struct.unpack('>f', bytes(response[5:9]))[0]
            except:
                return None
        return None
    
    def _get_encoder_value(self):
        """Query encoder and return position in mm."""
        if not self._clean_driver:
            return None
        r = self._clean_driver.query_encoder(0)
        return self._parse_encoder(r)
    
    def _handle_clog_detected(self, extruder_mm, encoder_mm):
        """Handle clog detection - pause print."""
        _log(f"CLOG DETECTED: extruder {extruder_mm:.1f}mm, encoder {encoder_mm:.1f}mm")
        self.gcode.respond_raw("!! Clog detected: extruder moved %.1fmm but encoder didn't" % extruder_mm)
        
        sd = self.printer.lookup_object('virtual_sdcard', None)
        if sd and sd.is_active():
            self.gcode.respond_info("Pausing print - check for nozzle clog")
            self.gcode.run_script_from_command("PAUSE")
    
    # =========================================================================
    # Status Verification
    # =========================================================================
    
    def _verify_status(self, gcmd, expected_sensor, expected_slot, expected_tracking):
        """Verify system state matches expectations. Raises gcmd.error on mismatch."""
        filament_detected, _ = self._get_filament_detected()
        slot, _ = self._get_loaded_slot()
        tracking_active = self._is_tracking_active()
        
        errors = []
        if filament_detected != expected_sensor:
            errors.append(f"Sensor: {'DETECTED' if filament_detected else 'NOT DETECTED'} (expected {'DETECTED' if expected_sensor else 'NOT DETECTED'})")
        if expected_slot is not None and slot != expected_slot:
            errors.append(f"Slot: {slot} (expected {expected_slot})")
        if tracking_active != expected_tracking:
            errors.append(f"Tracking: {'ACTIVE' if tracking_active else 'INACTIVE'} (expected {'ACTIVE' if expected_tracking else 'INACTIVE'})")
        
        if errors:
            raise gcmd.error("Status verification failed: " + ", ".join(errors))
    # =========================================================================
    # Commands
    # =========================================================================
    
    def cmd_debug(self, gcmd):
        """Dump all box state for debugging."""
        if not self._require_driver(gcmd):
            return
        
        gcmd.respond_info("=== BOX DEBUG DUMP ===")
        
        # 1. Filament sensor
        filament, err = self._get_filament_detected()
        gcmd.respond_info(f"Filament sensor: {'DETECTED' if filament else 'NOT DETECTED'}" + (f" (err: {err})" if err else ""))
        
        # 2. Get state (0x0800)
        r = self._clean_driver.get_state()
        if r and len(r) >= 5:
            state_byte = r[4] if len(r) > 4 else 0
            gcmd.respond_info(f"Get state: 0x{state_byte:02x} (raw: {self._fmt(r)})")
        else:
            gcmd.respond_info(f"Get state: FAILED (raw: {self._fmt(r)})")
        
        # 3. Loaded slot query (0x0801)
        slot, raw = self._get_loaded_slot()
        slot_str = f"{slot}" if slot is not None else "UNKNOWN"
        if slot == -1:
            slot_str = "NONE"
        gcmd.respond_info(f"Loaded slot: {slot_str} (raw: {raw})")
        
        # 4. Tracking query (0x0a) - includes temp/humidity
        r = self._clean_driver.query_tracking()
        if r and len(r) >= 9:
            temp = r[5]
            humidity = r[6]
            tracking_byte = r[8]
            tracking_str = "ACTIVE" if tracking_byte == 0x02 else f"INACTIVE (0x{tracking_byte:02x})"
            gcmd.respond_info(f"Tracking: {tracking_str}, Temp: {temp}°C, RH: {humidity}% (raw: {self._fmt(r)})")
        else:
            gcmd.respond_info(f"Tracking query: FAILED (raw: {self._fmt(r)})")
        
        # 5. Buffer state (0x05)
        r = self._clean_driver.get_buffer_state()
        if r and len(r) >= 6:
            status_byte = r[3]
            buffer_byte = r[5]
            gcmd.respond_info(f"Buffer: status=0x{status_byte:02x}, state=0x{buffer_byte:02x} (raw: {self._fmt(r)})")
        else:
            gcmd.respond_info(f"Buffer state: FAILED (raw: {self._fmt(r)})")
        
        # 6. Encoder (always slot 0 - encoder is in shared hub)
        r = self._clean_driver.query_encoder(0)
        encoder_val = self._parse_encoder(r)
        if encoder_val is not None:
            gcmd.respond_info(f"Encoder (hub): {encoder_val:.2f} mm (raw: {self._fmt(r)})")
        else:
            gcmd.respond_info(f"Encoder: FAILED (raw: {self._fmt(r)})")
        
        # 7. Hardware status (0xa2) - serial number
        r = self._clean_driver.query_status()
        if r and len(r) >= 10:
            status_byte = r[3]
            # Last 4 bytes before CRC might be ASCII serial
            serial_bytes = r[15:19] if len(r) >= 19 else r[-5:-1]
            try:
                serial_ascii = bytes(serial_bytes).decode('ascii', errors='replace')
            except:
                serial_ascii = "?"
            gcmd.respond_info(f"Hardware: status=0x{status_byte:02x}, serial_suffix={serial_ascii} (raw: {self._fmt(r)})")
        else:
            gcmd.respond_info(f"Hardware status: FAILED (raw: {self._fmt(r)})")
        
        # 8. Monitoring status (polling state)
        gcmd.respond_info("--- Monitoring Status ---")
        polling_active = self._poll_timer is not None
        gcmd.respond_info(f"Polling: {'ACTIVE' if polling_active else 'NOT STARTED'}")
        gcmd.respond_info(f"Cached tracking: {self._cached_tracking}, Cached slot: {self._cached_loaded_slot}")
        gcmd.respond_info(f"Box op in progress: {self._box_operation_in_progress}, Runout logged: {self._last_runout_logged}")
        
        # Clog detection state - detailed view
        gcmd.respond_info("--- Clog Detection ---")
        if self._clog_extruder_baseline is not None and self._last_poll_extruder is not None:
            # Use cached values from last poll - shows exactly what clog detection saw
            curr_extruder = self._last_poll_extruder
            curr_encoder = self._last_poll_encoder or 0.0
            
            ext_delta = curr_extruder - self._clog_extruder_baseline
            enc_delta = abs(curr_encoder - self._clog_encoder_baseline)
            
            source = "mcu_query" if self._last_poll_mcu_success else "FAILED"
            gcmd.respond_info(f"Last poll: extruder={curr_extruder:.1f}mm, encoder={curr_encoder:.2f}mm (source: {source})")
            gcmd.respond_info(f"Baseline:  extruder={self._clog_extruder_baseline:.1f}mm, encoder={self._clog_encoder_baseline:.2f}mm")
            gcmd.respond_info(f"Deltas:    extruder Δ{ext_delta:.1f}mm, encoder Δ{enc_delta:.1f}mm")
            gcmd.respond_info(f"Thresholds: extruder>{self._clog_window_mm}mm + encoder<{CLOG_ENCODER_MIN}mm = CLOG, encoder>{CLOG_ENCODER_RESET}mm = reset")
            
            # Status
            if ext_delta > self._clog_window_mm and enc_delta < CLOG_ENCODER_MIN:
                gcmd.respond_info(f"Status: CLOG CONDITION! (Δ{ext_delta:.1f}mm extruder, Δ{enc_delta:.1f}mm encoder)")
            elif enc_delta > CLOG_ENCODER_RESET:
                gcmd.respond_info(f"Status: Window will reset (encoder moved {enc_delta:.1f}mm > {CLOG_ENCODER_RESET}mm)")
            else:
                gcmd.respond_info(f"Status: OK (extruder Δ{ext_delta:.1f}mm < {self._clog_window_mm}mm)")
        else:
            gcmd.respond_info("Status: Not initialized (waiting for first poll with tracking active)")
        
        # Error detection status
        gcmd.respond_info("--- Error Detection ---")
        r = self._clean_driver.query_tracking()
        if r and len(r) >= 9:
            status_byte = r[3]
            tracking_byte = r[8]
            status_str = "OK" if status_byte == 0x00 else f"0x{status_byte:02x}"
            if status_byte == 0x50:
                status_str = "RUNOUT (0x50)"
            elif status_byte in (0x51, 0x52):
                status_str = f"ERROR (0x{status_byte:02x})"
            gcmd.respond_info(f"Box status={status_str}, tracking=0x{tracking_byte:02x}")
        
        # CRC stats
        gcmd.respond_info("--- CRC Validation ---")
        if self._crc_total > 0:
            success_rate = ((self._crc_total - self._crc_fails) / self._crc_total) * 100
            if self._last_crc_fail_time:
                ago = time.monotonic() - self._last_crc_fail_time
                last_str = f"{ago:.0f}s ago"
            else:
                last_str = "never"
            gcmd.respond_info(f"CRC: {self._crc_fails} fails / {self._crc_total} total ({success_rate:.1f}% success, last fail: {last_str})")
        else:
            gcmd.respond_info("CRC: No responses validated yet")
        
        gcmd.respond_info("=== END DEBUG DUMP ===")


    def cmd_encoder(self, gcmd):
        """Query measuring wheel encoder value."""
        if not self._require_driver(gcmd):
            return
        slot = gcmd.get_int('SLOT', 0)
        result = self._clean_driver.query_encoder(slot)
        if result and len(result) >= 9:
            try:
                float_bytes = result[5:9]
                encoder_val = struct.unpack('>f', float_bytes)[0]  # big-endian
                gcmd.respond_info(f"Encoder slot {slot}: {encoder_val:.2f} mm (raw: {self._fmt(result)})")
            except Exception as e:
                gcmd.respond_info(f"Encoder parse error: {e} (raw: {self._fmt(result)})")
        else:
            gcmd.respond_info(f"Encoder query failed: {self._fmt(result)}")

    def cmd_status(self, gcmd):
        """Full status check: filament sensor + loaded slot + tracking state."""
        if not self._require_driver(gcmd):
            return
        
        # 1. Check filament sensor
        filament_detected, err = self._get_filament_detected()
        if err:
            gcmd.respond_info(f"Filament sensor: ERROR ({err})")
        else:
            gcmd.respond_info(f"Filament sensor: {'DETECTED' if filament_detected else 'NOT DETECTED'}")
        
        # 2. Query loaded slot from box
        slot, raw_hex = self._get_loaded_slot()
        if slot == -1:
            gcmd.respond_info(f"Box loaded slot: NONE (raw: {raw_hex})")
        elif slot is not None:
            gcmd.respond_info(f"Box loaded slot: {slot} (raw: {raw_hex})")
        else:
            gcmd.respond_info(f"Box loaded slot: UNKNOWN (raw: {raw_hex})")
        
        # 3. Check tracking state
        tracking_active = self._is_tracking_active()
        gcmd.respond_info(f"Tracking: {'ACTIVE' if tracking_active else 'INACTIVE'}")
        
        # 4. Overall status
        if filament_detected and slot is not None and slot >= 0 and tracking_active:
            gcmd.respond_info(f"Status: OK - slot {slot} loaded, filament detected, tracking active")
        elif not filament_detected and (slot is None or slot == -1) and not tracking_active:
            gcmd.respond_info("Status: OK - no filament loaded")
        else:
            gcmd.respond_info("Status: MISMATCH - state inconsistent")


    def load_filament(self, slot: int) -> BoxResult:
        """Load filament from slot to printhead.
        
        Pure Python method - returns BoxResult, never raises.
        Called by toolchanger.py directly.
        """
        if not self._clean_driver:
            return BoxResult(success=False, error="Clean driver not available")
        
        # Set flag to skip error/clog detection during operation
        self._box_operation_in_progress = True
        try:
            return self._load_filament_impl(slot)
        finally:
            self._box_operation_in_progress = False
            # Reset clog baselines so next poll starts fresh
            self._clog_extruder_baseline = None
            self._clog_encoder_baseline = None
    
    def _load_filament_impl(self, slot: int) -> BoxResult:
        """Internal implementation of load_filament."""
        _log(f"=== LOAD FILAMENT: Slot {slot} ===")
        
        # Check if already loaded - slot matches and filament detected
        filament_already, _ = self._get_filament_detected()
        loaded_slot, _ = self._get_loaded_slot()
        
        # Safety check: box says nothing loaded but sensor sees filament
        if loaded_slot == -1 and filament_already:
            err_msg = "Box reports no filament loaded but printhead sensor detects filament"
            _log(f"SAFETY ABORT: {err_msg}")
            self.gcode.respond_raw(f"!! {err_msg}")
            return BoxResult(success=False, error=err_msg)
        
        if filament_already and loaded_slot == slot:
            self._respond(f"Slot {slot} already loaded - activating tracking only")
            self._clean_driver.finalize_session(slot)
            self._cached_tracking = True
            self._cached_loaded_slot = slot
            return BoxResult(success=True, data={'slot': slot, 'already_loaded': True})
        
        # Setup
        self._respond("Setup: Enable + Extrude mode")
        self._setup_load()
        self._clean_driver.get_state()
        
        # Stage 0 - Auto-unload prev slot (if loaded) + short initial feed
        r = self._clean_driver.load_stage(slot, 0, timeout=STAGE_0_TIMEOUT)
        self._respond(f"Stage 0 (Unload prev + feed): {self._fmt(r)}")
        
        # Stage 4 - Feed from buffer to printhead
        r = self._clean_driver.load_stage(slot, 4, timeout=STAGE_4_TIMEOUT)
        self._respond(f"Stage 4 (Feed to printhead): {self._fmt(r)}")
        
        # Stage 5 - Wait for box to stall with encoder monitoring
        self._respond(f"Stage 5: Waiting for box stall (timeout {LOAD_TIMEOUT:.0f}s)...")
        reactor = self.printer.get_reactor()
        
        wait_start = time.time()
        box_state = "FEEDING"
        last_encoder = None
        stable_count = 0
        
        while (time.time() - wait_start) < LOAD_TIMEOUT:
            r = self._clean_driver.load_stage(slot, 5)
            box_state = self._clean_driver.parse_stage5_state(r)
            
            if box_state == "STALL":
                break  # Box stopped - check sensor to determine success vs jam
            
            # Parse encoder float from bytes 5-8
            encoder_val = self._parse_encoder(r) or 0.0
            
            # Check encoder stability (grind detection)
            if last_encoder is not None:
                delta = abs(encoder_val - last_encoder)
                if delta < ENCODER_STABLE_THRESHOLD:
                    stable_count += 1
                    if stable_count >= ENCODER_STABLE_POLLS:
                        # Encoder not moving but box still feeding = grind
                        wait_elapsed = time.time() - wait_start
                        self._respond(f"=== LOAD FAILED: Filament not moving ({wait_elapsed:.1f}s) ===")
                        # Spam Stage 7 until we get a response
                        for attempt in range(5):
                            reactor.pause(reactor.monotonic() + 0.3)
                            r = self._clean_driver.load_stage(slot, 7)
                            if r is not None:
                                self._respond(f"Abort succeeded (attempt {attempt + 1})")
                                break
                            self._respond(f"Abort attempt {attempt + 1}/5 failed, retrying...")
                        self._clean_driver.clear_mode()
                        return BoxResult(success=False, error="Filament not moving")
                else:
                    stable_count = 0  # Reset if encoder moved
            
            last_encoder = encoder_val
            reactor.pause(reactor.monotonic() + STAGE_5_POLL_INTERVAL)
        
        wait_elapsed = time.time() - wait_start
        
        # Handle timeout (box never stalled)
        if box_state == "FEEDING":
            self._respond(f"=== LOAD FAILED: Safety timeout ({wait_elapsed:.1f}s) ===")
            self._clean_driver.clear_mode()
            return BoxResult(success=False, error="Safety timeout")
        
        # box_state == "STALL" - check sensor to determine success vs jam
        sensor_triggered, _ = self._get_filament_detected()
        
        if not sensor_triggered:
            # Stall without sensor = jam in tube before extruder
            self._respond(f"=== LOAD FAILED: Box stalled, sensor NOT triggered ({wait_elapsed:.1f}s) ===")
            self._clean_driver.clear_mode()
            return BoxResult(success=False, error="Box stalled but sensor not triggered")
        
        # Success! Sensor triggered, box stalled from resistance at extruder
        self._respond(f"Filament detected after {wait_elapsed:.1f}s")
        
        # Stage 6 - Confirm success
        r = self._clean_driver.load_stage(slot, 6)
        self._respond(f"Stage 6 (Confirm): {self._fmt(r)}")
        
        # Stage 7 - Finalize
        r = self._clean_driver.load_stage(slot, 7)
        self._respond(f"Stage 7 (Finalize): {self._fmt(r)}")
        
        # Buffer check
        r = self._clean_driver.get_buffer_state()
        self._respond(f"Buffer: {self._fmt(r)}")
        
        # Cleanup - finalize activates tracking
        self._clean_driver.finalize_session(slot)
        self._clean_driver.clear_mode()
        self._cached_tracking = True  # Tracking is now active
        self._cached_loaded_slot = slot
        
        self._respond("=== LOAD COMPLETE ===")
        return BoxResult(success=True, data={'slot': slot, 'wait_time': wait_elapsed})

    def cmd_load(self, gcmd):
        """GCode wrapper for BOX_LOAD - raises on failure."""
        slot = gcmd.get_int('SLOT', 0)
        gcmd.respond_info(f"Loading filament from slot {slot}...")
        
        result = self.load_filament(slot)
        
        if not result.success:
            raise gcmd.error(f"BOX_LOAD failed: {result.error}")
        
        # Verify and report
        if result.data and result.data.get('already_loaded'):
            gcmd.respond_info(f"Slot {slot} already loaded - tracking activated")
        else:
            wait_time = result.data.get('wait_time', 0) if result.data else 0
            gcmd.respond_info(f"Load successful (detected in {wait_time:.1f}s)")
        
        self._verify_status(gcmd, expected_sensor=True, expected_slot=slot, expected_tracking=True)
        gcmd.respond_info("Status verified OK")
    

    def cmd_activate(self, gcmd):
        """Finalize session for a slot. If SLOT not given, auto-detects loaded slot."""
        if not self._require_driver(gcmd):
            return
        
        slot = gcmd.get_int('SLOT', -1)
        
        if slot == -1:
            # Auto-detect slot
            slot, raw_hex = self._get_loaded_slot()
            if slot == -1:
                raise gcmd.error("No slot loaded")
            elif slot is None:
                raise gcmd.error(f"Could not determine loaded slot (raw: {raw_hex})")
            
            # Verify sensor when auto-detecting
            sensor_ok, _ = self._get_filament_detected()
            if not sensor_ok:
                raise gcmd.error("Cannot activate: filament not at sensor")
            
            gcmd.respond_info(f"Auto-detected slot {slot}")
        
        r = self._clean_driver.finalize_session(slot)
        self._cached_tracking = True
        self._cached_loaded_slot = slot
        # Reset clog baselines so next poll starts fresh
        self._clog_extruder_baseline = None
        self._clog_encoder_baseline = None
        gcmd.respond_info(f"Activated slot {slot}")

    def cmd_clear(self, gcmd):
        """Clear mode."""
        if not self._require_driver(gcmd):
            return
        r = self._clean_driver.clear_mode()
        gcmd.respond_info(f"clear_mode: {self._fmt(r)}")

    def cmd_loaded(self, gcmd):
        """Query which slot is currently loaded."""
        if not self._require_driver(gcmd):
            return
        slot, raw_hex = self._get_loaded_slot()
        if slot == -1:
            gcmd.respond_info(f"No slot loaded (raw: {raw_hex})")
        elif slot is not None:
            gcmd.respond_info(f"Loaded slot: {slot} (raw: {raw_hex})")
        else:
            gcmd.respond_info(f"Could not parse slot (raw: {raw_hex})")

    def cmd_unload(self, gcmd):
        """Unload filament. If SLOT not given, auto-detects and does full unload with extruder retractions."""
        if not self._require_driver(gcmd):
            return
        
        slot = gcmd.get_int('SLOT', -1)
        
        if slot == -1:
            # Auto-unload with extruder retractions
            gcmd.respond_info("Auto-unload: detecting slot...")
            gcode = self.printer.lookup_object('gcode')
            result = self.auto_unload(gcode=gcode)
            if not result.success:
                raise gcmd.error(f"Unload failed: {result.error}")
            gcmd.respond_info(f"Unload successful (slot {result.data.get('slot_unloaded', '?')})")
            self._verify_status(gcmd, expected_sensor=False, expected_slot=-1, expected_tracking=False)
            gcmd.respond_info("Status verified OK")
        else:
            # Manual slot specified - basic unload
            gcmd.respond_info(f"Unloading slot {slot}...")
            self._setup_unload()
            r = self._clean_driver.unload_slot(slot, slot_motor=True, timeout=SLOT_MOTOR_TIMEOUT)
            gcmd.respond_info(f"unload_slot(slot={slot}): {self._fmt(r)}")


    def cmd_hub_release(self, gcmd):
        """Hub motor only - releases slack into buffer (for extruder retraction)."""
        if not self._require_driver(gcmd):
            return
        slot = gcmd.get_int('SLOT', 0)
        gcmd.respond_info(f"Hub motor release slack for slot {slot}...")
        self._setup_unload()
        r = self._clean_driver.unload_slot(slot, slot_motor=False, timeout=5.0)
        gcmd.respond_info(f"hub_release(slot={slot}): {self._fmt(r)}")

    def auto_unload(self, gcode=None) -> BoxResult:
        """Auto-unload with synchronized hub motor + extruder retraction.
        
        Pure Python method - returns BoxResult, never raises.
        If gcode is provided AND filament is at printhead, performs synchronized extruder retractions.
        If filament not at printhead, skips extruder retractions and just does box-side unload.
        """
        if not self._clean_driver:
            return BoxResult(success=False, error="Clean driver not available")
        
        # Set flag to skip error/clog detection during operation
        self._box_operation_in_progress = True
        try:
            return self._auto_unload_impl(gcode)
        finally:
            self._box_operation_in_progress = False
            # Reset clog baselines so next poll starts fresh
            self._clog_extruder_baseline = None
            self._clog_encoder_baseline = None
    
    def _auto_unload_impl(self, gcode=None) -> BoxResult:
        """Internal implementation of auto_unload."""
        # Query which slot is loaded
        slot, raw = self._get_loaded_slot()
        if slot == -1:
            self._respond(f"No slot loaded, nothing to unload")
            return BoxResult(success=True, data={'slot': -1, 'already_empty': True})
        elif slot is None:
            return BoxResult(success=False, error=f"Could not determine loaded slot (raw: {raw})")
        
        self._respond(f"=== AUTO UNLOAD: Slot {slot} ===")
        
        # Check if filament is at printhead sensor
        filament_at_sensor, _ = self._get_filament_detected()
        
        # Complete setup (query_loaded_slot already did set_mode_unload)
        self._clean_driver.get_state()
        self._clean_driver.begin_session()
        
        # Only do synchronized extruder retractions if filament is at the printhead
        if filament_at_sensor and gcode:
            self._respond("Filament at sensor - doing synchronized hub + extruder retractions")
            for i in range(RETRACT_CYCLES):
                r = self._clean_driver.unload_slot(slot, slot_motor=False, timeout=5.0)
                self._respond(f"Hub motor cycle {i+1}/{RETRACT_CYCLES}: {self._fmt(r)}")
                
                gcode.run_script_from_command("SAVE_GCODE_STATE NAME=_box_retract")
                gcode.run_script_from_command("M83")
                gcode.run_script_from_command(f"G1 E-{RETRACT_DISTANCE_MM} F{RETRACT_SPEED_F}")
                gcode.run_script_from_command("RESTORE_GCODE_STATE NAME=_box_retract")
        else:
            self._respond("Filament not at sensor - skipping extruder retractions, box-side only")
        
        # Final slot motor retraction (always needed to pull filament back into slot)
        self._respond("Final: slot motor retract")
        r = self._clean_driver.unload_slot(slot, slot_motor=True, timeout=SLOT_MOTOR_TIMEOUT)
        self._respond(f"Slot motor result: {self._fmt(r)}")
        
        # Verify final state
        filament_detected, _ = self._get_filament_detected()
        loaded_slot_after, _ = self._get_loaded_slot()
        
        if filament_detected:
            return BoxResult(success=False, error="Filament still detected after unload")
        if loaded_slot_after != -1:
            return BoxResult(success=False, error=f"Box still reports slot {loaded_slot_after} loaded after unload")
        
        # Clear cached state
        self._cached_tracking = False
        self._cached_loaded_slot = -1
        
        self._respond("=== UNLOAD COMPLETE ===")
        return BoxResult(success=True, data={'slot_unloaded': slot, 'had_extruder_retract': filament_at_sensor})




# =============================================================================
# Command Registration
# =============================================================================

# (command_name, method_name, description)
COMMANDS = [
    ('BOX_LOAD',          'cmd_load',          'Load filament from slot'),
    ('BOX_STATUS',        'cmd_status',        'Full status check'),
    ('BOX_DEBUG',         'cmd_debug',         'Dump all box state for debugging'),
    ('BOX_ENCODER',       'cmd_encoder',       'Query encoder'),
    ('BOX_ACTIVATE',      'cmd_activate',      'Finalize session (auto-slot if SLOT not given)'),
    ('BOX_CLEAR',         'cmd_clear',         'Clear mode'),
    ('BOX_UNLOAD',        'cmd_unload',        'Unload filament (auto-slot if SLOT not given)'),
    ('BOX_HUB_RELEASE',   'cmd_hub_release',   'Hub motor release'),
    ('BOX_LOADED',        'cmd_loaded',        'Query loaded slot'),
]

def load_config(config):
    _log("*" * 60)
    _log("LOADING BOX DRIVER")
    _log("*" * 60)
    wrapper = MultiColorMeterialBoxWrapper(config)
    
    gcode = wrapper.printer.lookup_object('gcode')
    for name, method, desc in COMMANDS:
        gcode.register_command(name, getattr(wrapper, method), desc=desc)
    
    return wrapper
