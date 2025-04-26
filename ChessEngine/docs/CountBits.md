
# CountBits Detailed Documentation

## Purpose

`CountBits` counts the number of bits set to `1` in a 64-bit unsigned integer (bitboard).

This is sometimes called the **population count** or **Hamming weight**.

---

## How it Works

The function uses a loop that repeatedly:

- Clears the least significant 1-bit (`b &= b - 1`)
- Increments a counter `r` each time

Because each loop removes **one** bit, the total number of loops is exactly the number of bits that were set.

This method is efficient:  
Its time complexity is **O(number of set bits)** — very fast for sparse boards.

---

## Code

```c
int CountBits(U64 b) {
    int r;
    for (r = 0; b; r++, b &= b - 1)
        ;
    return r;
}
