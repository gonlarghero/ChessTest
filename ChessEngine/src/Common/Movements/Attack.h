#ifndef COMMON_MOVEMENTS_ATTACK_H
#define COMMON_MOVEMENTS_ATTACK_H

#include "../../Data/BoardValidator.h"
#include "../Board.h"
#include "../Validate.h"

bool SqAttacked(const int sq, const int side, const BOARD *position);

#endif