#include "GameRules.h"

int ThreeFoldRepetition(const BOARD *position) {
    int count = 0;
    for (int i = 0; i < position->historyPlay; ++i) {
        if (position->history[i].positionKey == position->positionKey) {
            count++;
        }
    }
    return count;
}

bool DrawMaterial(const BOARD *position) {
    if (position->pieceNumber[wP] || position->pieceNumber[bP])
        return false;
    if (position->pieceNumber[wR] || position->pieceNumber[bR])
        return false;
    if (position->pieceNumber[wQ] || position->pieceNumber[bQ])
        return false;
    if (position->pieceNumber[wN] > 1 || position->pieceNumber[bN] > 1)
        return false;
    if (position->pieceNumber[wB] > 1 || position->pieceNumber[bB] > 1)
        return false;
    if (position->pieceNumber[wN] && position->pieceNumber[wB])
        return false;
    if (position->pieceNumber[bN] && position->pieceNumber[bB])
        return false;
    return true;
}

bool StaleMate(BOARD *position) {
    MOVELIST list[1];
    GenerateAllMoves(position, list);
    for (int i = 0; i < list->count; ++i) {
        if (!MakeMove(position, list->moves[i].move))
            continue;
        TakeMove(position);
        return false;
    }
    return true;
}

bool CheckGameResult(BOARD *position) {
    if (position->fiftyMove >= 100) {
        std::cout << "Draw by fifty move rule claimed\n";
        return true;
    }

    if (ThreeFoldRepetition(position) >= 3) {
        std::cout << "Draw by threefold repetition claimed\n";
        return true;
    }

    if (DrawMaterial(position)) {
        std::cout << "Draw by insufficient material claimed\n";
        return true;
    }

    if (!StaleMate(position))
        return false;

    bool inCheck = SqAttacked(position->Kings[position->side], position->side ^ 1, position);

    if (inCheck) {
        std::cout << (position->side == WHITE ? "Black wins\n" : "White wins\n");
    } else {
        std::cout << "Stalemate\n";
    }

    return true;
}
