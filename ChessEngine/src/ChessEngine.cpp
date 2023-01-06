#include <iostream>
#include "Data/DataManager.h"
#include "Engine/EngineManager.h"
#include "Interface/InterfaceManager.h"

#include <stdlib.h>

#include "Data/Fen.h"
#include "Common/Board.h"
#include "Engine/Search.h"
#include "Engine/Perft.h"

int main(int, char**) {

    LoadData();
    StartEngine();
    StartInterface();

    BOARD board[1];
    SEARCHINFO info[1];
    ParseFen(TEST_FEN, board);

    char input[6];
    int move = NOMOVE;

    int pvnum = 0;
    int max = 0;

    while(true){
    	PrintBoard(board);
    	std::cout<<"Please enter a move> ";
    	fgets(input, 6, stdin);

    	if(input[0] == 'q' || input[0] == 'Q'){
    		break;
    	}else if(input[0] == 't'){
    		TakeMove(board);
    	}else if(input[0] == 'p'){
    		PerfTest(4, board);
    	}else if(input[0] == 'r'){
    		max = GetPVLine(4, board);
    		std::cout<<"PvLine of "<<max<<" moves: ";
    		for(pvnum =0; pvnum<max;++pvnum){
    			move = board->pvArray[pvnum];
    			std::cout<<PrintMove(move)<<" ";
    		}
    		std::cout<<"\n";
    	}else if(input[0] == 's'){
    		info->depth = 4;
    		SearchPosition(board, info);
    	}else{
    		move = ParseMove(input, board);
    		if(move != NOMOVE){
    			StorePVMove(board, move);
    			MakeMove(board, move);
    		}else {
    			std::cout<<"Move not parsed \n";
    		}
    	}

    	fflush(stdin);
    }

    return 0;
}
