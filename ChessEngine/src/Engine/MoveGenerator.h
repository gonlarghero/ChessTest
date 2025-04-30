#ifndef ENGINE_MOVEGENERATOR_H_
#define ENGINE_MOVEGENERATOR_H_

#include "../Common/Board.h"
#include "../Common/Movements/Attack.h"
#include "../Common/Movements/MakeMove.h"
#include "../Common/Movements/Move.h"
#include "../Common/Validate.h"
#include "../Data/BoardValidator.h"

void GenerateAllMoves(const BOARD *position, MOVELIST *list);
void GenerateAllCaptures(const BOARD *position, MOVELIST *list);
bool MoveExists(BOARD *position, const int move);
void InitMvvLva();

#endif
