# Verified

Confirmed facts from tracing and RE efforts. Content promoted here after passing tests.

## Structure

| Directory | Description |
|-----------|-------------|
| `docs/` | Verified documentation with trace evidence |
| `src/` | Tested, working implementations |

## Workflow

```
re/observations + tracing/observations → tests/ → verified/
```

Findings start as observations, get converted to test plans, and are promoted here when tests pass.

## Requirements

Content here MUST have:
1. **Evidence**: Captured traces demonstrating behavior
2. **Reproducibility**: Can trigger on demand
3. **Test Coverage**: Corresponding test in `tests/` passed

## Verification Checklist

- [ ] Behavior observed in 3+ sessions
- [ ] Input → Output documented
- [ ] Actual packet traces included
- [ ] No contradicting evidence
- [ ] Test plan in `tests/` passed
