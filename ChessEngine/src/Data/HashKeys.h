#ifndef DATA_HASHKEYS_H
#define DATA_HASHKEYS_H

#include "../Common/Board.h"

U64 GeneratePositionKey(const BOARD *position);
void InitializeHashKeys();

#endif