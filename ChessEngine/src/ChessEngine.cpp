#include <iostream>
#include "Data/DataManager.h"
#include "Engine/EngineManager.h"
#include "Interface/InterfaceManager.h"

#include <stdlib.h>

#include "Data/Fen.h"
#include "Common/Board.h"
#include "Engine/Search.h"

int main(int, char**) {

    LoadData();
    StartEngine();
    StartInterface();

    BOARD board[1];
    SEARCHINFO info[1];
    ParseFen(START_FEN, board);

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
    	}else if(input[0] == 's'){
    		info->depth = 4;
    		SearchPosition(board, info);
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
