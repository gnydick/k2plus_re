# Tracing

Runtime tracing and protocol capture from the K2 Plus printer.

## Structure

  Directory                        Description
  -------------------------------  ------------------------------------------------
  YYYYMMDD_HHMMSS_<description>/   Session directories with traces and analysis
  observations/                    Per-module observations from trace analysis
  scripts/                         Capture and tracing tools
  howto/                           Tool usage documentation

## Session Structure

Each session directory contains:

  File/Directory          Description
  ----------------------  ------------------------------------------------
  session.log             Human-readable session documentation
  sequence_diagrams.puml  PlantUML diagrams for discovered flows
  captures/               Raw JSONL trace files (auto-generated)

## Workflow

1. Create session directory under tracing/
2. Start trace capture from session directory
3. Execute tests and document in session.log
4. Analyze patterns and create PlantUML diagrams
5. Summarize findings in observations/<module>.md
6. When verified, promote to ../verified/

## Starting a Session

```bash
SESSION=tracing/$(date +%Y%m%d_%H%M%S)_<description>
mkdir -p $SESSION
cd $SESSION && python3 ../scripts/trace_capture.py k2plus 9876
```

## How To

See howto/tracing.md for detailed tracing workflow.
