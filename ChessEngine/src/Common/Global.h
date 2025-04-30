#ifndef COMMON_GLOBAL_H
#define COMMON_GLOBAL_H

#include "Definitions.h"
#include <stdio.h>
#include <stdlib.h>

extern int Sq120ToSq64[BOARD_SQUARE_NUMBER];
extern int Sq64ToSq120[BOARD_REAL_NUMBER];
extern U64 SetMask[BOARD_REAL_NUMBER];
extern U64 ClearMask[BOARD_REAL_NUMBER];
extern U64 PieceKeys[PIECE_TYPE_NUMBER][BOARD_SQUARE_NUMBER];
extern U64 SideKey;
extern U64 CastleKeys[CASTLE_BITS];
extern char PieceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];
extern int PieceBig[PIECE_TYPE_NUMBER];
extern int PieceMajor[PIECE_TYPE_NUMBER];
extern int PieceMinor[PIECE_TYPE_NUMBER];
extern int PieceValue[PIECE_TYPE_NUMBER];
extern int PieceColour[PIECE_TYPE_NUMBER];
extern int FilesBoard[BOARD_SQUARE_NUMBER];
extern int RanksBoard[BOARD_SQUARE_NUMBER];
extern int PieceKnight[PIECE_TYPE_NUMBER];
extern int PieceKing[PIECE_TYPE_NUMBER];
extern int PieceRookQueen[PIECE_TYPE_NUMBER];
extern int PieceBishopQueen[PIECE_TYPE_NUMBER];
extern int PieceSlides[PIECE_TYPE_NUMBER];
extern int PiecePawn[PIECE_TYPE_NUMBER];
extern int VictimScore[PIECE_TYPE_NUMBER];

// piecesquaretables
extern int Mirror64[BOARD_REAL_NUMBER];
extern int PawnTable[BOARD_REAL_NUMBER];
extern int KnightTable[BOARD_REAL_NUMBER];
extern int BishopTable[BOARD_REAL_NUMBER];
extern int RookTable[BOARD_REAL_NUMBER];
extern int KingE[BOARD_REAL_NUMBER];
extern int KingO[BOARD_REAL_NUMBER];

// Generates 64 bit random in blocks of 15
U64 RAND_64();

// MUGRE PARA PODER DEBUGGEAR //TODO sacar este codigo asqueroso
#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
#include <iostream>
#define ASSERT(n)                                                                                                      \
    if (!(n)) {                                                                                                        \
        std::cout << #n << " - Failed: ";                                                                              \
        std::cout << "On " << __DATE__ << " ";                                                                         \
        std::cout << "At " << __TIME__ << " ";                                                                         \
        std::cout << "In File " << __FILE__ << " ";                                                                    \
        std::cout << "At Line " << __LINE__ << std::endl;                                                              \
        exit(1);                                                                                                       \
    }
#endif

#endif
