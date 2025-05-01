#include "XBoard.h"

void XBoard_Loop(BOARD *position, SEARCHINFO *info) {

    info->xboard = true;
    info->postThinking = true;

    // Disable input/output buffering
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    // TODO:should be send to the search function
    int movestogo[2] = {30, 30};

    int depth = -1;
    int movetime = -1;
    int time = -1;
    int timeLeft = 0;
    int inc = 0;
    int engineSide = BOTH;
    int timeleft = 0;
    int mps = 0;
    int move = NOMOVE;

    std::string input, command;

    while (!info->quit) {
        if (position->side == engineSide && CheckGameResult(position) == false) {
            info->starttime = GetTickCount();
            info->depth = depth;

            if (time != -1) {
                info->timeset = true;
                time /= movestogo[position->side];
                time -= 50;
                info->stoptime = info->starttime + time + inc;
            }

            if (depth == -1 || depth > MAX_DEPTH) {
                info->depth = MAX_DEPTH;
            }

            std::cout << "time:" << time << " start:" << info->starttime << " stop:" << info->stoptime
                      << " depth:" << info->depth << " timeset:" << info->timeset
                      << " movestogo:" << movestogo[position->side] << " mps:" << mps << "\n";

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
            std::cout << "feature ping=1 setboard=1 colors=0 usermove=1\n";
            std::cout << "feature done=1\n";
        } else if (command == "sd") {
            iss >> depth;
        } else if (command == "st") {
            int seconds;
            iss >> seconds;
            movetime = seconds * 1000;
        } else if (command == "time") {
            int seconds = 0;
            iss >> seconds;
            movetime = seconds * 1000;
        } else if (command == "level") {
            int minutes = 0, seconds = 0;
            std::string timeToken;

            if (!(iss >> mps >> minutes >> inc)) {
                iss.clear();
                iss >> mps >> timeToken >> inc;

                size_t colon = timeToken.find(':');
                if (colon != std::string::npos) {
                    minutes = std::stoi(timeToken.substr(0, colon));
                    seconds = std::stoi(timeToken.substr(colon + 1));
                }
            }

            timeLeft = minutes * 60000 + seconds * 1000;
            movestogo[0] = movestogo[1] = (mps != 0 ? mps : 30);
            time = -1;
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
            engineSide = position->side;
        } else if (command == "usermove") {
            std::string moveStr = input.substr(command.size());
            move = ParseMove(moveStr.c_str(), position);
            if (move == NOMOVE)
                continue;
            MakeMove(position, move);
            position->play = 0;
        }
    }
}