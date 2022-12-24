#include <iostream>
#include "Data/DataManager.h"
#include "Engine/EngineManager.h"
#include "Interface/InterfaceManager.h"

#include <stdlib.h>

#include "Data/Fen.h"
#include "Common/Board.h"
#include "Engine/Perft.h"

int main(int, char**) {

    LoadData();
    StartEngine();
    StartInterface();

    BOARD board[1];
    //MOVELIST list[1];
    ParseFen(START_FEN, board);

    //PerfTest(3, board);
    char input[6];
    int move = NOMOVE;

    while(true){
    	PrintBoard(board);
    	std::cout<<"Please enter a move> ";
    	fgets(input, 6, stdin);

    	if(input[0] == 'q'){
    		break;
    	}else if(input[0] == 't'){
    		TakeMove(board);
    	}else if(input[0] == 'p'){
    		PerfTest(4, board);
    	}else{
    		move = ParseMove(input, board);
    		if(move != NOMOVE){
    			MakeMove(board, move);
    		}else {
    			std::cout<<"Move not parsed \n";
    		}
    	}

    	fflush(stdin);
    }

    return 0;
}
