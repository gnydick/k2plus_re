# K2 Plus Firmware Reverse Engineering

Reverse engineering project for Creality K2 Plus 3D printer firmware.

## Project Structure

```
k2plus/
├── re/                  # Reverse engineering
│   ├── from_printer/    # Binaries from device
│   ├── decompiled/      # Ghidra output
│   ├── introspection/   # Runtime inspection dumps
│   ├── observations/    # Observations & theories
│   └── reconstructed/   # Reconstructed Python code
│
├── tracing/             # Runtime tracing
│   ├── captures/        # Raw JSONL trace files
│   ├── observations/    # Observations from traces
│   └── scripts/         # Tracing scripts
│
├── tests/               # Test plans
│   ├── *.md             # Test procedures & inventories
│   └── test_scripts.py  # REPL test helpers
│
└── verified/            # Verified & confirmed
    ├── docs/            # Verified documentation
    └── src/             # Tested implementations
```

## Workflow

```
re/observations/        ─┐
                         ├─→ tests/  ─→ verified/{docs,src}
tracing/observations/   ─┘
```

1. **Observe** → Record findings in `*/observations/`
2. **Test** → Create test plans in `tests/`
3. **Verify** → Promote passing tests to `verified/`

## Setup

```bash
cd re/
git clone https://github.com/CrealityOfficial/K2_Series_Klipper.git
```
