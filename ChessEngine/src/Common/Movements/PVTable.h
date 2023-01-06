#ifndef ENGINE_PVTABLE_H_
#define ENGINE_PVTABLE_H_

#include "Move.h"
#include "../Board.h"
#include "../../Engine/MoveGenerator.h"

extern void InitPVTable(PVTABLE *table);
extern void ClearPVTable(PVTABLE *table);
extern void StorePVMove(const BOARD* position, const int move);
extern int ProbePVTable(const BOARD* position);
extern int GetPVLine(const int depth, BOARD * position);

#endif
