#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define BOARD_SQUARE_NUMBER 120
#define BOARD_REAL_NUMBER 64
#define PIECE_TYPE_NUMBER 13
#define COLOUR_NUMBER 3
#define MAX_GAME_MOVES 2048
#define MAX_POSITION_MOVES 256
#define MAX_OF_ONE_PICE 10
#define CASTLE_BITS 16
#define MAXDEPTH 64
#define NOMOVE 0
#define INFINITY 30000
#define MATE 29000

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define TEST_FEN "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"
#define TEST_FEN2 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

typedef unsigned long long U64;

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NULL };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NULL };
enum { WHITE, BLACK, BOTH };
enum { wKCastle = 1, wQCastle = 2, bKCastle = 4, bQCastle = 8 };

enum {
    A1=21,B1,C1,D1,E1,F1,G1,H1,
    A2=31,B2,C2,D2,E2,F2,G2,H2,
    A3=41,B3,C3,D3,E3,F3,G3,H3,
    A4=51,B4,C4,D4,E4,F4,G4,H4,
    A5=61,B5,C5,D5,E5,F5,G5,H5,
    A6=71,B6,C6,D6,E6,F6,G6,H6,
    A7=81,B7,C7,D7,E7,F7,G7,H7,
    A8=91,B8,C8,D8,E8,F8,G8,H8,SQUARE_NULL
};

#endif
