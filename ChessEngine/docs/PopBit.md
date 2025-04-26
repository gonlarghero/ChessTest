# PopBit Detailed Documentation

## Purpose

PopBit finds the least significant 1-bit and clears it from a bitboard.

## How it Works

0. XOR to turn on the last bit and every following bit.
1. Fold the 64-bit number into 32 bits.  
   There are no collisions for single-set-bit inputs:  
   - If the last bit was in the second half (bits 32–63), it folds into the lower half.
   - If it was in the first half (bits 0–31), it folds into the bitwise complement.
   - Examples: `[0000ffff]` vs `[ffff0000]` or `[00ffffff]` vs `[ff000000]`
2. Multiply the folded value by a magic number.  
   - Reference: [Bit Hacks Post (Google Groups)](https://groups.google.com/g/comp.lang.asm.x86/c/3pVGzQGb1ys)
3. Shift the result and lookup the final bit index in the `BitTable`.

## Code

```c
int PopBit(U64 *bb) {
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}
