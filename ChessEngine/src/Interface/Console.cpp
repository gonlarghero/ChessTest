#include "Console.h"

void Console_Loop(BOARD *position, SEARCHINFO *info) {

    std::cout << "Welcome to Console Mode!\n";
    std::cout << "Type 'help' for commands\n\n";

    info->xboard = false;
    info->postThinking = true;

    int depth = MAX_DEPTH, movetime = 3000;
    int engineSide = BLACK;
    int move = NOMOVE;

    ParseFen(START_FEN, position);

    std::string input, command;

    while (!info->quit) {
        if (position->side == engineSide && CheckGameResult(position) == false) {
            info->starttime = GetTickCount();
            info->depth = depth;

            if (movetime != 0) {
                info->timeset = TRUE;
                info->stoptime = info->starttime + movetime;
            }

            SearchPosition(position, info);
        }

        std::cout << "\n > ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        iss >> command;

        if (command == "help") {
            std::cout << "Commands:\n"
                      << "quit - quit game\n"
                      << "force - computer will not think\n"
                      << "print - show board\n"
                      << "post - show thinking\n"
                      << "nopost - do not show thinking\n"
                      << "new - start new game\n"
                      << "go - set computer thinking\n"
                      << "depth x - set depth to x\n"
                      << "time x - set thinking time to x seconds\n"
                      << "view - show current depth/time settings\n"
                      << "setboard <fen> - set position to FEN\n"
                      << "move <uci> - enter moves using e2e4 notation\n\n";
            continue;
        } else if (command == "setboard") {
            std::string fen = input.substr(input.find("setboard") + 9);
            engineSide = BOTH;
            ParseFen(fen.c_str(), position);
            continue;
        } else if (command == "quit") {
            info->quit = true;
            break;
        } else if (command == "post") {
            info->postThinking = true;
            continue;
        } else if (command == "nopost") {
            info->postThinking = false;
            continue;
        } else if (command == "print") {
            PrintBoard(position);
            continue;
        } else if (command == "force") {
            engineSide = BOTH;
            continue;
        } else if (command == "view") {
            std::cout << "depth: " << (depth == MAX_DEPTH ? "not set" : std::to_string(depth)) << "\n";
            std::cout << "movetime: " << (movetime != 0 ? std::to_string(movetime / 1000) + "s" : "not set") << "\n";
            continue;
        } else if (command == "depth") {
            iss >> depth;
            if (depth == 0)
                depth = MAX_DEPTH;
            continue;
        } else if (command == "time") {
            int seconds;
            iss >> seconds;
            movetime = seconds * 1000;
            continue;
        } else if (command == "new") {
            engineSide = BLACK;
            ParseFen(START_FEN, position);
            continue;
        } else if (command == "go") {
            engineSide = position->side;
            continue;
        }

        move = ParseMove(input.c_str(), position);
        if (move == NOMOVE) {
            std::cout << "Unknown command or invalid move: " << input << "\n";
            continue;
        }

        if (!MakeMove(position, move)) {
            std::cout << "Illegal move attempted\n";
            continue;
        }
    }
}