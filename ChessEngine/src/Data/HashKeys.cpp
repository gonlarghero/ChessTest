#include "HashKeys.h"

U64 GeneratePositionKey(const BOARD *position){

	int square = 0;
	U64 finalKey =0;
	int piece = EMPTY;

	for(square = 0; square < BOARD_SQUARE_NUMBER; ++square){
		piece = position->pieces[square];
		if(square != SQUARE_NULL && piece != EMPTY)
			finalKey ^= PieceKeys[piece][square];
	}

	if(position->side == WHITE){
		finalKey^= SideKey;
	}

	if(position->enPassant != SQUARE_NULL)
		finalKey ^= PieceKeys[EMPTY][position->enPassant];

	finalKey ^= CastleKeys[position->castlePermission];

	return finalKey;
}

void InitializeHashKeys(){

	int index = 0;
	int index2 = 0;
	for(index = 0; index < PIECE_TYPE_NUMBER; ++index){
		for(index2 = 0; index2 < BOARD_SQUARE_NUMBER; ++index2){
			PieceKeys[index][index2] = RAND_64();
		}
	}
	SideKey = RAND_64();
	for(index = 0; index < CASTLE_BITS; ++index){
		CastleKeys[index] = RAND_64();
	}
}
