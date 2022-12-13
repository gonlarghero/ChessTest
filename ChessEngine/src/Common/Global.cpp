#include "Global.h"
#include <stdio.h>
#include <stdlib.h>

int Sq120ToSq64[BOARD_SEQUENCE_NUMBER];
int Sq64ToSq120[BOARD_REAL_NUMBER];

U64 SetMask[BOARD_REAL_NUMBER];
U64 ClearMask[BOARD_REAL_NUMBER];

U64 PieceKeys[PIECE_TYPE_NUMBER][BOARD_SEQUENCE_NUMBER];
U64 SideKey;
U64 CastleKeys[CASTLE_BITS];

char PieceChar[] = ".PNBRQKpnbrqk";
char SideChar[] = "wb-";
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";

int PieceBig[PIECE_TYPE_NUMBER] = {false,false,true,true,true,true,true,false,true,true,true,true,true};
int PieceMajor[PIECE_TYPE_NUMBER] = {false,false,false,false,true,true,true,false,false,false,true,true,true};
int PieceMinor[PIECE_TYPE_NUMBER] = {false,false,true,true,false,false,false,false,true,true,false,false,false};
int PieceValue[PIECE_TYPE_NUMBER] = {0,100,305,333,563,950,10953,100,305,333,563,950,10953};
int PieceColour[PIECE_TYPE_NUMBER] = {BOTH,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK};

int FilesBoard[BOARD_SEQUENCE_NUMBER];
int RanksBoard[BOARD_SEQUENCE_NUMBER];


U64 RAND_AUX(){
	return (U64) rand();
}

U64 RAND_64(){
	return RAND_AUX() | (RAND_AUX() << 15) | (RAND_AUX() << 30) | (RAND_AUX() << 45) | ((RAND_AUX() & 0xf) << 60);
}



