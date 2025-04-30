#ifndef COMMON_MOVEMENTS_MAKEMOVE_H
#define COMMON_MOVEMENTS_MAKEMOVE_H

#include "../../Data/BoardValidator.h"
#include "../Board.h"
#include "../Validate.h"
#include "Attack.h"
#include "BaseHashKeys.h"
#include "Move.h"

bool MakeMove(BOARD *position, int move);
void TakeMove(BOARD *position);

#endif
