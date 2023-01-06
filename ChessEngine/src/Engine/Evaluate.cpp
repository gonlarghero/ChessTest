#include "Evaluate.h"

const int PawnIsolated = -10;
const int PawnPassed[8] = { 0, 5, 10, 20, 35, 60, 100, 200 };
const int RookOpenFile = 10;
const int RookSemiOpenFile = 5;
const int QueenOpenFile = 5;
const int QueenSemiOpenFile = 3;
const int BishopPair = 30;


int EvalPosition(const BOARD *position){
	int piece, pieceNum, square = 0;
	int score = position->material[WHITE] - position->material[BLACK];

	piece = wP;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum){
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		score += PawnTable[Sq120ToSq64[square]];
	}

	piece = bP;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(MIRROR64(Sq120ToSq64[square])>=0 && MIRROR64(Sq120ToSq64[square])<=63);
		score -= PawnTable[MIRROR64(Sq120ToSq64[square])];

	}

	piece = wN;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(Sq120ToSq64[square]>=0 && Sq120ToSq64[square]<=63);
		score += KnightTable[Sq120ToSq64[square]];
	}

	piece = bN;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(MIRROR64(Sq120ToSq64[square])>=0 && MIRROR64(Sq120ToSq64[square])<=63);
		score -= KnightTable[MIRROR64(Sq120ToSq64[square])];
	}

	piece = wB;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(Sq120ToSq64[square]>=0 && Sq120ToSq64[square]<=63);
		score += BishopTable[Sq120ToSq64[square]];
	}

	piece = bB;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(MIRROR64(Sq120ToSq64[square])>=0 && MIRROR64(Sq120ToSq64[square])<=63);
		score -= BishopTable[MIRROR64(Sq120ToSq64[square])];
	}

	piece = wR;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(Sq120ToSq64[square]>=0 && Sq120ToSq64[square]<=63);
		score += RookTable[Sq120ToSq64[square]];
	}

	piece = bR;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(MIRROR64(Sq120ToSq64[square])>=0 && MIRROR64(Sq120ToSq64[square])<=63);
		score -= RookTable[MIRROR64(Sq120ToSq64[square])];
	}

	/*piece = wQ;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(Sq120ToSq64[square]>=0 && Sq120ToSq64[square]<=63);
		ASSERT(FileRankValid(FilesBrd[square]));
		if(!(position->pawns[BOTH] & FileBBMask[FilesBrd[square]])) {
			score += QueenOpenFile;
		} else if(!(position->pawns[WHITE] & FileBBMask[FilesBrd[square]])) {
			score += QueenSemiOpenFile;
		}
	}

	piece = bQ;
	for(pieceNum = 0; pieceNum < position->pieceNumber[piece]; ++pieceNum) {
		square = position->pieceList[piece][pieceNum];
		ASSERT(SquareOnBoard(square));
		ASSERT(Sq120ToSq64[square]>=0 && Sq120ToSq64[square]<=63);
		ASSERT(FileRankValid(FilesBrd[square]));
		if(!(position->pawns[BOTH] & FileBBMask[FilesBrd[square]])) {
			score -= QueenOpenFile;
		} else if(!(position->pawns[BLACK] & FileBBMask[FilesBrd[square]])) {
			score -= QueenSemiOpenFile;
		}
	}*/

	if(position->side == WHITE)
		return score;
	else
		return -score;

}

