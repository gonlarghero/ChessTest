#include <iostream>
#include "Data/DataManager.h"
#include "Engine/EngineManager.h"
#include "Interface/InterfaceManager.h"

#include "Data/Fen.h"
#include "Common/Board.h"
#include "Engine/Perft.h"

int main(int, char**) {

    LoadData();
    StartEngine();
    StartInterface();

    BOARD board[1];
    MOVELIST list[1];
    ParseFen(TEST_FEN, board);

    PerfTest(3, board);

    return 0;
}
