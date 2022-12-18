#ifndef IO_H
#define IO_H

#include "../Common/Definitions.h"
#include "../Common/Global.h"
#include "../Common/Macros.h"
#include "../Common/Movements/Move.h"

extern char *PrintSquare(const int square);
extern char *PrintMove(const int move);
extern void PrintMoveList(const MOVELIST *list);

#endif
