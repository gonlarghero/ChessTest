# Move Encoding in ChessEngine

## Purpose

This document explains how moves are encoded into a single integer in the ChessEngine, as defined in `Move.h`.

## Bit Layout
Each move is packed into a 32-bit integer using specific bit fields for different move attributes:

| Bits         | Mask/Shift      | Purpose           |
|--------------|-----------------|-------------------|
| 0–6          | `0x7F`          | From square (0–127)|
| 7–13         | `0x7F << 7`     | To square (0–127)  |
| 14–17        | `0xF << 14`     | Captured piece (0–15)|
| 18           | `0x40000`       | En passant flag    |
| 19           | `0x80000`       | Pawn start flag    |
| 20–23        | `0xF << 20`     | Promoted piece (0–15)|
| 24           | `0x1000000`     | Castling flag      |

## Example from Code

0000 0000 0000 0000 0000 0111 1111 -> Hexa: 0x7F      -> from
0000 0000 0000 0011 1111 1000 0000 -> Hexa: >>7,0x7F  -> to
0000 0000 0011 1100 0000 0000 0000 -> Hexa: >>14,0x7F -> captured
0000 0000 0100 0000 0000 0000 0000 -> Hexa: 0x400000  -> ep
0000 0000 1000 0000 0000 0000 0000 -> Hexa: 0x800000  -> pawn start
0000 1111 0000 0000 0000 0000 0000 -> Hexa: >>20 0xF  -> promoted
0001 0000 0000 0000 0000 0000 0000 -> Hexa: 0x1000000 -> castle


## Macros for Extraction

To extract information from a move integer, the following macros are used:

```cpp
#define FROMSQ(m)    ((m) & 0x7F)
#define TOSQ(m)      (((m) >> 7) & 0x7F)
#define CAPTURED(m)  (((m) >> 14) & 0xF)
#define PROMOTED(m)  (((m) >> 20) & 0xF)
```

## Flags

- **MFLAGEP (`0x40000`)**: Set if the move is an en passant capture.
- **MFLAGPS (`0x80000`)**: Set if the move is a pawn's initial two-square advance.
- **MFLAGCA (`0x1000000`)**: Set if the move is a castling move.
- **MFLAGCAP (`0x7C000`)**: Set if the move is a capture (there's a piece at captured).
- **MFLAGPROM (`0xF00000`)** Set if the move is a promotion (promotion piece without from/to).

## Summary

This encoding scheme allows all relevant move information to be stored in a single integer, making move generation, storage, and comparison efficient and straightforward.