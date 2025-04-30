#ifndef COMMON_VALIDATE_H
#define COMMON_VALIDATE_H

#include "Definitions.h"
#include "Global.h"

extern bool SquareOnBoard(const int square);
extern bool SideValid(const int side);
extern bool FileRankValide(const int fr);
extern bool PieceValidEmpty(const int piece);
extern bool PieceValid(const int piece);

#endif
