#ifndef GLOBAL_H
#define GLOBAL_H

#include "Definitions.h"
#include <stdlib.h>
#include <stdio.h>

extern int Sq120ToSq64[BOARD_SEQUENCE_NUMBER];
extern int Sq64ToSq120[BOARD_REAL_NUMBER];
extern U64 SetMask[BOARD_REAL_NUMBER];
extern U64 ClearMask[BOARD_REAL_NUMBER];
extern U64 PieceKeys[PIECE_TYPE_NUMBER][BOARD_SEQUENCE_NUMBER];
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
extern int FilesBoard[BOARD_SEQUENCE_NUMBER];
extern int RanksBoard[BOARD_SEQUENCE_NUMBER];
extern int PieceKnight[PIECE_TYPE_NUMBER];
extern int PieceKing[PIECE_TYPE_NUMBER];
extern int PieceRookQueen[PIECE_TYPE_NUMBER];
extern int PieceBishopQueen[PIECE_TYPE_NUMBER];


//Generates 64 bit random in blocks of 15
U64 RAND_64();

//MUGRE PARA PODER DEBUGGEAR //TODO sacar este codigo asqueroso
#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)\
	if(!(n)){ \
		printf("%s - Failed: ", #n);\
		printf("On %s ", __DATE__);\
		printf("At %s ", __TIME__);\
		printf("In File %s ", __FILE__);\
		printf("At Line %d\n ", __LINE__);\
		exit(1);}
#endif

#endif
