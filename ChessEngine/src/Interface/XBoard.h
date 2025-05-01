#ifndef INTERFACE_XBOARD_H
#define INTERFACE_XBOARD_H

#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include "../Common/Board.h"
#include "../Common/Global.h"
#include "../Data/Fen.h"
#include "../Engine/MoveGenerator.h"
#include "../Engine/Search.h"
#include "GameRules.h"

void XBoard_Loop(BOARD *position, SEARCHINFO *info);

#endif