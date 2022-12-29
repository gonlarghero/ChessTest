#ifndef ENGINE_SEARCH_H_
#define ENGINE_SEARCH_H_

#include "../Common/Board.h"
#include "../Common/Movements/Move.h"
#include "../Common/Movements/PVTable.h"
#include "Evaluate.h"

extern void SearchPosition(BOARD *position, SEARCHINFO *info);

#endif
