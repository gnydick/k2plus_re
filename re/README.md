# Reverse Engineering

Analysis and reconstruction of K2 Plus firmware.

## Structure

| Type | Location | Description |
|------|----------|-------------|
| **Discovery** | `from_printer/` | Binaries pulled from device |
| **Discovery** | `decompiled/` | Ghidra C output |
| **Discovery** | `introspection/` | Runtime dir() results |
| **Analysis** | `docs/` | Best theories about firmware behavior |
| **Analysis** | `reconstructed/` | Reconstructed Python code |
| **Tools** | `ghidra/`, `tools/` | RE tools and scripts |

## Setup

```bash
git clone https://github.com/CrealityOfficial/K2_Series_Klipper.git
```

## Workflow

1. Pull binaries, run Ghidra, inspect runtime → discovery directories
2. Analyze and theorize → document in `docs/`, code in `reconstructed/`
3. When verified through testing → promote to `../verified/`

## Promotion to verified/

Move to `verified/` when:
- [ ] Hypothesis tested against live system
- [ ] Behavior matches prediction
- [ ] Evidence from traces supports conclusion
