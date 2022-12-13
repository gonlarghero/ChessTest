#include "BoardValidator.h"

#include <iostream>

bool CheckBoard(const BOARD *position){

	int t_pieceNumber[PIECE_TYPE_NUMBER] = {0};
	int t_bigPiece[COLOUR_NUMBER-1] = {0};
	int t_majorPiece[COLOUR_NUMBER-1] = {0};
	int t_minorPiece[COLOUR_NUMBER-1] = {0};
	int t_material[COLOUR_NUMBER-1] = {0};

	int square64, square120, t_piece, colour, pawnCount = 0;
	int t_piece_number = 0;

	U64 t_pawns[COLOUR_NUMBER];
	t_pawns[WHITE] = position->pawns[WHITE];
	t_pawns[BLACK] = position->pawns[BLACK];
	t_pawns[BOTH] = position->pawns[BOTH];

	for(t_piece = wP; t_piece <= bK; ++t_piece){
		square120 = position->pieceList[t_piece][t_piece_number];
		ASSERT(position->pieces[square120] == t_piece);
	}
	for(square64 = 0; square64 < BOARD_REAL_NUMBER; ++square64){
		square120 = Sq64ToSq120[square64];
		t_piece = position->pieces[square120];
		t_pieceNumber[t_piece]++;
		colour = PieceColour[t_piece];
		if(PieceBig[t_piece])
			t_bigPiece[colour]++;
		if(PieceMinor[t_piece])
			t_minorPiece[colour]++;
		if(PieceMajor[t_piece])
			t_majorPiece[colour]++;
		t_material[colour] += PieceValue[t_piece];
	}
	for(t_piece = wP; t_piece <= bK; ++t_piece)
		ASSERT(t_pieceNumber[t_piece] == position->pieceNumber[t_piece]);

	pawnCount = CountBits(t_pawns[WHITE]);
	ASSERT(pawnCount == position->pieceNumber[wP]);
	pawnCount = CountBits(t_pawns[BLACK]);
	ASSERT(pawnCount == position->pieceNumber[bP]);
	pawnCount = CountBits(t_pawns[BOTH]);
	ASSERT(pawnCount == (position->pieceNumber[wP]+ position->pieceNumber[bP]));

	while(t_pawns[WHITE]){
		square64 = PopBit(&t_pawns[WHITE]);
		ASSERT(position->pieces[Sq64ToSq120[square64]] == wP);
	}
	while(t_pawns[BLACK]){
		square64 = PopBit(&t_pawns[BLACK]);
		ASSERT(position->pieces[Sq64ToSq120[square64]] == bP);
	}
	while(t_pawns[BOTH]){
		square64 = PopBit(&t_pawns[BOTH]);
		ASSERT((position->pieces[Sq64ToSq120[square64]] == wP) || (position->pieces[Sq64ToSq120[square64]] == bP));
	}

	ASSERT(t_material[WHITE] == position->material[WHITE] && t_material[BLACK] == position->material[BLACK]);
	ASSERT(t_bigPiece[WHITE] == position->bigPieces[WHITE] && t_bigPiece[BLACK] == position->bigPieces[BLACK]);
	ASSERT(t_majorPiece[WHITE] == position->majorPieces[WHITE] && t_majorPiece[BLACK] == position->majorPieces[BLACK]);
	ASSERT(t_minorPiece[WHITE] == position->minorPieces[WHITE] && t_minorPiece[BLACK] == position->minorPieces[BLACK]);

	ASSERT(position->side == WHITE || position->side == BLACK);
	ASSERT(GeneratePositionKey(position) == position->positionKey);

	ASSERT(position->enPassant == SQUARE_NULL ||
			(RanksBoard[position->enPassant] == RANK_6 && position->side == WHITE)||
			(RanksBoard[position->enPassant] == RANK_3 && position->side == BLACK));

	ASSERT(position->pieces[position->Kings[WHITE]] == wK);
	ASSERT(position->pieces[position->Kings[BLACK]] == bK);

	return true;
}

