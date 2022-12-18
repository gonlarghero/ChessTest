#ifndef ENGINE_MOVEGENERATOR_H_
#define ENGINE_MOVEGENERATOR_H_

#include "../Common/Movements/Move.h"
#include "../Common/Board.h"
#include "../Data/BoardValidator.h"
#include "../Common/Validate.h"


#define MOVE_M(f,t,ca,pro,fl) ((f)|((t)<<7)|((ca)<<14)|((pro)<<20)|(fl))
#define SQUAREOFFBOARD(sq) (FilesBoard[(sq)] == SQUARE_NULL)

void AddQuietMove(const BOARD *position, int move, MOVELIST *list);
void AddCaptureMove(const BOARD *position, int move, MOVELIST *list);
void AddEnPassantMove(const BOARD *position, int move, MOVELIST *list);


void AddWhitePawnMove(const BOARD *position, const int from, const int to, MOVELIST * list);
void AddWhitePawnCapMove(const BOARD *position, const int from, const int to, const int cap, MOVELIST * list);


void GenerateAllMoves(const BOARD *position, MOVELIST *list);

#endif
