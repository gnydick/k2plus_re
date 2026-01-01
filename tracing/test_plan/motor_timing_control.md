# Motor Timing Control Test Plan

## Status: UNVERIFIED

Based on T2A load trace analysis (2026-01-01).

## Hypothesis

FF10 subcmd 0x06 starts continuous motor feed, subcmd 0x07 stops it.

| Subcmd | Behavior | Duration Control |
|--------|----------|------------------|
| 0x05   | Short movement, returns encoder position | **UNKNOWN** - see below |
| 0x06   | **Starts continuous feed** - motor runs until explicitly stopped | None - runs indefinitely |
| 0x07   | **Stop command** - halts motor | Immediate stop |

### Subcmd 0x05: Behavior Unknown

All observed 0x05 calls use identical parameters:
```
02 06 ff 10 01 05 00
                  ^^-- param=0x00 for ALL calls
```

**Observed behavior:**
- User heard very short stutter sounds (milliseconds, not seconds)
- Command durations: 24-135ms (first call longer, subsequent ~24-30ms)
- **~2s gaps between 0x05 calls - UNEXPLAINED**

**Timeline contradiction:**
```
787.302 - 0x05 #1 (135ms)
789.447 - 0x05 #2 (28ms)   ← 2.1s gap
791.484 - 0x05 #3 (30ms)   ← 2.0s gap
793.525 - 0x05 #4 (24ms)   ← 2.0s gap
795.558 - 0x05 #5 (24ms)   ← 2.0s gap
795.664 - 0x06 (29ms)      ← 0.1s gap
800.040 - 0x07 (56ms)      ← 4.4s gap (long continuous move)
```

- Total trace time: ~12.7 seconds
- Audible motor time: stutters (milliseconds each) + long move (~4s) ≈ 5s max
- **~8 seconds unaccounted for**

**Possible explanations for 2s gaps (all unverified):**
1. Motor actually runs for ~2s each 0x05 (stutter sound = start/stop clicks?)
2. Gaps contain filament sensing/verification (waiting for engagement?)
3. Filtered A2/FF0A polling commands control motor timing
4. Firmware internal delays/state machine transitions
5. Trace timing is misleading (async command completion?)

**What we DON'T know:**
- What controls 0x05 movement duration/distance
- What happens during the ~2s gaps
- Whether param byte (0x00) affects behavior
- Whether filtered commands are involved in motor control

## FF10 Command Structure

### TX Format
```
[addr] [len] ff 10 [variant] [subcmd] [param]
```

| Byte | Field | Description |
|------|-------|-------------|
| 0 | addr | Device address (01-04 for boxes) |
| 1 | len | Payload length (always 0x06 for FF10) |
| 2-3 | cmd | Command ID (0xFF 0x10) |
| 4 | variant | Slot selector: 0x01=A, 0x02=B, 0x03=C, 0x04=D |
| 5 | subcmd | Subcommand (see table below) |
| 6 | param | Parameter for subcmd |

### Subcommand Details

| Subcmd | Param | Full TX Bytes (Box 2, Slot A) | Purpose | Response |
|--------|-------|-------------------------------|---------|----------|
| 0x00 | 0x00 | `02 06 ff 10 01 00 00` | Initialize/reset | `f7 02 04 00 10 00 0f` (status=0x0F) |
| 0x04 | 0x00 | `02 06 ff 10 01 04 00` | Pre-feed preparation | `f7 02 03 00 10 cd` (ack) |
| 0x05 | 0x00 | `02 06 ff 10 01 05 00` | Short movement (limiting mechanism unknown) | `f7 02 07 00 10 [encoder_4bytes]` |
| 0x06 | 0x00 | `02 06 ff 10 01 06 00` | Start continuous feed | `f7 02 03 00 10 cd` (ack) |
| 0x07 | 0x03 | `02 06 ff 10 01 07 03` | Stop motor / complete | `f7 02 03 00 10 cd` (ack) |

### RX Response Format
```
f7 [addr] [len] 00 10 [payload...] [checksum]
```

| Response Type | Bytes | Description |
|---------------|-------|-------------|
| Status | `f7 02 04 00 10 00 0f` | 4-byte payload, status=0x0F |
| Ack | `f7 02 03 00 10 cd` | 3-byte payload, simple ack |
| Encoder | `f7 02 07 00 10 c4 XX XX XX` | 7-byte payload with encoder position |

### Address Reference

| Address | Box/Slot |
|---------|----------|
| 0x01 | Box 1 (T1A/T1B) |
| 0x02 | Box 2 (T2A/T2B) |
| 0x03 | Box 3 (T3A/T3B) |
| 0x04 | Box 4 (T4A/T4B) |

### Variant (Slot) Reference

| Variant | Slot |
|---------|------|
| 0x01 | Slot A |
| 0x02 | Slot B |
| 0x03 | Slot C (if exists) |
| 0x04 | Slot D (if exists) |

## Observed 0x05 Pulse Timings

From T2A load trace, subcmd 0x05 was called 5 times:

| Call # | TX Bytes | Duration | Response (Encoder) | Gap to Next |
|--------|----------|----------|-------------------|-------------|
| 1 | `02 06 ff 10 01 05 00` | 135ms | `f7 02 07 00 10 c4 12 ce 55 30` | ~2.1s |
| 2 | `02 06 ff 10 01 05 00` | 28ms | `f7 02 07 00 10 c4 5d cc ea ef` | ~2.0s |
| 3 | `02 06 ff 10 01 05 00` | 30ms | `f7 02 07 00 10 c4 96 38 f4 94` | ~2.0s |
| 4 | `02 06 ff 10 01 05 00` | 24ms | `f7 02 07 00 10 c4 bd 85 24 a3` | ~2.0s |
| 5 | `02 06 ff 10 01 05 00` | 24ms | `f7 02 07 00 10 c4 e4 c7 7c 43` | ~0.1s |

**Notes:**
- Command duration: 24-135ms (first longer, subsequent ~24-30ms)
- **~2s gaps between calls - purpose UNKNOWN**
- Encoder bytes change between calls = movement occurs
- All calls use param=0x00 - unknown if param controls behavior
- Motor movements were audibly very short (milliseconds)
- **Timeline doesn't add up** - 12.7s trace time vs ~5s audible motor time

## Evidence

- T2A load trace shows 0x06 followed by ~4.3s gap, then 0x07
- Subcmd 0x05 calls are very short (24-135ms) and return encoder data
- Previous motor tests ran indefinitely - likely missing the 0x07 stop command
- User reported audible "stutter steps" matching the 5x short 0x05 pulses
- **0x05 limiting mechanism is unknown** - all calls use identical param=0x00

## Observed Load Sequence

```
Subcmd    Duration   Notes
------    --------   -----
010000    4,482ms    INIT (long wait for ready)
010400       42ms    PRE-FEED
010500      135ms    FEED PULSE 1 (stutter)
010500       28ms    FEED PULSE 2 (stutter)
010500       30ms    FEED PULSE 3 (stutter)
010500       24ms    FEED PULSE 4 (stutter)
010500       24ms    FEED PULSE 5 (stutter)
010600       29ms    START CONTINUOUS FEED
... ~4.3s gap ...    (motor running)
010703       56ms    STOP / COMPLETE
```

## Test Procedure

### Test 1: Controlled Motor Run (Start/Stop)

1. Ensure box is not in error state
2. Send initialization:
   ```
   02 06 ff 10 01 00 00    (init)
   ```
3. Send start feed:
   ```
   02 06 ff 10 01 06 00    (start continuous feed)
   ```
4. Wait exactly 2 seconds
5. Send stop:
   ```
   02 06 ff 10 01 07 03    (stop motor)
   ```
6. **Expected:** Motor runs only during the 2-second window

### Test 2: Missing Stop Command

1. Send start feed without stop command
2. **Expected:** Motor runs indefinitely (or until timeout/sensor)
3. Use FF08 or emergency stop to halt if needed

### Test 3: Investigate 0x05 Behavior and Timing Gaps

**Part A: Single 0x05 timing**
1. Send single 0x05 command:
   ```
   02 06 ff 10 01 05 00
   ```
2. Measure: Command duration AND audible motor run time
3. Question: Does motor run only during command, or longer?
4. Record: Encoder delta from response

**Part B: Test param byte effect**
1. Send 0x05 with param=0x01:
   ```
   02 06 ff 10 01 05 01
   ```
2. Send 0x05 with param=0x02:
   ```
   02 06 ff 10 01 05 02
   ```
3. Send 0x05 with param=0x10:
   ```
   02 06 ff 10 01 05 10
   ```
4. Compare: Duration, motor run time, and encoder delta for each
5. Determine: Does param control movement?

**Part C: Investigate 2s gaps**
1. Enable full serial trace: `TRACE_SERIAL_POLLING ENABLE=1`
2. Trigger a load sequence (T2A or similar)
3. Examine: What commands occur during the ~2s gaps between 0x05 calls?
4. Check: Are A2/FF0A commands involved in motor control/timing?

**Part D: Measure actual movement**
1. Mark filament position
2. Send 5x 0x05 commands with 2s delays between (matching trace timing)
3. Measure total filament movement
4. Compare: Movement with vs without 2s delays
5. Determine: Does timing between commands affect total movement?

## Success Criteria

- [ ] Test 1: Motor runs for specified duration and stops on 0x07 command
- [ ] Test 2: Motor runs indefinitely without 0x07 (confirms 0x06/0x07 hypothesis)
- [ ] Test 3A: Determine relationship between command duration and motor run time
- [ ] Test 3B: Determine if param byte controls movement
- [ ] Test 3C: Explain what happens during ~2s gaps (filtered commands? firmware delays?)
- [ ] Test 3D: Measure actual filament distance and timing dependency

## Source Trace

`tracing/captures/captures/serial_485_serial485_20260101_105436.jsonl`
