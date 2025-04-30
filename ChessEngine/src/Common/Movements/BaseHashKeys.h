#ifndef COMMON_MOVEMENTS_BASEHASHKEYS_H
#define COMMON_MOVEMENTS_BASEHASHKEYS_H

#include "../Board.h"

namespace Hash {

inline void Piece(BOARD *position, int piece, int square) { position->positionKey ^= PieceKeys[piece][square]; }

inline void Castle(BOARD *position) { position->positionKey ^= CastleKeys[position->castlePermission]; }

inline void Side(BOARD *position) { position->positionKey ^= SideKey; }

inline void EnPassant(BOARD *position) { position->positionKey ^= PieceKeys[EMPTY][position->enPassant]; }

} // namespace Hash

#endif