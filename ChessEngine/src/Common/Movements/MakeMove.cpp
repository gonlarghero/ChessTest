#include "MakeMove.h"

const int CastlePermission[120] = {
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 7, 15, 15, 15, 3, 15, 15, 11, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};


static void ClearPiece(int square, BOARD *position);
static void AddPiece(const int square, BOARD *position, int piece);
static void MovePiece(const int from, const int to, BOARD * position);






static void ClearPiece(int square, BOARD *position){

	ASSERT(SquareOnBoard(square));

	int piece = position->pieces[square];

	ASSERT(PieceValid(piece));

	int colour = PieceColour[piece];
	int index = 0;
	int t_pieceNum = -1;

	HASH_PIECE(piece,square);

	position->pieces[square] = EMPTY;
	position->material[colour] -= PieceValue[piece];

	if(PieceBig[piece]){
		position->bigPieces[colour]--;
		if(PieceMajor[piece])
			position->majorPieces[colour]--;
		else
			position->minorPieces[colour]--;
	}else{
		CLEARBIT(position->pawns[colour],Sq120ToSq64(square));
		CLEARBIT(position->pawns[BOTH],Sq120ToSq64(square));
	}

	for(index = 0; index < position->pieceNumber[piece]; +++piece){
		if(position->pieceList[piece][index] == square){
			t_pieceNum = index;
			break;
		}
	}

	ASSERT(t_pieceNum != -1);

	position->pieceNumber[piece]--;
	position->pieceList[piece][t_pieceNum] = position->pieceList[piece][position->pieceNumber[piece]];

}

static void AddPiece(const int square, BOARD *position, int piece){

	ASSERT(PieceValid(piece));
	ASSERT(SquareOnBoard(square));

	int colour = PieceColour[piece];

	HASH_PIECE(piece,square);

	position->pieces[square] = piece;
	position->material[colour] += PieceValue[piece];

	if(PieceBig[piece]){
		position->bigPieces[colour]++;
		if(PieceMajor[piece])
			position->majorPieces[colour]++;
		else
			position->minorPieces[colour]++;
	}else{
		SETBIT(position->pawns[colour],Sq120ToSq64(square));
		SETBIT(position->pawns[BOTH],Sq120ToSq64(square));
	}


	position->pieceList[piece][position->pieceNumber[piece]] = square;
	position->pieceNumber[piece]++;

}

static void MovePiece(const int from, const int to, BOARD * position){

	ASSERT(SquareOnBoard(from));
	ASSERT(SquareOnBoard(to));

	int index = 0;
	int piece = position->pieces[from];
	int colour = PieceColour[piece];
#ifdef DEBUG
	bool t_pieceNumber = false;
#endif
	HASH_PIECE(piece,from);
	position->pieces[from] = EMPTY;
	HASH_PIECE(piece,to);
	position->pieces[to] = piece;

	if(!PieceBig[piece]){
		CLEARBIT(position->pawns[colour],Sq120ToSq64(from));
		CLEARBIT(position->pawns[BOTH],Sq120ToSq64(from));
		SETBIT(position->pawns[colour],Sq120ToSq64(to));
		SETBIT(position->pawns[BOTH],Sq120ToSq64(to));
	}

	for(index = 0; index < position->pieceNumber[piece]; ++index){
		if(position->pieceList[piece][index] == from){
			position->pieceList[piece][index] = to;
#ifdef DEBUG
			t_pieceNumber = true;
#endif
		}
	}
	ASSERT(t_pieceNumber);
}
