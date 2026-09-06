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

    // Make sure the piece belongs to the player whose turn it is.
    if (piece->getColor() != currentTurn) {
        return false;
    }

    // Check whether the move is legal.
    if (!MoveValidator::isValidMove(board, move)) {
        return false;
    }

    // Apply the move.
    if (!board.executeMove(move)) {
        return false;
    }

    // Successful move → change turn.
    switchTurn();

    return true;
}