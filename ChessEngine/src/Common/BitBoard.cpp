#include "BitBoard.h"

#include <iostream>
#include <stdio.h>

const int BitTable[BOARD_REAL_NUMBER] = {63, 30, 3,  32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34,
                                         61, 29, 2,  51, 21, 43, 45, 10, 18, 47, 1,  54, 9,  57, 0,  35,
                                         62, 31, 40, 4,  49, 5,  52, 26, 60, 6,  23, 44, 46, 27, 56, 16,
                                         7,  39, 48, 24, 59, 14, 12, 55, 38, 28, 58, 20, 37, 17, 36, 8};

// Details: in docs/PopBit.md
int PopBit(U64 *bb) {
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}

// Details: in docs/CountBits.md
int CountBits(U64 b) {
    int r;
    for (r = 0; b; r++, b &= b - 1);
    return r;
}

void PrintBitBoard(U64 bb) {
    U64 shiftMe = 1ULL;

    int rank = 0;
    int file = 0;
    int square120 = 0;
    int square64 = 0;

    std::cout << "\n";
    for (rank = RANK_8; rank >= RANK_1; --rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            square120 = FR2SQ(file, rank);
            square64 = Sq120ToSq64[square120];

            if ((shiftMe << square64) & bb)
                std::cout << "X";
            else
                std::cout << "-";
        }
        std::cout << "\n\n";
    }
}
