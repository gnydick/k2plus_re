#!/usr/bin/env python3 -u
"""
Trace capture client - connects to printer and captures streaming traces.

Part of the K2 Plus firmware reverse engineering toolkit.
Works with trace_hooks_streaming.py deployed on the printer.

Saves traces to separate files per object type in captures/ directory.

Created: 2024-12-30
Project: Creality K2 Plus Klipper Firmware Reconstruction

Usage:
    python3 trace_capture.py <printer-ip> [port]

Example:
    python3 trace_capture.py 192.168.1.100
    python3 trace_capture.py k2plus 9876
"""

import socket
import sys
import json
import time
import signal
import os
from datetime import datetime

# Force unbuffered output
sys.stdout.reconfigure(line_buffering=True)
sys.stderr.reconfigure(line_buffering=True)

class TraceCapture:
    def __init__(self, host, port=9876):
        self.host = host
        self.port = port
        self.session_id = datetime.now().strftime('%Y%m%d_%H%M%S')
        self.captures_dir = "captures"
        self.socket = None
        self.running = False
        self.events = []
        self.call_stack = {}  # Track in-flight calls

        # Per-object file handles: object_name -> file handle
        self.object_files = {}
        # Per-object event counts
        self.object_counts = {}
        # File for system/meta events (connected, trace_enabled, etc.)
        self.system_file = None

    def _ensure_captures_dir(self):
        """Create captures directory if it doesn't exist."""
        if not os.path.exists(self.captures_dir):
            os.makedirs(self.captures_dir)
            print(f"Created directory: {self.captures_dir}/")

    def _get_object_file(self, object_name):
        """Get or create file handle for an object type."""
        if object_name not in self.object_files:
            # Sanitize object name for filename
            safe_name = object_name.replace(' ', '_').replace('/', '_')
            filename = os.path.join(self.captures_dir, f"{safe_name}_{self.session_id}.jsonl")
            self.object_files[object_name] = open(filename, 'w')
            self.object_counts[object_name] = 0
            print(f"📁 New file: {filename}")
        return self.object_files[object_name]

    def _write_event(self, event, line):
        """Write event to appropriate file based on object type."""
        event_type = event.get('type', 'unknown')
        object_name = event.get('object', None)

        # System events go to system file
        if event_type in ('connected', 'trace_enabled', 'trace_disabled', 'traces_enabled', 'test'):
            if self.system_file is None:
                filename = os.path.join(self.captures_dir, f"_system_{self.session_id}.jsonl")
                self.system_file = open(filename, 'w')
                print(f"📁 System file: {filename}")
            self.system_file.write(line + '\n')
            self.system_file.flush()
        elif object_name:
            # Object-specific events
            f = self._get_object_file(object_name)
            f.write(line + '\n')
            f.flush()
            self.object_counts[object_name] = self.object_counts.get(object_name, 0) + 1
        else:
            # Unknown events go to system file
            if self.system_file is None:
                filename = os.path.join(self.captures_dir, f"_system_{self.session_id}.jsonl")
                self.system_file = open(filename, 'w')
            self.system_file.write(line + '\n')
            self.system_file.flush()

    def connect(self):
        """Connect to the printer's trace server."""
        print(f"Connecting to {self.host}:{self.port}...")
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.settimeout(30.0)  # Longer timeout
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
        try:
            self.socket.connect((self.host, self.port))
            self.socket.settimeout(None)
            self._ensure_captures_dir()
            print(f"Connected! Session: {self.session_id}")
            print(f"Saving to: {self.captures_dir}/<object>_{self.session_id}.jsonl")
            return True
        except Exception as e:
            print(f"Connection failed: {e}")
            return False

    def format_event(self, event):
        """Format event for console display."""
        event_type = event.get('type', 'unknown')

        if event_type == 'connected':
            traces = event.get('active_traces', [])
            if traces:
                return f"🔗 Connected - Active traces: {len(traces)}"
            return "🔗 Connected - No active traces (use TRACE_ALL on printer)"

        elif event_type == 'trace_enabled':
            return f"✅ Enabled: {event['class']}.{event['method']}"

        elif event_type == 'trace_disabled':
            return f"⛔ Disabled: {event['class']}.{event['method']}"

        elif event_type == 'traces_enabled':
            return f"✅ Enabled {event.get('total', '?')} traces on {event.get('objects', [])}"

        elif event_type == 'gcode_call':
            call_id = event['id']
            cmd = event.get('command', '?')
            params = event.get('params', '')
            self.call_stack[call_id] = event
            if params:
                return f"⚙️  #{call_id} GCODE {cmd} {params}"
            return f"⚙️  #{call_id} GCODE {cmd}"

        elif event_type == 'gcode_return':
            call_id = event['id']
            cmd = event.get('command', '?')
            duration = event.get('duration_ms', 0)
            self.call_stack.pop(call_id, None)
            return f"✅ #{call_id} GCODE {cmd} ({duration:.2f}ms)"

        elif event_type == 'gcode_error':
            call_id = event['id']
            cmd = event.get('command', '?')
            error = event.get('error', 'unknown')
            duration = event.get('duration_ms', 0)
            self.call_stack.pop(call_id, None)
            return f"❌ #{call_id} GCODE {cmd}: {error} ({duration:.2f}ms)"

        elif event_type == 'gcode_line':
            call_id = event['id']
            cmd = event.get('command', '?')
            return f"📜 #{call_id} GCODE_LINE: {cmd}"

        elif event_type == 'call':
            call_id = event['id']
            obj = event.get('object', '?')
            method = f"{event['class']}.{event['method']}"
            args = event.get('args', '')
            self.call_stack[call_id] = event

            # Truncate long args
            if len(args) > 80:
                args = args[:77] + '...'
            return f"📞 #{call_id} [{obj}] CALL {method}({args})"

        elif event_type == 'return':
            call_id = event['id']
            obj = event.get('object', '?')
            method = f"{event['class']}.{event['method']}"
            result = event.get('result', '')
            duration = event.get('duration_ms', 0)

            # Clean up call stack
            self.call_stack.pop(call_id, None)

            # Format result
            result_str = json.dumps(result) if not isinstance(result, str) else result
            if len(result_str) > 60:
                result_str = result_str[:57] + '...'

            return f"✅ #{call_id} [{obj}] RETURN {method} → {result_str} ({duration:.2f}ms)"

        elif event_type == 'error':
            call_id = event['id']
            obj = event.get('object', '?')
            method = f"{event['class']}.{event['method']}"
            error = event.get('error', 'unknown')
            duration = event.get('duration_ms', 0)

            self.call_stack.pop(call_id, None)

            return f"❌ #{call_id} [{obj}] ERROR {method}: {error} ({duration:.2f}ms)"

        else:
            return f"❓ {event_type}: {event}"

    def capture(self):
        """Main capture loop."""
        self.running = True
        buffer = ""

        print("\n" + "=" * 60)
        print("CAPTURING TRACES - Press Ctrl+C to stop")
        print("=" * 60 + "\n")

        while self.running:
            try:
                data = self.socket.recv(4096)
                if not data:
                    print("\nConnection closed by printer")
                    break

                buffer += data.decode('utf-8')

                # Process complete lines
                while '\n' in buffer:
                    line, buffer = buffer.split('\n', 1)
                    if line.strip():
                        try:
                            event = json.loads(line)
                            self.events.append(event)

                            # Write to appropriate file
                            self._write_event(event, line)

                            # Display formatted
                            formatted = self.format_event(event)
                            timestamp = datetime.now().strftime('%H:%M:%S.%f')[:-3]
                            print(f"[{timestamp}] {formatted}")

                        except json.JSONDecodeError as e:
                            print(f"Parse error: {e}")

            except socket.timeout:
                continue
            except KeyboardInterrupt:
                break
            except Exception as e:
                print(f"Error: {e}")
                break

        self.running = False
        self._cleanup()

    def _cleanup(self):
        """Close all file handles and socket."""
        if self.socket:
            self.socket.close()

        # Close all object files
        for name, f in self.object_files.items():
            try:
                f.close()
            except:
                pass

        if self.system_file:
            try:
                self.system_file.close()
            except:
                pass

        # Print summary
        print("\n" + "=" * 60)
        print("CAPTURE COMPLETE")
        print("=" * 60)
        print(f"Total events: {len(self.events)}")
        print(f"Session: {self.session_id}")

        # Count by type
        type_counts = {}
        for event in self.events:
            t = event.get('type', 'unknown')
            type_counts[t] = type_counts.get(t, 0) + 1

        print("\nEvent breakdown by type:")
        for t, count in sorted(type_counts.items()):
            print(f"  {t}: {count}")

        print("\nEvents by object:")
        for obj, count in sorted(self.object_counts.items(), key=lambda x: -x[1]):
            print(f"  {obj}: {count}")

        print(f"\nFiles written to: {self.captures_dir}/")

        # Show any incomplete calls
        if self.call_stack:
            print(f"\n⚠️  {len(self.call_stack)} calls still in progress when stopped")

    def stop(self):
        """Stop capturing."""
        self.running = False


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2]) if len(sys.argv) > 2 else 9876

    capture = TraceCapture(host, port)

    # Handle Ctrl+C gracefully
    def signal_handler(sig, frame):
        print("\n\nStopping capture...")
        capture.stop()

    signal.signal(signal.SIGINT, signal_handler)

    if capture.connect():
        capture.capture()


if __name__ == '__main__':
    main()
