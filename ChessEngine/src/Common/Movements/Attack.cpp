#include "Attack.h"

#include <iostream>

const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir[4] = {-9, -11, 11, 9};
const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

const int wPDir[2] = {-11, -9};
const int bPDir[2] = {11, 9};

// Check if the square is attacked by the given side
bool SqAttacked(const int square, const int side, const BOARD *position) {

    ASSERT(SquareOnBoard(square));
    ASSERT(SideValid(side));
    ASSERT(CheckBoard(position));

    int piece, index, t_square, dir = 0;

    // pawns
    if (side == WHITE) {
        if (position->pieces[square + wPDir[0]] == wP || position->pieces[square + wPDir[1]] == wP)
            return true;
    } else {
        if (position->pieces[square + bPDir[0]] == bP || position->pieces[square + bPDir[1]] == bP)
            return true;
    }

    for (index = 0; index < 8; ++index) {
        // knights
        piece = position->pieces[square + KnDir[index]];
        if (piece != SQUARE_NULL && Global::IsKnight(piece) && PieceColour[piece] == side)
            return true;
        // kings
        piece = position->pieces[square + KiDir[index]];
        if (piece != SQUARE_NULL && Global::IsKing(piece) && PieceColour[piece] == side)
            return true;
    }

    for (index = 0; index < 4; ++index) {
        // rooks && queens
        dir = RkDir[index];
        t_square = square + dir;
        piece = position->pieces[t_square];
        while (piece != SQUARE_NULL) {
            if (piece != EMPTY) {
                if (Global::IsRookQueen(piece) && PieceColour[piece] == side) {
                    return true;
                }
                break;
            }
            t_square += dir;
            piece = position->pieces[t_square];
        }
        // bishops && queens
        dir = BiDir[index];
        t_square = square + dir;
        piece = position->pieces[t_square];
        while (piece != SQUARE_NULL) {
            if (piece != EMPTY) {
                if (Global::IsBishopQueen(piece) && PieceColour[piece] == side) {
                    return true;
                }
                break;
            }
            t_square += dir;
            piece = position->pieces[t_square];
        }
    }

    return false;
}
