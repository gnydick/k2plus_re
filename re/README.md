# Reverse Engineering - Stage 2: Theorized

Analysis, interpretation, and reconstruction of firmware behavior. This is the **theory** stage - data here represents our best understanding but is not yet verified.

## Confidence Level: MEDIUM
- Interpretations based on evidence
- May contain errors or misunderstandings
- Useful for guiding verification efforts
- Should be tested before trusting

## Contents

| Directory | Purpose | Source |
|-----------|---------|--------|
| `K2_Series_Klipper/` | Creality source repo (clone it here) | GitHub |
| `from_printer/` | Binaries pulled from device | Device |
| `decompiled/` | Ghidra C output | Ghidra |
| `reconstructed/` | Our Python reconstructions | Analysis |
| `introspection/` | Runtime `dir()` output, method lists | Live inspection |
| `ghidra/` | Ghidra projects and scripts | RE tools |
| `tools/` | Analysis scripts | Our work |
| `docs/` | RE documentation and analysis | Our work |

## Setup

```bash
git clone https://github.com/CrealityOfficial/K2_Series_Klipper.git
```

## Inputs (from `tracing/`)

- Raw JSONL trace captures
- Protocol packet captures
- Method call sequences

## Outputs (to `verified/`)

When a theory is confirmed through testing, document it in `verified/`:
- Protocol specifications → `verified/test_plan/`
- Working implementations → `verified/src/`
- Confirmed behavior → `verified/docs/`

## Promotion to `verified/` (Fact)

Move information to `verified/` when:
- [ ] Hypothesis tested against live system
- [ ] Behavior reproduced with controlled inputs
- [ ] At least 3 captured traces confirm the behavior
- [ ] Edge cases documented
- [ ] No contradicting evidence found

## Key Documents

| Document | Purpose |
|----------|---------|
| `docs/CODEBASE_MAP.md` | Overview of firmware structure |
| `docs/serial_485_protocol.md` | RS-485 protocol analysis |
| `docs/ALGORITHMS.md` | Reverse-engineered algorithms |
| `docs/SYMBOL_MAP.md` | Function symbol mappings |
| `introspection/*.txt` | Method lists from live inspection |
