#include <iostream>

#include "GameState.h"
#include "Move.h"

int main() {

    GameState game;

    std::cout << std::boolalpha;

    // White: e2 -> e4
    Move whiteMove{
        Position{1, 4},
        Position{3, 4}
    };

    bool whiteResult = game.makeMove(whiteMove);

    std::cout << "White e2-e4: "
              << whiteResult
              << std::endl;

    std::cout << "Black's turn: "
              << (game.getCurrentTurn() == Color::BLACK)
              << std::endl;


    // Black: e7 -> e5
    Move blackMove{
        Position{6, 4},
        Position{4, 4}
    };

    bool blackResult = game.makeMove(blackMove);

    std::cout << "Black e7-e5: "
              << blackResult
              << std::endl;

    std::cout << "White's turn: "
              << (game.getCurrentTurn() == Color::WHITE)
              << std::endl;


    // Try Black again — should fail.
    Move illegalTurnMove{
        Position{4, 4},
        Position{3, 4}
    };

    bool illegalResult = game.makeMove(illegalTurnMove);

    std::cout << "Black tries to move again: "
              << illegalResult
              << std::endl;

    return 0;
}