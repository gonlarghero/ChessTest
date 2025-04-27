#include "MoveGenerator.h"

#include <iostream>

// Helper function declarations
static void AddMove(const BOARD *position, int move, MOVELIST *list, bool capture);
static void AddPawnMove(const BOARD *position, int from, int to, int cap, MOVELIST *list, bool capture, bool isWhite);
static void AddCastleMove(const BOARD *position, int from, int to, MOVELIST *list);
static void AddEnPassantMove(const BOARD *position, int move, MOVELIST *list);

static int MvvLvaScores[PIECE_TYPE_NUMBER][PIECE_TYPE_NUMBER];

const int LoopSlidePiece[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};
const int LoopNonSlidePiece[8] = {wN, wK, 0, bN, bK, 0};
const int LoopSlideIndex[2] = {0, 4};
const int LoopNonSlideIndex[2] = {0, 3};
const int PieceDirection[13][8] = {{0},
                                   {0},
                                   {-8, -19, -21, -12, 8, 19, 21, 12},
                                   {-9, -11, 11, 9, 0, 0, 0, 0},
                                   {-1, -10, 1, 10, 0, 0, 0, 0},
                                   {-1, -10, 1, 10, -9, -11, 11, 9},
                                   {-1, -10, 1, 10, -9, -11, 11, 9},
                                   {0},
                                   {-8, -19, -21, -12, 8, 19, 21, 12},
                                   {-9, -11, 11, 9, 0, 0, 0, 0},
                                   {-1, -10, 1, 10, 0, 0, 0, 0},
                                   {-1, -10, 1, 10, -9, -11, 11, 9},
                                   {-1, -10, 1, 10, -9, -11, 11, 9}};

const int PawnForward[2] = {10, -10};
const int PawnLeftCapture[2] = {9, -11};
const int PawnRightCapture[2] = {11, -9};

const int DirectionNumber[13] = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

void InitMvvLva() {
    for (int Victim = wP; Victim <= bK; ++Victim) {
        for (int Attacker = wP; Attacker <= bK; ++Attacker) {
            MvvLvaScores[Victim][Attacker] = VictimScore[Victim] + 6 - (VictimScore[Attacker] / 100);
        }
    }
}

void GenerateAllMoves(const BOARD *position, MOVELIST *list) {
    ASSERT(CheckBoard(position));
    list->count = 0;

    int side = position->side;
    int dir, index, square, t_square;

    // pawns
    int pawnPiece = (side == WHITE) ? wP : bP;
    int forward = PawnForward[side];
    int dblForward = forward * 2;
    int leftCapture = PawnLeftCapture[side];
    int rightCapture = PawnRightCapture[side];
    for (int pieceNumber = 0; pieceNumber < position->pieceNumber[pawnPiece]; ++pieceNumber) {
        square = position->pieceList[pawnPiece][pieceNumber];
        ASSERT(SquareOnBoard(square));

        // normal and double moves
        if (position->pieces[square + forward] == EMPTY) {
            AddPawnMove(position, square, square + forward, EMPTY, list, false, side == WHITE);
            if ((side == WHITE && RanksBoard[square] == RANK_2) || (side == BLACK && RanksBoard[square] == RANK_7))
                if (position->pieces[square + dblForward] == EMPTY)
                    AddMove(position, MOVE_M(square, (square + dblForward), EMPTY, EMPTY, MFLAGPS), list, false);
        }

        // captures
        for (int capOffset : {leftCapture, rightCapture}) {
            t_square = square + capOffset;
            if (!SQUAREOFFBOARD(t_square)) {
                int captured = position->pieces[t_square];
                if (captured != EMPTY && PieceColour[captured] == (side ^ 1))
                    AddPawnMove(position, square, t_square, captured, list, true, side == WHITE);
                else if (t_square == position->enPassant)
                    AddEnPassantMove(position, MOVE_M(square, t_square, EMPTY, EMPTY, MFLAGEP), list);
            }
        }
    }

    if (side == WHITE) {
        if (position->castlePermission & wKCastle)
            AddCastleMove(position, E1, G1, list);
        if (position->castlePermission & wQCastle)
            AddCastleMove(position, E1, C1, list);
    } else {
        if (position->castlePermission & bKCastle)
            AddCastleMove(position, E8, G8, list);
        if (position->castlePermission & bQCastle)
            AddCastleMove(position, E8, C8, list);
    }

    // lambda funtion for sliders and non-sliders
    auto GeneratePieceMoves = [&](const int *pieceLoop, int startIndex) {
        int piece = pieceLoop[startIndex++];
        while (piece != 0) {
            for (int i = 0; i < position->pieceNumber[piece]; ++i) {
                square = position->pieceList[piece][i];
                for (index = 0; index < DirectionNumber[piece]; ++index) {
                    dir = PieceDirection[piece][index];
                    t_square = square + dir;
                    while (!SQUAREOFFBOARD(t_square)) {
                        int target = position->pieces[t_square];
                        if (target != EMPTY) {
                            if (PieceColour[target] == (side ^ 1))
                                AddMove(position, MOVE_M(square, t_square, target, EMPTY, 0), list, true);
                            break;
                        }
                        AddMove(position, MOVE_M(square, t_square, EMPTY, EMPTY, 0), list, false);
                        if (IsKi(piece) || IsKn(piece))
                            break;
                        t_square += dir;
                    }
                }
            }
            piece = pieceLoop[startIndex++];
        }
    };

    GeneratePieceMoves(LoopSlidePiece, LoopSlideIndex[side]);
    GeneratePieceMoves(LoopNonSlidePiece, LoopNonSlideIndex[side]);
}

void GenerateAllCaptures(const BOARD *position, MOVELIST *list) {
    ASSERT(CheckBoard(position));
    list->count = 0;

    int side = position->side;
    int dir, index, square, t_square;

    int pawnPiece = (side == WHITE) ? wP : bP;
    int leftCap = PawnLeftCapture[side];
    int rightCap = PawnRightCapture[side];
    for (int pieceNumber = 0; pieceNumber < position->pieceNumber[pawnPiece]; ++pieceNumber) {
        square = position->pieceList[pawnPiece][pieceNumber];
        ASSERT(SquareOnBoard(square));

        for (int capOffset : {leftCap, rightCap}) {
            t_square = square + capOffset;
            if (!SQUAREOFFBOARD(t_square)) {
                int captured = position->pieces[t_square];
                if (captured != EMPTY && PieceColour[captured] == (side ^ 1))
                    AddPawnMove(position, square, t_square, captured, list, true, side == WHITE);
                else if (t_square == position->enPassant)
                    AddEnPassantMove(position, MOVE_M(square, t_square, EMPTY, EMPTY, MFLAGEP), list);
            }
        }
    }

    auto GeneratePieceCaptures = [&](const int *pieceLoop, int startIndex) {
        int piece = pieceLoop[startIndex++];
        while (piece != 0) {
            for (int i = 0; i < position->pieceNumber[piece]; ++i) {
                square = position->pieceList[piece][i];
                for (index = 0; index < DirectionNumber[piece]; ++index) {
                    dir = PieceDirection[piece][index];
                    t_square = square + dir;
                    while (!SQUAREOFFBOARD(t_square)) {
                        int target = position->pieces[t_square];
                        if (target != EMPTY) {
                            if (PieceColour[target] == (side ^ 1))
                                AddMove(position, MOVE_M(square, t_square, target, EMPTY, 0), list, true);
                            break;
                        }
                        if (IsKi(piece) || IsKn(piece))
                            break;
                        t_square += dir;
                    }
                }
            }
            piece = pieceLoop[startIndex++];
        }
    };

    GeneratePieceCaptures(LoopSlidePiece, LoopSlideIndex[side]);
    GeneratePieceCaptures(LoopNonSlidePiece, LoopNonSlideIndex[side]);
}

bool MoveExists(BOARD *position, const int move) {
    MOVELIST list[1];
    GenerateAllMoves(position, list);

    for (int moveNum = 0; moveNum < list->count; ++moveNum) {
        if (list->moves[moveNum].move == move) {
            if (MakeMove(position, move)) {
                TakeMove(position);
                return true;
            }
        }
    }
    return false;
}

static void AddPawnMove(const BOARD *position, int from, int to, int cap, MOVELIST *list, bool capture, bool isWhite) {
    ASSERT(SquareOnBoard(from));
    ASSERT(SquareOnBoard(to));
    ASSERT(CheckBoard(position));

    if (capture)
        ASSERT(PieceValidEmpty(cap));

    if ((isWhite && RanksBoard[from] == RANK_7) || (!isWhite && RanksBoard[from] == RANK_2)) {
        int promos[] = {isWhite ? wQ : bQ, isWhite ? wR : bR, isWhite ? wB : bB, isWhite ? wN : bN};
        for (int promo : promos) AddMove(position, MOVE_M(from, to, cap, promo, 0), list, capture);
    } else {
        AddMove(position, MOVE_M(from, to, cap, EMPTY, 0), list, capture);
    }
}

static void AddMove(const BOARD *position, int move, MOVELIST *list, bool capture) {
    ASSERT(SquareOnBoard(FROMSQ(move)));
    ASSERT(SquareOnBoard(TOSQ(move)));
    ASSERT(position->play >= 0 && position->play < MAXDEPTH);

    if (capture) {
        ASSERT(PieceValid(CAPTURED(move)));
        list->moves[list->count].score = MvvLvaScores[CAPTURED(move)][position->pieces[FROMSQ(move)]] + 1000000;
    } else {
        int fromPiece = position->pieces[FROMSQ(move)];
        if (position->searchKillers[0][position->play] == move)
            list->moves[list->count].score = 900000;
        else if (position->searchKillers[1][position->play] == move)
            list->moves[list->count].score = 800000;
        else
            list->moves[list->count].score = position->searchHistory[fromPiece][TOSQ(move)];
    }

    list->moves[list->count].move = move;
    list->count++;
}

static void AddEnPassantMove(const BOARD *position, int move, MOVELIST *list) {
    ASSERT(SquareOnBoard(FROMSQ(move)));
    ASSERT(SquareOnBoard(TOSQ(move)));
    ASSERT(CheckBoard(position));
    ASSERT((RanksBoard[TOSQ(move)] == RANK_6 && position->side == WHITE) ||
           (RanksBoard[TOSQ(move)] == RANK_3 && position->side == BLACK));

    list->moves[list->count].move = move;
    list->moves[list->count].score = 105 + 1000000;
    list->count++;
}

static void AddCastleMove(const BOARD *position, int from, int to, MOVELIST *list) {
    bool emptyRoad = true, safeRoad = true;

    if (from == E1 && to == G1) {
        emptyRoad = (position->pieces[F1] == EMPTY && position->pieces[G1] == EMPTY);
        safeRoad = !SqAttacked(E1, BLACK, position) && !SqAttacked(F1, BLACK, position);
    } else if (from == E1 && to == C1) {
        emptyRoad = (position->pieces[D1] == EMPTY && position->pieces[C1] == EMPTY && position->pieces[B1] == EMPTY);
        safeRoad = !SqAttacked(E1, BLACK, position) && !SqAttacked(D1, BLACK, position);
    } else if (from == E8 && to == G8) {
        emptyRoad = (position->pieces[F8] == EMPTY && position->pieces[G8] == EMPTY);
        safeRoad = !SqAttacked(E8, WHITE, position) && !SqAttacked(F8, WHITE, position);
    } else if (from == E8 && to == C8) {
        emptyRoad = (position->pieces[D8] == EMPTY && position->pieces[C8] == EMPTY && position->pieces[B8] == EMPTY);
        safeRoad = !SqAttacked(E8, WHITE, position) && !SqAttacked(D8, WHITE, position);
    }

    if (emptyRoad && safeRoad) {
        AddMove(position, MOVE_M(from, to, EMPTY, EMPTY, MFLAGCA), list, false);
    }
}
