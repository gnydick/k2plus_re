# Trace Captures

Each subdirectory is a capture session. Sessions are named: `YYYYMMDD_HHMMSS_<description>`

## Sessions

| Session | Description | Key Findings |
|---------|-------------|--------------|
| [20260101_105436_t2a_load_unload](20260101_105436_t2a_load_unload/) | T2A load/unload test | FF10=load, FF11=unload, timing gaps |

## Session Structure

Each session directory contains:
- `session.log` - Session documentation (purpose, actions, findings)
- `*.jsonl` - Captured trace files per object/component

## Top-Level Files

- `ANALYSIS.md` - Cumulative analysis across all sessions
