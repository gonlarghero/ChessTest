#include "Validate.h"

bool SquareOnBoard(const int square){
	return FilesBoard[square] != SQUARE_NULL;
}

bool SideValid(const int side){
	return side == WHITE || side == BLACK;
}

bool FileRankValide(const int fr){
	return fr >= 0 && fr <= 7;
}

bool PieceValidEmpty(const int piece){
	return piece >= EMPTY && piece <= bK;
}

bool PieceValid(const int piece){
	return piece >= wP && piece <= bK;
}
