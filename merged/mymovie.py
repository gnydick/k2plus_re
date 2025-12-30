# ===========================================================================
# MERGED FILE: Accurate signatures from live introspection + inferred implementations
#
# SIGNATURE SOURCE: Live printer introspection (ACCURATE)
# IMPLEMENTATION: Reverse engineered (INFERRED - may have errors)
#
# Parameter names in implementations may still use old names.
# See PARAM_MAPPING comments for required renames.
# ===========================================================================

# Reconstructed from mymovie.cpython-39.so
# Original: klippy/mymodule/move.pyx (Cython + C++)
# Creality K2 Series - Move Planner/Splitter
#
# Copyright (C) Creality
# Reverse engineered by Claude Code
#
# This file may be distributed under the terms of the GNU GPLv3 license.
#
# Note: This module is compiled from Cython (.pyx) wrapping C++ code.
# The original name 'mymovie' appears to be a contraction of 'mymove'.
# It provides optimized move planning for Klipper's toolhead motion.
#
# Architecture:
# - Python interface wraps C++ Move/MoveSplitter classes
# - Uses native move queue for high-performance path planning
# - Integrates with bed mesh for Z compensation
# - Supports CoreXY kinematics
#
# =============================================================================
# PROVENANCE NOTICE - READ BEFORE USING THIS CODE
# =============================================================================
#
# This file was reconstructed through reverse engineering of compiled Cython
# binaries (.cpython-39.so). The code quality and accuracy varies by section:
#
# EXTRACTED (high confidence) - Directly from binary strings:
#   - Function names: Py_get_monotonic, Py_zmesh_calc_c, Py_set_corexykin_info,
#     Py_set_extruder_info, Py_set_cur_move_addr, Py_move_queue_add, etc.
#   - Class names: PyMove, PyMoveSplitter
#   - Attribute names from PyMove: start_pos, end_pos, axes_d, axes_r, start_v,
#     cruise_v, accel_t, cruise_t, decel_t, move_d, is_kinematic_move
#   - Log message strings: "!!!!!!!!!!!!!!!!!!!!set max_z_velocity..."
#   - Cython pickle methods: __reduce_cython__, __setstate_cython__
#
# INFERRED (lower confidence) - Educated guesses based on:
#   - Klipper's standard move planning algorithms (junction deviation, S-curve)
#   - CoreXY kinematics equations from Klipper source
#   - Bed mesh bilinear interpolation (standard algorithm)
#   - Move splitting logic for Z compensation
#   - Velocity/acceleration calculations (kinematics 101)
#
# HIGHLY UNCERTAIN - The internal C++ implementation details:
#   - Actual native move queue data structures
#   - Pointer arithmetic / memory layout
#   - Exact velocity profile calculations
#   - Move timing synchronization
#
# Sections are marked with:
#   # [EXTRACTED] - From binary strings or decompiled code
#   # [INFERRED]  - Logic reconstructed from context/patterns
#   # [PARTIAL]   - Mix of extracted names with inferred logic
# =============================================================================

import math
import time
import logging
import ctypes

# ============================================
# Global State
# ============================================

# Current move address (pointer to native move object)
_cur_move_addr = 0

# CoreXY kinematics info
_corexy_info = {
    'max_velocity': 500.0,
    'max_accel': 3000.0,
    'max_z_velocity': 15.0,
    'max_z_accel': 100.0,
    'square_corner_velocity': 5.0,
    'split_delta_z': 0.025,
    'move_check_distance': 5.0,
    'min_move_t': 0.01
}

# Extruder info storage
_extruder_info = {
    'addr': 0,
    'p_heater_info': 0.0,
    'max_e_velocity': 100.0,
    'max_e_accel': 1000.0,
    'max_extrude_ratio': 0.5,
    'nozzle_diameter': 0.4,
    'max_e_dist': 50.0,
    'instant_corner_v': 1.0
}

# Move queue (simulated in Python)
_move_queue = []


# ============================================
# Utility Functions
# ============================================

def Py_get_monotonic():
    """
    Get monotonic time in seconds.

    Returns:
        float: Current monotonic time
    """
    return time.monotonic()


def Py_estimated_print_time():
    """
    Get estimated print time based on queued moves.

    Returns:
        float: Estimated print time in seconds
    """
    total_time = 0.0
    for move in _move_queue:
        if hasattr(move, 'accel_t'):
            total_time += move.accel_t + move.cruise_t + move.decel_t
    return total_time


def Py_fast_convert_to_int(value):
    """
    Fast conversion to integer using C-style truncation.

    Args:
        value: Numeric value to convert

    Returns:
        int: Truncated integer value
    """
    if value >= 0:
        return int(value)
    else:
        return int(value)


def Py_get_z_factor(move_addr=0, z_value=0.0):
    """
    Get Z factor for motion calculations.

    Used for scaling Z movements based on kinematics configuration.

    Args:
        move_addr: Address of move object
        z_value: Current Z value

    Returns:
        float: Z scaling factor (typically 1.0)
    """
    # Factor can vary based on Z position for certain kinematics
    return 1.0


def Py_zmesh_calc_c(x, y, z_mesh=None):
    """
    Calculate Z compensation from mesh at position (x, y).

    Performs bilinear interpolation on the bed mesh to determine
    Z offset correction at the given XY coordinate.

    Args:
        x: X coordinate
        y: Y coordinate
        z_mesh: Z mesh object (BedMesh) or None

    Returns:
        float: Z offset compensation value
    """
    if z_mesh is None:
        return 0.0

    # Get mesh parameters
    if not hasattr(z_mesh, 'probed_matrix') or z_mesh.probed_matrix is None:
        return 0.0

    try:
        mesh = z_mesh.probed_matrix
        min_x = z_mesh.mesh_min[0]
        max_x = z_mesh.mesh_max[0]
        min_y = z_mesh.mesh_min[1]
        max_y = z_mesh.mesh_max[1]

        # Clamp to mesh bounds
        x = max(min_x, min(max_x, x))
        y = max(min_y, min(max_y, y))

        # Calculate grid position
        x_count = len(mesh[0])
        y_count = len(mesh)

        x_step = (max_x - min_x) / (x_count - 1) if x_count > 1 else 1.0
        y_step = (max_y - min_y) / (y_count - 1) if y_count > 1 else 1.0

        x_idx = (x - min_x) / x_step
        y_idx = (y - min_y) / y_step

        # Get integer indices
        x0 = int(x_idx)
        y0 = int(y_idx)
        x1 = min(x0 + 1, x_count - 1)
        y1 = min(y0 + 1, y_count - 1)

        # Get fractional parts
        x_frac = x_idx - x0
        y_frac = y_idx - y0

        # Bilinear interpolation
        z00 = mesh[y0][x0]
        z01 = mesh[y0][x1]
        z10 = mesh[y1][x0]
        z11 = mesh[y1][x1]

        z0 = z00 * (1 - x_frac) + z01 * x_frac
        z1 = z10 * (1 - x_frac) + z11 * x_frac

        return z0 * (1 - y_frac) + z1 * y_frac

    except Exception as e:
        logging.warning("zmesh_calc_c error: %s", e)
        return 0.0


def Py_set_corexykin_info(max_velocity, max_accel, max_z_velocity, max_z_accel,
                          square_corner_velocity, split_delta_z,
                          move_check_distance, min_move_t):
    """
    Set CoreXY kinematics info for motion planning.

    Args:
        max_velocity: Maximum XY velocity (mm/s)
        max_accel: Maximum XY acceleration (mm/s²)
        max_z_velocity: Maximum Z velocity (mm/s)
        max_z_accel: Maximum Z acceleration (mm/s²)
        square_corner_velocity: Corner velocity limit (mm/s)
        split_delta_z: Z delta for move splitting (mm)
        move_check_distance: Distance to check moves (mm)
        min_move_t: Minimum move time (s)
    """
    global _corexy_info

    logging.info("!!!!!!!!!!!!!!!!!!!!set max_z_velocity %f,max_z_accel %f",
                 max_z_velocity, max_z_accel)

    _corexy_info = {
        'max_velocity': float(max_velocity),
        'max_accel': float(max_accel),
        'max_z_velocity': float(max_z_velocity),
        'max_z_accel': float(max_z_accel),
        'square_corner_velocity': float(square_corner_velocity),
        'split_delta_z': float(split_delta_z),
        'move_check_distance': float(move_check_distance),
        'min_move_t': float(min_move_t)
    }


def Py_set_extruder_info(addr, p_heater_info, max_e_velocity, max_e_accel,
                         max_extrude_ratio, nozzle_diameter, max_e_dist,
                         instant_corner_v):
    """
    Set extruder info for motion planning.

    Args:
        addr: Extruder address/index
        p_heater_info: Heater info pointer
        max_e_velocity: Maximum extruder velocity (mm/s)
        max_e_accel: Maximum extruder acceleration (mm/s²)
        max_extrude_ratio: Maximum extrusion ratio
        nozzle_diameter: Nozzle diameter (mm)
        max_e_dist: Maximum extrusion distance (mm)
        instant_corner_v: Instant corner velocity for extruder
    """
    global _extruder_info

    logging.info("set_extruder_info addr %d  p_heater_info %f,max_e_velocity %f,"
                 "max_e_accel %f,max_extrude_ratio %f,nozzle_diameter %f,"
                 "max_e_dist %f,instant_corner_v %f",
                 addr, p_heater_info, max_e_velocity, max_e_accel,
                 max_extrude_ratio, nozzle_diameter, max_e_dist, instant_corner_v)

    _extruder_info = {
        'addr': int(addr),
        'p_heater_info': float(p_heater_info),
        'max_e_velocity': float(max_e_velocity),
        'max_e_accel': float(max_e_accel),
        'max_extrude_ratio': float(max_extrude_ratio),
        'nozzle_diameter': float(nozzle_diameter),
        'max_e_dist': float(max_e_dist),
        'instant_corner_v': float(instant_corner_v)
    }


def Py_set_cur_move_addr(addr):
    """
    Set current move address for queue operations.

    Args:
        addr: Move object address (pointer)
    """
    global _cur_move_addr
    _cur_move_addr = int(addr)


def Py_get_moveq_only_data_buffer():
    """
    Get move queue data buffer.

    Returns the internal buffer used for move queue operations.
    In native code, this returns a pointer to the move queue buffer.

    Returns:
        list: Move queue buffer (or None in native code)
    """
    if _cur_move_addr == 0:
        logging.warning("bed_mesh: move_addr is null")
        return None
    return _move_queue


def Py_move_queue_add(move):
    """
    Add move to the motion queue.

    Args:
        move: PyMove object to add
    """
    global _move_queue
    _move_queue.append(move)


def Py_move_queue_del(index):
    """
    Delete move from queue by index.

    Args:
        index: Index of move to delete
    """
    global _move_queue
    if 0 <= index < len(_move_queue):
        del _move_queue[index]


def Py_move_queue_flush_cal(start_index=0, end_index=-1):
    """
    Flush and calculate move queue.

    Processes the move queue to calculate junction velocities,
    acceleration profiles, and timing for all queued moves.

    Args:
        start_index: Starting index for calculation
        end_index: Ending index (-1 for all)
    """
    global _move_queue

    if end_index < 0:
        end_index = len(_move_queue)

    # Process moves in queue
    prev_move = None
    for i in range(start_index, min(end_index, len(_move_queue))):
        move = _move_queue[i]

        if prev_move is not None and hasattr(move, 'calc_junction'):
            # Calculate junction velocity with previous move
            junction_v2 = move.calc_junction(prev_move)
            move.start_v2 = junction_v2

        prev_move = move


# ============================================
# PyMove Class
# ============================================

class PyMove:
    """
    Represents a single movement in the motion planner.

    This class holds all the kinematic parameters for a move segment,
    including acceleration, cruise velocity, and timing information.
    Wraps native C++ Move class functionality.

    Attributes:
        start_pos: Starting position [x, y, z, e]
        end_pos: Ending position [x, y, z, e]
        axes_d: Distance per axis
        axes_r: Ratio per axis (direction unit vector)
        start_v: Starting velocity
        end_v: Ending velocity
        cruise_v: Cruise (peak) velocity
        accel: Acceleration
        accel_t: Acceleration time
        cruise_t: Cruise time
        decel_t: Deceleration time
        move_d: Total move distance
        is_kinematic_move: True if involves XYZ motion
    """

    def __init__(self, *args, **kwargs):
        # Position data
        self.start_pos = [0.0, 0.0, 0.0, 0.0]  # x, y, z, e
        self.end_pos = [0.0, 0.0, 0.0, 0.0]
        self.axes_d = [0.0, 0.0, 0.0, 0.0]  # Distance per axis
        self.axes_r = [0.0, 0.0, 0.0, 0.0]  # Ratio per axis

        # Velocity data
        self.start_v = 0.0      # Start velocity
        self.end_v = 0.0        # End velocity
        self.cruise_v = 0.0     # Cruise velocity
        self.start_v2 = 0.0     # Start velocity squared
        self.max_start_v2 = 0.0
        self.max_cruise_v2 = 0.0
        self.delta_v2 = 0.0
        self.max_smoothed_v2 = 0.0
        self.smooth_delta_v2 = 0.0

        # Acceleration and timing
        self.accel = 0.0        # Acceleration
        self.accel_t = 0.0      # Acceleration time
        self.cruise_t = 0.0     # Cruise time
        self.decel_t = 0.0      # Deceleration time
        self.min_move_t = 0.0   # Minimum move time

        # Move properties
        self.move_d = 0.0       # Total move distance
        self.is_kinematic_move = False
        self.junction_deviation = 0.0

    def calc_junction(self, *args, **kwargs):
        """
        Calculate junction velocity between this move and previous move.

        Uses junction deviation to compute the maximum corner velocity
        that maintains acceleration limits. Based on Klipper's junction
        velocity calculation.

        Args:
            prev_move: Previous PyMove object

        Returns:
            float: Maximum junction velocity squared
        """
        if prev_move is None:
            return 0.0

        # Get direction vectors
        prev_d = prev_move.axes_r
        this_d = self.axes_r

        # Calculate dot product (cos of angle between moves)
        cos_theta = sum(p * t for p, t in zip(prev_d[:3], this_d[:3]))
        cos_theta = max(-1.0, min(1.0, cos_theta))  # Clamp

        if cos_theta >= 0.9999:
            # Essentially straight line, no junction limit
            return min(self.max_start_v2, prev_move.max_cruise_v2)

        # Calculate junction velocity using junction deviation formula
        # sin(theta/2) = sqrt((1 - cos(theta)) / 2)
        sin_theta_d2 = math.sqrt(0.5 * (1.0 - cos_theta))

        if sin_theta_d2 < 0.0001:
            return min(self.max_start_v2, prev_move.max_cruise_v2)

        # r = jd / sin(theta/2)
        # v^2 = a * r = a * jd / sin(theta/2)
        r_jd = sin_theta_d2 / (1.0 - sin_theta_d2)
        junction_v2 = r_jd * self.junction_deviation * self.accel

        return min(junction_v2, self.max_start_v2, prev_move.max_cruise_v2)

    def set_junction(self, *args, **kwargs):
        """
        Set junction velocities for this move.

        Args:
            start_v2: Starting velocity squared
            cruise_v2: Cruise velocity squared
            end_v2: Ending velocity squared
        """
        self.start_v2 = start_v2
        self.max_cruise_v2 = cruise_v2
        self.delta_v2 = end_v2 - start_v2

        # Calculate actual velocities
        self.start_v = math.sqrt(start_v2) if start_v2 > 0 else 0.0
        self.cruise_v = math.sqrt(cruise_v2) if cruise_v2 > 0 else 0.0
        self.end_v = math.sqrt(end_v2) if end_v2 > 0 else 0.0

    def limit_speed(self, *args, **kwargs):
        """
        Limit the move speed and acceleration.

        Args:
            speed: Maximum speed
            accel: Maximum acceleration
        """
        v2 = speed * speed
        self.max_cruise_v2 = min(self.max_cruise_v2, v2)
        self.max_start_v2 = min(self.max_start_v2, v2)
        self.cruise_v = min(self.cruise_v, speed)
        self.accel = min(self.accel, accel)

    def move_error(self, *args, **kwargs):
        """
        Calculate move error/deviation.

        Used for error checking and debugging move calculations.

        Args:
            error_buffer: Optional buffer for error message

        Returns:
            float: Error value for this move (0.0 if valid)
        """
        error = 0.0

        # Check for invalid velocities
        if self.cruise_v < 0 or self.start_v < 0 or self.end_v < 0:
            error = 1.0

        # Check for invalid times
        if self.accel_t < 0 or self.cruise_t < 0 or self.decel_t < 0:
            error = 2.0

        # Check for invalid acceleration
        if self.accel <= 0 and self.move_d > 0:
            error = 3.0

        return error

    # [INVENTED] This method does not exist in live module
    def __reduce_cython__(self):
        """Support for pickling."""
        return (PyMove, (), self.__dict__)

    # [INVENTED] This method does not exist in live module
    def __setstate_cython__(self, state):
        """Restore from pickled state."""
        self.__dict__.update(state)


# ============================================
# PyMoveSplitter Class
# ============================================

class PyMoveSplitter:
    """
    Splits moves into segments for motion planning.

    This class handles the segmentation of large moves into smaller
    segments that can be processed by the motion controller, taking
    into account acceleration limits, bed mesh compensation, and
    lookahead optimization.

    The splitter integrates with bed mesh to apply Z compensation
    during moves, splitting moves where Z compensation changes
    significantly.

    Attributes:
        max_velocity: Maximum XY velocity
        max_accel: Maximum acceleration
        max_accel_to_decel: Maximum accel-to-decel transition
        square_corner_velocity: Corner velocity limit
        junction_deviation: Calculated junction deviation
        z_mesh: Bed mesh for Z compensation
    """

    def __init__(self, *args, **kwargs):
        """
        Initialize the move splitter.

        Args:
            min_cruise_ratio: Minimum cruise ratio (0.0-1.0)
            split_delta_z: Z delta threshold for splitting
        """
        self.max_velocity = 500.0
        self.max_accel = 3000.0
        self.max_accel_to_decel = 1500.0
        self.square_corner_velocity = 5.0
        self.junction_deviation = 0.0
        self.min_cruise_ratio = min_cruise_ratio
        self.split_delta_z = split_delta_z

        # Z mesh compensation
        self.z_mesh = None

        # Z limits
        self.max_z_velocity = 15.0
        self.max_z_accel = 100.0

        # Extruder parameters
        self.max_e_velocity = 100.0
        self.max_e_accel = 1000.0
        self.pressure_advance = 0.0

        # Move check distance
        self.move_check_distance = 5.0

        # Move queue
        self.moves = []

    # [INVENTED] This method does not exist in live module
    def __cinit__(self):
        """Cython-style initialization (no-op in pure Python)."""
        # Native code would allocate C++ MoveSplitter here
        pass

    def initialize(self, *args, **kwargs):
        """
        Initialize the move splitter with kinematic limits.

        Args:
            max_velocity: Maximum velocity
            max_accel: Maximum acceleration
            max_accel_to_decel: Maximum accel to decel transition
            square_corner_velocity: Square corner velocity limit
        """
        self.max_velocity = float(max_velocity)
        self.max_accel = float(max_accel)
        self.max_accel_to_decel = float(max_accel_to_decel)
        self.square_corner_velocity = float(square_corner_velocity)

        # Calculate junction deviation from square corner velocity
        # Formula: jd = scv^2 * (sqrt(2) - 1) / accel
        scv2 = square_corner_velocity * square_corner_velocity
        self.junction_deviation = scv2 * (math.sqrt(2.0) - 1.0) / max_accel

    # [INVENTED] This method does not exist in live module
    def set_z_mesh(self, z_mesh):
        """
        Set the bed mesh for Z compensation.

        Args:
            z_mesh: BedMesh object or None
        """
        self.z_mesh = z_mesh

    # [INVENTED] This method does not exist in live module
    def _calc_z_offset(self, x, y):
        """
        Calculate Z offset at given position using bed mesh.

        Args:
            x: X coordinate
            y: Y coordinate

        Returns:
            float: Z offset from bed mesh
        """
        return Py_zmesh_calc_c(x, y, self.z_mesh)

    def build_move(self, *args, **kwargs):
        """
        Build a single move from start to end position.

        Args:
            start_pos: Starting position [x, y, z, e]
            end_pos: Ending position [x, y, z, e]
            speed: Requested move speed

        Returns:
            PyMove object
        """
        move = PyMove()
        move.start_pos = list(start_pos)
        move.end_pos = list(end_pos)

        # Calculate distances
        axes_d = [e - s for s, e in zip(start_pos, end_pos)]
        move.axes_d = axes_d

        # Calculate total move distance (XY only for kinematic)
        xy_d = math.sqrt(axes_d[0] ** 2 + axes_d[1] ** 2)
        move_d = xy_d

        if move_d == 0.0:
            move_d = abs(axes_d[2])  # Z-only move
        if move_d == 0.0:
            move_d = abs(axes_d[3])  # E-only move

        move.move_d = move_d

        if move_d > 0.0:
            move.axes_r = [d / move_d for d in axes_d]
        else:
            move.axes_r = [0.0, 0.0, 0.0, 0.0]

        # Determine velocity limits based on move type
        max_v = min(speed, self.max_velocity)

        # Apply Z velocity limit if Z motion
        if abs(axes_d[2]) > 0.0 and xy_d > 0.0:
            z_ratio = abs(axes_d[2]) / move_d
            if z_ratio > 0.0:
                z_limited_v = self.max_z_velocity / z_ratio
                max_v = min(max_v, z_limited_v)
        elif xy_d == 0.0 and abs(axes_d[2]) > 0.0:
            max_v = min(max_v, self.max_z_velocity)

        # Set velocity limits
        move.cruise_v = max_v
        move.max_cruise_v2 = max_v ** 2
        move.max_start_v2 = move.max_cruise_v2
        move.accel = self.max_accel
        move.junction_deviation = self.junction_deviation
        move.min_move_t = _corexy_info.get('min_move_t', 0.01)

        # Determine if kinematic move
        move.is_kinematic_move = (axes_d[0] != 0.0 or axes_d[1] != 0.0 or
                                  axes_d[2] != 0.0)

        return move

    def build_move_and_split(self, *args, **kwargs):
        """
        Build and split a move into segments.

        Splits the move if:
        - Z compensation changes significantly along the path
        - Move exceeds move_check_distance

        Args:
            start_pos: Starting position
            end_pos: Ending position
            speed: Requested speed

        Returns:
            List of PyMove segments
        """
        move = self.build_move(start_pos, end_pos, speed)

        # Check if splitting needed for bed mesh
        if self.z_mesh is not None and move.move_d > 0:
            segments = self._split_for_mesh(move)
            if len(segments) > 1:
                return segments

        return self.split(move)

    # [INVENTED] This method does not exist in live module
    def _split_for_mesh(self, move):
        """
        Split move for bed mesh Z compensation.

        Args:
            move: PyMove to potentially split

        Returns:
            List of PyMove segments
        """
        segments = []

        # Calculate Z offset at start and end
        z0 = self._calc_z_offset(move.start_pos[0], move.start_pos[1])
        z1 = self._calc_z_offset(move.end_pos[0], move.end_pos[1])

        delta_z = abs(z1 - z0)

        if delta_z <= self.split_delta_z:
            # No significant Z change, no split needed
            segments.append(move)
            return segments

        # Calculate number of splits needed
        num_splits = int(math.ceil(delta_z / self.split_delta_z))
        num_splits = max(2, min(num_splits, 100))  # Limit splits

        # Split the move
        for i in range(num_splits):
            t0 = i / num_splits
            t1 = (i + 1) / num_splits

            # Interpolate positions
            start = [s + (e - s) * t0 for s, e in
                     zip(move.start_pos, move.end_pos)]
            end = [s + (e - s) * t1 for s, e in
                   zip(move.start_pos, move.end_pos)]

            seg = self.build_move(start, end, move.cruise_v)
            segments.append(seg)

        return segments

    def split(self, *args, **kwargs):
        """
        Split a move into segments based on acceleration limits.

        Calculates the acceleration, cruise, and deceleration phases
        of the move and returns timing information.

        Args:
            move: PyMove to split

        Returns:
            List of PyMove segments
        """
        segments = []

        if move.move_d == 0.0:
            return segments

        # Calculate timing
        cruise_v = move.cruise_v
        accel = move.accel
        move_d = move.move_d

        # Calculate acceleration/deceleration distances
        # d = v²/(2a)
        accel_d = cruise_v ** 2 / (2.0 * accel)
        decel_d = cruise_v ** 2 / (2.0 * accel)

        if accel_d + decel_d > move_d:
            # Can't reach cruise velocity
            # Peak velocity at midpoint: v² = a*d, so v = sqrt(a*d)
            peak_v = math.sqrt(accel * move_d)
            move.cruise_v = peak_v
            move.accel_t = peak_v / accel
            move.cruise_t = 0.0
            move.decel_t = peak_v / accel
        else:
            # Can reach cruise velocity
            cruise_d = move_d - accel_d - decel_d
            move.accel_t = cruise_v / accel
            move.cruise_t = cruise_d / cruise_v if cruise_v > 0 else 0.0
            move.decel_t = cruise_v / accel

        segments.append(move)
        return segments

    def split_for_loop(self, *args, **kwargs):
        """
        Split multiple moves in a loop.

        Processes a list of moves, calculating junction velocities
        and splitting as needed.

        Args:
            moves: List of moves to process

        Returns:
            List of processed moves
        """
        result = []
        prev_move = None

        for move in moves:
            # Calculate junction with previous move
            if prev_move is not None:
                junction_v2 = move.calc_junction(prev_move)
                move.start_v2 = min(junction_v2, move.max_start_v2)

            # Split the move
            split_moves = self.split(move)
            result.extend(split_moves)

            if split_moves:
                prev_move = split_moves[-1]

        return result

    # [INVENTED] This method does not exist in live module
    def _set_next_move(self, move_time):
        """
        Set timing for next move.

        Args:
            move_time: Time for next move
        """
        # Used by native code for move scheduling
        pass

    # [INVENTED] This method does not exist in live module
    def __reduce_cython__(self):
        """Support for pickling."""
        return (PyMoveSplitter, (), self.__dict__)

    # [INVENTED] This method does not exist in live module
    def __setstate_cython__(self, state):
        """Restore from pickled state."""
        self.__dict__.update(state)
