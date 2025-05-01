#include "PVTable.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

const int PvSize = 0x100000 * 2;

int GetPVLine(const int depth, BOARD *position) {

    ASSERT(depth < MAX_DEPTH);

    int move = ProbePVTable(position);
    int count = 0;

    while (move != NOMOVE && count < depth) {

        ASSERT(count < MAX_DEPTH);

        if (MoveExists(position, move)) {
            MakeMove(position, move);
            position->pvArray[count] = move;
            count++;
        } else
            break;

        move = ProbePVTable(position);
    }

    while (position->play > 0) TakeMove(position);

    return count;
}

void InitPVTable(PVTABLE *table) {
    delete[] table->pTable;
    table->numEntries = PvSize / sizeof(PVENTRY);
    table->numEntries -= 2; // just in case to not go out of bounds.
    table->pTable = new PVENTRY[table->numEntries];
    ClearPVTable(table);

    std::cout << "PvTable init complete with " << table->numEntries << " entries\n";
}

void ClearPVTable(PVTABLE *table) {
    for (int i = 0; i < table->numEntries; ++i) {
        table->pTable[i].positionKey = 0ULL;
        table->pTable[i].move = NOMOVE;
    }
}

void StorePVMove(const BOARD *position, const int move) {

    int index = position->positionKey % position->pvTable->numEntries;

    ASSERT(index >= 0 && index <= position->pvTable->numEntries - 1);

    position->pvTable->pTable[index].move = move;
    position->pvTable->pTable[index].positionKey = position->positionKey;
}

int ProbePVTable(const BOARD *position) {

    int index = static_cast<int>(position->positionKey % position->pvTable->numEntries);

    ASSERT(index >= 0 && index <= position->pvTable->numEntries - 1);

    if (position->pvTable->pTable[index].positionKey == position->positionKey) {
        return position->pvTable->pTable[index].move;
    }

    return NOMOVE;
}
