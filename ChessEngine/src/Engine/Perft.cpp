#include "Perft.h"

#include <iostream>
#include <iomanip>
#include <windows.h>

long leafNodes;

void Perft(int depth,BOARD *position, int parent){

	ASSERT(CheckBoard(position));

	if(depth == 0){
		leafNodes++;
		return;
	}

	MOVELIST list[1];
	GenerateAllMoves(position, list);
	int moveNum = 0;
	for(moveNum = 0; moveNum < list->count; ++moveNum){
		if(!MakeMove(position, list->moves[moveNum].move)){
			continue;
		}

		Perft(depth-1,position,list->moves[moveNum].move);
		TakeMove(position);
	}

	return;
}

void PerfTest(int depth, BOARD *position){

	ASSERT(CheckBoard(position));

	PrintBoard(position);

	std::cout<<"\nSTARTING TEST TO DEPTH: "<< depth<<"\n";

	leafNodes = 0;

	int start = GetTickCount();

	MOVELIST list[1];
	GenerateAllMoves(position, list);

	int move;
	int moveNum = 0;
	for(moveNum = 0; moveNum < list->count; ++moveNum){
		move = list->moves[moveNum].move;
		if(!MakeMove(position, move)){
			continue;
		}
		long cumnodes = leafNodes;
		Perft(depth-1,position,move);
		TakeMove(position);
		long oldnodes = leafNodes - cumnodes;
		std::cout<<"MOVE: "<<moveNum+1<<" : "<<PrintMove(move)<<" : "<<oldnodes<<"\n";
	}
	std::cout<<std::setprecision(6)<<"TEST COMPLETE: "<<leafNodes<<" VISITED IN "<<GetTickCount()- start<<" MILISECONDS.\n";
	return;

}
