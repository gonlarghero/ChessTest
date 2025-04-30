#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#define FR2SQ(file, rank) ((21 + (file)) + ((rank) * 10))
#define SETBIT(bb, square) ((bb) |= SetMask[(square)])
#define CLEARBIT(bb, square) ((bb) &= ClearMask[(square)])

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])
#define MIRROR64(sq) (Mirror64[(sq)])

#endif
