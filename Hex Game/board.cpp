#include "board.h"
#include <iostream>
#include <queue>
#include <set>
#include <array>

const int EMPTY_CELL = 0;
const int RED_PIECE = 1;
const int BLUE_PIECE = 2;
const int NOT_FOUND = 0;
const int FOUND_BLUE = 2;
const int FOUND_RED = 1;
const int DISCONNECTED_CHAIN = 0;
const int CONNECTED_CHAIN = 1;
const int NO_CHAIN_DISCONNECTED = 4;
const int NO_CHAIN_CONNECTED = 5;
const int ADJACENT_POSITIONS = 6;
const int MAX_MOVES_DISTANCE = 2;
const int OFFSET = 4;
const int DISTANCE_BEETWEEN_CELSS = 6;

void board::findNearbyEmptyCells(std::vector<std::pair<int, int>>& emptyCells) {
    std::set<std::pair<int, int>> emptyCellSet;

    // Loop through every cell on the board
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            // Check if the cell is not empty
            if (board_array[x][y] != EMPTY_CELL) {
                // Explore all cells within 2 moves distance
                for (int dy = -MAX_MOVES_DISTANCE; dy <= MAX_MOVES_DISTANCE; ++dy) {
                    for (int dx = -MAX_MOVES_DISTANCE; dx <= MAX_MOVES_DISTANCE; ++dx) {
                        int ny = y + dy;
                        int nx = x + dx;
                        // Check boundaries and ensure we are looking at an empty cell
                        if (ny >= 0 && ny < size && nx >= 0 && nx < size && board_array[nx][ny] == EMPTY_CELL) {
                            // Add to set to avoid duplicates
                            emptyCellSet.insert(std::make_pair(nx, ny));
                        }
                    }
                }
            }
        }
    }

    // Convert set to vector
    emptyCells.clear();
    for (const auto& cell : emptyCellSet) {
        emptyCells.push_back(cell);
    }
}

void board::reset() {
    size = 0;
    isPossible = true;
    isCorrect = false;
    isGameOver = false;
    winner = EMPTY_CELL;
    red_piecies_number = 0;
    blue_piecies_number = 0;
    pieces_number = 0;
    is_it_blue_turn = false;
    board_array.clear();
    chains.clear();
}

void board::resizeBoard() {
    board_array.resize(size);

    for (int i = 0; i < size; ++i) {
        board_array[i].resize(size);
        for (int j = 0; j < size; ++j) {
            board_array[i][j] = EMPTY_CELL;
        }
    }
}

void board::printBoard(int displayValue) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << board_array[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




std::vector<int> board::calcuateIndex(int x, int y) {
    int spaces;
    if (y == size + 1) {
        spaces = 0;
        x = x - spaces - OFFSET;
        x = x / DISTANCE_BEETWEEN_CELSS;
    }
    else if (y <= size) {
        spaces = size * 3 - 2 - 3 * y; //CACULATION OF EXPECTED AMOUT OF SPACES FOR GIVEN Y POSITION IN INPUT
        x = x - spaces - OFFSET;
        x = x / DISTANCE_BEETWEEN_CELSS;
    }
    else if (y > size + 1) {
        spaces = size * 3 - 2 - 3 * (2 * size - y); //CACULATION OF EXPECTED AMOUT OF SPACES FOR GIVEN Y POSITION IN INPUT
        x = x - spaces - OFFSET; // WE IGNORE EVERY CHARACTER UP TO THE FIRST CELL
        x = x / DISTANCE_BEETWEEN_CELSS;
    }
    y = y - 1;
    int yp = 0, xp = 0, fy = 0, fx = 0;
    if (y < size) {
        yp = y;
    }
    else {
        yp = size - 1, xp = y - size + 1;
    }
    fy = yp - x;
    fx = xp + x;
    return std::vector<int>{fx, fy};
}

void board::addToken(int color, int x, int y) {
    if (color == RED_PIECE) {
        red_piecies_number++;
    }
    else if (color == BLUE_PIECE) {
        blue_piecies_number++;
    }
    std::vector<int> index = calcuateIndex(x, y);
    board_array[index[1]][index[0]] = color;
}

void board::setup() {
    pieces_number = red_piecies_number + blue_piecies_number;
    if (blue_piecies_number == red_piecies_number) {
        isCorrect = true;
        is_it_blue_turn = false;
    }
    else if (blue_piecies_number == red_piecies_number - 1) {
        isCorrect = true;
        is_it_blue_turn = true;
    }

    findAllChains();

    checkAllChains();
    if (!isCorrect) {
        isPossible = false;
        isGameOver = false;
    }
}

void initializeBoard(board& currentboard, int length) {
    currentboard.reset();
    currentboard.size = (length - 1) / 3;
    currentboard.resizeBoard();
}

void board::dfs(int row, int col, std::vector<std::vector<bool>>& visited, std::set<std::set<std::array<int, 2>>>& chains) {
    std::queue<std::array<int, 2>> q;
    q.push({ row, col });
    std::set<std::array<int, 2>> current_chain;
    current_chain.insert({ row, col });

    visited[row][col] = true;

    while (!q.empty()) {
        std::array<int, 2> current_pos = q.front();
        q.pop();

        int current_row = current_pos[0];
        int current_col = current_pos[1];

        std::vector<std::array<int, 2>> neighbors = {
                {current_row - 1, current_col},
                {current_row + 1, current_col},
                {current_row, current_col - 1},
                {current_row, current_col + 1},
                {current_row - 1, current_col - 1},
                {current_row + 1, current_col + 1}
        };

        for (const auto& neighbor : neighbors) {
            int n_row = neighbor[0];
            int n_col = neighbor[1];
            if (n_row >= 0 && n_row < size && n_col >= 0 && n_col < size &&
                board_array[n_row][n_col] == board_array[row][col] &&
                !visited[n_row][n_col]) {
                current_chain.insert(neighbor);
                q.push(neighbor);
                visited[n_row][n_col] = true;
            }
        }
    }
    chains.insert(current_chain);
}

bool isPositionInSet(const std::set<std::array<int, 2>>& positions, int row, int col) {
    for (const auto& pos : positions) {
        if (pos[0] == row && pos[1] == col) {
            return true;
        }
    }
    return false; // Position not found in the set
}

int board::connectsTwoSides(const std::set<std::array<int, 2>>& chain) {
    std::queue<std::array<int, 2>> q;
    std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));
    bool connectsLeft = false;
    bool connectsRight = false;
    bool connectsTop = false;
    bool connectsBottom = false;

    auto it = chain.begin();
    int row = (*it)[0];
    int col = (*it)[1];

    int color = board_array[row][col];

    for (const auto& pos : chain) {
        row = pos[0];
        col = pos[1];
        if (!visited[row][col]) {
            q.push({ row, col });

            visited[row][col] = true;
            while (!q.empty()) {
                std::array<int, 2> current_pos = q.front();
                q.pop();

                int current_row = current_pos[0];
                int current_col = current_pos[1];

                if (current_col == 0)
                    connectsLeft = true;
                if (current_col == size - 1)
                    connectsRight = true;

                if (current_row == 0)
                    connectsTop = true;
                if (current_row == size - 1)
                    connectsBottom = true;

                std::vector<std::array<int, 2>> neighbors = {
                        {current_row - 1, current_col},
                        {current_row + 1, current_col},
                        {current_row, current_col - 1},
                        {current_row, current_col + 1},
                        {current_row - 1, current_col - 1},
                        {current_row + 1, current_col + 1}
                };

                for (const auto& neighbor : neighbors) {
                    int n_row = neighbor[0];
                    int n_col = neighbor[1];
                    if (n_row >= 0 && n_row < size && n_col >= 0 && n_col < size &&
                        board_array[n_row][n_col] == board_array[row][col] &&
                        !visited[n_row][n_col] && isPositionInSet(chain, n_row, n_col)) {
                        q.push(neighbor);
                        visited[n_row][n_col] = true;
                    }
                }
            }
            // If any two opposite sides are connected, return true
            if (connectsLeft && connectsRight && color == RED_PIECE) { return FOUND_RED; }
            else if (connectsTop && connectsBottom && color == BLUE_PIECE) { return FOUND_BLUE; }
            connectsLeft = false;
            connectsRight = false;
            connectsTop = false;
            connectsBottom = false;
        }
    }
    return NOT_FOUND;
}

void board::findAllChains() {
    std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (board_array[row][col] != EMPTY_CELL && !visited[row][col]) {
                dfs(row, col, visited, chains);
            }
        }
    }
    return;
}

void board::checkAllChains() {
    for (auto& chain : chains) {
        int res = connectsTwoSides(chain);
        if (res != NOT_FOUND) {
            didBlueWin = res == FOUND_BLUE ? true : false;
            if (didBlueWin && is_it_blue_turn || !didBlueWin && !is_it_blue_turn) {
                isPossible = false;
            }
            if (!isCorrect || isGameOver) {
                isPossible = false;
            }
            isGameOver = true;
            if (!stoneRemovalDisconnectsChain(chain)) {
                isPossible = false;
            }
        }
    }
    return;
}

bool board::stoneRemovalDisconnectsChain(const std::set<std::array<int, 2>>& chain) {
    std::set<std::array<int, 2>> tempChain = chain;
    int res = NO_CHAIN_CONNECTED;
    // Iterate over each stone in the chain set
    for (auto it = tempChain.begin(); it != tempChain.end(); ++it) {
        // Store the stone temporarily
        auto stone = *it;

        // Remove the stone from the chain set
        if (tempChain.size() > 1) {
            res = NO_CHAIN_DISCONNECTED;
            it = tempChain.erase(it);

            // Check if the chain still connects two sides after stone removal
            res = connectsTwoSides(tempChain);

            // Insert the stone back into the chain set
            it = tempChain.insert(it, stone);

            // If removing this stone disconnects the chain, return true
            if (res == NOT_FOUND) {
                return true;
            }
        }
    }
    if (res == NO_CHAIN_CONNECTED) { return true; }
    // If removing any stone maintains the connection, return false
    return false;
}
