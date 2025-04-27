#ifndef ENGINE_MOVEGENERATOR_H_
#define ENGINE_MOVEGENERATOR_H_

#include "../Common/Board.h"
#include "../Common/Movements/Attack.h"
#include "../Common/Movements/MakeMove.h"
#include "../Common/Movements/Move.h"
#include "../Common/Validate.h"
#include "../Data/BoardValidator.h"

// Generates a new move based on move.h structure
#define MOVE_M(f, t, ca, pro, fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
#define SQUAREOFFBOARD(sq) (FilesBoard[(sq)] == SQUARE_NULL)

void GenerateAllMoves(const BOARD *position, MOVELIST *list);
void GenerateAllCaptures(const BOARD *position, MOVELIST *list);
bool MoveExists(BOARD *position, const int move);
void InitMvvLva();

#endif
