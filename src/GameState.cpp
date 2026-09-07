#include "GameState.h"
#include "MoveValidator.h"

GameState::GameState()
    : currentTurn(Color::WHITE) {

    board.setup();
}

Board& GameState::getBoard() {
    return board;
}

const Board& GameState::getBoard() const {
    return board;
}

Color GameState::getCurrentTurn() const {
    return currentTurn;
}

const std::vector<MoveRecord>& GameState::getMoveHistory() const {
    return moveHistory;
}

void GameState::switchTurn() {

    if (currentTurn == Color::WHITE) {
        currentTurn = Color::BLACK;
    } else {
        currentTurn = Color::WHITE;
    }
}

bool GameState::makeMove(const Move& move) {

    Piece* piece = board.getPiece(move.from);

    if (piece == nullptr) {
        return false;
    }

    // Make sure the piece belongs to the player
    // whose turn it is.
    if (piece->getColor() != currentTurn) {
        return false;
    }

    // Check whether the move is legal.
    if (!MoveValidator::isValidMove(board, move)) {
        return false;
    }

    // Save the piece's state BEFORE the move.
    std::unique_ptr<PieceState> previousState =
        piece->saveState();

    // Save the captured piece before executing the move.
    std::unique_ptr<Piece> capturedPiece =
        board.takePiece(move.to);

    // Apply the move.
    if (!board.executeMove(move)) {

        // Restore the captured piece if execution failed.
        if (capturedPiece != nullptr) {
            board.placePiece(
                std::move(capturedPiece),
                move.to
            );
        }

        return false;
    }

    // Tell the piece that its move was successful.
    piece->onMove();

    // Create a record of the move.
    MoveRecord record{
        move,
        std::move(capturedPiece),
        std::move(previousState)
    };

    // Store the record in history.
    moveHistory.push_back(std::move(record));

    // Successful move → change turn.
    switchTurn();

    return true;
}

bool GameState::undoMove() {

    // There must be a move to undo.
    if (moveHistory.empty()) {
        return false;
    }

    // Get the last move.
    MoveRecord& record = moveHistory.back();

    // Move the piece from its current square
    // back to its original square.
    std::unique_ptr<Piece> piece =
        board.takePiece(record.move.to);

    if (piece == nullptr) {
        return false;
    }

    // Restore the piece to its original square.
    if (!board.placePiece(
            std::move(piece),
            record.move.from)) {
        return false;
    }

    // Get the piece we just restored.
    Piece* restoredPiece =
        board.getPiece(record.move.from);

    // Restore its state from before the move.
    if (restoredPiece != nullptr &&
        record.previousState != nullptr) {

        restoredPiece->restoreState(
            *record.previousState
        );
    }

    // If a piece was captured, restore it.
    if (record.capturedPiece != nullptr) {

        if (!board.placePiece(
                std::move(record.capturedPiece),
                record.move.to)) {
            return false;
        }
    }

    // The move no longer exists in history.
    moveHistory.pop_back();

    // Give the turn back to the player who made
    // the move we just reversed.
    switchTurn();

    return true;
}