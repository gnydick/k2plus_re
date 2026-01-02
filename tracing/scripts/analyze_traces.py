#!/usr/bin/env python3
"""Analyze trace captures - merge, interleave, and correlate parameters."""

import json
import os
import sys
from collections import defaultdict
from datetime import datetime

def load_traces(captures_dir):
    """Load all JSONL files and merge by timestamp."""
    all_events = []

    for fname in os.listdir(captures_dir):
        if not fname.endswith('.jsonl') or fname.startswith('_system'):
            continue

        fpath = os.path.join(captures_dir, fname)
        with open(fpath, 'r') as f:
            for line in f:
                try:
                    event = json.loads(line.strip())
                    event['_source'] = fname.replace('_20260101_235813.jsonl', '')
                    all_events.append(event)
                except:
                    pass

    # Sort by timestamp
    all_events.sort(key=lambda x: x.get('time', 0))
    return all_events

def find_load_unload_sequences(events):
    """Find ff10 (load) and ff11 (unload) command sequences."""
    sequences = []
    current_seq = None

    for e in events:
        if e.get('type') != 'call':
            continue

        args = e.get('args', '')
        if 'ff10' in str(args).lower():
            # Load command
            if current_seq is None or current_seq['type'] != 'load':
                if current_seq:
                    sequences.append(current_seq)
                current_seq = {
                    'type': 'load',
                    'start_time': e['time'],
                    'commands': [],
                    'box_status': [],
                    'temps': [],
                    'humidity': [],
                    'velocities': []
                }
            current_seq['commands'].append(e)
        elif 'ff11' in str(args).lower():
            # Unload command
            if current_seq is None or current_seq['type'] != 'unload':
                if current_seq:
                    sequences.append(current_seq)
                current_seq = {
                    'type': 'unload',
                    'start_time': e['time'],
                    'commands': [],
                    'box_status': [],
                    'temps': [],
                    'humidity': [],
                    'velocities': []
                }
            current_seq['commands'].append(e)

    if current_seq:
        sequences.append(current_seq)

    return sequences

def extract_box_params(events):
    """Extract temperature, humidity, velocity from box status."""
    params = []

    for e in events:
        if e.get('type') != 'return' or e.get('method') != 'get_status':
            continue

        result = e.get('result', {})
        if not isinstance(result, dict):
            continue

        record = {'time': e['time'], 'source': e.get('_source', '')}

        # Box status
        for box in ['T1', 'T2', 'T3', 'T4']:
            if box in result:
                box_data = result[box]
                if isinstance(box_data, dict):
                    record[f'{box}_temp'] = box_data.get('temperature')
                    record[f'{box}_humidity'] = box_data.get('dry_and_humidity')
                    record[f'{box}_filament'] = box_data.get('filament')

        # Filament rack velocity
        if 'remain_material_velocity' in result:
            record['velocity'] = result['remain_material_velocity']

        if len(record) > 2:  # Has data beyond time and source
            params.append(record)

    return params

def decode_ff10_subcmd(cmd_bytes):
    """Decode ff10 load subcommand."""
    # Format: ADDR 06 FF 10 SLOT SUBCMD PARAM
    subcmds = {
        0x00: 'INIT',
        0x01: 'START_PUSH',
        0x02: 'PUSH_RUNNING',
        0x03: 'WAIT_SENSOR',
        0x04: 'SENSOR_DETECTED',
        0x05: 'FEED_TO_EXTRUDER',
        0x06: 'FLUSH',
        0x07: 'COMPLETE'
    }
    try:
        if isinstance(cmd_bytes, dict) and '_bytes' in cmd_bytes:
            hex_str = cmd_bytes['_bytes']
        else:
            hex_str = str(cmd_bytes)

        # Parse: e.g., '0106ff10010400' -> addr=01, len=06, cmd=ff10, slot=01, subcmd=04
        if 'ff10' in hex_str.lower():
            idx = hex_str.lower().find('ff10')
            if idx + 8 <= len(hex_str):
                slot = int(hex_str[idx+4:idx+6], 16)
                subcmd = int(hex_str[idx+6:idx+8], 16)
                param = int(hex_str[idx+8:idx+10], 16) if idx+10 <= len(hex_str) else 0
                return {'slot': slot, 'subcmd': subcmds.get(subcmd, f'0x{subcmd:02x}'), 'param': param}
    except:
        pass
    return None

def decode_ff11_subcmd(cmd_bytes):
    """Decode ff11 unload subcommand."""
    subcmds = {
        0x00: 'INIT',
        0x01: 'PRE_RETRACT',
        0x02: 'MAIN_RETRACT',
        0x03: 'COMPLETE'
    }
    try:
        if isinstance(cmd_bytes, dict) and '_bytes' in cmd_bytes:
            hex_str = cmd_bytes['_bytes']
        else:
            hex_str = str(cmd_bytes)

        if 'ff11' in hex_str.lower():
            idx = hex_str.lower().find('ff11')
            if idx + 8 <= len(hex_str):
                slot = int(hex_str[idx+4:idx+6], 16)
                subcmd = int(hex_str[idx+6:idx+8], 16)
                param = int(hex_str[idx+8:idx+10], 16) if idx+10 <= len(hex_str) else 0
                return {'slot': slot, 'subcmd': subcmds.get(subcmd, f'0x{subcmd:02x}'), 'param': param}
    except:
        pass
    return None

def analyze_workflows(events, params):
    """Analyze load/unload workflows with correlated params."""
    workflows = []
    current_workflow = None

    for e in events:
        args = str(e.get('args', ''))

        # Detect workflow start
        if 'ff10' in args.lower() and e.get('type') == 'call':
            decoded = decode_ff10_subcmd(args)
            if decoded and decoded['subcmd'] == 'INIT':
                if current_workflow:
                    workflows.append(current_workflow)
                current_workflow = {
                    'type': 'LOAD',
                    'slot': decoded['slot'],
                    'start_time': e['time'],
                    'end_time': None,
                    'phases': [],
                    'temp_samples': [],
                    'humidity_samples': [],
                    'velocity_samples': [],
                    'duration_ms': 0
                }
            if current_workflow and decoded:
                current_workflow['phases'].append({
                    'time': e['time'],
                    'phase': decoded['subcmd'],
                    'param': decoded['param']
                })
                if decoded['subcmd'] == 'COMPLETE':
                    current_workflow['end_time'] = e['time']
                    current_workflow['duration_ms'] = (e['time'] - current_workflow['start_time']) * 1000

        elif 'ff11' in args.lower() and e.get('type') == 'call':
            decoded = decode_ff11_subcmd(args)
            if decoded and decoded['subcmd'] == 'INIT':
                if current_workflow:
                    workflows.append(current_workflow)
                current_workflow = {
                    'type': 'UNLOAD',
                    'slot': decoded['slot'],
                    'start_time': e['time'],
                    'end_time': None,
                    'phases': [],
                    'temp_samples': [],
                    'humidity_samples': [],
                    'velocity_samples': [],
                    'duration_ms': 0
                }
            if current_workflow and decoded:
                current_workflow['phases'].append({
                    'time': e['time'],
                    'phase': decoded['subcmd'],
                    'param': decoded['param']
                })
                if decoded['subcmd'] == 'COMPLETE':
                    current_workflow['end_time'] = e['time']
                    current_workflow['duration_ms'] = (e['time'] - current_workflow['start_time']) * 1000

    if current_workflow:
        workflows.append(current_workflow)

    # Correlate params with workflows
    for wf in workflows:
        start = wf['start_time']
        end = wf['end_time'] or (start + 60)  # Default 60s window

        for p in params:
            if start <= p['time'] <= end:
                for key in p:
                    if 'temp' in key and p[key]:
                        wf['temp_samples'].append((p['time'] - start, p[key]))
                    if 'humidity' in key and p[key]:
                        wf['humidity_samples'].append((p['time'] - start, p[key]))
                    if 'velocity' in key and p[key]:
                        wf['velocity_samples'].append((p['time'] - start, p[key]))

    return workflows

def print_workflow_summary(workflows):
    """Print summary of workflows."""
    print("\n" + "="*70)
    print("WORKFLOW SUMMARY")
    print("="*70)

    slot_names = {1: 'A', 2: 'B', 3: 'C', 4: 'D'}

    for i, wf in enumerate(workflows):
        slot_letter = slot_names.get(wf['slot'], '?')
        box_num = ((wf.get('addr', 1) - 1) // 1) + 1  # Approximate

        print(f"\n[{i+1}] {wf['type']} Slot {wf['slot']} ({slot_letter})")
        print(f"    Duration: {wf['duration_ms']:.0f}ms")
        print(f"    Phases: {len(wf['phases'])}")

        for phase in wf['phases']:
            offset_ms = (phase['time'] - wf['start_time']) * 1000
            print(f"      +{offset_ms:6.0f}ms: {phase['phase']} (param={phase['param']})")

        if wf['temp_samples']:
            temps = [t[1] for t in wf['temp_samples'] if t[1]]
            if temps:
                print(f"    Temps: {min(temps)}-{max(temps)}C")

        if wf['humidity_samples']:
            hums = [h[1] for h in wf['humidity_samples'] if h[1]]
            if hums:
                print(f"    Humidity: {min(hums)}-{max(hums)}%")

        if wf['velocity_samples']:
            vels = [v[1] for v in wf['velocity_samples'] if v[1]]
            if vels:
                print(f"    Velocity: {min(vels)}-{max(vels)}")

def main():
    if len(sys.argv) < 2:
        captures_dir = '/home/gnydick/IdeaProjects/k2plus/tracing/20260101_221648_filament_sensors/captures'
    else:
        captures_dir = sys.argv[1]

    print(f"Loading traces from: {captures_dir}")
    events = load_traces(captures_dir)
    print(f"Loaded {len(events)} events")

    print("\nExtracting parameters...")
    params = extract_box_params(events)
    print(f"Found {len(params)} parameter samples")

    print("\nAnalyzing workflows...")
    workflows = analyze_workflows(events, params)
    print(f"Found {len(workflows)} workflows")

    print_workflow_summary(workflows)

    # Write detailed output
    output_file = os.path.join(os.path.dirname(captures_dir), 'workflow_analysis.json')
    with open(output_file, 'w') as f:
        json.dump({
            'total_events': len(events),
            'param_samples': len(params),
            'workflows': workflows
        }, f, indent=2, default=str)
    print(f"\nDetailed analysis saved to: {output_file}")

if __name__ == '__main__':
    main()
