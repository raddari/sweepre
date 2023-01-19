#!/usr/bin/env python3
import sys

def decompose(flags: int) -> list[int]:
    binstr = bin(flags)[2:]
    return [2 ** i for i, c in enumerate(reversed(binstr)) if c == '1']

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'usage: {sys.argv[0]} <hex_flags>')
        sys.exit(0)

    decomposed = decompose(int(sys.argv[1], 16))
    print(' | '.join([f'0x{i:08X}' for i in reversed(decomposed)]))

