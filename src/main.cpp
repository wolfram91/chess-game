#include <iostream>
#include <memory>

#include "Board.h"
#include "Knight.h"

int main() {

    Board board;

    // Place first Knight at (4,4)
    auto knight1 = std::make_unique<Knight>(
        Color::WHITE
    );

    board.placePiece(
        std::move(knight1),
        Position{4, 4}
    );

    // Place second Knight at (6,5)
    auto knight2 = std::make_unique<Knight>(
        Color::BLACK
    );

    board.placePiece(
        std::move(knight2),
        Position{6, 5}
    );


    // -----------------------------------
    // Test 1: Move from an empty square
    // -----------------------------------

    bool moved = board.movePiece(
        Position{3, 3},
        Position{5, 4}
    );

    if (!moved) {
        std::cout << "Test 1 passed: Cannot move from an empty square."
                  << std::endl;
    }


    // -----------------------------------
    // Test 2: Move to an occupied square
    // -----------------------------------

    moved = board.movePiece(
        Position{4, 4},
        Position{6, 5}
    );

    if (!moved) {
        std::cout << "Test 2 passed: Cannot move to an occupied square."
                  << std::endl;
    }


    // -----------------------------------
    // Test 3: Invalid source position
    // -----------------------------------

    moved = board.movePiece(
        Position{-1, 4},
        Position{5, 4}
    );

    if (!moved) {
        std::cout << "Test 3 passed: Invalid position rejected."
                  << std::endl;
    }


    return 0;
}