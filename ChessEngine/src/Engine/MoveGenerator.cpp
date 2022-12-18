#include "MoveGenerator.h"

#include <iostream>

static void AddQuietMove(const BOARD *position, int move, MOVELIST *list);
static void AddCaptureMove(const BOARD *position, int move, MOVELIST *list);
static void AddEnPassantMove(const BOARD *position, int move, MOVELIST *list);
static void AddWhitePawnMove(const BOARD *position, const int from, const int to, MOVELIST * list);
static void AddWhitePawnCapMove(const BOARD *position, const int from, const int to, const int cap, MOVELIST * list);
static void AddBlackPawnMove(const BOARD *position, const int from, const int to, MOVELIST * list);
static void AddBlackPawnCapMove(const BOARD *position, const int from, const int to, const int cap, MOVELIST * list);

const int LoopSlidePiece[8] = {
	wB, wR, wQ, 0, bB, bR, bQ, 0
};

const int LoopNonSlidePiece[8] = {
	wN, wK, 0, bN, bK, 0
};

const int LoopSlideIndex[2] = {0,4};
const int LoopNonSlideIndex[2] = {0,3};

const int PieceDirection[13][8] = {
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{-8, -19, -21, -12, 8, 19, 21, 12},
		{-9, -11, 11, 9, 0, 0, 0, 0},
		{-1, -10, 1, 10, 0, 0, 0, 0},
		{-1, -10, 1, 10, -9, -11, 11, 9},
		{-1, -10, 1, 10, -9, -11, 11, 9},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{-8, -19, -21, -12, 8, 19, 21, 12},
		{-9, -11, 11, 9, 0, 0, 0, 0},
		{-1, -10, 1, 10, 0, 0, 0, 0},
		{-1, -10, 1, 10, -9, -11, 11, 9},
		{-1, -10, 1, 10, -9, -11, 11, 9}
};

int DirectionNumber[13] = {0,0,8,4,4,8,8,0,8,4,4,8,8};

void GenerateAllMoves(const BOARD *position, MOVELIST *list){

	ASSERT(CheckBoard(position));
	list->count = 0;
	int piece = EMPTY;
	int side = position->side;
	int square, t_square, pieceNumber = 0;

	int dir, index, pieceIndex = 0;
	bool emptyRoad,safeRoad;

	if(side == WHITE){
		//pawns
		for(pieceNumber = 0; pieceNumber < position->pieceNumber[wP]; ++pieceNumber){
			square = position->pieceList[wP][pieceNumber];
			ASSERT(SquareOnBoard(square));

			if(position->pieces[square + 10] == EMPTY){
				AddWhitePawnMove(position, square, square + 10, list);
				if(RanksBoard[square] == RANK_2 && position->pieces[square + 20] == EMPTY)
					AddQuietMove(position, MOVE_M(square,square + 20,EMPTY,EMPTY,MFLAGPS), list);
			}

			if(!SQUAREOFFBOARD(square + 9) && PieceColour[position->pieces[square + 9]] == BLACK)
				AddWhitePawnCapMove(position, square, square + 9, position->pieces[square + 9], list);
			if(!SQUAREOFFBOARD(square + 11) && PieceColour[position->pieces[square + 11]] == BLACK)
				AddWhitePawnCapMove(position, square, square + 11, position->pieces[square + 11], list);

			if(square + 9 == position->enPassant)
				AddCaptureMove(position,MOVE_M(square,square + 9, EMPTY,EMPTY,MFLAGEP),list);
			if(square + 11 == position->enPassant)
				AddCaptureMove(position,MOVE_M(square,square + 11, EMPTY,EMPTY,MFLAGEP),list);
		}

		//castle
		if(position->castlePermission & wKCastle){
			emptyRoad = position->pieces[F1] == EMPTY && position->pieces[G1] == EMPTY;
			safeRoad = !SqAttacked(E1, BLACK, position) && !SqAttacked(F1, BLACK, position);
			if(emptyRoad && safeRoad){
				AddQuietMove(position, MOVE_M(E1,G1,EMPTY,EMPTY,MFLAGCA), list);
			}
		}

		if(position->castlePermission & wQCastle){
			emptyRoad = position->pieces[D1] == EMPTY && position->pieces[C1] == EMPTY && position->pieces[B1] == EMPTY;
			safeRoad = !SqAttacked(E1, BLACK, position) && !SqAttacked(D1, BLACK, position);
			if(emptyRoad && safeRoad){
				AddQuietMove(position, MOVE_M(E1,C1,EMPTY,EMPTY,MFLAGCA), list);
			}
		}
	}else{
		//pawns
		std::cout<<position->enPassant<<" ENPASSANT\n";
		for(pieceNumber = 0; pieceNumber < position->pieceNumber[bP]; ++pieceNumber){
			square = position->pieceList[bP][pieceNumber];
			ASSERT(SquareOnBoard(square));

			if(position->pieces[square - 10] == EMPTY){
				AddBlackPawnMove(position, square, square - 10, list);
				if(RanksBoard[square] == RANK_7 && position->pieces[square - 20] == EMPTY)
					AddQuietMove(position, MOVE_M(square,square - 20,EMPTY,EMPTY,MFLAGPS), list);
			}

			if(!SQUAREOFFBOARD(square - 9) && PieceColour[position->pieces[square - 9]] == WHITE)
				AddBlackPawnCapMove(position, square, square - 9, position->pieces[square - 9], list);
			if(!SQUAREOFFBOARD(square - 11) && PieceColour[position->pieces[square - 11]] == WHITE)
				AddBlackPawnCapMove(position, square, square - 11, position->pieces[square - 11], list);

			if(square - 9 == position->enPassant)
				AddCaptureMove(position,MOVE_M(square,square - 9, EMPTY,EMPTY,MFLAGEP),list);
			if(square - 11 == position->enPassant)
				AddCaptureMove(position,MOVE_M(square,square - 11, EMPTY,EMPTY,MFLAGEP),list);
		}

		//castle
		if(position->castlePermission & bKCastle){
			emptyRoad = position->pieces[F8] == EMPTY && position->pieces[G8] == EMPTY;
		safeRoad = !SqAttacked(E8, WHITE, position) && !SqAttacked(F8, WHITE, position);
			if(emptyRoad && safeRoad){
				AddQuietMove(position, MOVE_M(E8,G8,EMPTY,EMPTY,MFLAGCA), list);
			}
		}

		if(position->castlePermission & bQCastle){
			emptyRoad = position->pieces[D8] == EMPTY && position->pieces[C8] == EMPTY && position->pieces[B8] == EMPTY;
			safeRoad = !SqAttacked(E8, WHITE, position) && !SqAttacked(D8, WHITE, position);
			if(emptyRoad && safeRoad){
				AddQuietMove(position, MOVE_M(E8,C8,EMPTY,EMPTY,MFLAGCA), list);
			}
		}
	}

	//sliders
	pieceIndex = LoopSlideIndex[side];
	piece =  LoopSlidePiece[pieceIndex++];
	while(piece != 0){
		ASSERT(PieceValid(piece));

		for(pieceNumber = 0; pieceNumber < position->pieceNumber[piece]; ++pieceNumber){
			square = position->pieceList[piece][pieceNumber];
			ASSERT(SquareOnBoard(square));

			for(index = 0; index < DirectionNumber[piece]; ++index){
				dir = PieceDirection[piece][index];
				t_square = square + dir;

				while(!SQUAREOFFBOARD(t_square)){
					if(position->pieces[t_square] != EMPTY){
						if(PieceColour[position->pieces[t_square]] == (side ^ 1)){
							AddCaptureMove(position, MOVE_M(square,t_square,position->pieces[t_square],EMPTY,0), list);
						}
						break;
					}
					AddQuietMove(position, MOVE_M(square,t_square,EMPTY,EMPTY,0), list);
					t_square +=dir;
				}
			}
		}

		piece = LoopSlidePiece[pieceIndex++];
	}

	//non-sliders
	pieceIndex = LoopNonSlideIndex[side];
	piece =  LoopNonSlidePiece[pieceIndex++];
	while(piece != 0){
		ASSERT(PieceValid(piece));

		for(pieceNumber = 0; pieceNumber < position->pieceNumber[piece]; ++pieceNumber){
			square = position->pieceList[piece][pieceNumber];
			ASSERT(SquareOnBoard(square));

			for(index = 0; index < DirectionNumber[piece]; ++index){
				dir = PieceDirection[piece][index];
				t_square = square + dir;

				if(SQUAREOFFBOARD(t_square)){
					continue;
				}

				if(position->pieces[t_square] != EMPTY){
					if(PieceColour[position->pieces[t_square]] == (side ^ 1)){
						AddCaptureMove(position, MOVE_M(square,t_square,position->pieces[t_square],EMPTY,0), list);
					}
					continue;
				}
				AddQuietMove(position, MOVE_M(square,t_square,EMPTY,EMPTY,0), list);
			}
		}

		piece = LoopNonSlidePiece[pieceIndex++];
	}
}

static void AddWhitePawnCapMove(const BOARD *position, const int from, const int to, const int cap, MOVELIST * list){

	ASSERT(SquareOnBoard(from));
	ASSERT(SquareOnBoard(to));
	ASSERT(PieceValidEmpty(cap));

	if(RanksBoard[from] == RANK_7){
		AddCaptureMove(position,MOVE_M(from,to,cap,wQ,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,wR,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,wB,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,wN,0),list);
	}else{
		AddCaptureMove(position,MOVE_M(from,to,cap,EMPTY,0),list);
	}
}

static void AddWhitePawnMove(const BOARD *position, const int from, const int to, MOVELIST * list){

	ASSERT(SquareOnBoard(from));
	ASSERT(SquareOnBoard(to));

	if(RanksBoard[from] == RANK_7){
		AddQuietMove(position,MOVE_M(from,to,EMPTY,wQ,0),list);
		AddQuietMove(position,MOVE_M(from,to,EMPTY,wR,0),list);
		AddQuietMove(position,MOVE_M(from,to,EMPTY,wB,0),list);
		AddQuietMove(position,MOVE_M(from,to,EMPTY,wN,0),list);
	}else{
		AddQuietMove(position,MOVE_M(from,to,EMPTY,EMPTY,0),list);
	}
}

static void AddBlackPawnCapMove(const BOARD *position, const int from, const int to, const int cap, MOVELIST * list){

	ASSERT(SquareOnBoard(from));
	ASSERT(SquareOnBoard(to));
	ASSERT(PieceValidEmpty(cap));

	if(RanksBoard[from] == RANK_2){
		AddCaptureMove(position,MOVE_M(from,to,cap,bQ,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,bR,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,bB,0),list);
		AddCaptureMove(position,MOVE_M(from,to,cap,bN,0),list);
	}else{
		AddCaptureMove(position,MOVE_M(from,to,cap,EMPTY,0),list);
	}
}

static void AddBlackPawnMove(const BOARD *position, const int from, const int to, MOVELIST * list){

	ASSERT(SquareOnBoard(from));
	ASSERT(SquareOnBoard(to));

	if(RanksBoard[from] == RANK_2){
		AddQuietMove(position,MOVE_M(from,to,EMPTY,bQ,0),list);
		AddQuietMove(position,MOVE_M(from,to,EMPTY,bR,0),list);
		AddQuietMove(position,MOVE_M(from,to,EMPTY,bB,0),list);
		AddQuietMove(position,MOVE_M(from,to,EMPTY,bN,0),list);
	}else{
		AddQuietMove(position,MOVE_M(from,to,EMPTY,EMPTY,0),list);
	}
}

static void AddQuietMove(const BOARD *position, int move, MOVELIST *list){
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

static void AddCaptureMove(const BOARD *position, int move, MOVELIST *list){
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}

static void AddEnPassantMove(const BOARD *position, int move, MOVELIST *list){
	list->moves[list->count].move = move;
	list->moves[list->count].score = 0;
	list->count++;
}



