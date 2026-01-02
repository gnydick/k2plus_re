# Reverse Engineering

Analysis and reconstruction of K2 Plus firmware.

## Structure

| Directory | Description |
|-----------|-------------|
| `from_printer/` | Binaries pulled from device |
| `decompiled/` | Ghidra C output |
| `introspection/` | Runtime dir() results |
| `observations/` | Per-module observations and theories |
| `reconstructed/` | Reconstructed Python code |
| `ghidra/` | Ghidra projects |
| `tools/` | RE scripts |
| `howto/` | Tool usage documentation |

## Setup

```bash
git clone https://github.com/CrealityOfficial/K2_Series_Klipper.git
```

## Workflow

1. Pull binaries, run Ghidra, inspect runtime → discovery directories
2. Analyze and theorize → `observations/`, code in `reconstructed/`
3. Create test plan → `../tests/`
4. When verified → promote to `../verified/`

## How To

- [howto/tools.md](howto/tools.md) - RE tools and scripts usage
