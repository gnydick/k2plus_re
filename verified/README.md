# Verified - Stage 3: Fact

Tested and confirmed information. This is the **trusted** stage - data here has been verified through controlled testing.

## Confidence Level: HIGH
- Tested against live system
- Behavior is reproducible
- Includes actual captured traces as evidence
- Safe to build upon

## Contents

| Directory | Purpose |
|-----------|---------|
| `docs/` | Verified documentation |
| `test_plan/` | Test protocols and verified results |
| `src/` | Tested, working implementations |

## Requirements for Inclusion

Information in this directory MUST have:
1. **Evidence**: At least 3 captured traces demonstrating behavior
2. **Reproducibility**: Can be triggered on demand
3. **Testing**: Verified through controlled experiments
4. **Documentation**: Clear description with examples

## Verification Checklist

Before adding content here, confirm:
- [ ] Behavior observed in multiple trace sessions
- [ ] Input → Output relationship documented
- [ ] Edge cases tested
- [ ] Failure modes documented (if applicable)
- [ ] Actual TX/RX traces included in documentation
- [ ] No contradicting evidence from other traces

## Key Documents

| Document | Purpose |
|----------|---------|
| `test_plan/serial_protocol.md` | Verified RS-485 protocol with traces |
| `test_plan/motor_control.md` | Motor control command verification |
| `test_plan/gcode_commands.md` | G-code command mappings |
| `docs/filament_rack.md` | Verified filament rack behavior |

## Regression

If new evidence contradicts verified information:
1. Add note to affected document with new evidence
2. Move contradicted claims back to `re/docs/` for re-analysis
3. Update this README if major changes needed
