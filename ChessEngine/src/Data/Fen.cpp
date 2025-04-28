#include "Fen.h"

#include <iostream>
#include <stdio.h>

int ParseFen(const char *fen, BOARD *position) {

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int count = 0;
    int index = 0;
    int square64 = 0;
    int square120 = 0;

    ResetBoard(position);
    InitPVTable(position->pvTable);

    while ((rank >= RANK_1) && *fen) {
        count = 1;
        switch (*fen) {
        case 'p':
            piece = bP;
            break;
        case 'n':
            piece = bN;
            break;
        case 'b':
            piece = bB;
            break;
        case 'r':
            piece = bR;
            break;
        case 'q':
            piece = bQ;
            break;
        case 'k':
            piece = bK;
            break;
        case 'P':
            piece = wP;
            break;
        case 'N':
            piece = wN;
            break;
        case 'B':
            piece = wB;
            break;
        case 'R':
            piece = wR;
            break;
        case 'Q':
            piece = wQ;
            break;
        case 'K':
            piece = wK;
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            piece = EMPTY;
            count = *fen - '0';
            break;
        case '/':
        case ' ':
            rank--;
            file = FILE_A;
            fen++;
            continue;
        default:
            std::cout << "FEN error: " << *fen << "\n";
            return -1;
        }

        for (index = 0; index < count; index++) {
            square64 = rank * 8 + file;
            square120 = Sq64ToSq120[square64];
            position->pieces[square120] = piece;
            file++;
        }
        fen++;
    }

    position->side = (*fen == 'w') ? WHITE : BLACK;
    fen += 2;

    for (index = 0; index < 4; index++) {
        if (*fen == ' ')
            break;
        switch (*fen) {
        case 'K':
            position->castlePermission |= wKCastle;
            break;
        case 'Q':
            position->castlePermission |= wQCastle;
            break;
        case 'k':
            position->castlePermission |= bKCastle;
            break;
        case 'q':
            position->castlePermission |= bQCastle;
            break;
        default:
            break;
        }
        fen++;
    }
    fen++;
    if (*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        position->enPassant = FR2SQ(file, rank);
    }

    position->positionKey = GeneratePositionKey(position);
    UpdateListMaterial(position);
    return 0;
}
