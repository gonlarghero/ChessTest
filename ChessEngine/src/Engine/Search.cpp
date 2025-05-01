#include "Search.h"

#include <iostream>
#include <windows.h>

static bool isRepetition(const BOARD *position);
static void CheckUp(SEARCHINFO *info);
static void ClearForSearch(BOARD *position, SEARCHINFO *info);
static int AlphaBeta(int alpha, int beta, int depth, BOARD *position, SEARCHINFO *info, bool doNull);
static int Quiescence(int alpha, int beta, BOARD *position, SEARCHINFO *info);
static void SortMoveList(MOVELIST *list);

void SearchPosition(BOARD *position, SEARCHINFO *info) {

    int bestMove = NOMOVE;
    int bestScore = -INFINITY_SCORE;
    int currentDepth, pvMoves, pvNum = 0;

    ClearForSearch(position, info);

    // if(EngineOptions->UseBook == TRUE) {
    //	bestMove = GetBookMove(pos);

    if (bestMove == NOMOVE) {
        for (currentDepth = 1; currentDepth <= info->depth; ++currentDepth) {

            bestScore = AlphaBeta(-INFINITY_SCORE, INFINITY_SCORE, currentDepth, position, info, TRUE);

            if (info->stopped == true)
                break;

            pvMoves = GetPVLine(currentDepth, position);
            bestMove = position->pvArray[0];

            std::cout << "Depth:" << currentDepth << " score:" << bestScore << " move:" << PrintMove(bestMove)
                      << " nodes:" << info->nodes << " ";

            pvMoves = GetPVLine(currentDepth, position);
            std::cout << "pv";
            for (pvNum = 0; pvNum < pvMoves; ++pvNum) {
                std::cout << " " << PrintMove(position->pvArray[pvNum]);
            }
            std::cout << "\n";
            if (info->failHigh > 0) {
                std::cout << "Ordering: " << (info->failHighFirst / info->failHigh) << "\n";
            } else {
                std::cout << "Ordering: N/A\n";
            }
        }
    }
}

static void CheckUp(SEARCHINFO *info) {
    if (info->timeset == true && GetTickCount() > static_cast<DWORD>(info->stoptime))
        info->stopped = true;
}

static void ClearForSearch(BOARD *position, SEARCHINFO *info) {
    for (int index = 0; index < PIECE_TYPE_NUMBER; ++index) {
        for (int index2 = 0; index2 < BOARD_SQUARE_NUMBER; ++index2) {
            position->searchHistory[index][index2] = 0;
        }
    }

    for (int index = 0; index < 2; ++index) {
        for (int index2 = 0; index2 < MAX_DEPTH; ++index2) {
            position->searchKillers[index][index2] = 0;
        }
    }

    ClearPVTable(position->pvTable);
    position->play = 0;

    info->starttime = GetTickCount();
    info->stopped = 0;
    info->nodes = 0;
    info->failHigh = 0;
    info->failHighFirst = 0;
}

static int AlphaBeta(int alpha, int beta, int depth, BOARD *position, SEARCHINFO *info, bool doNull) {

    ASSERT(CheckBoard(position));
    ASSERT(beta > alpha);
    ASSERT(depth >= 0);

    if (depth <= 0)
        return Quiescence(alpha, beta, position, info);

    if ((info->nodes & SEARCH_TIMEOUT_INTERVAL) == 0)
        CheckUp(info);

    info->nodes++;

    if ((isRepetition(position) || position->fiftyMove >= 100))
        return 0;

    if (position->play > MAX_DEPTH - 1)
        return EvalPosition(position);

    bool InCheck = SqAttacked(position->Kings[position->side], position->side ^ 1, position);

    if (InCheck == true)
        depth++;

    if (doNull && depth >= 3 && !InCheck && position->material[position->side] > 0) {
        int oldEnPassant = position->enPassant;
        if (position->enPassant != SQUARE_NULL) {
            Hash::Piece(position, EMPTY, position->enPassant);
        }
        position->enPassant = SQUARE_NULL;

        position->side ^= 1;
        Hash::Side(position);
        position->play++;

        int score = -AlphaBeta(-beta, -beta + 1, depth - 1 - 2, position, info, FALSE);

        position->play--;
        position->side ^= 1;
        Hash::Side(position);

        if (oldEnPassant != SQUARE_NULL) {
            Hash::Piece(position, EMPTY, oldEnPassant);
        }
        position->enPassant = oldEnPassant;

        if (info->stopped)
            return 0;

        if (score >= beta)
            return beta;
    }

    int Score = -INFINITY_SCORE;
    int PvMove = ProbePVTable(position); /*NOMOVE;*/

    MOVELIST list[1];
    GenerateAllMoves(position, list);
    SortMoveList(list);

    int Legal = 0;
    int OldAlpha = alpha;
    int BestMove = NOMOVE;

    if (PvMove != NOMOVE) {
        for (int MoveNum = 0; MoveNum < list->count; ++MoveNum) {
            if (list->moves[MoveNum].move == PvMove) {
                list->moves[MoveNum].score = PV_MOVE_SCORE;
                break;
            }
        }
    }

    for (int MoveNum = 0; MoveNum < list->count; ++MoveNum) {
        if (!MakeMove(position, list->moves[MoveNum].move)) {
            continue;
        }

        Legal++;
        Score = -AlphaBeta(-beta, -alpha, depth - 1, position, info, TRUE);
        TakeMove(position);

        if (info->stopped == TRUE)
            return 0;

        if (Score > alpha) {
            if (Score >= beta) {
                if (Legal == 1)
                    info->failHighFirst++;
                info->failHigh++;

                if (!(list->moves[MoveNum].move & Move::FlagCastle)) {
                    position->searchKillers[1][position->play] = position->searchKillers[0][position->play];
                    position->searchKillers[0][position->play] = list->moves[MoveNum].move;
                }
                return beta;
            }
            alpha = Score;
            BestMove = list->moves[MoveNum].move;
            if (!(list->moves[MoveNum].move & Move::FlagCastle)) {
                position->searchHistory[position->pieces[Move::From(BestMove)]][Move::To(BestMove)] += depth;
            }
        }
    }

    if (Legal == 0) {
        if (InCheck)
            return -MATE_SCORE + position->play;
        else
            return 0;
    }

    if (alpha != OldAlpha)
        StorePVMove(position, BestMove);

    return alpha;
}

static int Quiescence(int alpha, int beta, BOARD *position, SEARCHINFO *info) {
    ASSERT(CheckBoard(position));

    if ((info->nodes & SEARCH_TIMEOUT_INTERVAL) == 0)
        CheckUp(info);

    info->nodes++;

    if (isRepetition(position) || position->fiftyMove >= 100)
        return 0;

    if (position->play > MAX_DEPTH - 1)
        return EvalPosition(position);

    int standPat = EvalPosition(position);
    if (standPat >= beta)
        return beta;
    if (standPat > alpha)
        alpha = standPat;

    MOVELIST list[1];
    GenerateAllCaptures(position, list);
    SortMoveList(list);

    for (int i = 0; i < list->count; ++i) {
        int move = list->moves[i].move;

        if (!MakeMove(position, move)) {
            continue;
        }
        int score = -Quiescence(-beta, -alpha, position, info);
        TakeMove(position);

        if (info->stopped == TRUE)
            return 0;

        if (score >= beta)
            return beta;
        if (score > alpha) {
            alpha = score;
            StorePVMove(position, move);
        }
    }

    return alpha;
}

static void SortMoveList(MOVELIST *list) {
    for (int i = 0; i < list->count - 1; ++i) {
        int bestIndex = i;
        for (int j = i + 1; j < list->count; ++j) {
            if (list->moves[j].score > list->moves[bestIndex].score) {
                bestIndex = j;
            }
        }
        if (bestIndex != i) {
            MOVE temp = list->moves[i];
            list->moves[i] = list->moves[bestIndex];
            list->moves[bestIndex] = temp;
        }
    }
}

static bool isRepetition(const BOARD *position) {

    for (int index = position->historyPlay - position->fiftyMove; index < position->historyPlay - 1; ++index) {

        ASSERT(index >= 0 && index < MAX_GAME_MOVES);

        if (position->positionKey == position->history[index].positionKey)
            return true;
    }

    return false;
}
