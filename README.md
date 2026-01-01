# K2 Plus Firmware Reverse Engineering

Reverse engineering project for Creality K2 Plus 3D printer firmware.

## Project Structure

```
k2plus/
├── tracing/           # Runtime traces
│   ├── captures/      # Discovery: raw JSONL traces
│   └── (ANALYSIS.md)  # Analysis: theories about traces
│
├── re/                # Reverse engineering
│   ├── from_printer/  # Discovery: binaries from device
│   ├── decompiled/    # Discovery: Ghidra output
│   ├── introspection/ # Discovery: runtime inspection
│   ├── docs/          # Analysis: theories about behavior
│   └── reconstructed/ # Analysis: reconstructed code
│
└── verified/          # Confirmed facts
    ├── test_plan/     # Verified protocols
    ├── docs/          # Verified documentation
    └── src/           # Tested implementations
```

## Workflow

1. **Discover** → Raw data in `tracing/captures/` and `re/` discovery dirs
2. **Analyze** → Best theories in `tracing/ANALYSIS.md` and `re/docs/`
3. **Verify** → Confirmed facts promoted to `verified/`

## Setup

```bash
cd re/
git clone https://github.com/CrealityOfficial/K2_Series_Klipper.git
```
