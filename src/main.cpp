#include <iostream>

#include "Board.h"

int main() {

    Board board;

    board.setup();

    if (board.getPiece(Position{0, 1}) != nullptr) {
        std::cout << "White Knight found at (0,1)." << std::endl;
    }

    if (board.getPiece(Position{0, 6}) != nullptr) {
        std::cout << "White Knight found at (0,6)." << std::endl;
    }

    if (board.getPiece(Position{7, 1}) != nullptr) {
        std::cout << "Black Knight found at (7,1)." << std::endl;
    }

    if (board.getPiece(Position{7, 6}) != nullptr) {
        std::cout << "Black Knight found at (7,6)." << std::endl;
    }

    return 0;
}