#include "IO.h"

#include <stdio.h>
#include <iostream>

char *PrintSquare(const int square){

	static char SqStr[3];

	int file = FilesBoard[square];
	int rank = RanksBoard[square];

	sprintf(SqStr, "%c%c", ('a'+file),('1'+rank));

	return SqStr;
}

char *PrintMove(const int move){
	static char MoveStr[6];

	int ff = FilesBoard[FROMSQ(move)];
	int rf = RanksBoard[FROMSQ(move)];
	int ft = FilesBoard[TOSQ(move)];
	int rt = RanksBoard[TOSQ(move)];

	int promoted = PROMOTED(move);

	if(promoted){
		char pchar = 'q';
		if(IsKn(promoted)){
			pchar = 'n';
		}else if(IsRQ(promoted) && !IsBQ(promoted)){
			pchar = 'r';
		}else if(!IsRQ(promoted) && IsBQ(promoted)){
			pchar = 'b';
		}
		sprintf(MoveStr, "%c%c%c%c%c", ('a'+ff),('1'+rf), ('a'+ft),('1'+rt),pchar);
	}else{
		sprintf(MoveStr, "%c%c%c%c", ('a'+ff),('1'+rf), ('a'+ft),('1'+rt));
	}

	return MoveStr;
}

void PrintMoveList(const MOVELIST *list){
	int index,score,move = 0;
	std::cout<<"MoveList: "<<list->count<<"\n";

	for(index = 0; index < list->count ;++index){
		move = list->moves[index].move;
		score = list->moves[index].score;
		printf("Move %d > %s (score %d)\n", index+1, PrintMove(move),score);
	}
	std::cout<<"MoveList Total "<< list->count << " moves: \n\n";
}

int ParseMove(char *ptrChar, BOARD* position){

	if(ptrChar[0] > 'h' || ptrChar[0] < 'a') return NOMOVE;
	if(ptrChar[1] > '8' || ptrChar[1] < '1') return NOMOVE;
	if(ptrChar[2] > 'h' || ptrChar[2] < 'a') return NOMOVE;
	if(ptrChar[3] > '8' || ptrChar[3] < '1') return NOMOVE;

	int from = FR2SQ(ptrChar [0] - 'a', ptrChar[1] - '1');
	int to = FR2SQ(ptrChar [2] - 'a', ptrChar[3] - '1');

	std::cout<<"Move: "<<ptrChar<<" from: "<< from<<" to: "<<to<<"\n";

	ASSERT(SquareOnBoard(from) && SquareOnBoard(to));

	MOVELIST list[1];
	GenerateAllMoves(position, list);
	int moveNum,move = 0;
	int promotionPiece = EMPTY;

	for(moveNum = 0; moveNum <list->count; ++moveNum){
		move = list->moves[moveNum].move;
		if(FROMSQ(move) == from && TOSQ(move) == to){
			promotionPiece = PROMOTED(move);
			if(promotionPiece != EMPTY){
				if(IsRQ(promotionPiece) && !IsBQ(promotionPiece) && ptrChar[4] == 'r')
					return move;
				else if(!IsRQ(promotionPiece) && IsBQ(promotionPiece) && ptrChar[4] == 'b')
					return move;
				else if(IsRQ(promotionPiece) && IsBQ(promotionPiece) && ptrChar[4] == 'q')
					return move;
				else if(IsKn(promotionPiece) && ptrChar[4] == 'n')
					return move;
			}
			return move;
		}
	}

	return NOMOVE;
}

