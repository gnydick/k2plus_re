#!/usr/bin/env python3
"""
Capture and decode RS-485 traffic from K2 printer.

Run this script ON THE PRINTER via SSH:
    python3 capture_rs485.py /dev/ttyS1 > rs485_traffic.log

This captures raw RS-485 packets and decodes them using the known protocol:
- Header: 0xF7
- Format: HEAD(1) + ADDR(1) + LEN(1) + STATUS(1) + FUNC(1) + DATA(var) + CRC(1)
"""

import sys
import os
import time
import serial
import argparse
from datetime import datetime

# Protocol constants (from decompiled code)
PACK_HEAD = 0xF7

# Device address ranges
DEVICE_TYPES = {
    range(0x01, 0x05): "MaterialBox",
    range(0x81, 0x85): "ClosedLoopMotor",
    range(0x91, 0x93): "BeltTensionMotor",
    0xFE: "Broadcast_MB",
    0xFD: "Broadcast_CLM",
    0xFC: "Broadcast_BTM",
}

# Known function codes (partially inferred)
FUNC_CODES = {
    0xA0: "SET_SLAVE_ADDR",
    0xA1: "GET_SLAVE_INFO",
    0xA2: "ONLINE_CHECK",
    0xA3: "GET_ADDR_TABLE",
    0x0B: "LOADER_TO_APP",
}


def crc8(data):
    """CRC-8 with polynomial 0x07."""
    crc = 0
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x80:
                crc = (crc << 1) ^ 0x07
            else:
                crc = crc << 1
            crc &= 0xFF
    return crc


def get_device_type(addr):
    """Get device type from address."""
    for key, name in DEVICE_TYPES.items():
        if isinstance(key, range):
            if addr in key:
                return name
        elif addr == key:
            return name
    return f"Unknown(0x{addr:02X})"


def decode_packet(packet):
    """Decode an RS-485 packet."""
    if len(packet) < 6:
        return {'error': 'Packet too short', 'raw': packet.hex()}

    if packet[0] != PACK_HEAD:
        return {'error': 'Invalid header', 'raw': packet.hex()}

    addr = packet[1]
    length = packet[2]

    if len(packet) < length + 3:
        return {'error': 'Incomplete packet', 'raw': packet.hex()}

    status = packet[3]
    func = packet[4]
    data = packet[5:2+length]
    packet_crc = packet[2+length] if len(packet) > 2+length else None

    # Verify CRC
    calc_crc = crc8(packet[2:2+length])
    crc_valid = calc_crc == packet_crc if packet_crc else None

    return {
        'addr': addr,
        'addr_type': get_device_type(addr),
        'length': length,
        'status': status,
        'func': func,
        'func_name': FUNC_CODES.get(func, f"0x{func:02X}"),
        'data': data.hex() if data else '',
        'data_bytes': list(data),
        'crc': packet_crc,
        'crc_valid': crc_valid,
        'raw': packet.hex(),
    }


def find_packets(buffer):
    """Find and extract packets from buffer."""
    packets = []
    i = 0

    while i < len(buffer):
        # Find header
        if buffer[i] != PACK_HEAD:
            i += 1
            continue

        # Need at least 6 bytes for minimum packet
        if i + 6 > len(buffer):
            break

        length = buffer[i + 2]
        if length < 3:
            i += 1
            continue

        packet_len = length + 3
        if i + packet_len > len(buffer):
            break

        packet = buffer[i:i + packet_len]
        packets.append(packet)
        i += packet_len

    return packets, buffer[i:]


def main():
    parser = argparse.ArgumentParser(description='Capture RS-485 traffic')
    parser.add_argument('device', help='Serial device (e.g., /dev/ttyS1)')
    parser.add_argument('--baud', type=int, default=115200, help='Baud rate')
    parser.add_argument('--duration', type=int, default=0, help='Capture duration in seconds (0=infinite)')
    parser.add_argument('--raw', action='store_true', help='Output raw hex only')
    args = parser.parse_args()

    try:
        ser = serial.Serial(args.device, args.baud, timeout=0.1)
    except serial.SerialException as e:
        sys.stderr.write(f"Error opening {args.device}: {e}\n")
        sys.exit(1)

    sys.stderr.write(f"Capturing RS-485 traffic from {args.device} at {args.baud} baud\n")
    sys.stderr.write("Press Ctrl+C to stop\n\n")

    buffer = bytearray()
    start_time = time.time()
    packet_count = 0

    try:
        while True:
            if args.duration > 0 and time.time() - start_time > args.duration:
                break

            data = ser.read(256)
            if data:
                buffer.extend(data)

                if args.raw:
                    print(data.hex())
                    continue

                packets, buffer = find_packets(buffer)

                for packet in packets:
                    packet_count += 1
                    timestamp = datetime.now().strftime('%H:%M:%S.%f')[:-3]
                    decoded = decode_packet(packet)

                    if 'error' in decoded:
                        print(f"[{timestamp}] ERROR: {decoded['error']} - {decoded['raw']}")
                    else:
                        direction = "TX" if decoded['addr'] < 0x80 else "RX"
                        crc_status = "OK" if decoded['crc_valid'] else "BAD"
                        print(f"[{timestamp}] {direction} #{packet_count:04d} "
                              f"ADDR={decoded['addr_type']}(0x{decoded['addr']:02X}) "
                              f"FUNC={decoded['func_name']} "
                              f"DATA=[{decoded['data']}] "
                              f"CRC={crc_status}")

    except KeyboardInterrupt:
        pass
    finally:
        ser.close()
        sys.stderr.write(f"\nCaptured {packet_count} packets\n")


if __name__ == '__main__':
    main()
