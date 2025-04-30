#include "Board.h"

#include <iostream>
#include <stdio.h>

void PrintBoard(const BOARD *position) {
    int square, file, rank, piece = 0;

    std::cout << ("\nGame Board: \n\n");

    for (rank = RANK_8; rank >= RANK_1; rank--) {
        std::cout << (rank + 1) << " ";
        for (file = FILE_A; file <= FILE_H; file++) {
            square = Global::FrToSq(file, rank);
            piece = position->pieces[square];
            std::cout << " " << PieceChar[piece] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n  ";

    for (file = FILE_A; file <= FILE_H; file++) std::cout << " " << static_cast<char>('a' + file) << " ";

    std::cout << "\n\n";
    std::cout << "side: " << SideChar[position->side] << "\n";
    std::cout << "enPassant: " << position->enPassant << "\n";
    std::cout << "castle: " << (position->castlePermission & wKCastle ? 'K' : '-')
              << (position->castlePermission & wQCastle ? 'Q' : '-')
              << (position->castlePermission & bKCastle ? 'k' : '-')
              << (position->castlePermission & bQCastle ? 'q' : '-') << "\n";
    std::cout << "PosKey: " << std::hex << std::uppercase << position->positionKey << std::dec << "\n";
}

void UpdateListMaterial(BOARD *position) {

    int piece, square, index, colour = 0;
    for (index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        square = index;
        piece = position->pieces[index];
        if (piece != SQUARE_NULL && piece != EMPTY) {
            colour = PieceColour[piece];
            if (PieceBig[piece])
                position->bigPieces[colour]++;
            if (PieceMinor[piece])
                position->minorPieces[colour]++;
            if (PieceMajor[piece])
                position->majorPieces[colour]++;

            position->material[colour] += PieceValue[piece];
            position->pieceList[piece][position->pieceNumber[piece]] = square;
            position->pieceNumber[piece]++;

            if (piece == wK)
                position->Kings[WHITE] = square;
            if (piece == bK)
                position->Kings[BLACK] = square;

            if (piece == wP) {
                Global::SetBit(position->pawns[WHITE], Sq120ToSq64[square]);
                Global::SetBit(position->pawns[BOTH], Sq120ToSq64[square]);
            }
            if (piece == bP) {
                Global::SetBit(position->pawns[BLACK], Sq120ToSq64[square]);
                Global::SetBit(position->pawns[BOTH], Sq120ToSq64[square]);
            }
        }
    }
}

void ResetBoard(BOARD *position) {

    int index = 0;

    for (index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        position->pieces[index] = SQUARE_NULL;
    }

    for (index = 0; index < BOARD_REAL_NUMBER; ++index) {
        position->pieces[Sq64ToSq120[index]] = EMPTY;
    }

    for (index = 0; index < COLOUR_NUMBER - 1; ++index) {
        position->bigPieces[index] = 0;
        position->majorPieces[index] = 0;
        position->minorPieces[index] = 0;
        position->material[index] = 0;
        position->pawns[index] = 0ULL;
    }

    // pawns are stored for both colors
    for (index = 0; index < COLOUR_NUMBER; ++index) {
        position->pawns[index] = 0ULL;
    }

    for (index = 0; index < PIECE_TYPE_NUMBER; ++index) {
        position->pieceNumber[index] = 0;
    }

    position->Kings[WHITE] = position->Kings[BLACK] = SQUARE_NULL;
    position->side = BOTH;
    position->enPassant = SQUARE_NULL;
    position->fiftyMove = 0;
    position->play = 0;
    position->historyPlay = 0;
    position->castlePermission = 0;
    position->positionKey = 0ULL;
}
