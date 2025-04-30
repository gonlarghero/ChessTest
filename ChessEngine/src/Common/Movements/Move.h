#ifndef COMMON_MOVEMENTSMOVE_H
#define COMMON_MOVEMENTSMOVE_H

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

// details in docs/Move.md

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
