#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <set>
#include <array>





struct board {
    int size;
    bool isPossible = true;
    bool isCorrect;
    bool isGameOver;
    bool didBlueWin = false;
    int winner;
    int red_piecies_number;
    int blue_piecies_number;
    int pieces_number;
    bool is_it_blue_turn;

    bool end_search = false;

    std::set<std::set<std::array<int, 2>>> chains;


    std::vector<std::vector<int>> board_array;

    void findNearbyEmptyCells(std::vector<std::pair<int, int>>& emptyCells);

    void reset();
    void resizeBoard();
    void printBoard(int displayValue = 0);
    std::vector<int> calcuateIndex(int x, int y);
    void addToken(int color, int x, int y);
    void setup();


    void dfs(int row, int col, std::vector<std::vector<bool>>& visited, std::set<std::set<std::array<int, 2>>>& chains);

    int connectsTwoSides(const std::set<std::array<int, 2>>& chain);

    void findAllChains();

    void checkAllChains();


    bool stoneRemovalDisconnectsChain(const std::set<std::array<int, 2>>& chain);


};

void initializeBoard(board& currentboard, int length);

#endif