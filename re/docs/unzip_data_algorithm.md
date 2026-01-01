# unzip_data Compression Algorithm

Reverse-engineered from Creality K2 Plus Klipper firmware traces.

## Provenance

| Field              | Value                                                                |
|--------------------|----------------------------------------------------------------------|
| **Printer**        | Creality K2 Plus                                                     |
| **Firmware**       | Klipper (Creality fork)                                              |
| **Source**         | Compiled Cython modules (`klippy/extras/*.cpython-39.so`)            |
| **Method**         | Runtime tracing via `trace_hooks_streaming.py` injected into Klipper |
| **Capture Dates**  | 2024-12-30                                                           |
| **Capture Files**  | `../../tracing/captures/prtouch_v3_prtouch_*.jsonl`                  |
| **Primary Module** | `prtouch_v3.cpython-39.so` (`PRTouchEndstopWrapper` class)           |
| **Analysis Tool**  | Claude Code (Anthropic)                                              |

### Trace Method

Traces captured by:
1. Deploying `trace_hooks_streaming.py` to printer via rsync
2. Streaming method calls over TCP port 9876
3. Triggering Z-probe operations (homing, bed mesh calibration)
4. Parsing JSONL trace logs for `unzip_data` method calls
5. Correlating input hex strings with output `[count, [values...]]` arrays

### Analysis Scripts

- `../tools/analyze_unzip.py` - Decoder implementation and validation

---

## Overview

The `unzip_data` method in `prtouch_v3` decompresses step count and pressure sensor data. It has two modes based on the `is_data_obj` parameter.

## Data Structure

```
Input: bytes array
Output: [count, [values...]]
```

### Common Header
- byte[0]: count (number of values)
- byte[1]: flags
- byte[2]: hint

---

## Step Data (`is_data_obj=False`)

Used for stepper motor position data during Z probing.

### Structure
```
byte[0]     = count (number of values)
bytes[1:4]  = 3-byte header (flags, hint, extra)
bytes[4:8]  = first value (4-byte unsigned LE)
bytes[8:]   = deltas (3-byte unsigned LE each)
```

### Decoding Algorithm
```python
def decode_step_data(hex_str):
    raw = bytes.fromhex(hex_str)
    count = raw[0]

    # First value: 4 bytes starting at position 4
    first_val = raw[4] | (raw[5] << 8) | (raw[6] << 16) | (raw[7] << 24)

    # Deltas: 3 bytes each, unsigned LE
    values = [first_val]
    delta_bytes = raw[8:]

    for i in range(count - 1):
        start = i * 3
        d = delta_bytes[start] | (delta_bytes[start+1] << 8) | (delta_bytes[start+2] << 16)
        values.append(values[-1] + d)

    return [count, values]
```

### Example
```
Hex: 0902aaab11aa9a10767101887101ae71017671018871014e7101827101867101

count = 9
first_val = 0x109AAA11 = 278,571,537 steps
deltas:
  76 71 01 = 0x017176 = 94,582
  88 71 01 = 0x017188 = 94,600
  ...

Note: "7101" pattern repeats because Z motor moves at ~94,500 steps/sample
```

---

## Pressure Data (`is_data_obj=True`)

Used for pressure sensor readings during probing.

### Structure
More complex variable-length encoding.

```
byte[0]     = count
byte[1]     = flags
byte[2]     = hint
byte[3:]    = data (variable encoding)
```

### First Value Encoding (partially decoded)

The first value location and size depends on flags and hint:

| Condition                              | First Value Location  | Size                      |
|----------------------------------------|-----------------------|---------------------------|
| hint == 0x00                           | data[1]               | (data[0] & 3) + 1 bytes   |
| flags == 0x00, hint & 3 == 2           | data[0]               | 3 bytes                   |
| flags == 0x00, (hint & 0x05) == 0x05   | data[0]               | 2 bytes                   |
| flags == 0x00, other                   | data[1]               | (data[0] & 3) + 1 bytes   |
| flags & 0x02                           | hint:data[0]:data[1]  | 3 bytes (hint=low)        |
| (flags & 0x41) == 0x41, hint >= 0x40   | hint:data[0]          | 2 bytes (hint=low)        |
| flags & 0x40                           | data[0]               | (hint & 3) + 1 bytes      |
| default                                | data[0]               | (hint & 3) + 1 bytes      |

### Delta Encoding (mostly decoded)

Deltas use a variable-length encoding:

- **1-byte delta**: signed, range -128 to 127
- **2-byte delta**: signed LE, when value outside 1-byte range

The flags and hint bytes appear to encode which deltas use 2 bytes, but the exact bitmap interpretation is not fully determined.

### Self-Describing Pattern (partial)

When examining byte sequences:
- If next byte is 0x00 or 0x01: could be 2-byte positive value
- If next byte is 0xFF: could be 2-byte negative value
- Otherwise: 1-byte signed value

**Caveat**: This heuristic fails when a 1-byte value is followed by 0x00, 0x01, or 0xFF. The full algorithm likely uses the hint byte as a bitmap.

---

## Accuracy

Current decoder accuracy on captured data:
- **Step data**: 100% (structure fully understood)
- **Pressure data first value**: ~95%
- **Pressure data full decode**: ~35% (delta encoding needs more work)

---

## Future Work

1. Fully decode the hint/flags bitmap for 2-byte delta positions
2. Handle edge cases in first value encoding
3. Validate against more trace data
