#ifndef BOARD_H
#define BOARD_H

#include "Definitions.h";

//Structured used to undo moves
typedef struct UNDO
{
    int move;
    int castlePermision;
    int enPassant;
    int fiftyMove;
    U64 positionKey;
} UNDO;


typedef struct Board
{
    int pieces [BOARD_SEQUENCE_NUMBER];
    U64 pawns [COLOR_NUMBER];
    int Kings [2];
    int side;
    int enPassant;
    int castlePermision;
    int fiftyMove;

    int play;
    int halfPlay;

    U64 positionKey;
    
    int piece[PIECE_TYPE_NUMBER];
    int bigPieces[COLOR_NUMBER];
    int majorPieces[COLOR_NUMBER];
    int minorPiecesp[COLOR_NUMBER];

    UNDO histoty[MAX_GAME_MOVES];

    int pieceList[PIECE_TYPE_NUMBER][MAX_OF_ONE_PICE];

} Board;

#endif
