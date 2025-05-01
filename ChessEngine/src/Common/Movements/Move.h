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

    bool xboard;
    bool postThinking;
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

namespace Move {

constexpr int From(int move) { return move & 0x7F; }
constexpr int To(int move) { return (move >> 7) & 0x7F; }
constexpr int Captured(int move) { return (move >> 14) & 0xF; }
constexpr int Promoted(int move) { return (move >> 20) & 0xF; }

constexpr int FlagEnPassant = 0x40000;
constexpr int FlagPawnStart = 0x80000;
constexpr int FlagCastle = 0x1000000;

constexpr int FlagCapture = 0x7C000;
constexpr int FlagPromote = 0xF00000;

} // namespace Move

#endif
