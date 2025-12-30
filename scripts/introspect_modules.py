#!/usr/bin/env python3
"""
Introspect Creality K2 Klipper modules from live printer.

Run this script ON THE PRINTER via SSH:
    scp introspect_modules.py root@<printer-ip>:/tmp/
    ssh root@<printer-ip> python3 /tmp/introspect_modules.py > module_dump.json

This extracts accurate method signatures, docstrings, and class structure
from the compiled Cython modules.
"""

import sys
import os
import json
import inspect
from types import FunctionType, MethodType

# Add Klipper paths - K2 printer uses /usr/share/klipper/
# For local development, set KLIPPER_SOURCE environment variable
KLIPPER_SOURCE = os.environ.get('KLIPPER_SOURCE', '')

KLIPPER_PATHS = [
    '/usr/share/klipper/klippy',
    '/usr/share/klipper/klippy/extras',
    '/usr/share/klipper/klippy/mymodule',
]

# Add fallback paths for local development if KLIPPER_SOURCE is set
if KLIPPER_SOURCE:
    KLIPPER_PATHS.extend([
        os.path.join(KLIPPER_SOURCE, 'klippy'),
        os.path.join(KLIPPER_SOURCE, 'klippy/extras'),
    ])

for path in KLIPPER_PATHS:
    if os.path.exists(path) and path not in sys.path:
        sys.path.insert(0, path)

# Modules to introspect with their .so file paths for direct loading
# Use KLIPPER_SOURCE if set, otherwise default to printer paths
if KLIPPER_SOURCE:
    EXTRAS_DIR = os.path.join(KLIPPER_SOURCE, 'klippy/extras')
    MYMODULE_DIR = os.path.join(KLIPPER_SOURCE, 'klippy/mymodule')
else:
    EXTRAS_DIR = '/usr/share/klipper/klippy/extras'
    MYMODULE_DIR = '/usr/share/klipper/klippy/mymodule'

MODULES = [
    ('box_wrapper', f'{EXTRAS_DIR}/box_wrapper.cpython-39.so'),
    ('serial_485_wrapper', f'{EXTRAS_DIR}/serial_485_wrapper.cpython-39.so'),
    ('motor_control_wrapper', f'{EXTRAS_DIR}/motor_control_wrapper.cpython-39.so'),
    ('filament_rack_wrapper', f'{EXTRAS_DIR}/filament_rack_wrapper.cpython-39.so'),
    ('prtouch_v1_wrapper', f'{EXTRAS_DIR}/prtouch_v1_wrapper.cpython-39.so'),
    ('prtouch_v2_wrapper', f'{EXTRAS_DIR}/prtouch_v2_wrapper.cpython-39.so'),
    ('prtouch_v3_wrapper', f'{EXTRAS_DIR}/prtouch_v3_wrapper.cpython-39.so'),
    ('mymovie', f'{MYMODULE_DIR}/mymovie.cpython-39.so'),
]


def get_signature_safe(obj):
    """Get function signature, handling Cython edge cases."""
    try:
        sig = inspect.signature(obj)
        params = []
        for name, param in sig.parameters.items():
            param_info = {'name': name}
            if param.default is not inspect.Parameter.empty:
                try:
                    # Try to serialize the default
                    json.dumps(param.default)
                    param_info['default'] = param.default
                except (TypeError, ValueError):
                    param_info['default'] = repr(param.default)
            if param.annotation is not inspect.Parameter.empty:
                param_info['annotation'] = str(param.annotation)
            if param.kind == inspect.Parameter.VAR_POSITIONAL:
                param_info['var_positional'] = True
            if param.kind == inspect.Parameter.VAR_KEYWORD:
                param_info['var_keyword'] = True
            params.append(param_info)
        return {'params': params, 'signature_str': str(sig)}
    except (ValueError, TypeError) as e:
        return {'error': str(e)}


def introspect_class(cls):
    """Extract all information from a class."""
    result = {
        'name': cls.__name__,
        'module': getattr(cls, '__module__', None),
        'doc': cls.__doc__,
        'bases': [b.__name__ for b in cls.__bases__],
        'methods': {},
        'properties': {},
        'class_attributes': {},
    }

    for name in dir(cls):
        if name.startswith('__') and name.endswith('__'):
            # Skip most dunder methods except __init__
            if name not in ('__init__', '__call__', '__getitem__', '__setitem__'):
                continue

        try:
            obj = getattr(cls, name)
        except AttributeError:
            continue

        # Methods
        if callable(obj) and not isinstance(obj, type):
            method_info = {
                'doc': obj.__doc__,
                'signature': get_signature_safe(obj),
            }

            # Check if it's a classmethod or staticmethod
            for klass in cls.__mro__:
                if name in klass.__dict__:
                    if isinstance(klass.__dict__[name], classmethod):
                        method_info['classmethod'] = True
                    elif isinstance(klass.__dict__[name], staticmethod):
                        method_info['staticmethod'] = True
                    break

            result['methods'][name] = method_info

        # Properties
        elif isinstance(obj, property):
            result['properties'][name] = {
                'doc': obj.__doc__,
                'has_getter': obj.fget is not None,
                'has_setter': obj.fset is not None,
                'has_deleter': obj.fdel is not None,
            }

        # Class attributes (non-callable, non-property)
        elif not callable(obj) and not name.startswith('_'):
            try:
                json.dumps(obj)
                result['class_attributes'][name] = obj
            except (TypeError, ValueError):
                result['class_attributes'][name] = repr(obj)

    return result


def setup_extras_package():
    """Set up the extras package for relative imports."""
    import types
    extras_path = '/usr/share/klipper/klippy/extras'

    if 'extras' not in sys.modules and os.path.exists(extras_path):
        extras_pkg = types.ModuleType('extras')
        extras_pkg.__path__ = [extras_path]
        extras_pkg.__file__ = os.path.join(extras_path, '__init__.py')
        extras_pkg.__package__ = 'extras'
        sys.modules['extras'] = extras_pkg


def introspect_module(module_name, so_file_path=None):
    """Introspect a single module."""
    import importlib.util

    result = {
        'name': module_name,
        'classes': {},
        'functions': {},
        'constants': {},
        'error': None,
    }

    module = None
    last_error = None

    # Set up extras package for modules with relative imports
    setup_extras_package()

    # Try loading directly from .so file first
    if so_file_path and os.path.exists(so_file_path):
        try:
            # For modules in extras/, load as extras.module_name to support relative imports
            if '/extras/' in so_file_path:
                full_name = f'extras.{module_name}'
            else:
                full_name = module_name

            spec = importlib.util.spec_from_file_location(
                full_name, so_file_path,
                submodule_search_locations=[]
            )
            if spec and spec.loader:
                module = importlib.util.module_from_spec(spec)
                module.__package__ = 'extras' if '/extras/' in so_file_path else ''
                sys.modules[full_name] = module
                spec.loader.exec_module(module)
        except Exception as e:
            last_error = e
            module = None

    # Fallback to regular import
    if module is None:
        try:
            module = __import__(module_name)
        except Exception as e:
            if last_error is None:
                last_error = e

    if module is None:
        result['error'] = f"ImportError: {last_error}"
        return result

    try:
        result['file'] = getattr(module, '__file__', None)
        result['doc'] = module.__doc__

        for name in dir(module):
            if name.startswith('_'):
                continue

            try:
                obj = getattr(module, name)
            except AttributeError:
                continue

            # Classes
            if isinstance(obj, type):
                result['classes'][name] = introspect_class(obj)

            # Functions
            elif callable(obj):
                result['functions'][name] = {
                    'doc': obj.__doc__,
                    'signature': get_signature_safe(obj),
                }

            # Constants
            else:
                try:
                    json.dumps(obj)
                    result['constants'][name] = obj
                except (TypeError, ValueError):
                    result['constants'][name] = repr(obj)

    except ImportError as e:
        result['error'] = f"ImportError: {e}"
    except Exception as e:
        result['error'] = f"{type(e).__name__}: {e}"

    return result


def main():
    """Main entry point."""
    output = {
        'python_version': sys.version,
        'platform': sys.platform,
        'paths': sys.path[:10],
        'modules': {}
    }

    for module_name, so_path in MODULES:
        sys.stderr.write(f"Introspecting {module_name}...\n")
        output['modules'][module_name] = introspect_module(module_name, so_path)

    # Output as JSON
    print(json.dumps(output, indent=2, default=str))


if __name__ == '__main__':
    main()
