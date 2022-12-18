#include <iostream>
#include "Data/DataManager.h"
#include "Engine/EngineManager.h"
#include "Interface/InterfaceManager.h"

#include "Data/Fen.h"
#include "Common/Board.h"
#include "Engine/MoveGenerator.h"

int main(int, char**) {

    LoadData();
    StartEngine();
    StartInterface();

    BOARD board[1];
    ParseFen(TEST_FEN, board);
    PrintBoard(board);

    MOVELIST list[1];

    GenerateAllMoves(board, list);
    PrintMoveList(list);

    return 0;
}
