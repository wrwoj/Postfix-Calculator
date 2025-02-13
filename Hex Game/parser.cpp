#include "parser.h"
#include <iostream>

void processFirstLine(board& currentboard, bool& new_board_flag, int& y, int length, bool& fboardflag) {
    new_board_flag = !new_board_flag;
    if (new_board_flag) {
        if (!fboardflag) std::cout << std::endl;
        initializeBoard(currentboard, length);
        fboardflag = false;
        y = 0;
    }
    else {
        currentboard.setup();
    }
}

void parseGameLine(board& currentboard, const std::string& current_line, int y) {
    int length = current_line.length();
    for (int x = 0; x < length; x++) {
        if (current_line[x] == 'r') {
            currentboard.addToken(1, x, y);
        }
        else if (current_line[x] == 'b') {
            currentboard.addToken(2, x, y);
        }
    }
}

void parseCommand(const std::string& current_line, board& currentboard) {
    if (current_line == "PRINT") {
        //currentboard.generateChainsMap();
            std::vector<std::pair<int, int>> emptyCells;
            currentboard.findNearbyEmptyCells(emptyCells);
            for (const auto& cell : emptyCells) {
                std::cout << "(" << cell.first << ", " << cell.second << ")" << std::endl <<std::endl;
            }
            currentboard.findAllChains();
            int chain_number = 1;
            for (const auto& chain :currentboard.chains) {
                std::cout << "Chain " << chain_number << ":" << std::endl;
                for (const auto& pos : chain) {
                    std::cout << "(" << pos[0] << "," << pos[1] << ") ";
                }
                std::cout << std::endl;
                chain_number++;
            }
            currentboard.checkAllChains();
            std::cout << "GO " << currentboard.isGameOver << ";" << std::endl;
            std::cout << "BW " << currentboard.didBlueWin << ";" << std::endl;
            std::cout << "POS " << currentboard.isPossible << ";" << std::endl;

    }
    else if (current_line == "BOARD_SIZE") {
        std::cout << currentboard.size << std::endl;
    }
    else if (current_line == "PAWNS_NUMBER") {
        std::cout << currentboard.pieces_number << std::endl;
    }
    else if (current_line == "IS_BOARD_CORRECT") {
        std::cout << (currentboard.isCorrect ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "IS_GAME_OVER") {
        std::cout << (currentboard.isGameOver ? "YES " : "NO ");
        if (currentboard.isGameOver && currentboard.didBlueWin) {
            std::cout << "BLUE" << std::endl;
        }
        else if (currentboard.isGameOver && !currentboard.didBlueWin) {
            std::cout << "RED" << std::endl;
        }
        else { std::cout << std::endl; }
    }
    else if (current_line == "IS_BOARD_POSSIBLE") {
        std::cout << (currentboard.isPossible ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
      //  std::cout << (currentboard.canWinInMoves(1, 1, false) ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
    //    std::cout << (currentboard.canWinInMoves(2, 1, false) ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
      ///  std::cout << (currentboard.canWinInMoves(1, 2, false) ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
      //  std::cout << (currentboard.canWinInMoves(2, 2, false) ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
  //      std::cout << (currentboard.canWinInMoves(1, 1, true) ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
    ///    std::cout << (currentboard.canWinInMoves(2, 1, true) ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
       // std::cout << (currentboard.canWinInMoves(1, 2, true) ? "YES" : "NO") << std::endl;
    }
    else if (current_line == "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
      //  std::cout << (currentboard.canWinInMoves(2, 2, true) ? "YES" : "NO") << std::endl;
    }
}
