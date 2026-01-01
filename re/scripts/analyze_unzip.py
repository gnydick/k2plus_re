#!/usr/bin/env python3
"""Analyze unzip_data compression algorithm from traces."""

import struct
import json


def load_pressure_data(filepath):
    """Load pressure data (is_data_obj=True) samples from trace file."""
    pairs = []
    import re

    with open(filepath) as f:
        for line in f:
            d = json.loads(line)
            if d.get("method") == "unzip_data" and d["type"] == "call":
                args = d["args"]
                # Parse: {'_bytes': 'hex...'}, True/False
                if "True" in args:
                    # Extract hex string using regex
                    match = re.search(r"'([0-9a-fA-F]+)'", args)
                    if match:
                        hex_str = match.group(1)
                        pairs.append(("call", d["id"], hex_str))
            elif d.get("method") == "unzip_data" and d["type"] == "return":
                pairs.append(("return", d["id"], d["result"]))

    # Match calls with returns
    call_data = {}
    return_data = {}
    for item in pairs:
        if item[0] == "call":
            call_data[item[1]] = item[2]
        else:
            return_data[item[1]] = item[2]

    matched = []
    for id_, hex_str in call_data.items():
        if id_ in return_data:
            matched.append((hex_str, return_data[id_]))

    return matched


def analyze_sample(hex_str, result):
    """Analyze a single sample in detail."""
    raw = bytes.fromhex(hex_str)
    count = raw[0]
    flags = raw[1]
    hint = raw[2]
    data = raw[3:]

    expected = result[1]
    deltas = [expected[i+1] - expected[i] for i in range(len(expected)-1)]

    print(f"\n{'='*50}")
    print(f"Hex: {hex_str}")
    print(f"Count={count}, Flags=0x{flags:02x}, Hint=0x{hint:02x}")
    print(f"Expected values: {expected}")
    print(f"Deltas: {deltas}")
    print(f"Data bytes: {' '.join(f'{b:02x}' for b in data)}")

    # First value
    v0 = data[0] | (data[1] << 8) | (data[2] << 16)
    if v0 >= 0x800000:
        v0 -= 0x1000000
    print(f"First value (bytes 0-2): {v0}")

    # Try to understand delta encoding
    remaining = data[3:]
    print(f"Delta bytes: {' '.join(f'{b:02x}' for b in remaining)}")

    # Manual decode based on delta requirements
    print("Manual decode:")
    pos = 0
    for i, d in enumerate(deltas):
        if -128 <= d <= 127:
            # Should be 1 byte
            if pos < len(remaining):
                b = remaining[pos]
                val = b if b < 128 else b - 256
                print(f"  d[{i}]={d}: 1-byte at pos {pos}, byte=0x{b:02x}={val}")
                pos += 1
        else:
            # Should be 2 bytes
            if pos + 1 < len(remaining):
                val = struct.unpack("<h", remaining[pos:pos+2])[0]
                print(f"  d[{i}]={d}: 2-byte at pos {pos}, "
                      f"bytes=0x{remaining[pos]:02x}{remaining[pos+1]:02x}={val}")
                pos += 2

    print(f"Bytes used: {pos}, available: {len(remaining)}")

    return {
        'flags': flags,
        'hint': hint,
        'deltas': deltas,
        'delta_sizes': [1 if -128 <= d <= 127 else 2 for d in deltas]
    }


def decode_deltas_auto(data, num_deltas):
    """
    Decode deltas using self-describing format.

    Pattern discovered (little-endian, so b0=low byte, b1=high byte):
    - Check b1 (high byte) FIRST to determine size
    - If b1 is 0x00 or 0x01: 2-byte positive (0 to 511)
    - If b1 is 0xFF: 2-byte negative (-256 to -1)
    - Otherwise: 1-byte signed (-128 to 127)

    This works because:
    - 2-byte positive values 128-511 have high byte 0x00 or 0x01
    - 2-byte negative values -256 to -129 have high byte 0xFF
    - 1-byte values in -128 to 127 won't have next byte be 0x00/0x01/0xFF
      (statistically unlikely in delta sequences)
    """
    values = []
    pos = 0

    while len(values) < num_deltas and pos < len(data):
        b0 = data[pos]

        # Check if there's a next byte that indicates 2-byte value
        if pos + 1 < len(data):
            b1 = data[pos + 1]

            # 2-byte positive: high byte is 0x00 or 0x01
            if b1 in (0x00, 0x01):
                val = struct.unpack("<H", bytes([b0, b1]))[0]  # unsigned
                values.append(val)
                pos += 2
                continue

            # 2-byte negative: high byte is 0xFF
            if b1 == 0xFF:
                val = struct.unpack("<h", bytes([b0, b1]))[0]  # signed
                values.append(val)
                pos += 2
                continue

        # Default: 1-byte signed
        val = b0 if b0 < 128 else b0 - 256
        values.append(val)
        pos += 1

    return values, pos


def decode_with_hint(data, num_deltas, hint):
    """
    Decode deltas using hint byte as bitmap for 2-byte positions.

    Try different interpretations of hint.
    """
    values = []
    pos = 0

    for i in range(num_deltas):
        if pos >= len(data):
            break

        # Check if this delta should be 2 bytes based on hint
        # Try: bit (i+1) indicates 2-byte
        is_2byte = (hint >> (i + 1)) & 1

        if is_2byte and pos + 1 < len(data):
            val = struct.unpack("<h", data[pos:pos+2])[0]
            pos += 2
        else:
            val = data[pos] if data[pos] < 128 else data[pos] - 256
            pos += 1

        values.append(val)

    return values, pos


def test_hint_decoder():
    """Test decoding with hint byte as bitmap."""
    print("\n" + "="*60)
    print("TESTING HINT-BASED DECODER")
    print("="*60)

    # Test cases: (delta_bytes, expected_deltas, hint, flags)
    tests = [
        ("e49400843c80", [-28, 148, -124, 60, -128], 0x12, 0x00),
        ("64ffce720171f6", [-156, -50, 370, 113, -10], 0x46, 0x00),
        ("0ad2fc1101b300", [10, -46, -4, 273, 179], 0x02, 0x05),
        ("5ea620fff4c2", [94, -90, -224, -12, -62], 0x42, 0x00),
    ]

    for delta_hex, expected, hint, flags in tests:
        data = bytes.fromhex(delta_hex)
        print(f"\nInput: {delta_hex}")
        print(f"flags=0x{flags:02x}, hint=0x{hint:02x} ({hint:08b})")
        print(f"Expected: {expected}")

        # Figure out actual 2-byte positions
        sizes = [1 if -128 <= d <= 127 else 2 for d in expected]
        pos_2byte = [i for i, s in enumerate(sizes) if s == 2]
        print(f"2-byte at indices: {pos_2byte}")

        # Calculate what bitmap SHOULD be
        bitmap = sum(1 << i for i in pos_2byte)
        print(f"Needed bitmap: 0x{bitmap:02x} ({bitmap:08b})")

        # Look for relationship with hint
        print(f"hint ^ bitmap = 0x{hint ^ bitmap:02x}")
        print(f"hint - bitmap = {hint - bitmap}")
        print(f"(hint >> 1) ^ bitmap = 0x{(hint >> 1) ^ bitmap:02x}")
        print(f"flags | hint = 0x{flags | hint:02x}")
        print(f"(flags << 4) | (hint & 0x0F) = 0x{(flags << 4) | (hint & 0x0F):02x}")


def analyze_all_samples(matched):
    """Analyze all samples to find patterns in flags/hint encoding."""
    print("\n" + "="*60)
    print("LOOKING FOR SELF-DESCRIBING PATTERNS IN DELTA BYTES")
    print("="*60)

    # Look at transitions between 1-byte and 2-byte values
    for hex_str, result in matched[:20]:
        raw = bytes.fromhex(hex_str)
        if len(raw) < 6:
            continue

        count = raw[0]
        flags = raw[1]
        hint = raw[2]
        data = raw[3:]

        expected = result[1]
        if len(expected) < 2:
            continue

        deltas = [expected[i+1] - expected[i] for i in range(len(expected)-1)]

        # Get the delta bytes (after first 3-byte value)
        delta_bytes = data[3:]

        print(f"\nSample: hint=0x{hint:02x}, flags=0x{flags:02x}")
        print(f"Delta bytes: {' '.join(f'{b:02x}' for b in delta_bytes)}")
        print(f"Deltas: {deltas}")

        # Manually trace through and look for patterns
        pos = 0
        for i, d in enumerate(deltas):
            if pos >= len(delta_bytes):
                break

            b0 = delta_bytes[pos]
            b1 = delta_bytes[pos+1] if pos+1 < len(delta_bytes) else None

            if -128 <= d <= 127:
                # 1-byte delta
                actual_1b = b0 if b0 < 128 else b0 - 256
                print(f"  d[{i}]={d:4d}: 1-byte 0x{b0:02x}={actual_1b:4d}", end="")
                if b1 is not None:
                    print(f" (next=0x{b1:02x})", end="")
                print()
                pos += 1
            else:
                # 2-byte delta
                if b1 is not None:
                    actual_2b = struct.unpack("<h", bytes([b0, b1]))[0]
                    # Check what hints might tell us this is 2-byte
                    print(f"  d[{i}]={d:4d}: 2-byte 0x{b0:02x}{b1:02x}={actual_2b:4d}", end="")
                    # Check patterns
                    if b1 == 0x00:
                        print(" [high=0x00 for positive]", end="")
                    elif b1 == 0xFF:
                        print(" [high=0xFF for negative]", end="")
                    elif b1 == 0x01:
                        print(" [high=0x01 for positive]", end="")
                    elif b1 == 0xFE:
                        print(" [high=0xFE for negative]", end="")
                    print()
                pos += 2


def test_auto_decoder():
    """Test the auto-decoder on sample data."""
    print("\n" + "="*60)
    print("TESTING AUTO-DECODER")
    print("="*60)

    # Test cases from analysis
    tests = [
        # (delta_bytes, expected_deltas)
        ("e49400843c80", [-28, 148, -124, 60, -128]),
        ("64ffce720171f6", [-156, -50, 370, 113, -10]),
        ("0ad2fc1101b300", [10, -46, -4, 273, 179]),
        ("5ea620fff4c2", [94, -90, -224, -12, -62]),
    ]

    for delta_hex, expected in tests:
        data = bytes.fromhex(delta_hex)
        decoded, bytes_used = decode_deltas_auto(data, len(expected))
        match = decoded == expected
        print(f"\nInput: {delta_hex}")
        print(f"Expected: {expected}")
        print(f"Decoded:  {decoded}")
        print(f"Match: {match}, bytes used: {bytes_used}/{len(data)}")


def main():
    import glob
    # Find the most recent capture file
    files = sorted(glob.glob("captures/prtouch_v3_*.jsonl"))
    if not files:
        print("No capture files found!")
        return
    filepath = files[-1]
    print(f"Using capture file: {filepath}")
    matched = load_pressure_data(filepath)
    print(f"Loaded {len(matched)} pressure data samples")

    print("\n" + "="*60)
    print("DETAILED BYTE ANALYSIS")
    print("="*60)

    results = []
    for hex_str, result in matched[:5]:
        info = analyze_sample(hex_str, result)
        results.append(info)

    # Look for patterns
    print("\n" + "="*60)
    print("PATTERN ANALYSIS")
    print("="*60)

    for r in results:
        num_2byte = sum(1 for s in r['delta_sizes'] if s == 2)
        hint_low = r['hint'] & 0x0F
        hint_high = (r['hint'] >> 4) & 0x0F
        print(f"flags=0x{r['flags']:02x}, hint=0x{r['hint']:02x} "
              f"(low={hint_low}, high={hint_high}), "
              f"2-byte deltas={num_2byte}, sizes={r['delta_sizes']}")

    # Test auto decoder
    test_auto_decoder()

    # Test hint-based decoder
    test_hint_decoder()

    # Large scale analysis
    analyze_all_samples(matched)


if __name__ == "__main__":
    main()
