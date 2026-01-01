#!/usr/bin/env python3
"""Debug why introspection misses prtouch classes."""

import sys
import os
import importlib.util

sys.path.insert(0, '/usr/share/klipper/klippy')
sys.path.insert(0, '/usr/share/klipper/klippy/extras')

EXTRAS_DIR = '/usr/share/klipper/klippy/extras'
so_path = f'{EXTRAS_DIR}/prtouch_v1_wrapper.cpython-39.so'

# Load module
spec = importlib.util.spec_from_file_location('prtouch_v1_wrapper', so_path)
module = importlib.util.module_from_spec(spec)
sys.modules['prtouch_v1_wrapper'] = module
spec.loader.exec_module(module)

print("=== Module loaded ===")
print(f"dir(module): {[n for n in dir(module) if not n.startswith('__')]}")

# Check each attribute
for name in dir(module):
    if name.startswith('_'):
        continue

    obj = getattr(module, name)
    print(f"\n{name}:")
    print(f"  type: {type(obj)}")
    print(f"  isinstance(obj, type): {isinstance(obj, type)}")
    print(f"  callable: {callable(obj)}")

    if isinstance(obj, type):
        print(f"  __bases__: {obj.__bases__}")
        print(f"  __mro__: {obj.__mro__}")

        # Get methods
        methods = [m for m in dir(obj) if not m.startswith('_') and callable(getattr(obj, m, None))]
        print(f"  methods ({len(methods)}): {methods[:15]}...")
