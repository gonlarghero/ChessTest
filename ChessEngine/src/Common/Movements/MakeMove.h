#ifndef COMMON_MOVEMENTS_MAKEMOVE_H_
#define COMMON_MOVEMENTS_MAKEMOVE_H_

#include "../Board.h"
#include "../Validate.h"
#include "../../Data/BoardValidator.h"
#include "Move.h"
#include "Attack.h"


//Horrible forma de definir constantes dependiente del nombre de la variable position
#define HASH_PIECE(piece,square) (position->positionKey ^= PieceKeys[(piece)][(square)])
#define HASH_CA (position->positionKey ^= (CastleKeys[(position->castlePermission)]))
#define HASH_SIDE (position->positionKey ^= (SideKey))
#define HASH_EP (position->positionKey ^= (PieceKeys[EMPTY][(position->enPassant)]))


bool MakeMove(BOARD *position, int move);
void TakeMove(BOARD *position);

#endif
