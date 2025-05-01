#include <iostream>
#include <string>

#include "Common/Board.h"
#include "Data/DataManager.h"
#include "Data/Fen.h"
#include "Engine/EngineManager.h"
#include "Engine/Perft.h"
#include "Engine/Search.h"
#include "Interface/Console.h"
#include "Interface/XBoard.h"

int main(int, char **) {

    LoadData();
    StartEngine();

    BOARD board[1];
    SEARCHINFO info[1];
    info->quit = false;

    std::string input;
    int move = NOMOVE;
    int pvnum = 0;
    int max = 0;

    while (true) {

        std::cout << ">";
        std::getline(std::cin, input);

        if (input == "p") {
            PerfTest(PERF_DEPTH_DEFAULT, board);
        } else if (input == "r") {
            max = GetPVLine(PV_LINE_DEPTH_DEFAULT, board);
            std::cout << "PvLine of " << max << " moves: ";
            for (pvnum = 0; pvnum < max; ++pvnum) {
                move = board->pvArray[pvnum];
                std::cout << PrintMove(move) << " ";
            }
            std::cout << "\n";
        } else if (input == "s") {
            info->depth = SEARCH_DEPTH_DEFAULT;
            SearchPosition(board, info);
        } else if (input == "xboard") {
            XBoard_Loop(board, info);
            if (info->quit == true)
                break;
            continue;
        } else if (input == "console") {
            Console_Loop(board, info);
            if (info->quit == true)
                break;
            continue;
        } else if (input == "quit") {
            break;
        }
    }

    delete[] board->pvTable->pTable;
    return 0;
}
