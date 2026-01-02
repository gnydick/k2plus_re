# Tracing

Runtime tracing and protocol capture from the K2 Plus printer.

## Structure

| Directory | Description |
|-----------|-------------|
| `captures/` | Session subdirectories with raw JSONL trace files |
| `observations/` | Per-module observations from trace analysis |
| `scripts/` | Capture and tracing tools |
| `howto/` | Tool usage documentation |

## Workflow

1. Capture raw traces → `captures/<session>/`
2. Analyze patterns → document in `observations/<module>.md`
3. Create test plan → `../tests/`
4. When verified → promote to `../verified/`

## How To

- [howto/tracing.md](howto/tracing.md) - Tracing commands and capture workflow
