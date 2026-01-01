# Tracing

Runtime tracing and protocol capture from the K2 Plus printer.

## Structure

| Type | Location | Description |
|------|----------|-------------|
| **Discovery** | `captures/` | Raw JSONL trace files |
| **Analysis** | `captures/ANALYSIS.md` | Best theories about trace data |
| **Tools** | `scripts/` | Capture and tracing tools |
| **Docs** | `docs/` | Tool usage documentation |

## Workflow

1. Capture raw traces → `captures/*.jsonl`
2. Analyze patterns → document in `captures/ANALYSIS.md`
3. When verified through testing → promote to `../verified/`

## Promotion to verified/

Move to `verified/` when:
- [ ] Behavior reproduced with controlled inputs
- [ ] At least 3 traces confirm the pattern
- [ ] TX/RX examples documented
