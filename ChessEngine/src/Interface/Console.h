#ifndef INTERFACE_CONSOLE_H
#define INTERFACE_CONSOLE_H

#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>

#include "../Common/Board.h"
#include "../Data/Fen.h"
#include "../Engine/Search.h"
#include "GameRules.h"

void Console_Loop(BOARD *position, SEARCHINFO *info);

#endif