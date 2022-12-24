#include "PVTable.h"

#include <stdio.h>
#include <stdlib.h>

const int PvSize = 0x100000 *2;

void InitPVTable(PVTABLE *table){

	table->numEntries = PvSize/ sizeof(PVENTRY);
	//para no salirse del arreglo.
	table-> numEntries -= 2;
	free(table->pTable);
	table->pTable = (PVENTRY *) malloc(table->numEntries * sizeof(PVENTRY));
	ClearPVTable(table);
}


void ClearPVTable(PVTABLE *table){

	PVENTRY *pvEntry;
	for(pvEntry = table->pTable; pvEntry< table->pTable + table->numEntries; pvEntry++){
		pvEntry->positionKey = 0ULL;
		pvEntry->move = NOMOVE;
	}
}

void StorePVMove(const BOARD* position, const int move){

	int index = position->positionKey % position->pvTable->numEntries;
	ASSERT(index >= 0 && index <= position->pvTable->numEntries -1);

	position->pvTable->pTable[index].move = move;
	position->pvTable->pTable[index].positionKey = position->positionKey;

}

int ProbePVTable(const BOARD* position){

	int index = position->positionKey % position->pvTable->numEntries;
	ASSERT(index >= 0 && index <= position->pvTable->numEntries -1);

	if(position->pvTable->pTable[index].positionKey == position->positionKey){
		return position->pvTable->pTable[index].move;
	}

	return NOMOVE;
}
