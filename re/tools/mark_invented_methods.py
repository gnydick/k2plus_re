#!/usr/bin/env python3
"""
Mark invented methods that don't exist in live modules.

Usage:
    python3 mark_invented_methods.py [reconstructed_dir]

Adds # [INVENTED] comments to methods that exist in reconstructed
but not in live modules.

Default directory: re/reconstructed/

Project structure:
    k2plus/
    └── re/
        ├── reconstructed/   <- Files to mark (default)
        └── tools/           <- This script
"""

import re
import sys
from pathlib import Path

# Methods that exist in our files but NOT in live modules
INVENTED_METHODS = {
    'box_wrapper.py': {
        'MultiColorMeterialBoxWrapper': ['_register_commands'],
        'BoxAction': ['_get_color_for_tnn', '_calc_crc'],
    },
    'motor_control_wrapper.py': {
        'Motor_Control': ['cmd_ZDOWN_FORCE_STOP', '_register_commands',
                          '_motor_init_axis', 'motor_cancel_print_start',
                          'motor_send_data', '_handle_ready'],
    },
    'filament_rack_wrapper.py': {
        'FilamentRackWrapper': ['_get_temp_by_type', '_load_filament', '_detect_material',
                                'get_material_type', '_update_hotend_temp_variable',
                                '_is_beep_enabled', '_load_material_database',
                                '_load_system_config', 'send_data_string',
                                'check_and_extrude', 'get_material_vendor',
                                '_unload_filament', '_register_buttons', 'get_material_color'],
        'RemainMaterial': ['update_remain_length', 'set_material_info', '_load_saved_state'],
    },
    'prtouch_v1_wrapper.py': {
        'PRTouchEndstopWrapper': ['_register_commands', 'get_status',
                                   '_handle_connect', '_handle_mcu_identify'],
    },
    'prtouch_v2_wrapper.py': {
        'PRTouchEndstopWrapper': ['_register_commands', 'probe_helper', 'get_status',
                                   '_handle_connect', 'clear_nozzle_quick',
                                   'probe_min_3err', '_handle_mcu_identify', 'cmd_TRIG_Z_TILT'],
    },
    'prtouch_v3_wrapper.py': {
        'PRTouchEndstopWrapper': ['get_step_dist', '_register_commands'],
    },
    'mymovie.py': {
        'PyMoveSplitter': ['__cinit__', '_calc_z_offset', '__setstate_cython__',
                           'set_z_mesh', '_split_for_mesh', '_set_next_move',
                           '__reduce_cython__'],
        'PyMove': ['__reduce_cython__', '__setstate_cython__'],
    },
}


def mark_invented_methods(filepath, class_methods):
    """Add [INVENTED] comment to invented methods."""
    with open(filepath) as f:
        content = f.read()

    modified = False

    for class_name, methods in class_methods.items():
        for method_name in methods:
            # Pattern to find the method definition
            # Match "def method_name(" with any indentation
            pattern = rf'(\n([ \t]+)def {re.escape(method_name)}\([^)]*\):)'

            def replacer(match):
                full_match = match.group(1)
                indent = match.group(2)
                # Check if already marked
                if '[INVENTED]' in content[max(0, match.start()-100):match.start()]:
                    return full_match
                # Add comment before the def
                return f'\n{indent}# [INVENTED] This method does not exist in live module\n{indent}def {method_name}' + full_match[full_match.index('('):]

            new_content = re.sub(pattern, replacer, content)
            if new_content != content:
                content = new_content
                modified = True
                print(f"  Marked {class_name}.{method_name}")

    if modified:
        with open(filepath, 'w') as f:
            f.write(content)

    return modified


def main():
    # Default to re/reconstructed relative to this script's location
    script_dir = Path(__file__).parent
    project_root = script_dir.parent.parent  # re/tools -> re -> k2plus
    default_dir = project_root / 're' / 'reconstructed'
    merged_dir = Path(sys.argv[1]) if len(sys.argv) > 1 else default_dir

    for filename, class_methods in INVENTED_METHODS.items():
        filepath = merged_dir / filename
        if filepath.exists():
            print(f"Processing {filename}...")
            mark_invented_methods(filepath, class_methods)
        else:
            print(f"Skipping {filename} - not found")


if __name__ == '__main__':
    main()
