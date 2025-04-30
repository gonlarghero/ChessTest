#include "Evaluate.h"

const int PawnIsolated = -10;
const int PawnPassed[8] = {0, 5, 10, 20, 35, 60, 100, 200};
const int RookOpenFile = 10;
const int RookSemiOpenFile = 5;
const int QueenOpenFile = 5;
const int QueenSemiOpenFile = 3;
const int BishopPair = 30;

int EvalPosition(const BOARD *position) {
    int piece, pieceNum, square = 0;
    int score = position->material[WHITE] - position->material[BLACK];

    piece = wP;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        score += PawnTable[Sq120ToSq64[square]];
    }

    piece = bP;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        ASSERT(Global::Mirror64(Sq120ToSq64[square]) >= 0 && Global::Mirror64(Sq120ToSq64[square]) <= 63);
        score -= PawnTable[Global::Mirror64(Sq120ToSq64[square])];
    }

    piece = wN;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        ASSERT(Sq120ToSq64[square] >= 0 && Sq120ToSq64[square] <= 63);
        score += KnightTable[Sq120ToSq64[square]];
    }

    piece = bN;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        ASSERT(Global::Mirror64(Sq120ToSq64[square]) >= 0 && Global::Mirror64(Sq120ToSq64[square]) <= 63);
        score -= KnightTable[Global::Mirror64(Sq120ToSq64[square])];
    }

    piece = wB;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        ASSERT(Sq120ToSq64[square] >= 0 && Sq120ToSq64[square] <= 63);
        score += BishopTable[Sq120ToSq64[square]];
    }

    piece = bB;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        ASSERT(Global::Mirror64(Sq120ToSq64[square]) >= 0 && Global::Mirror64(Sq120ToSq64[square]) <= 63);
        score -= BishopTable[Global::Mirror64(Sq120ToSq64[square])];
    }

    piece = wR;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        ASSERT(Sq120ToSq64[square] >= 0 && Sq120ToSq64[square] <= 63);
        score += RookTable[Sq120ToSq64[square]];
    }

    piece = bR;
    for (pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
        square = position->pieceList[piece][pieceNum];
        ASSERT(SquareOnBoard(square));
        ASSERT(Global::Mirror64(Sq120ToSq64[square]) >= 0 &&
               Global::Mirror64(Sq120ToSq64[square]) <= BOARD_REAL_NUMBER - 1);
        score -= RookTable[Global::Mirror64(Sq120ToSq64[square])];
    }
    if (position->side == WHITE)
        return score;
    else
        return -score;
}
