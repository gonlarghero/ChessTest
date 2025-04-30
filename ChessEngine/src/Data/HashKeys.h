#ifndef DATA_HASHKEYS_H
#define DATA_HASHKEYS_H

#include "../Common/Board.h"
#include "../Common/Macros.h"

U64 GeneratePositionKey(const BOARD *position);
void InitializeHashKeys();

#endif