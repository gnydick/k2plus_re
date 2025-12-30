#!/usr/bin/env python3
"""
Flush Volume Data Collector for K2 Plus

Part of the K2 Plus firmware reverse engineering toolkit.
Systematically runs tool changes to collect input/output data
for reverse-engineering the calc_flushing_volume algorithm.

Created: 2024-12-30
Project: Creality K2 Plus Klipper Firmware Reconstruction

Prerequisites:
1. Trace hooks deployed and running on printer
2. Capture client running: python3 trace_capture.py <printer_ip>
3. TRACE_DEEP and TRACE_ATTRS enabled on box object:
   TRACE_DEEP OBJECT=box
   TRACE_ATTRS OBJECT=box ENABLE=1

Usage:
    python3 flush_data_collector.py <printer_ip> [--dry-run]

The script will:
1. Query current tool/material state
2. Run systematic tool changes (T0->T1, T0->T2, etc.)
3. Record flush lengths and material combinations
4. Output a summary of collected data
"""

import argparse
import json
import time
import sys
from itertools import permutations


class FlushDataCollector:
    def __init__(self, host, port=7125):
        self.host = host
        self.port = port  # Moonraker port
        self.collected_data = []
        self.dry_run = False

    def send_gcode(self, gcode):
        """Send GCode command via Moonraker HTTP API."""
        import urllib.request
        import urllib.parse

        if self.dry_run:
            print(f"[DRY-RUN] Would send: {gcode}")
            return True

        url = f"http://{self.host}:{self.port}/printer/gcode/script"
        data = urllib.parse.urlencode({'script': gcode}).encode('utf-8')

        try:
            req = urllib.request.Request(url, data=data, method='POST')
            with urllib.request.urlopen(req, timeout=300) as response:
                result = response.read().decode('utf-8')
                return True
        except Exception as e:
            print(f"Error sending gcode: {e}")
            return False

    def query_printer_state(self):
        """Query current printer state via Moonraker."""
        import urllib.request

        url = f"http://{self.host}:{self.port}/printer/objects/query?box"
        try:
            with urllib.request.urlopen(url, timeout=10) as response:
                result = json.loads(response.read().decode('utf-8'))
                return result.get('result', {}).get('status', {})
        except Exception as e:
            print(f"Error querying state: {e}")
            return {}

    def wait_for_idle(self, timeout=300):
        """Wait for printer to become idle."""
        import urllib.request

        start = time.time()
        while time.time() - start < timeout:
            url = f"http://{self.host}:{self.port}/printer/objects/query?print_stats"
            try:
                with urllib.request.urlopen(url, timeout=10) as response:
                    result = json.loads(response.read().decode('utf-8'))
                    state = result.get('result', {}).get('status', {}).get('print_stats', {}).get('state', '')
                    if state in ('standby', 'complete', 'cancelled', ''):
                        return True
            except:
                pass
            time.sleep(2)
        return False

    def setup_tracing(self):
        """Enable deep tracing on box module."""
        print("Setting up deep tracing on box module...")

        commands = [
            "TRACE_DEEP OBJECT=box",
            "TRACE_ATTRS OBJECT=box ENABLE=1",
        ]

        for cmd in commands:
            self.send_gcode(cmd)
            time.sleep(0.5)

        print("Tracing enabled. Make sure capture client is running!")

    def collect_tool_change_data(self, tools=None, materials=None):
        """
        Run systematic tool changes to collect flush data.

        Args:
            tools: List of tool names to test (default: T0A-T3A, T0B-T3B)
            materials: Dict of tool -> material type (optional)
        """
        if tools is None:
            # Default K2 Plus tools (4 slots, A and B sides)
            tools = ['T0A', 'T1A', 'T2A', 'T3A']  # Start with A side

        print(f"\nCollecting flush data for tools: {tools}")
        print("=" * 60)

        # Track current tool
        current_tool = None

        # Test all permutations
        for prev_tool, next_tool in permutations(tools, 2):
            print(f"\nTesting: {prev_tool or 'None'} -> {next_tool}")

            # Record the test
            test_record = {
                'timestamp': time.time(),
                'prev_tool': prev_tool,
                'next_tool': next_tool,
                'status': 'pending'
            }

            if not self.dry_run:
                # First, make sure we're at prev_tool
                if current_tool != prev_tool:
                    print(f"  Setting up: switching to {prev_tool}")
                    self.send_gcode(f"Tn_action tool={prev_tool}")
                    time.sleep(5)  # Short wait
                    self.wait_for_idle()
                    current_tool = prev_tool

                # Now do the actual test: switch to next_tool
                print(f"  Executing: {prev_tool} -> {next_tool}")
                start_time = time.time()
                success = self.send_gcode(f"Tn_action tool={next_tool}")
                self.wait_for_idle()
                duration = time.time() - start_time

                test_record['duration'] = duration
                test_record['status'] = 'success' if success else 'failed'
                current_tool = next_tool if success else None

                print(f"  Duration: {duration:.1f}s")
            else:
                test_record['status'] = 'dry_run'

            self.collected_data.append(test_record)

        return self.collected_data

    def collect_first_load_data(self, tools=None):
        """
        Test first load (None -> tool) scenarios.
        """
        if tools is None:
            tools = ['T0A', 'T1A', 'T2A', 'T3A']

        print(f"\nCollecting first-load data for tools: {tools}")
        print("=" * 60)

        for tool in tools:
            print(f"\nTesting first load: None -> {tool}")

            test_record = {
                'timestamp': time.time(),
                'prev_tool': None,
                'next_tool': tool,
                'test_type': 'first_load',
                'status': 'pending'
            }

            if not self.dry_run:
                # Unload current tool first
                print("  Unloading current tool...")
                self.send_gcode("UNLOAD_FILAMENT")
                time.sleep(2)
                self.wait_for_idle()

                # Now load the test tool
                print(f"  Loading {tool}...")
                start_time = time.time()
                success = self.send_gcode(f"Tn_action tool={tool}")
                self.wait_for_idle()
                duration = time.time() - start_time

                test_record['duration'] = duration
                test_record['status'] = 'success' if success else 'failed'

                print(f"  Duration: {duration:.1f}s")
            else:
                test_record['status'] = 'dry_run'

            self.collected_data.append(test_record)

        return self.collected_data

    def save_results(self, filename='flush_data_collected.json'):
        """Save collected data to file."""
        output = {
            'collection_time': time.time(),
            'host': self.host,
            'data': self.collected_data
        }

        with open(filename, 'w') as f:
            json.dump(output, f, indent=2)

        print(f"\nResults saved to {filename}")

    def print_summary(self):
        """Print summary of collected data."""
        print("\n" + "=" * 60)
        print("COLLECTION SUMMARY")
        print("=" * 60)

        success_count = sum(1 for d in self.collected_data if d.get('status') == 'success')
        failed_count = sum(1 for d in self.collected_data if d.get('status') == 'failed')
        dry_run_count = sum(1 for d in self.collected_data if d.get('status') == 'dry_run')

        print(f"Total tests: {len(self.collected_data)}")
        print(f"  Success: {success_count}")
        print(f"  Failed: {failed_count}")
        print(f"  Dry-run: {dry_run_count}")

        if success_count > 0:
            durations = [d['duration'] for d in self.collected_data if d.get('duration')]
            print(f"\nDurations:")
            print(f"  Min: {min(durations):.1f}s")
            print(f"  Max: {max(durations):.1f}s")
            print(f"  Avg: {sum(durations)/len(durations):.1f}s")


def main():
    parser = argparse.ArgumentParser(
        description='Collect flush volume data from K2 Plus printer'
    )
    parser.add_argument('host', help='Printer IP address')
    parser.add_argument('--port', type=int, default=7125, help='Moonraker port (default: 7125)')
    parser.add_argument('--dry-run', action='store_true', help='Simulate without actually running commands')
    parser.add_argument('--tools', nargs='+', default=['T0A', 'T1A', 'T2A', 'T3A'],
                        help='Tools to test (default: T0A T1A T2A T3A)')
    parser.add_argument('--first-load-only', action='store_true',
                        help='Only test first-load scenarios')
    parser.add_argument('--changes-only', action='store_true',
                        help='Only test tool change scenarios (skip first load)')
    parser.add_argument('--output', default='flush_data_collected.json',
                        help='Output file for results')

    args = parser.parse_args()

    print("=" * 60)
    print("K2 Plus Flush Volume Data Collector")
    print("=" * 60)
    print(f"Host: {args.host}:{args.port}")
    print(f"Tools: {args.tools}")
    print(f"Dry run: {args.dry_run}")
    print()

    collector = FlushDataCollector(args.host, args.port)
    collector.dry_run = args.dry_run

    # Setup tracing
    collector.setup_tracing()
    input("Press Enter when capture client is ready...")

    try:
        # Run tests
        if not args.changes_only:
            collector.collect_first_load_data(args.tools)

        if not args.first_load_only:
            collector.collect_tool_change_data(args.tools)

        # Save and summarize
        collector.save_results(args.output)
        collector.print_summary()

        print("\nDone! Check capture files for trace data.")
        print("Look for 'get_flush_len' and 'calc_flushing_volume' calls.")

    except KeyboardInterrupt:
        print("\n\nInterrupted by user")
        collector.save_results(args.output)
        collector.print_summary()


if __name__ == '__main__':
    main()
