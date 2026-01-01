#!/usr/bin/env python3
"""
Diagnostic script to find Klipper module locations on K2 printer.

Run ON THE PRINTER:
    scp find_klipper_paths.py root@k2plus:/tmp/
    ssh root@k2plus python3 /tmp/find_klipper_paths.py
"""

import os
import sys
import glob

print("=== Python Info ===")
print(f"Python: {sys.executable}")
print(f"Version: {sys.version}")
print(f"sys.path: {sys.path}")
print()

# Common locations to check
SEARCH_PATHS = [
    '/usr/share/klippy',
    '/usr/share/klipper',
    '/home/*/klipper',
    '/home/*/klippy',
    '/opt/klipper',
    '/opt/klippy',
    '/root/klipper',
    '/root/klippy',
    '/usr/lib/python*/site-packages',
    '/usr/local/lib/python*/site-packages',
]

# Files we're looking for
TARGET_FILES = [
    '**/box_wrapper*.so',
    '**/serial_485_wrapper*.so',
    '**/motor_control_wrapper*.so',
    '**/prtouch_v1_wrapper*.so',
    '**/prtouch_v2_wrapper*.so',
    '**/prtouch_v3_wrapper*.so',
    '**/filament_rack_wrapper*.so',
    '**/mymovie*.so',
    '**/extras/*.so',
    '**/klippy.py',
    '**/gcode.py',
]

print("=== Searching for Klipper files ===")

# Use find command for thorough search
found_paths = set()

for pattern in ['/usr', '/home', '/opt', '/root']:
    if os.path.exists(pattern):
        for root, dirs, files in os.walk(pattern):
            # Skip some dirs for speed
            dirs[:] = [d for d in dirs if d not in ['.git', 'node_modules', '__pycache__']]

            for f in files:
                if f.endswith('.so') and 'wrapper' in f:
                    full_path = os.path.join(root, f)
                    print(f"FOUND .so: {full_path}")
                    found_paths.add(os.path.dirname(full_path))
                elif f == 'klippy.py':
                    full_path = os.path.join(root, f)
                    print(f"FOUND klippy.py: {full_path}")
                    found_paths.add(os.path.dirname(full_path))
                elif f.endswith('_wrapper.cpython-39.so'):
                    full_path = os.path.join(root, f)
                    print(f"FOUND wrapper: {full_path}")
                    found_paths.add(os.path.dirname(full_path))

print()
print("=== Recommended sys.path additions ===")
for p in sorted(found_paths):
    print(f"  '{p}',")

print()
print("=== Trying to import modules ===")

# Add found paths
for p in found_paths:
    if p not in sys.path:
        sys.path.insert(0, p)

# Try imports
modules_to_try = [
    'box_wrapper',
    'serial_485_wrapper',
    'motor_control_wrapper',
    'prtouch_v1_wrapper',
    'prtouch_v2_wrapper',
    'prtouch_v3_wrapper',
    'filament_rack_wrapper',
    'mymovie',
]

for mod in modules_to_try:
    try:
        m = __import__(mod)
        print(f"  {mod}: OK - {getattr(m, '__file__', 'no __file__')}")
    except ImportError as e:
        print(f"  {mod}: FAILED - {e}")
    except Exception as e:
        print(f"  {mod}: ERROR - {type(e).__name__}: {e}")

print()
print("=== Done ===")
