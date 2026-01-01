# Tracing - Stage 1: Discovered

Raw observations from runtime tracing and protocol capture. This is the **discovery** stage - data here is uninterpreted.

## Confidence Level: LOW
- Raw captures, no interpretation
- May contain noise or irrelevant data
- Timestamps and sequences are factual
- Meaning is not yet determined

## Contents

| Directory | Purpose |
|-----------|---------|
| `captures/` | JSONL trace files from live printer |
| `scripts/` | Tracing tools (trace_hooks, capture clients) |
| `docs/` | Tracing methodology and tool usage |

## Workflow

1. Deploy `scripts/trace_hooks_streaming.py` to printer
2. Run `scripts/trace_capture.py` to collect traces
3. Raw data lands in `captures/`
4. Initial observations documented in `captures/ANALYSIS.md`

## Promotion to `re/` (Theorized)

Move information to `re/docs/` when:
- [ ] Patterns have been identified in multiple traces
- [ ] A hypothesis exists about what the data means
- [ ] The observation is reproducible

## Key Files

- `captures/ANALYSIS.md` - Running analysis of captured data
- `scripts/trace_hooks_streaming.py` - Klipper extra for method tracing
- `scripts/trace_capture.py` - TCP client for capturing traces
- `docs/TRACE_HOOKS_README.md` - Tracing command reference
