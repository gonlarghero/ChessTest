#ifndef MOVE_H
#define MOVE_H

#include "../Definitions.h"

typedef struct SEARCHINFO {
    bool timeset;
    int starttime;
    int stoptime;

    bool depthset;
    int depth;

    int movestogo;
    int infinite;

    long nodes;

    bool quit;
    bool stopped;

    float failHigh;
    float failHighFirst;
} SEARCHINFO;

typedef struct PVENTRY {
    U64 positionKey;
    int move;
} PVENTRY;

typedef struct PVTABLE {
    PVENTRY *pTable;
    int numEntries;
} PVTABLE;

typedef struct MOVE {
    int move;
    int score;
} MOVE;

typedef struct MOVELIST {
    MOVE moves[MAX_POSITION_MOVES];
    int count;
} MOVELIST;

/*
0000 0000 0000 0000 0000 0111 1111 0x7F      -> from
0000 0000 0000 0011 1111 1000 0000 >>7,0x7F  -> to
0000 0000 0011 1100 0000 0000 0000 >>14,0x7F -> captured
0000 0000 0100 0000 0000 0000 0000 0x400000  -> ep
0000 0000 1000 0000 0000 0000 0000 0x800000  -> pawn start
0000 1111 0000 0000 0000 0000 0000 >>20 0xF  -> promoted
0001 0000 0000 0000 0000 0000 0000 0x1000000 -> castle
*/

#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m) >> 7) & 0x7F)
#define CAPTURED(m) (((m) >> 14) & 0xF)
#define PROMOTED(m) (((m) >> 20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7C000
#define MFLAGPROM 0xF00000

#endif
