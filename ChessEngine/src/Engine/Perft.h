#ifndef ENGINE_PERFT_H_
#define ENGINE_PERFT_H_

#include "../Common/Board.h"
#include "../Data/BoardValidator.h"
#include "../Common/Movements/Move.h"
#include "MoveGenerator.h"
#include "../Common/Movements/MakeMove.h"
#include "../Interface/IO.h"


extern void Perft(int depth,BOARD *position, int parent);
extern void PerfTest(int depth, BOARD *position);

#endif
