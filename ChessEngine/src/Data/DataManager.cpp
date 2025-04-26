#include "DataManager.h"

#include <iomanip>
#include <iostream>
#include <stdio.h>

void InitiFilesRanksBoard() {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int square = A1;

    for (index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        FilesBoard[index] = SQUARE_NULL;
        RanksBoard[index] = SQUARE_NULL;
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            square = FR2SQ(file, rank);
            FilesBoard[square] = file;
            RanksBoard[square] = rank;
        }
    }
}

void InitializeBitMask() {
    int index = 0;

    for (index = 0; index < BOARD_REAL_NUMBER; index++) {
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }

    for (index = 0; index < BOARD_REAL_NUMBER; index++) {
        SetMask[index] |= (1ULL << index);
        ClearMask[index] = ~SetMask[index];
    }
}

void InitializeSq120To64() {
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    for (index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        Sq120ToSq64[index] = 65;
    }
    for (index = 0; index < BOARD_REAL_NUMBER; ++index) {
        Sq64ToSq120[index] = 120;
    }
    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for (file = FILE_A; file <= FILE_H; ++file) {
            sq = FR2SQ(file, rank);
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
}

void printArrays() {
    int index = 0;
    for (index = 0; index < BOARD_SQUARE_NUMBER; ++index) {
        if (index % 10 == 0)
            std::cout << "\n";
        std::cout << std::setw(5) << Sq120ToSq64[index];
    }
    std::cout << "\n";
    for (index = 0; index < BOARD_REAL_NUMBER; ++index) {
        if (index % 8 == 0)
            std::cout << "\n";
        std::cout << std::setw(5) << Sq64ToSq120[index];
    }
}

void LoadData() {
    InitializeSq120To64();
    InitializeBitMask();
    InitializeHashKeys();
    InitiFilesRanksBoard();
}
