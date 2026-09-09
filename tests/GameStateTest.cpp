#include <iostream>
#include <memory>

#include "GameState.h"
#include "Pawn.h"
#include "Move.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "MoveValidator.h"

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
        Position{3, 4},
        MoveType::NORMAL
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
    
    // --------------------------------------------------
    // 6. Test Rook state restoration
    // --------------------------------------------------

    GameState rookGame;
    Board& rookBoard = rookGame.getBoard();

    clearBoard(rookBoard);

    rookBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 0}
    );

    Move rookMove{
        Position{0, 0},
        Position{0, 3},
        MoveType::NORMAL
    };

    std::cout << "Rook move: "
              << rookGame.makeMove(rookMove)
              << std::endl;

    std::cout << "Undo Rook move: "
              << rookGame.undoMove()
              << std::endl;

    std::cout << "Rook restored to original square: "
              << (rookBoard.getPiece(Position{0, 0}) != nullptr)
              << std::endl;

    std::cout << "Original square contains Rook: "
              << (dynamic_cast<Rook*>(
                      rookBoard.getPiece(Position{0, 0})
                  ) != nullptr)
              << std::endl;
    
        // --------------------------------------------------
    // 7. Test hasMoved state
    // --------------------------------------------------

    GameState stateGame;
    Board& stateBoard = stateGame.getBoard();

    clearBoard(stateBoard);

    stateBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    stateBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    King* king =
        dynamic_cast<King*>(
            stateBoard.getPiece(Position{0, 4})
        );

    Rook* rook =
        dynamic_cast<Rook*>(
            stateBoard.getPiece(Position{0, 7})
        );

    std::cout << "King initially hasn't moved: "
              << (king != nullptr && !king->hasMoved())
              << std::endl;

    std::cout << "Rook initially hasn't moved: "
              << (rook != nullptr && !rook->hasMoved())
              << std::endl;
    
    // --------------------------------------------------
    // 8. Test King hasMoved after moving
    // --------------------------------------------------

    Move kingMove2{
        Position{0, 4},
        Position{1, 4},
        MoveType::NORMAL
    };

    std::cout << "King move successful: "
              << stateGame.makeMove(kingMove2)
              << std::endl;

    king =
        dynamic_cast<King*>(
            stateBoard.getPiece(Position{1, 4})
        );

    std::cout << "King has moved after move: "
              << (king != nullptr && king->hasMoved())
              << std::endl;
    
        // --------------------------------------------------
    // 8. Test basic castling validation
    // --------------------------------------------------

    GameState castleGame;
    Board& castleBoard = castleGame.getBoard();

    clearBoard(castleBoard);

    castleBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    castleBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    Move castleMove{
        Position{0, 4},
        Position{0, 6},
        MoveType::CASTLING
    };

    std::cout << "Basic kingside castling is valid: "
              << MoveValidator::isValidMove(
                     castleBoard,
                     castleMove
                 )
              << std::endl;
    
        // --------------------------------------------------
    // 9. Castling blocked by a piece
    // --------------------------------------------------

    GameState blockedCastleGame;
    Board& blockedCastleBoard = blockedCastleGame.getBoard();

    clearBoard(blockedCastleBoard);

    blockedCastleBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    blockedCastleBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    // Piece between King and Rook.
    blockedCastleBoard.placePiece(
        std::make_unique<Bishop>(Color::WHITE),
        Position{0, 5}
    );

    std::cout << "Castling blocked by piece: "
              << !MoveValidator::isValidMove(
                     blockedCastleBoard,
                     castleMove
                 )
              << std::endl;


    // --------------------------------------------------
    // 10. Castling without a Rook
    // --------------------------------------------------

    GameState noRookGame;
    Board& noRookBoard = noRookGame.getBoard();

    clearBoard(noRookBoard);

    noRookBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    std::cout << "Castling without Rook rejected: "
              << !MoveValidator::isValidMove(
                     noRookBoard,
                     castleMove
                 )
              << std::endl;


    // --------------------------------------------------
    // 11. Wrong-colored Rook
    // --------------------------------------------------

    GameState wrongRookGame;
    Board& wrongRookBoard = wrongRookGame.getBoard();

    clearBoard(wrongRookBoard);

    wrongRookBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    wrongRookBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{0, 7}
    );

    std::cout << "Wrong-colored Rook rejected: "
              << !MoveValidator::isValidMove(
                     wrongRookBoard,
                     castleMove
                 )
              << std::endl;
    
        // --------------------------------------------------
    // 12. Test Board castling execution
    // --------------------------------------------------

    GameState boardCastleGame;
    Board& boardCastle = boardCastleGame.getBoard();

    clearBoard(boardCastle);

    boardCastle.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    boardCastle.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    Move boardCastleMove{
        Position{0, 4},
        Position{0, 6},
        MoveType::CASTLING
    };

    std::cout << "Board executes castling: "
              << boardCastle.executeCastling(boardCastleMove)
              << std::endl;

    std::cout << "King moved to g1: "
              << (dynamic_cast<King*>(
                      boardCastle.getPiece(Position{0, 6})
                  ) != nullptr)
              << std::endl;

    std::cout << "Rook moved to f1: "
              << (dynamic_cast<Rook*>(
                      boardCastle.getPiece(Position{0, 5})
                  ) != nullptr)
              << std::endl;

    std::cout << "e1 is empty: "
              << boardCastle.isEmpty(Position{0, 4})
              << std::endl;

    std::cout << "h1 is empty: "
              << boardCastle.isEmpty(Position{0, 7})
              << std::endl;
    
        // --------------------------------------------------
    // 13. Test complete castling and undo
    // --------------------------------------------------

    GameState fullCastleGame;
    Board& fullCastleBoard = fullCastleGame.getBoard();

    clearBoard(fullCastleBoard);

    fullCastleBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    fullCastleBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    Move fullCastleMove{
        Position{0, 4},
        Position{0, 6},
        MoveType::CASTLING
    };

    std::cout << "Full castling successful: "
              << fullCastleGame.makeMove(fullCastleMove)
              << std::endl;

    std::cout << "King on g1 after castling: "
              << (dynamic_cast<King*>(
                      fullCastleBoard.getPiece(Position{0, 6})
                  ) != nullptr)
              << std::endl;

    std::cout << "Rook on f1 after castling: "
              << (dynamic_cast<Rook*>(
                      fullCastleBoard.getPiece(Position{0, 5})
                  ) != nullptr)
              << std::endl;

    std::cout << "Undo castling successful: "
              << fullCastleGame.undoMove()
              << std::endl;

    std::cout << "King restored to e1: "
              << (dynamic_cast<King*>(
                      fullCastleBoard.getPiece(Position{0, 4})
                  ) != nullptr)
              << std::endl;

    std::cout << "Rook restored to h1: "
              << (dynamic_cast<Rook*>(
                      fullCastleBoard.getPiece(Position{0, 7})
                  ) != nullptr)
              << std::endl;
    
    return 0;
}