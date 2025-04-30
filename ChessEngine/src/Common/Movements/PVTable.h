#ifndef COMMON_MOVEMENTS_PVTABLE_H
#define COMMON_MOVEMENTS_PVTABLE_H

#include "../../Engine/MoveGenerator.h"
#include "../Board.h"
#include "Move.h"

extern void InitPVTable(PVTABLE *table);
extern void ClearPVTable(PVTABLE *table);
extern void StorePVMove(const BOARD *position, const int move);
extern int ProbePVTable(const BOARD *position);
extern int GetPVLine(const int depth, BOARD *position);

#endif
