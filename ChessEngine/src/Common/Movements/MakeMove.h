#ifndef COMMON_MOVEMENTS_MAKEMOVE_H_
#define COMMON_MOVEMENTS_MAKEMOVE_H_

#include "../../Data/BoardValidator.h"
#include "../Board.h"
#include "../Validate.h"
#include "Attack.h"
#include "Move.h"

namespace Hash {

inline void Piece(BOARD *position, int piece, int square) { position->positionKey ^= PieceKeys[piece][square]; }

inline void Castle(BOARD *position) { position->positionKey ^= CastleKeys[position->castlePermission]; }

inline void Side(BOARD *position) { position->positionKey ^= SideKey; }

inline void EnPassant(BOARD *position) { position->positionKey ^= PieceKeys[EMPTY][position->enPassant]; }

} // namespace Hash

bool MakeMove(BOARD *position, int move);
void TakeMove(BOARD *position);

#endif
