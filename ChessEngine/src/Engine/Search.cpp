#include "Search.h"

bool isRepetition(const BOARD *position){

	int index = 0;

	for(index = position->historyPlay - position->fiftyMove; index < position->historyPlay-1; ++index){

		ASSERT(index >= 0 && index< MAX_GAME_MOVES);

		if(position->positionKey == position->history[index].positionKey)
			return true;
	}

	return false;
}
