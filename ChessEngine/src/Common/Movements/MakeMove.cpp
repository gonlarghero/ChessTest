#include "MakeMove.h"

#include <iostream>

const int CastlePermission[120] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                                   15, 13, 15, 15, 15, 12, 15, 15, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                                   15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                                   15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                                   15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7,  15, 15, 15, 3,  15, 15, 11, 15,
                                   15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};

static void ClearPiece(int square, BOARD *position);
static void AddPiece(const int square, BOARD *position, int piece);
static void MovePiece(const int from, const int to, BOARD *position);

static void ClearPiece(const int square, BOARD *position) {

    ASSERT(SquareOnBoard(square));
    ASSERT(CheckBoard(position));

    int piece = position->pieces[square];

    ASSERT(PieceValid(piece));

    int colour = PieceColour[piece];
    int index = 0;
    int t_pieceNum = -1;

    ASSERT(SideValid(colour));

    Hash::Piece(position, piece, square);

    position->pieces[square] = EMPTY;
    position->material[colour] -= PieceValue[piece];

    if (PieceBig[piece]) {
        position->bigPieces[colour]--;
        if (PieceMajor[piece])
            position->majorPieces[colour]--;
        else
            position->minorPieces[colour]--;
    } else {
        Global::ClearBit(position->pawns[colour], Sq120ToSq64[square]);
        Global::ClearBit(position->pawns[BOTH], Sq120ToSq64[square]);
    }

    // Details at docs/ClearPiece.md
    for (index = 0; index < position->pieceNumber[piece]; ++index) {
        if (position->pieceList[piece][index] == square) {
            t_pieceNum = index;
            break;
        }
    }

    ASSERT(t_pieceNum != -1);
    ASSERT(t_pieceNum >= 0 && t_pieceNum < 10);

    position->pieceNumber[piece]--;
    position->pieceList[piece][t_pieceNum] = position->pieceList[piece][position->pieceNumber[piece]];
}

static void AddPiece(const int square, BOARD *position, int piece) {

    ASSERT(PieceValid(piece));
    ASSERT(SquareOnBoard(square));

    int colour = PieceColour[piece];
    ASSERT(SideValid(colour));

    Hash::Piece(position, piece, square);

    position->pieces[square] = piece;

    if (PieceBig[piece]) {
        position->bigPieces[colour]++;
        if (PieceMajor[piece])
            position->majorPieces[colour]++;
        else
            position->minorPieces[colour]++;
    } else {
        Global::SetBit(position->pawns[colour], Sq120ToSq64[square]);
        Global::SetBit(position->pawns[BOTH], Sq120ToSq64[square]);
    }

    position->material[colour] += PieceValue[piece];
    position->pieceList[piece][position->pieceNumber[piece]] = square;
    position->pieceNumber[piece]++;
}

static void MovePiece(const int from, const int to, BOARD *position) {

    ASSERT(SquareOnBoard(from));
    ASSERT(SquareOnBoard(to));

    int index = 0;
    int piece = position->pieces[from];
    int colour = PieceColour[piece];
    ASSERT(SideValid(colour));
    ASSERT(PieceValid(piece));

    Hash::Piece(position, piece, from);
    position->pieces[from] = EMPTY;

    Hash::Piece(position, piece, to);
    position->pieces[to] = piece;

    if (!PieceBig[piece]) {
        Global::ClearBit(position->pawns[colour], Sq120ToSq64[from]);
        Global::ClearBit(position->pawns[BOTH], Sq120ToSq64[from]);
        Global::SetBit(position->pawns[colour], Sq120ToSq64[to]);
        Global::SetBit(position->pawns[BOTH], Sq120ToSq64[to]);
    }

    for (index = 0; index < position->pieceNumber[piece]; ++index) {
        if (position->pieceList[piece][index] == from) {
            position->pieceList[piece][index] = to;
            break;
        }
    }
}

bool MakeMove(BOARD *position, int move) {

    ASSERT(CheckBoard(position));

    int from = Move::From(move);
    int to = Move::To(move);
    int side = position->side;

    ASSERT(SquareOnBoard(from));
    ASSERT(SquareOnBoard(to));
    ASSERT(SideValid(side));
    ASSERT(PieceValid(position->pieces[from]));
    ASSERT(position->historyPlay >= 0 && position->historyPlay < MAX_GAME_MOVES);
    ASSERT(position->play >= 0 && position->play < MAX_DEPTH);

    position->history[position->historyPlay].positionKey = position->positionKey;

    if (move & Move::FlagEnPassant) {
        if (side == WHITE)
            ClearPiece(to - 10, position);
        else
            ClearPiece(to + 10, position);
    } else if (move & Move::FlagCastle) {
        switch (to) {
        case C1:
            MovePiece(A1, D1, position);
            break;
        case C8:
            MovePiece(A8, D8, position);
            break;
        case G1:
            MovePiece(H1, F1, position);
            break;
        case G8:
            MovePiece(H8, F8, position);
            break;
        default:
            ASSERT(false);
            break;
        }
    }

    if (position->enPassant != SQUARE_NULL)
        Hash::EnPassant(position);
    Hash::Castle(position);

    position->history[position->historyPlay].move = move;
    position->history[position->historyPlay].fiftyMove = position->fiftyMove;
    position->history[position->historyPlay].enPassant = position->enPassant;
    position->history[position->historyPlay].castlePermission = position->castlePermission;

    position->castlePermission &= CastlePermission[from];
    position->castlePermission &= CastlePermission[to];
    position->enPassant = SQUARE_NULL;
    Hash::Castle(position);

    int captured = Move::Captured(move);
    position->fiftyMove++;

    if (captured != EMPTY) {
        ASSERT(PieceValid(captured));
        ClearPiece(to, position);
        position->fiftyMove = 0;
    }

    position->historyPlay++;
    position->play++;

    ASSERT(position->historyPlay >= 0 && position->historyPlay < MAX_GAME_MOVES);
    ASSERT(position->play >= 0 && position->play < MAX_DEPTH);

    if (PiecePawn[position->pieces[from]]) {
        position->fiftyMove = 0;
        if (move & Move::FlagPawnStart) {
            if (side == WHITE) {
                position->enPassant = from + 10;
                ASSERT(RanksBoard[position->enPassant] == RANK_3);
            } else {
                position->enPassant = from - 10;
                ASSERT(RanksBoard[position->enPassant] == RANK_6);
            }
            Hash::EnPassant(position);
        }
    }

    MovePiece(from, to, position);

    int promotedPiece = Move::Promoted(move);
    if (promotedPiece != EMPTY) {
        ASSERT(PieceValid(promotedPiece) && !PiecePawn[promotedPiece]);
        ClearPiece(to, position);
        AddPiece(to, position, promotedPiece);
    }

    if (PieceKing[position->pieces[to]]) {
        position->Kings[position->side] = to;
    }

    position->side ^= 1;
    Hash::Side(position);

    ASSERT(CheckBoard(position));

    if (SqAttacked(position->Kings[side], position->side, position)) {
        TakeMove(position);
        return false;
    }

    return true;
}

void TakeMove(BOARD *position) {

    ASSERT(CheckBoard(position));

    position->historyPlay--;
    position->play--;

    ASSERT(position->historyPlay >= 0 && position->historyPlay < MAX_GAME_MOVES);
    ASSERT(position->play >= 0 && position->play < MAX_DEPTH);

    int move = position->history[position->historyPlay].move;
    int from = Move::From(move);
    int to = Move::To(move);

    ASSERT(SquareOnBoard(from));
    ASSERT(SquareOnBoard(to));

    if (position->enPassant != SQUARE_NULL)
        Hash::EnPassant(position);
    Hash::Castle(position);

    position->fiftyMove = position->history[position->historyPlay].fiftyMove;
    position->enPassant = position->history[position->historyPlay].enPassant;
    position->castlePermission = position->history[position->historyPlay].castlePermission;

    if (position->enPassant != SQUARE_NULL)
        Hash::EnPassant(position);
    Hash::Castle(position);

    position->side ^= 1;
    Hash::Side(position);

    if (Move::FlagEnPassant & move) {
        if (position->side == WHITE)
            AddPiece(to - 10, position, bP);
        else
            AddPiece(to + 10, position, wP);
    } else if (Move::FlagCastle & move) {
        switch (to) {
        case C1:
            MovePiece(D1, A1, position);
            break;
        case C8:
            MovePiece(D8, A8, position);
            break;
        case G1:
            MovePiece(F1, H1, position);
            break;
        case G8:
            MovePiece(F8, H8, position);
            break;
        default:
            ASSERT(false);
            break;
        }
    }

    MovePiece(to, from, position);

    if (PieceKing[position->pieces[from]]) {
        position->Kings[position->side] = from;
    }

    int captured = Move::Captured(move);
    if (captured != EMPTY) {
        ASSERT(PieceValid(captured));
        AddPiece(to, position, captured);
    }

    int promotedPiece = Move::Promoted(move);
    if (promotedPiece != EMPTY) {
        ASSERT(PieceValid(promotedPiece) && !PiecePawn[promotedPiece]);
        ClearPiece(from, position);
        AddPiece(from, position, (PieceColour[promotedPiece] == WHITE ? wP : bP));
    }

    ASSERT(CheckBoard(position));
}
