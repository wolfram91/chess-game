#include <iostream>
#include <memory>
#include <vector>

#include "GameState.h"
#include "Pawn.h"
#include "Move.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "MoveValidator.h"
#include "Knight.h"
#include "Queen.h"

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
    
    // Test Knight attack detection

    Board knightBoard;

    knightBoard.placePiece(
        std::make_unique<Knight>(Color::WHITE),
        Position{4, 4}
    );

    bool knightAttack =
        MoveValidator::isSquareAttacked(
            knightBoard,
            Position{6, 5},
            Color::WHITE
        );

    bool nonKnightAttack =
        MoveValidator::isSquareAttacked(
            knightBoard,
            Position{6, 6},
            Color::WHITE
        );

    std::cout
        << "Knight attacks (6,5): "
        << knightAttack
        << std::endl;

    std::cout
        << "Knight attacks (6,6): "
        << nonKnightAttack
        << std::endl;
    
    // Test Pawn attack detection

    Board pawnBoard;

    pawnBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{3, 3}
    );

    bool whitePawnAttack =
        MoveValidator::isSquareAttacked(
            pawnBoard,
            Position{4, 4},
            Color::WHITE
        );

    bool whitePawnNonAttack =
        MoveValidator::isSquareAttacked(
            pawnBoard,
            Position{4, 3},
            Color::WHITE
        );

    std::cout
        << "White Pawn attacks (4,4): "
        << whitePawnAttack
        << std::endl;

    std::cout
        << "White Pawn attacks (4,3): "
        << whitePawnNonAttack
        << std::endl;

    pawnBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{4, 4}
    );

    bool blackPawnAttack =
        MoveValidator::isSquareAttacked(
            pawnBoard,
            Position{3, 3},
            Color::BLACK
        );

    bool blackPawnNonAttack =
        MoveValidator::isSquareAttacked(
            pawnBoard,
            Position{3, 4},
            Color::BLACK
        );

    std::cout
        << "Black Pawn attacks (3,3): "
        << blackPawnAttack
        << std::endl;

    std::cout
        << "Black Pawn attacks (3,4): "
        << blackPawnNonAttack
        << std::endl;
    
    // Test King attack detection

    Board kingAttackBoard;

    kingBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{4, 4}
    );

    bool kingAttack =
        MoveValidator::isSquareAttacked(
            kingBoard,
            Position{5, 5},
            Color::WHITE
        );

    bool kingNonAttack =
        MoveValidator::isSquareAttacked(
            kingBoard,
            Position{6, 6},
            Color::WHITE
        );

    std::cout
        << "King attacks (5,5): "
        << kingAttack
        << std::endl;

    std::cout
        << "King attacks (6,6): "
        << kingNonAttack
        << std::endl;
    
    // Test sliding piece attack detection

    // Rook
    Board rookAttackBoard;

    rookAttackBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{4, 4}
    );

    bool rookAttack =
        MoveValidator::isSquareAttacked(
            rookAttackBoard,
            Position{4, 7},
            Color::WHITE
        );

    bool rookNonAttack =
        MoveValidator::isSquareAttacked(
            rookAttackBoard,
            Position{6, 6},
            Color::WHITE
        );

    std::cout
        << "Rook attacks (4,7): "
        << rookAttack
        << std::endl;

    std::cout
        << "Rook attacks (6,6): "
        << rookNonAttack
        << std::endl;


    // Bishop
    Board bishopAttackBoard;

    bishopAttackBoard.placePiece(
        std::make_unique<Bishop>(Color::WHITE),
        Position{4, 4}
    );

    bool bishopAttack =
        MoveValidator::isSquareAttacked(
            bishopAttackBoard,
            Position{7, 7},
            Color::WHITE
        );

    bool bishopNonAttack =
        MoveValidator::isSquareAttacked(
            bishopAttackBoard,
            Position{6, 5},
            Color::WHITE
        );

    std::cout
        << "Bishop attacks (7,7): "
        << bishopAttack
        << std::endl;

    std::cout
        << "Bishop attacks (6,5): "
        << bishopNonAttack
        << std::endl;


    // Queen
    Board queenAttackBoard;

    queenAttackBoard.placePiece(
        std::make_unique<Queen>(Color::WHITE),
        Position{4, 4}
    );

    bool queenAttack =
        MoveValidator::isSquareAttacked(
            queenAttackBoard,
            Position{4, 7},
            Color::WHITE
        );

    bool queenNonAttack =
        MoveValidator::isSquareAttacked(
            queenAttackBoard,
            Position{6, 5},
            Color::WHITE
        );

    std::cout
        << "Queen attacks (4,7): "
        << queenAttack
        << std::endl;

    std::cout
        << "Queen attacks (6,5): "
        << queenNonAttack
        << std::endl;

    // Test blocked sliding piece attack

    Board blockedRookBoard;

    blockedRookBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{4, 4}
    );

    blockedRookBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{4, 6}
    );

    bool blockedRookAttack =
        MoveValidator::isSquareAttacked(
            blockedRookBoard,
            Position{4, 7},
            Color::WHITE
        );

    std::cout
        << "Rook blocked at (4,6), attacks (4,7): "
        << blockedRookAttack
        << std::endl;

    // Test King in check detection

    // King attacked by Rook
    Board checkBoard;

    checkBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{4, 4}
    );

    checkBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{4, 7}
    );

    bool kingInCheck =
        MoveValidator::isKingInCheck(
            checkBoard,
            Color::WHITE
        );

    std::cout
        << "White King in check by Rook: "
        << kingInCheck
        << std::endl;


    // King not attacked
    Board safeBoard;

    safeBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{4, 4}
    );

    safeBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{6, 7}
    );

    bool kingSafe =
        MoveValidator::isKingInCheck(
            safeBoard,
            Color::WHITE
        );

    std::cout
        << "White King not in check: "
        << !kingSafe
        << std::endl;


    // Rook attack blocked
    Board blockedCheckBoard;

    blockedCheckBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{4, 4}
    );

    blockedCheckBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{4, 6}
    );

    blockedCheckBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{4, 7}
    );

    bool blockedKingCheck =
        MoveValidator::isKingInCheck(
            blockedCheckBoard,
            Color::WHITE
        );

    std::cout
        << "White King protected by blocker: "
        << !blockedKingCheck
        << std::endl;

    // Test that a move cannot leave the King in check

    GameState illegalMoveState;

    Board& illegalBoard =
        illegalMoveState.getBoard();

    // Clear the default starting position
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            illegalBoard.removePiece(
                Position{row, col}
            );
        }
    }

    // White King at (4,4)
    illegalBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{4, 4}
    );

    // White Pawn protecting the King
    illegalBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{4, 5}
    );

    // Black Rook attacking along the row
    illegalBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{4, 7}
    );

    // White tries to move Pawn away from the Rook's line
    Move illegalMove{
        Position{4, 5},
        Position{5, 5},
        MoveType::NORMAL
    };

    bool moveResult =
        illegalMoveState.makeMove(illegalMove);

    std::cout
        << "Move exposing King rejected: "
        << !moveResult
        << std::endl;

    std::cout
        << "Pawn restored after rejection: "
        << (illegalBoard.getPiece(
                Position{4, 5}) != nullptr)
        << std::endl;

    std::cout
        << "King still safe after rejection: "
        << !MoveValidator::isKingInCheck(
                illegalBoard,
                Color::WHITE)
        << std::endl;

    // Test castling while in check

    GameState castleCheckState;

    Board& castleCheckBoard =
        castleCheckState.getBoard();

    // Clear board
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            castleCheckBoard.removePiece(
                Position{row, col}
            );
        }
    }

    // White King e1
    castleCheckBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    // White Rook h1
    castleCheckBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    // Black Rook attacks e1
    castleCheckBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{0, 0}
    );

    Move castleWhileInCheck{
        Position{0, 4},
        Position{0, 6},
        MoveType::CASTLING
    };

    bool castleInCheckResult =
        castleCheckState.makeMove(castleWhileInCheck);

    std::cout
        << "Castling while in check rejected: "
        << !castleInCheckResult
        << std::endl;

    // Test castling through an attacked square

    GameState castleThroughCheckState;

    Board& castleThroughBoard =
        castleThroughCheckState.getBoard();

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            castleThroughBoard.removePiece(
                Position{row, col}
            );
        }
    }

    // White King e1
    castleThroughBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    // White Rook h1
    castleThroughBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    // Black Rook attacks f1
    castleThroughBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{5, 5}
    );

    Move castleThroughCheck{
        Position{0, 4},
        Position{0, 6},
        MoveType::CASTLING
    };

    bool castleThroughCheckResult =
        castleThroughCheckState.makeMove(
            castleThroughCheck
        );

    std::cout
        << "Castling through check rejected: "
        << !castleThroughCheckResult
        << std::endl;

    // Test castling onto an attacked square

    GameState castleDestinationState;

    Board& castleDestinationBoard =
        castleDestinationState.getBoard();

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            castleDestinationBoard.removePiece(
                Position{row, col}
            );
        }
    }

    // White King e1
    castleDestinationBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    // White Rook h1
    castleDestinationBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    // Black Rook attacks g1
    castleDestinationBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{6, 6}
    );

    Move castleOntoCheck{
        Position{0, 4},
        Position{0, 6},
        MoveType::CASTLING
    };

    bool castleDestinationResult =
        castleDestinationState.makeMove(
            castleOntoCheck
        );

    std::cout
        << "Castling onto attacked square rejected: "
        << !castleDestinationResult
        << std::endl;

    // Test Knight pseudo-legal move generation

    Board knightMoveBoard;

    knightMoveBoard.placePiece(
        std::make_unique<Knight>(Color::WHITE),
        Position{4, 4}
    );

    std::vector<Move> knightMoves =
        MoveValidator::getPseudoLegalMoves(
            knightMoveBoard,
            Position{4, 4}
        );

    std::cout
        << "Knight moves from (4,4): "
        << knightMoves.size()
        << std::endl;

    // Test Knight moves with occupied destination squares

    Board knightCaptureBoard;

    knightCaptureBoard.placePiece(
        std::make_unique<Knight>(Color::WHITE),
        Position{4, 4}
    );

    // Friendly piece blocks this destination
    knightCaptureBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{6, 5}
    );

    // Enemy piece can be captured
    knightCaptureBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{6, 3}
    );

    std::vector<Move> knightCaptureMoves =
        MoveValidator::getPseudoLegalMoves(
            knightCaptureBoard,
            Position{4, 4}
        );

    std::cout
        << "Knight moves with friendly blocker and enemy target: "
        << knightCaptureMoves.size()
        << std::endl;

    // Test Rook pseudo-legal move generation

    Board rookMoveBoard;

    rookMoveBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{4, 4}
    );

    std::vector<Move> rookMoves =
        MoveValidator::getPseudoLegalMoves(
            rookMoveBoard,
            Position{4, 4}
        );

    std::cout
        << "Rook moves from (4,4): "
        << rookMoves.size()
        << std::endl;

    // Test Rook move generation with a blocker

    Board blockedRookMoveBoard;

    blockedRookMoveBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{4, 4}
    );

    blockedRookMoveBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{4, 6}
    );

    std::vector<Move> blockedRookMoves =
        MoveValidator::getPseudoLegalMoves(
            blockedRookMoveBoard,
            Position{4, 4}
        );

    std::cout
        << "Rook moves with blocker at (4,6): "
        << blockedRookMoves.size()
        << std::endl;
    
    // Test Rook move generation with an enemy piece

    Board rookCaptureBoard;

    rookCaptureBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{4, 4}
    );

    rookCaptureBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{4, 6}
    );

    std::vector<Move> rookCaptureMoves =
        MoveValidator::getPseudoLegalMoves(
            rookCaptureBoard,
            Position{4, 4}
        );

    std::cout
        << "Rook moves with enemy at (4,6): "
        << rookCaptureMoves.size()
        << std::endl;

    // Test Bishop pseudo-legal move generation

    Board bishopMoveBoard;

    bishopMoveBoard.placePiece(
        std::make_unique<Bishop>(Color::WHITE),
        Position{4, 4}
    );

    std::vector<Move> bishopMoves =
        MoveValidator::getPseudoLegalMoves(
            bishopMoveBoard,
            Position{4, 4}
        );

    std::cout
        << "Bishop moves from (4,4): "
        << bishopMoves.size()
        << std::endl;

    // Test Queen pseudo-legal move generation

    Board queenMoveBoard;

    queenMoveBoard.placePiece(
        std::make_unique<Queen>(Color::WHITE),
        Position{4, 4}
    );

    std::vector<Move> queenMoves =
        MoveValidator::getPseudoLegalMoves(
            queenMoveBoard,
            Position{4, 4}
        );

    std::cout
        << "Queen moves from (4,4): "
        << queenMoves.size()
        << std::endl;

    // Test White Pawn pseudo-legal moves from starting position

    Board pawnMoveBoard;

    pawnMoveBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{1, 4}
    );

    std::vector<Move> pawnMoves =
        MoveValidator::getPseudoLegalMoves(
            pawnMoveBoard,
            Position{1, 4}
        );

    std::cout
        << "White Pawn moves from starting position: "
        << pawnMoves.size()
        << std::endl;

    // Test Pawn blocked directly ahead

    Board blockedPawnBoard;

    blockedPawnBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{1, 4}
    );

    blockedPawnBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{2, 4}
    );

    std::vector<Move> blockedPawnMoves =
        MoveValidator::getPseudoLegalMoves(
            blockedPawnBoard,
            Position{1, 4}
        );

    std::cout
        << "Blocked Pawn moves: "
        << blockedPawnMoves.size()
        << std::endl;

    // Test Pawn diagonal captures

    Board pawnCaptureBoard;

    pawnCaptureBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{4, 4}
    );

    pawnCaptureBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{5, 3}
    );

    pawnCaptureBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{5, 5}
    );

    std::vector<Move> pawnCaptureMoves =
        MoveValidator::getPseudoLegalMoves(
            pawnCaptureBoard,
            Position{4, 4}
        );

    std::cout
        << "Pawn moves with two enemy diagonals: "
        << pawnCaptureMoves.size()
        << std::endl;

    // Test Black Pawn pseudo-legal moves from starting position

    Board blackPawnBoard;

    blackPawnBoard.placePiece(
        std::make_unique<Pawn>(Color::BLACK),
        Position{6, 4}
    );

    std::vector<Move> blackPawnMoves =
        MoveValidator::getPseudoLegalMoves(
            blackPawnBoard,
            Position{6, 4}
        );

    std::cout
        << "Black Pawn moves from starting position: "
        << blackPawnMoves.size()
        << std::endl;

    // Test Pawn away from starting rank

    Board advancedPawnBoard;

    advancedPawnBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{4, 4}
    );

    std::vector<Move> advancedPawnMoves =
        MoveValidator::getPseudoLegalMoves(
            advancedPawnBoard,
            Position{4, 4}
        );

    std::cout
        << "White Pawn moves from (4,4): "
        << advancedPawnMoves.size()
        << std::endl;

    // Test King pseudo-legal moves from center

    Board kingMoveBoard;

    kingMoveBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{4, 4}
    );

    std::vector<Move> kingMoves =
        MoveValidator::getPseudoLegalMoves(
            kingMoveBoard,
            Position{4, 4}
        );

    std::cout
        << "King moves from (4,4): "
        << kingMoves.size()
        << std::endl;

    // Test King pseudo-legal moves from corner

    Board cornerKingBoard;

    cornerKingBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 0}
    );

    std::vector<Move> cornerKingMoves =
        MoveValidator::getPseudoLegalMoves(
            cornerKingBoard,
            Position{0, 0}
        );

    std::cout
        << "King moves from (0,0): "
        << cornerKingMoves.size()
        << std::endl;

    // Test King with friendly piece blocking

    Board blockedKingBoard;

    blockedKingBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{4, 4}
    );

    blockedKingBoard.placePiece(
        std::make_unique<Pawn>(Color::WHITE),
        Position{3, 3}
    );

    std::vector<Move> blockedKingMoves =
        MoveValidator::getPseudoLegalMoves(
            blockedKingBoard,
            Position{4, 4}
        );

    std::cout
        << "King moves with friendly blocker: "
        << blockedKingMoves.size()
        << std::endl;

    // Test legal move generation: safe move

    Board legalMoveBoard;

    legalMoveBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    legalMoveBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{1, 4}
    );

    std::vector<Move> legalMoves =
        MoveValidator::getLegalMoves(
            legalMoveBoard,
            Position{1, 4}
        );

    std::cout
        << "Safe Rook legal moves: "
        << legalMoves.size()
        << std::endl;

    // Test legal move generation: pinned Rook

    Board pinnedRookBoard;

    pinnedRookBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    pinnedRookBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{1, 4}
    );

    pinnedRookBoard.placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{7, 4}
    );

    std::vector<Move> pinnedRookMoves =
        MoveValidator::getLegalMoves(
            pinnedRookBoard,
            Position{1, 4}
        );

    std::cout
        << "Pinned Rook legal moves: "
        << pinnedRookMoves.size()
        << std::endl;

    // Test castling in pseudo-legal move generation

    Board kingCastlingBoard;

    kingCastlingBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    kingCastlingBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    std::vector<Move> kingCastlingMoves =
        MoveValidator::getPseudoLegalMoves(
            kingCastlingBoard,
            Position{0, 4}
        );

    int castlingMoves = 0;

    for (const Move& move : kingCastlingMoves) {
        if (move.type == MoveType::CASTLING) {
            castlingMoves++;
        }
    }

    std::cout
        << "King castling moves generated: "
        << castlingMoves
        << std::endl;

    // Test blocked castling is not generated

    Board blockedCastlingBoard;

    blockedCastlingBoard.placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    blockedCastlingBoard.placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    blockedCastlingBoard.placePiece(
        std::make_unique<Bishop>(Color::WHITE),
        Position{0, 5}
    );

    std::vector<Move> blockedCastlingMoves =
        MoveValidator::getPseudoLegalMoves(
            blockedCastlingBoard,
            Position{0, 4}
        );

    int blockedCastlingCount = 0;

    for (const Move& move : blockedCastlingMoves) {
        if (move.type == MoveType::CASTLING) {
            blockedCastlingCount++;
        }
    }

    std::cout
        << "Blocked castling moves generated: "
        << blockedCastlingCount
        << std::endl;

    return 0;

    return 0;
}