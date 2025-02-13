#ifndef PARSER_H
#define PARSER_H

#include "board.h"
#include <string>

void processFirstLine(board& currentboard, bool& new_board_flag, int& y, int length, bool& fboardflag);
void parseGameLine(board& currentboard, const std::string& current_line, int y);
void parseCommand(const std::string& current_line, board& currentboard);

#endif
