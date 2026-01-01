#!/usr/bin/env python3
"""
Debug prtouch module loading issues.

Run ON THE PRINTER:
    scp debug_prtouch.py root@k2plus:/tmp/
    ssh root@k2plus python3 /tmp/debug_prtouch.py
"""

import sys
import os
import importlib.util

# Add paths
sys.path.insert(0, '/usr/share/klipper/klippy')
sys.path.insert(0, '/usr/share/klipper/klippy/extras')

EXTRAS_DIR = '/usr/share/klipper/klippy/extras'

# Try to understand what prtouch modules need
print("=== Checking prtouch_v1_wrapper ===")
so_path = f'{EXTRAS_DIR}/prtouch_v1_wrapper.cpython-39.so'

print(f"File exists: {os.path.exists(so_path)}")
print(f"File size: {os.path.getsize(so_path)} bytes")

# Check what strings mention imports
import subprocess
result = subprocess.run(['strings', so_path], capture_output=True, text=True)
imports = [line for line in result.stdout.split('\n') if 'import' in line.lower() or line.startswith('from ')]
print(f"\nImport-related strings ({len(imports)} found):")
for imp in imports[:20]:
    print(f"  {imp}")

# Try loading with verbose errors
print("\n=== Attempting import ===")
try:
    spec = importlib.util.spec_from_file_location('prtouch_v1_wrapper', so_path)
    print(f"Spec: {spec}")
    print(f"Spec.loader: {spec.loader}")

    module = importlib.util.module_from_spec(spec)
    print(f"Module created: {module}")

    # This is where it might fail
    print("Executing module...")
    spec.loader.exec_module(module)

    print(f"\nModule loaded successfully!")
    print(f"dir(module): {dir(module)}")
    print(f"Classes: {[n for n in dir(module) if not n.startswith('_')]}")

except Exception as e:
    import traceback
    print(f"\nException: {type(e).__name__}: {e}")
    traceback.print_exc()

# Also try regular import to see full error
print("\n=== Trying regular import ===")
try:
    import prtouch_v1_wrapper
    print(f"Success! dir: {dir(prtouch_v1_wrapper)}")
except Exception as e:
    import traceback
    print(f"Exception: {type(e).__name__}: {e}")
    traceback.print_exc()
