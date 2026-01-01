#!/usr/bin/env python3
"""
Generate accurate Python stub files from introspection data.

Usage:
    python3 generate_stubs.py re/introspection/module_dump.json re/decompiled/

This creates stub files with correct signatures from live module introspection.

Project structure:
    k2plus/
    ├── re/
    │   ├── introspection/   <- JSON from introspect_modules.py
    │   ├── decompiled/      <- Generated stubs go here
    │   └── tools/           <- This script
    └── ...
"""

import json
import os
import sys
import argparse
from pathlib import Path


HEADER_TEMPLATE = '''"""
{module_name} - Auto-generated stubs from live introspection

This file contains accurate method signatures extracted from the live K2 printer.
Implementations are stubs - the actual logic is in the compiled .cpython-39.so

Generated from: {source_file}

SIGNATURE SOURCE: Live introspection (ACCURATE)
IMPLEMENTATION: Stub only (NOT IMPLEMENTED)
"""

'''


def format_param(param):
    """Format a parameter for a function signature."""
    name = param.get('name', 'arg')

    # Handle *args and **kwargs
    if param.get('var_positional'):
        return f"*{name}"
    if param.get('var_keyword'):
        return f"**{name}"

    # Handle default values
    if 'default' in param:
        default = param['default']
        if default is None:
            return f"{name}=None"
        elif isinstance(default, str):
            return f"{name}={repr(default)}"
        elif isinstance(default, bool):
            return f"{name}={default}"
        elif isinstance(default, (int, float)):
            return f"{name}={default}"
        elif isinstance(default, bytes):
            return f"{name}={repr(default)}"
        elif isinstance(default, (list, dict)):
            return f"{name}={repr(default)}"
        else:
            # Complex default, use repr
            return f"{name}={repr(default)}"

    return name


def format_signature(method_info):
    """Format method signature from introspection data."""
    sig_info = method_info.get('signature', {})

    if 'error' in sig_info:
        return "self, *args, **kwargs"

    params = sig_info.get('params', [])
    if not params:
        return "self"

    formatted = []
    for param in params:
        formatted.append(format_param(param))

    return ", ".join(formatted)


def generate_class_stub(class_name, class_info, indent=""):
    """Generate stub code for a class."""
    lines = []

    # Class definition
    bases = class_info.get('bases', ['object'])
    bases_str = ", ".join(bases) if bases else "object"
    lines.append(f"{indent}class {class_name}({bases_str}):")

    # Docstring
    doc = class_info.get('doc')
    if doc:
        doc_escaped = doc.replace('"""', '\\"\\"\\"')
        lines.append(f'{indent}    """{doc_escaped}"""')
    else:
        lines.append(f'{indent}    """[STUB] Auto-generated from live introspection."""')

    # Class attributes
    class_attrs = class_info.get('class_attributes', {})
    if class_attrs:
        lines.append(f"{indent}    ")
        lines.append(f"{indent}    # Class attributes")
        for attr_name, attr_value in class_attrs.items():
            if isinstance(attr_value, str) and len(attr_value) > 50:
                lines.append(f"{indent}    {attr_name} = ...  # Long string")
            else:
                try:
                    lines.append(f"{indent}    {attr_name} = {repr(attr_value)}")
                except:
                    lines.append(f"{indent}    {attr_name} = None  # Complex value")

    # Properties
    properties = class_info.get('properties', {})
    if properties:
        lines.append(f"{indent}    ")
        lines.append(f"{indent}    # Properties")
        for prop_name, prop_info in properties.items():
            lines.append(f"{indent}    @property")
            lines.append(f"{indent}    def {prop_name}(self):")
            if prop_info.get('doc'):
                lines.append(f'{indent}        """{prop_info["doc"]}"""')
            lines.append(f"{indent}        raise NotImplementedError")
            lines.append(f"{indent}    ")

    # Methods
    methods = class_info.get('methods', {})
    if methods:
        lines.append(f"{indent}    ")
        # Sort methods: __init__ first, then __special__, then regular
        def method_sort_key(name):
            if name == '__init__':
                return (0, name)
            elif name.startswith('__') and name.endswith('__'):
                return (1, name)
            elif name.startswith('_'):
                return (3, name)
            else:
                return (2, name)

        sorted_methods = sorted(methods.keys(), key=method_sort_key)

        for method_name in sorted_methods:
            method_info = methods[method_name]

            # Decorators
            if method_info.get('classmethod'):
                lines.append(f"{indent}    @classmethod")
            elif method_info.get('staticmethod'):
                lines.append(f"{indent}    @staticmethod")

            # Method signature
            sig = format_signature(method_info)
            lines.append(f"{indent}    def {method_name}({sig}):")

            # Docstring
            doc = method_info.get('doc')
            if doc:
                doc_lines = doc.split('\n')
                if len(doc_lines) == 1:
                    lines.append(f'{indent}        """{doc}"""')
                else:
                    lines.append(f'{indent}        """')
                    for doc_line in doc_lines:
                        lines.append(f'{indent}        {doc_line}')
                    lines.append(f'{indent}        """')

            # Body
            if method_name == '__init__':
                lines.append(f"{indent}        pass  # [STUB] Initialize from config")
            else:
                lines.append(f"{indent}        raise NotImplementedError  # [STUB]")

            lines.append(f"{indent}    ")

    if not methods and not properties and not class_attrs:
        lines.append(f"{indent}    pass")

    return "\n".join(lines)


def generate_function_stub(func_name, func_info):
    """Generate stub code for a module-level function."""
    lines = []

    sig = format_signature(func_info)
    # Remove 'self' for module-level functions
    if sig.startswith("self, "):
        sig = sig[6:]
    elif sig == "self":
        sig = ""

    lines.append(f"def {func_name}({sig}):")

    doc = func_info.get('doc')
    if doc:
        lines.append(f'    """{doc}"""')

    lines.append("    raise NotImplementedError  # [STUB]")
    lines.append("")

    return "\n".join(lines)


def generate_module_stub(module_name, module_info, output_path):
    """Generate a complete stub file for a module."""
    lines = []

    # Header
    source_file = module_info.get('file', 'unknown')
    lines.append(HEADER_TEMPLATE.format(
        module_name=module_name,
        source_file=source_file
    ))

    # Imports (common ones used by Klipper modules)
    lines.append("import logging")
    lines.append("import threading")
    lines.append("import time")
    lines.append("")
    lines.append("")

    # Constants
    constants = module_info.get('constants', {})
    if constants:
        lines.append("# Constants")
        for const_name, const_value in constants.items():
            # Skip module references
            if isinstance(const_value, str) and const_value.startswith('<module'):
                continue
            try:
                lines.append(f"{const_name} = {repr(const_value)}")
            except:
                lines.append(f"{const_name} = None  # Complex value")
        lines.append("")
        lines.append("")

    # Functions
    functions = module_info.get('functions', {})
    if functions:
        lines.append("# Module-level functions")
        for func_name, func_info in sorted(functions.items()):
            lines.append(generate_function_stub(func_name, func_info))
        lines.append("")

    # Classes
    classes = module_info.get('classes', {})

    # Filter out imported classes (like MCU, ToolHead, etc.)
    # These have too many methods or are clearly from other modules
    own_classes = {}
    for class_name, class_info in classes.items():
        # Skip if it looks like an imported class
        if class_name in ['MCU', 'ToolHead', 'Reactor', 'GCodeDispatch', 'PrinterConfig',
                          'MCU_stepper', 'MCU_endstop', 'MCU_adc', 'MCU_pwm', 'MCU_digital_out',
                          'MCU_trsync', 'CommandWrapper', 'CommandQueryWrapper', 'ConfigWrapper',
                          'GCodeCommand', 'GCodeIO', 'PrinterRail', 'MoveQueue', 'Coord',
                          'PollReactor', 'SelectReactor', 'EPollReactor', 'ReactorTimer',
                          'ReactorCallback', 'ReactorFileHandler', 'ReactorCompletion',
                          'ReactorGreenlet', 'ReactorMutex', 'DripModeEndSignal',
                          'RetryAsyncCommand', 'ExtruderRetryAsyncCommand',
                          'CommandError', 'error', 'sentinel']:
            continue
        own_classes[class_name] = class_info

    if own_classes:
        for class_name, class_info in sorted(own_classes.items()):
            lines.append(generate_class_stub(class_name, class_info))
            lines.append("")
            lines.append("")

    # Write to file
    output_file = output_path / f"{module_name}_stub.py"
    with open(output_file, 'w') as f:
        f.write("\n".join(lines))

    return output_file


def main():
    parser = argparse.ArgumentParser(description='Generate stubs from introspection')
    parser.add_argument('introspection_json', help='JSON from introspect_modules.py')
    parser.add_argument('output_dir', help='Directory for generated stubs')
    parser.add_argument('--modules', nargs='*', help='Specific modules to generate (default: all)')
    args = parser.parse_args()

    # Load introspection data
    with open(args.introspection_json) as f:
        data = json.load(f)

    output_path = Path(args.output_dir)
    output_path.mkdir(parents=True, exist_ok=True)

    modules = data.get('modules', {})

    # Filter modules if specified
    if args.modules:
        modules = {k: v for k, v in modules.items() if k in args.modules}

    print(f"Generating stubs for {len(modules)} modules...")

    for module_name, module_info in modules.items():
        if module_info.get('error'):
            print(f"  Skipping {module_name}: {module_info['error']}")
            continue

        output_file = generate_module_stub(module_name, module_info, output_path)

        # Count classes and methods
        classes = module_info.get('classes', {})
        total_methods = sum(len(c.get('methods', {})) for c in classes.values())

        print(f"  {module_name}: {len(classes)} classes, {total_methods} methods -> {output_file}")

    print(f"\nStubs written to: {output_path}")


if __name__ == '__main__':
    main()
