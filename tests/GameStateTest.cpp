#include <iostream>
#include <memory>

#include "GameState.h"
#include "Pawn.h"
#include "Move.h"
#include "King.h"
#include "Rook.h"

void clearBoard(Board& board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (board.getPiece(Position{row, col}) != nullptr) {
                board.removePiece(Position{row, col});
            }
        }
    }
}

int main() {

    std::cout << std::boolalpha;

    GameState game;
    Board& board = game.getBoard();

    clearBoard(board);

    board.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{1, 4}
    );

    // e2 -> e4
    Move firstMove{
        Position{1, 4},
        Position{3, 4}
    };

    std::cout << "e2-e4 successful: "
              << game.makeMove(firstMove)
              << std::endl;

    std::cout << "Pawn on e4: "
              << (board.getPiece(Position{3, 4}) != nullptr)
              << std::endl;

    // Undo e2 -> e4
    std::cout << "Undo successful: "
              << game.undoMove()
              << std::endl;

    std::cout << "Pawn restored to e2: "
              << (board.getPiece(Position{1, 4}) != nullptr)
              << std::endl;

    std::cout << "e4 empty after undo: "
              << (board.getPiece(Position{3, 4}) == nullptr)
              << std::endl;

    // e2 -> e4 again.
    Move secondMove{
        Position{1, 4},
        Position{3, 4}
    };

    std::cout << "e2-e4 again after undo: "
              << game.makeMove(secondMove)
              << std::endl;

    // --------------------------------------------------
    // 4. Test capture and undo
    // --------------------------------------------------

    GameState captureGame;
    Board& captureBoard = captureGame.getBoard();

    clearBoard(captureBoard);

    // Place a white rook on d4.
    captureBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{3, 3}
    );

    // Place a black pawn on d7.
    captureBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{6, 3}
    );

    // White rook captures black pawn.
    Move captureMove{
        Position{3, 3},
        Position{6, 3}
    };

    std::cout << "Rook captures pawn: "
            << captureGame.makeMove(captureMove)
            << std::endl;

    std::cout << "Black pawn removed from d7: "
            << (captureBoard.getPiece(Position{6, 3}) != nullptr)
            << std::endl;

    // Undo the capture.
    std::cout << "Undo capture: "
            << captureGame.undoMove()
            << std::endl;

    Piece* restoredPiece =
        captureBoard.getPiece(Position{6, 3});

    std::cout << "Captured piece restored: "
            << (restoredPiece != nullptr)
            << std::endl;

    std::cout << "Restored piece is black: "
            << (restoredPiece != nullptr &&
                restoredPiece->getColor() == Color::BLACK)
            << std::endl;

    std::cout << "Restored piece is a Pawn: "
            << (dynamic_cast<Pawn*>(restoredPiece) != nullptr)
            << std::endl;

        // --------------------------------------------------
    // 5. Test King move and undo
    // --------------------------------------------------

    GameState kingGame;
    Board& kingBoard = kingGame.getBoard();

    clearBoard(kingBoard);

    kingBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    Move kingMove{
        Position{0, 4},
        Position{1, 4}
    };

    std::cout << "King move: "
              << kingGame.makeMove(kingMove)
              << std::endl;

    std::cout << "Undo King move: "
              << kingGame.undoMove()
              << std::endl;

    std::cout << "King restored to original square: "
              << (kingBoard.getPiece(Position{0, 4}) != nullptr)
              << std::endl;

    std::cout << "Original square contains King: "
              << (dynamic_cast<King*>(
                      kingBoard.getPiece(Position{0, 4})
                  ) != nullptr)
              << std::endl;
    
    return 0;
}