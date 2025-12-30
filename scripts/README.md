# K2 Plus Firmware Reverse Engineering Scripts

Tools for reverse engineering Creality K2 Plus Klipper firmware from compiled Cython modules.

## Overview

| Script | Purpose |
|--------|---------|
| `trace_hooks_streaming.py` | Klipper extra - wraps methods, streams traces over TCP |
| `trace_capture.py` | Capture client - saves streaming traces to JSONL files |
| `introspect_modules.py` | Extract method signatures from live printer |
| `compare_signatures.py` | Compare live signatures vs reconstructed code |
| `generate_stubs.py` | Generate Python stubs from introspection data |
| `merge_signatures.py` | Merge accurate signatures with implementations |
| `capture_rs485.py` | Capture raw RS-485 serial traffic |

## Live Tracing (Primary Method)

### Setup

1. **Deploy trace_hooks to printer:**
   ```bash
   scp trace_hooks_streaming.py root@<printer-ip>:/usr/share/klipper/klippy/extras/trace_hooks.py
   ```

2. **Add to printer.cfg:**
   ```ini
   [trace_hooks]
   stream_port: 9876
   ```

3. **Restart Klipper**

### Capture Workflow

```bash
# Terminal 1: Start capture client
python3 trace_capture.py <printer-ip>

# Klipper console: Enable tracing
TRACE_DEEP OBJECT=box                    # Trace all methods including _private
TRACE_ATTRS OBJECT=box ENABLE=1          # Trace attribute access
TRACE_ATTRS OBJECT=box ENABLE=1 RECURSIVE=1  # Recursive attr tracing

# Trigger operations on printer...

# Terminal 1: Ctrl+C to stop and save
```

### Output Files

Captures saved to `captures/` directory:
- `box_<timestamp>.jsonl` - Box module traces
- `prtouch_v3_<timestamp>.jsonl` - PRTouch traces
- `serial_485_serial485_<timestamp>.jsonl` - RS-485 traces
- `_system_<timestamp>.jsonl` - Connection metadata

### Trace Commands Reference

See [TRACE_HOOKS_README.md](TRACE_HOOKS_README.md) for full command reference.

---

## Introspection (Secondary Method)

For extracting accurate method signatures without runtime tracing.

### Step 1: Run on Printer

```bash
scp introspect_modules.py root@<printer-ip>:/tmp/
ssh root@<printer-ip> 'python3 /tmp/introspect_modules.py' > module_dump.json
```

### Step 2: Generate Stubs

```bash
python3 generate_stubs.py module_dump.json stubs/
```

### Step 3: Compare with Reconstructed

```bash
python3 compare_signatures.py module_dump.json reconstructed/
```

---

## RS-485 Protocol Capture

For low-level protocol analysis:

```bash
# On printer
python3 capture_rs485.py /dev/ttyS1 > rs485_traffic.log
# Trigger operations, Ctrl+C to stop
```

---

## Directory Structure

```
scripts/
├── trace_hooks_streaming.py  # Deploy to printer as trace_hooks.py
├── trace_capture.py          # Run on workstation
├── introspect_modules.py     # Run on printer
├── compare_signatures.py     # Run on workstation
├── generate_stubs.py         # Run on workstation
├── merge_signatures.py       # Run on workstation
├── capture_rs485.py          # Run on printer
├── README.md                 # This file
└── TRACE_HOOKS_README.md     # Detailed tracing documentation
```

---

## Prerequisites

- SSH access to K2 Plus printer
- Python 3.9+ on both machines
- Network connectivity between workstation and printer

---

## Quick Start

```bash
# 1. Deploy tracing
scp trace_hooks_streaming.py root@k2plus:/usr/share/klipper/klippy/extras/trace_hooks.py
# Add [trace_hooks] to printer.cfg and restart Klipper

# 2. Start capture
python3 trace_capture.py k2plus

# 3. Enable traces (in Klipper console)
TRACE_DEEP OBJECT=box
TRACE_ATTRS OBJECT=box ENABLE=1

# 4. Trigger operations, then Ctrl+C to stop capture

# 5. Analyze
cat captures/box_*.jsonl | grep calc_flushing
```
