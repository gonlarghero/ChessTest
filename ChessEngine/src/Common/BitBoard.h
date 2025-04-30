#ifndef COMMON_BITBOARD_H
#define COMMON_BITBOARD_H

#include "../Common/Global.h"
#include "../Common/Macros.h"

void PrintBitBoard(U64 bb);
int PopBit(U64 *bb);
int CountBits(U64 b);

#endif