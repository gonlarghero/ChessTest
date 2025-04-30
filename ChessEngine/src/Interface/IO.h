#ifndef INTERFACE_IO_H
#define INTERFACE_IO_H

#include "../Common/Board.h"
#include "../Common/Definitions.h"
#include "../Common/Global.h"
#include "../Common/Macros.h"
#include "../Common/Movements/Move.h"
#include "../Common/Validate.h"
#include "../Engine/MoveGenerator.h"
#include <string>

extern std::string PrintSquare(const int square);
extern std::string PrintMove(const int move);
extern void PrintMoveList(const MOVELIST *list);
extern int ParseMove(char *ptrChar, BOARD *position);

#endif
