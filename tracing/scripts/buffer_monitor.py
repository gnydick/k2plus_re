#!/usr/bin/env python3
"""
Buffer monitoring script for K2 Plus filament rack signaling.
Monitors:
1. Raw serial traffic on /dev/ttyS5 (RS-485)
2. GPIO PA5 state changes (filament_rack not_pin)
3. Additional serial traffic on /dev/ttyS7 (main MCU)

Run on the printer: python3 buffer_monitor.py
"""

import os
import sys
import time
import threading
import select
import struct
from datetime import datetime

# Output file
OUTPUT_FILE = "/tmp/buffer_monitor.log"

class SerialMonitor(threading.Thread):
    """Monitor raw serial port traffic."""

    def __init__(self, port, name, output_func):
        super().__init__(daemon=True)
        self.port = port
        self.name = name
        self.output = output_func
        self.running = True
        self.fd = None

    def run(self):
        try:
            # Open port in raw mode
            self.fd = os.open(self.port, os.O_RDONLY | os.O_NONBLOCK)
            self.output(f"[{self.name}] Monitoring {self.port}")

            while self.running:
                try:
                    r, _, _ = select.select([self.fd], [], [], 0.1)
                    if r:
                        data = os.read(self.fd, 4096)
                        if data:
                            hex_data = data.hex()
                            ts = datetime.now().strftime("%H:%M:%S.%f")[:-3]
                            self.output(f"[{ts}] [{self.name}] RX {len(data)}B: {hex_data}")
                except BlockingIOError:
                    pass
                except Exception as e:
                    self.output(f"[{self.name}] Read error: {e}")
                    time.sleep(0.5)
        except Exception as e:
            self.output(f"[{self.name}] Failed to open {self.port}: {e}")
        finally:
            if self.fd:
                os.close(self.fd)

    def stop(self):
        self.running = False


class GPIOMonitor(threading.Thread):
    """Monitor GPIO pin state changes."""

    def __init__(self, gpio_num, name, output_func):
        super().__init__(daemon=True)
        self.gpio_num = gpio_num
        self.name = name
        self.output = output_func
        self.running = True
        self.gpio_path = f"/sys/class/gpio/gpio{gpio_num}"
        self.last_value = None

    def _export_gpio(self):
        """Export GPIO if not already exported."""
        if not os.path.exists(self.gpio_path):
            try:
                with open("/sys/class/gpio/export", "w") as f:
                    f.write(str(self.gpio_num))
                time.sleep(0.1)
                self.output(f"[{self.name}] Exported GPIO {self.gpio_num}")
            except Exception as e:
                self.output(f"[{self.name}] Export failed: {e}")
                return False
        return True

    def run(self):
        if not self._export_gpio():
            # Try common GPIO numbers for PA5
            for try_gpio in [5, 32+5, 64+5, 128+5, 160+5, 192+5]:
                self.gpio_num = try_gpio
                self.gpio_path = f"/sys/class/gpio/gpio{try_gpio}"
                if self._export_gpio():
                    break
            else:
                self.output(f"[{self.name}] Could not find/export GPIO for PA5")
                return

        value_path = f"{self.gpio_path}/value"

        try:
            self.output(f"[{self.name}] Monitoring GPIO {self.gpio_num}")

            while self.running:
                try:
                    with open(value_path, "r") as f:
                        value = f.read().strip()

                    if value != self.last_value:
                        ts = datetime.now().strftime("%H:%M:%S.%f")[:-3]
                        if self.last_value is not None:
                            self.output(f"[{ts}] [{self.name}] GPIO {self.gpio_num}: {self.last_value} -> {value}")
                        self.last_value = value

                except Exception as e:
                    pass

                time.sleep(0.01)  # 10ms polling

        except Exception as e:
            self.output(f"[{self.name}] Error: {e}")

    def stop(self):
        self.running = False


class StraceMonitotr(threading.Thread):
    """Monitor serial syscalls via strace on klippy process."""

    def __init__(self, pid, output_func):
        super().__init__(daemon=True)
        self.pid = pid
        self.output = output_func
        self.running = True
        self.proc = None

    def run(self):
        import subprocess

        try:
            # Attach strace to klippy, filtering for read/write on ttyS*
            cmd = [
                "strace", "-p", str(self.pid),
                "-e", "trace=read,write",
                "-e", "read=3,4,5,6,7,8,9,10",  # Common FDs for serial
                "-e", "write=3,4,5,6,7,8,9,10",
                "-s", "256",
                "-t",
            ]

            self.output(f"[STRACE] Attaching to PID {self.pid}")
            self.proc = subprocess.Popen(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True
            )

            for line in self.proc.stdout:
                if not self.running:
                    break
                if "ttyS" in line or ("read" in line and "=" in line) or ("write" in line and "=" in line):
                    line = line.strip()
                    if len(line) > 10:
                        ts = datetime.now().strftime("%H:%M:%S.%f")[:-3]
                        self.output(f"[{ts}] [STRACE] {line}")

        except Exception as e:
            self.output(f"[STRACE] Error: {e}")
        finally:
            if self.proc:
                self.proc.terminate()

    def stop(self):
        self.running = False
        if self.proc:
            self.proc.terminate()


def main():
    print(f"Buffer Monitor starting - logging to {OUTPUT_FILE}")

    # Output function that writes to both console and file
    log_file = open(OUTPUT_FILE, "w", buffering=1)

    def output(msg):
        print(msg)
        log_file.write(msg + "\n")
        log_file.flush()

    output(f"=== Buffer Monitor Started {datetime.now()} ===")

    # Find klippy PID
    klippy_pid = None
    try:
        import subprocess
        result = subprocess.run(["pgrep", "-f", "klippy.py"], capture_output=True, text=True)
        if result.stdout.strip():
            klippy_pid = int(result.stdout.strip().split()[0])
            output(f"Found klippy PID: {klippy_pid}")
    except:
        pass

    monitors = []

    # 1. Serial monitor on ttyS5 (RS-485)
    # Note: This may fail if port is exclusively locked by klippy
    # monitors.append(SerialMonitor("/dev/ttyS5", "ttyS5", output))

    # 2. GPIO monitor for PA5
    monitors.append(GPIOMonitor(5, "PA5", output))

    # 3. Strace monitor (if we have klippy PID)
    if klippy_pid:
        monitors.append(StraceMonitotr(klippy_pid, output))

    # Start all monitors
    for m in monitors:
        m.start()

    output("Monitors started. Press Ctrl+C to stop.")
    output("Now extrude filament to see buffer signaling...")

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        output("\nStopping monitors...")
        for m in monitors:
            m.stop()
        for m in monitors:
            m.join(timeout=2)

    output(f"=== Buffer Monitor Stopped {datetime.now()} ===")
    log_file.close()


if __name__ == "__main__":
    main()
