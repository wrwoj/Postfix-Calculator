#include "board.h"
#include "parser.h"
#include <iostream>
#include <string>

/*
Very simple implementation of the popular hex game.
*/


int main(void) {
    board currentboard;
    bool new_board_flag = false;
    bool first_board = true;
    int y = 0;

    std::string current_line;
    while (std::getline(std::cin, current_line)) {
        int length = current_line.length();
        y++;

        if (length > 3 && current_line[length - 1] == '-' && current_line[length - 2] == '-' && current_line[length - 3] == '-') {
            processFirstLine(currentboard, new_board_flag, y, length, first_board);
        }
        else if (current_line[0] == ' ' || current_line[0] == '<') {
            parseGameLine(currentboard, current_line, y);
        }
        else {
            parseCommand(current_line, currentboard);
        }
    }
    return 0;
}
