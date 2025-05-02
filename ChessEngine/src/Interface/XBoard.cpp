#include "XBoard.h"

// TODO: shouldnt be necesarry with usermove flag on
bool IsValidMoveFormat(const char *moveStr) {
    if (!moveStr)
        return false;

    size_t len = strlen(moveStr);
    if (len < 4 || len > 5)
        return false;

    char fromFile = moveStr[0];
    char fromRank = moveStr[1];
    char toFile = moveStr[2];
    char toRank = moveStr[3];

    if (fromFile < 'a' || fromFile > 'h')
        return false;
    if (fromRank < '1' || fromRank > '8')
        return false;
    if (toFile < 'a' || toFile > 'h')
        return false;
    if (toRank < '1' || toRank > '8')
        return false;

    if (len == 5) {
        char promo = moveStr[4];
        if (promo != 'q' && promo != 'r' && promo != 'b' && promo != 'n')
            return false;
    }

    return true;
}

void PrintOptions() {
    std::cout << "feature ping=1 setboard=1 colors=0 usermove=1" << std::endl;
    std::cout << "feature done=1" << std::endl;
}

void XBoard_Loop(BOARD *position, SEARCHINFO *info) {

    info->xboard = true;
    info->postThinking = false;

    // Disable input/output buffering
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    // Vice Hack for WindBoard
    PrintOptions();

    // TODO:should be send to the search function
    int movestogo[2] = {30, 30};

    int depth = -1;
    int movetime = -1;
    int time = -1;
    int inc = 0;
    int engineSide = BOTH;
    int mps = 0;
    int move = NOMOVE;

    std::string input, command;

    while (!info->quit) {
        if (position->side == engineSide && CheckGameResult(position) == false) {
            info->starttime = GetTickCount();
            info->depth = depth;

            if (movetime != -1) {
                info->timeset = true;
                info->stoptime = info->starttime + movetime;
            } else if (time != -1) {
                info->timeset = true;
                int timePerMove = time / movestogo[position->side];
                timePerMove -= 50;
                info->stoptime = info->starttime + timePerMove + inc;
            }

            if (depth == -1 || depth > MAX_DEPTH) {
                info->depth = MAX_DEPTH;
            }

            if (info->postThinking) {
                std::cout << "time:" << time << " start:" << info->starttime << " stop:" << info->stoptime
                          << " depth:" << info->depth << " timeset:" << info->timeset
                          << " movestogo:" << movestogo[position->side] << " mps:" << mps << "\n";
            }

            SearchPosition(position, info);

            if (mps != 0) {
                movestogo[position->side ^ 1]--;
                if (movestogo[position->side ^ 1] < 1) {
                    movestogo[position->side ^ 1] = mps;
                }
            }
        }

        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> command;

        if (command == "quit") {
            info->quit = true;
            break;
        } else if (command == "force") {
            position->side = BOTH;
            continue;
        } else if (command == "protover") {
            PrintOptions();
        } else if (command == "sd") {
            iss >> depth;
        } else if (command == "st") {
            int seconds;
            iss >> seconds;
            movetime = seconds * 1000;
        } else if (command == "time") {
            int centiseconds = 0;
            iss >> centiseconds;
            time = centiseconds * 10;
        } else if (command == "level") {
            int minutes = 0;
            std::string timeToken;

            if (!(iss >> mps >> minutes >> inc)) {
                iss.clear();
                iss >> mps >> timeToken >> inc;
            }

            movestogo[0] = movestogo[1] = (mps != 0 ? mps : 30);
            time = -1;
            movetime = -1;
        } else if (command == "ping") {
            std::string number;
            iss >> number;
            std::cout << "pong" << number << "\n";
        } else if (command == "new") {
            engineSide = BLACK;
            ParseFen(START_FEN, position);
            depth = -1;
        } else if (command == "setboard") {
            std::string fen = input.substr(command.size());
            ParseFen(fen.c_str(), position);
            engineSide = BOTH;
        } else if (command == "go") {
            engineSide = position->side ^ 1;
        } else if (command == "usermove") {
            std::string moveStr = input.substr(command.size() + 1);
            move = ParseMove(moveStr.c_str(), position);
            if (move == NOMOVE)
                continue;
            MakeMove(position, move);
            position->play = 0;
        } else if (IsValidMoveFormat(command.c_str())) {
            move = ParseMove(command.c_str(), position);
            if (move == NOMOVE)
                continue;
            MakeMove(position, move);
            position->play = 0;
        }
    }
}