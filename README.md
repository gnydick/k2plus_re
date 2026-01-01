# K2 Plus Firmware Reverse Engineering

Reverse engineering project for Creality K2 Plus 3D printer firmware (Klipper fork with proprietary Cython modules).

## Discovery Pipeline

Information flows through three stages, with increasing confidence:

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   tracing/  │ ──▶ │     re/     │ ──▶ │  verified/  │
│  DISCOVERED │     │  THEORIZED  │     │    FACT     │
└─────────────┘     └─────────────┘     └─────────────┘
```

| Stage | Directory | Confidence | Contents |
|-------|-----------|------------|----------|
| **Discovered** | `tracing/` | Raw observations | Trace captures, raw protocol data |
| **Theorized** | `re/` | Interpreted but unverified | Decompiled code, reconstructed logic, analysis |
| **Fact** | `verified/` | Tested and confirmed | Verified protocols, working implementations |

## Directory Structure

```
k2plus/
├── tracing/              # Stage 1: Raw discoveries
│   ├── captures/         # JSONL trace files
│   ├── scripts/          # Capture tools
│   └── docs/             # Trace methodology
│
├── re/                   # Stage 2: Analysis & theory
│   ├── K2_Series_Klipper/  # (clone the source repo here)
│   ├── from_printer/     # Binaries pulled from device
│   ├── decompiled/       # Ghidra C output
│   ├── reconstructed/    # Our Python reconstructions
│   ├── introspection/    # Runtime inspection data
│   ├── ghidra/           # RE project files
│   ├── tools/            # Analysis scripts
│   └── docs/             # RE documentation
│
└── verified/             # Stage 3: Confirmed facts
    ├── docs/             # Verified documentation
    ├── test_plan/        # Test protocols & results
    └── src/              # Tested implementations
```

## Promotion Criteria

### Discovered → Theorized
- Raw trace data has been analyzed
- Patterns identified and documented
- Hypotheses formed about behavior

### Theorized → Fact
- Hypothesis tested against live system
- Behavior reproduced independently
- Edge cases verified
- Documentation includes actual captured traces

## Setup

```bash
# Clone the Creality Klipper source into re/
cd re/
git clone https://github.com/CrealityOfficial/K2_Series_Klipper.git
```

## Key Documents

| Document | Location | Stage |
|----------|----------|-------|
| Trace Analysis | `tracing/captures/ANALYSIS.md` | Discovered |
| Protocol RE | `re/docs/serial_485_protocol.md` | Theorized |
| Verified Protocol | `verified/test_plan/serial_protocol.md` | Fact |
