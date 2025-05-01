#ifndef COMMON_GAMERULES_H
#define COMMON_GAMERULES_H

#include <iostream>

#include "../Common/Board.h"
#include "../Common/Movements/Move.h"
#include "../Engine/MoveGenerator.h"

int ThreeFoldRepetition(const BOARD *position);
bool DrawMaterial(const BOARD *position);
bool StaleMate(BOARD *position);
bool CheckGameResult(BOARD *position);

#endif