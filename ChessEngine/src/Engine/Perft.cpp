#include "Perft.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <windows.h>

void Perft(int depth, BOARD *position, long &leafNodes) {

    ASSERT(CheckBoard(position));

    if (depth == 0) {
        leafNodes++;
        return;
    }

    MOVELIST list[1];
    GenerateAllMoves(position, list);
    int moveNum = 0;
    for (moveNum = 0; moveNum < list->count; ++moveNum) {
        if (!MakeMove(position, list->moves[moveNum].move)) {
            continue;
        }

        Perft(depth - 1, position, leafNodes);
        TakeMove(position);
    }
}

void PerfTest(int depth, BOARD *position) {

    ASSERT(CheckBoard(position));

    PrintBoard(position);

    std::cout << "\nSTARTING TEST TO DEPTH: " << depth << "\n";

    long leafNodes = 0;

    auto start = std::chrono::high_resolution_clock::now();

    MOVELIST list[1];
    GenerateAllMoves(position, list);

    for (int moveNum = 0; moveNum < list->count; ++moveNum) {
        int move = list->moves[moveNum].move;
        if (!MakeMove(position, move)) {
            continue;
        }
        long cumnodes = leafNodes;
        Perft(depth - 1, position, leafNodes);
        TakeMove(position);
        long oldnodes = leafNodes - cumnodes;
        std::cout << "MOVE: " << moveNum + 1 << " : " << PrintMove(move) << " : " << oldnodes << "\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::setprecision(6) << "TEST COMPLETE: " << leafNodes << " NODES VISITED IN " << durationMs
              << " MILLISECONDS.\n";
}
