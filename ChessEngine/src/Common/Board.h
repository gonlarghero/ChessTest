#ifndef BOARD_H
#define BOARD_H

#include "BitBoard.h"
#include "Movements/Move.h"


//Structured used to undo moves
typedef struct UNDO
{
    int move;
    int castlePermission;
    int enPassant;
    int fiftyMove;
    U64 positionKey;
} UNDO;


typedef struct BOARD
{
    int pieces [BOARD_SEQUENCE_NUMBER];
    int Kings [2];
    int side;
    int enPassant;
    int castlePermission;
    int fiftyMove;

    int play;
    int historyPlay;

    U64 positionKey;
    
    int pieceNumber[PIECE_TYPE_NUMBER];

    int bigPieces[COLOUR_NUMBER-1];
    int majorPieces[COLOUR_NUMBER-1];
    int minorPieces[COLOUR_NUMBER-1];
    U64 pawns [COLOUR_NUMBER];
    int material[COLOUR_NUMBER-1];

    UNDO history[MAX_GAME_MOVES];

    int pieceList[PIECE_TYPE_NUMBER][MAX_OF_ONE_PICE];

    PVTABLE pvTable[1];

} BOARD;

extern void ResetBoard(BOARD *position);
extern void PrintBoard(const BOARD* position);
extern void UpdateListMaterial(BOARD *position);

#endif
