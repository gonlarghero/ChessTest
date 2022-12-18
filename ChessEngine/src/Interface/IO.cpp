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


