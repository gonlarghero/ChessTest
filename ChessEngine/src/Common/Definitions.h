#ifndef COMMON_DEFINITIONS_H
#define COMMON_DEFINITIONS_H

#include <cstdint>

namespace Definitions {

using U64 = std::uint64_t;

// Board dimensions and piece definitions
constexpr int BOARD_SQUARE_NUMBER = 120;
constexpr int BOARD_REAL_NUMBER = 64;
constexpr int PIECE_TYPE_NUMBER = 13;
constexpr int COLOUR_NUMBER = 3;
constexpr int MAX_GAME_MOVES = 2048;
constexpr int MAX_POSITION_MOVES = 256;
constexpr int MAX_OF_ONE_PIECE = 10;
constexpr int CASTLE_BITS = 16;
constexpr int MAX_DEPTH = 64;

// Move & search
constexpr int NOMOVE = 0;
constexpr int INFINITY_SCORE = 30000;
constexpr int MATE_SCORE = 29000;
constexpr int PERF_DEPTH_DEFAULT = 5;
constexpr int PV_LINE_DEPTH_DEFAULT = 4;
constexpr int SEARCH_DEPTH_DEFAULT = 5;
constexpr int SEARCH_TIMEOUT_INTERVAL = 2047;

// Bit encoding for moves
constexpr int TO_SHIFT = 7;
constexpr int CAPTURE_SHIFT = 14;
constexpr int PROMOTE_SHIFT = 20;

// Move ordering scores
constexpr int PV_MOVE_SCORE = 2000000;
constexpr int CAPTURE_MOVE_SCORE = 1000000;
constexpr int KILLER_MOVE_SCORE = 900000;
constexpr int COUNTER_MOVE_SCORE = 800000;

// FENs
constexpr const char *START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
constexpr const char *TEST_FEN = "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1";
constexpr const char *TEST_FEN2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";

} // namespace Definitions
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
