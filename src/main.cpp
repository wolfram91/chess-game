#include <iostream>
#include <memory>

#include "Board.h"
#include "Move.h"
#include "MoveValidator.h"
#include "Pawn.h"
#include "Rook.h"

int main() {

    std::cout << std::boolalpha;

    // --------------------------------
    // Test 1: Clear two-square move
    // --------------------------------

    Board board1;

    board1.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{6, 3}
    );

    Move clearDoubleMove{
        Position{6, 3},
        Position{4, 3}
    };

    std::cout << "Clear two-square pawn move: "
              << MoveValidator::isValidMove(
                     board1,
                     clearDoubleMove
                 )
              << std::endl;


    // --------------------------------
    // Test 2: Blocked two-square move
    // --------------------------------

    Board board2;

    board2.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{6, 3}
    );

    board2.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{5, 3}
    );

    Move blockedDoubleMove{
        Position{6, 3},
        Position{4, 3}
    };

    std::cout << "Blocked two-square pawn move: "
              << MoveValidator::isValidMove(
                     board2,
                     blockedDoubleMove
                 )
              << std::endl;


    // --------------------------------
    // Test 3: One-square blocked move
    // --------------------------------

    Board board3;

    board3.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{6, 3}
    );

    board3.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{5, 3}
    );

    Move blockedOneMove{
        Position{6, 3},
        Position{5, 3}
    };

    std::cout << "Blocked one-square pawn move: "
              << MoveValidator::isValidMove(
                     board3,
                     blockedOneMove
                 )
              << std::endl;

    return 0;
}