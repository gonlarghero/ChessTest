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


## Visual Example

| Field       | Binary Value                         | Hex Value     | Notes                      |
|-------------|--------------------------------------|---------------|----------------------------|
| From        | `0000 0000 0000 0000 0000 0111 1111` | `0x0000007F`  | Use `Move::From(move)`     |
| To          | `0000 0000 0000 0011 1111 1000 0000` | `0x00003F80`  | Use `Move::To(move)`       |
| Captured    | `0000 0000 0011 1100 0000 0000 0000` | `0x0003C000`  | Use `Move::Captured(move)` |
| En Passant  | `0000 0000 0100 0000 0000 0000 0000` | `0x00040000`  | Use `Move::FlagEnPassant`  |
| Pawn Start  | `0000 0000 1000 0000 0000 0000 0000` | `0x00080000`  | Use `Move::FlagPawnStart`  |
| Promoted    | `0000 1111 0000 0000 0000 0000 0000` | `0x00F00000`  | Use `Move::Promoted(move)` |
| Castling    | `0001 0000 0000 0000 0000 0000 0000` | `0x01000000`  | Use `Move::FlagCastle`     |

## Move Accessors (`Move.h`)

These `constexpr` functions extract information from a move integer cleanly:

```cpp
namespace Move {

constexpr int From(int move)       { return move & 0x7F; }
constexpr int To(int move)         { return (move >> 7) & 0x7F; }
constexpr int Captured(int move)   { return (move >> 14) & 0xF; }
constexpr int Promoted(int move)   { return (move >> 20) & 0xF; }

}

## Summary

This encoding scheme allows all relevant move information to be stored in a single integer, making move generation, storage, and comparison efficient and straightforward.