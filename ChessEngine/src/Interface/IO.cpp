#include "IO.h"

#include <iostream>
#include <sstream>

std::string PrintSquare(const int square) {
    int file = FilesBoard[square];
    int rank = RanksBoard[square];

    std::stringstream ss;
    ss << static_cast<char>('a' + file) << static_cast<char>('1' + rank);
    return ss.str();
}

std::string PrintMove(const int move) {

    int ff = FilesBoard[FROMSQ(move)];
    int rf = RanksBoard[FROMSQ(move)];
    int ft = FilesBoard[TOSQ(move)];
    int rt = RanksBoard[TOSQ(move)];

    int promoted = PROMOTED(move);

    std::stringstream ss;
    ss << static_cast<char>('a' + ff) << static_cast<char>('1' + rf) << static_cast<char>('a' + ft)
       << static_cast<char>('1' + rt);

    if (promoted) {
        char pchar = 'q';
        if (IsKn(promoted)) {
            pchar = 'n';
        } else if (IsRQ(promoted) && !IsBQ(promoted)) {
            pchar = 'r';
        } else if (!IsRQ(promoted) && IsBQ(promoted)) {
            pchar = 'b';
        }
        ss << pchar;
    }

    return ss.str();
}

void PrintMoveList(const MOVELIST *list) {
    int index, score, move = 0;
    std::cout << "MoveList: " << list->count << "\n";

    for (index = 0; index < list->count; ++index) {
        move = list->moves[index].move;
        score = list->moves[index].score;
        std::cout << "Move " << (index + 1) << " > " << PrintMove(move) << " (score " << score << ")\n";
    }
    std::cout << "MoveList Total " << list->count << " moves: \n\n";
}

int ParseMove(char *ptrChar, BOARD *position) {

    if (ptrChar[0] > 'h' || ptrChar[0] < 'a')
        return NOMOVE;
    if (ptrChar[1] > '8' || ptrChar[1] < '1')
        return NOMOVE;
    if (ptrChar[2] > 'h' || ptrChar[2] < 'a')
        return NOMOVE;
    if (ptrChar[3] > '8' || ptrChar[3] < '1')
        return NOMOVE;

    int from = FR2SQ(ptrChar[0] - 'a', ptrChar[1] - '1');
    int to = FR2SQ(ptrChar[2] - 'a', ptrChar[3] - '1');

    ASSERT(SquareOnBoard(from) && SquareOnBoard(to));

    MOVELIST list[1];
    GenerateAllMoves(position, list);
    int moveNum, move = 0;
    int promotionPiece = EMPTY;

    for (moveNum = 0; moveNum < list->count; ++moveNum) {
        move = list->moves[moveNum].move;
        if (FROMSQ(move) == from && TOSQ(move) == to) {
            promotionPiece = PROMOTED(move);
            if (promotionPiece != EMPTY) {
                if (IsRQ(promotionPiece) && !IsBQ(promotionPiece) && ptrChar[4] == 'r')
                    return move;
                else if (!IsRQ(promotionPiece) && IsBQ(promotionPiece) && ptrChar[4] == 'b')
                    return move;
                else if (IsRQ(promotionPiece) && IsBQ(promotionPiece) && ptrChar[4] == 'q')
                    return move;
                else if (IsKn(promotionPiece) && ptrChar[4] == 'n')
                    return move;
            }
            return move;
        }
    }

    return NOMOVE;
}
