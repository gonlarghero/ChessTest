#include "MoveGenerator.h"


void GenerateAllMoves(const BOARD *position, MOVELIST *list){

	ASSERT(CheckBoard(position));
	list->count = 0;
	int piece = EMPTY;
	int side = position->side;
	int square, t_square, pieceNumber = 0;

	if(side == WHITE){
		//pawns
		for(pieceNumber = 0; pieceNumber < position->pieceNumber[wP]; ++pieceNumber){
			square = position->pieceList[wP][pieceNumber];
			ASSERT(SquareOnBoard(square));

			if(position->pieces[square + 10 == EMPTY]){
				AddWhitePawnMove(position, square, square + 10, list);
				if(RanksBoard[square] == RANK_2 && position->pieces[square + 20] == EMPTY)
					AddQuietMove(position, MOVE_M(square,square + 20,EMPTY,EMPTY,MFLAGPS), list);
			}

			if(!SQUAREOFFBOARD(square) && PieceColour[position->pieces[square + 9]] == BLACK)
				AddWhitePawnCapMove(position, square, square + 9, position->pieces[square + 9], list);
			if(!SQUAREOFFBOARD(square) && PieceColour[position->pieces[square + 11]] == BLACK)
				AddWhitePawnCapMove(position, square, square + 11, position->pieces[square + 11], list);

			if(square + 9 == position->enPassant)
				AddCaptureMove(position,MOVE_M(square,square + 9, EMPTY,EMPTY,MFLAGEP),list);
			if(square + 11 == position->enPassant)
				AddCaptureMove(position,MOVE_M(square,square + 11, EMPTY,EMPTY,MFLAGEP),list);


		}
	}else{

	}
}

void AddWhitePawnCapMove(const BOARD *position, const int from, const int to, const int cap, MOVELIST * list){
	if(RanksBoard[from] == RANK_7){
		AddCaptureMove(position,MOVE_M(from,to,cap,wQ,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,wR,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,wB,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,wN,0),list);
	}else{
		AddCaptureMove(position,MOVE_M(from,to,cap,EMPTY,0),list);
	}
}

void AddWhitePawnMove(const BOARD *position, const int from, const int to, MOVELIST * list){
	if(RanksBoard[from] == RANK_7){
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,wQ,0),list);
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,wR,0),list);
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,wB,0),list);
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,wN,0),list);
	}else{
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,EMPTY,0),list);
	}
}

void AddBlackPawnCapMove(const BOARD *position, const int from, const int to, const int cap, MOVELIST * list){
	if(RanksBoard[from] == RANK_2){
		AddCaptureMove(position,MOVE_M(from,to,cap,bQ,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,bR,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,bB,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,bN,0),list);
	}else{
		AddCaptureMove(position,MOVE_M(from,to,cap,EMPTY,0),list);
	}
}

void AddBlackPawnMove(const BOARD *position, const int from, const int to, MOVELIST * list){
	if(RanksBoard[from] == RANK_2){
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,bQ,0),list);
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,bR,0),list);
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,bB,0),list);
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,bN,0),list);
	}else{
		AddCaptureMove(position,MOVE_M(from,to,EMPTY,EMPTY,0),list);
	}
}

void AddQuietMove(const BOARD *position, int move, MOVELIST *list){
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddCaptureMove(const BOARD *position, int move, MOVELIST *list){
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

void AddEnPassantMove(const BOARD *position, int move, MOVELIST *list){
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}



