#include "Attack.h"

const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir[4] = {-9, -11, 11, 9};
const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};


bool SqAttacked(const int square, const int side, const BOARD *position){

	ASSERT(SquareOnBoard(square));
	ASSERT(SideValid(side));
	ASSERT(CheckBoard(position));

	int piece, index , t_square, dir = 0;

	//pawns
	if(side == WHITE){
		if(position->pieces[square-11] == wP || position->pieces[square-9] == wP)
			return true;
	}
	if(position->pieces[square+11] == bP || position->pieces[square+9] == bP)
		return true;

	for(index = 0; index < 8; ++index){
		//knights
		piece = position->pieces[square + KnDir[index]];
		if(IsKn(piece) && PieceColour[piece] == side)
			return true;
		//kings
		piece = position->pieces[square + KiDir[index]];
		if(IsKi(piece) && PieceColour[piece] == side)
			return true;
	}

	for(index = 0; index < 4; ++index){
		//rooks && queens
		dir = RkDir[index];
		t_square = square + dir;
		piece = position->pieces[t_square];
		while(piece != SQUARE_NULL){
			if(piece != EMPTY){
				if(IsRQ(piece) && PieceColour[piece]){
					return true;
				}
				break;
			}
			t_square += dir;
			piece = position->pieces[t_square];
		}
		//bishops && queens
		dir = BiDir[index];
		t_square = square + dir;
		piece = position->pieces[t_square];
		while(piece != SQUARE_NULL){
			if(piece != EMPTY){
				if(IsBQ(piece) && PieceColour[piece]){
					return true;
				}
				break;
			}
			t_square += dir;
			piece = position->pieces[t_square];
		}
	}

	return false;
}

