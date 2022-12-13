#include <iostream>
#include "Data/DataManager.h"
#include "Engine/EngineManager.h"
#include "Interface/InterfaceManager.h"

//#include "../Data/Fen.h"
//#include "../Data/BoardValidator.h"

int main(int, char**) {

    LoadData();
    StartEngine();
    StartInterface();

    /*BOARD board[1];
    ParseFen(TEST_FEN,board);
    PrintBoard(board);
    ASSERT(CheckBoard(board));*/
}
