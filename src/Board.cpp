#include "Board.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"

Board::Board() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            squares[row][col] = nullptr;
        }
    }
}

bool Board::placePiece(
    std::unique_ptr<Piece> piece,
    Position position
) {
    if (!isValidPosition(position)) {
        return false;
    }

    if (piece == nullptr) {
        return false;
    }

    if (squares[position.row][position.col] != nullptr) {
        return false;
    }

    squares[position.row][position.col] = std::move(piece);

    return true;
}

Piece* Board::getPiece(Position position) const {

    if (!isValidPosition(position)) {
        return nullptr;
    }

    return squares[position.row][position.col].get();
}

bool Board::isEmpty(Position position) const {

    if (!isValidPosition(position)) {
        return false;
    }

    return squares[position.row][position.col] == nullptr;
}

bool Board::isValidPosition(Position position) const {
    return position.row >= 0 &&
           position.row < 8 &&
           position.col >= 0 &&
           position.col < 8;
}

bool Board::removePiece(Position position) {

    if (!isValidPosition(position)) {
        return false;
    }

    if (squares[position.row][position.col] == nullptr) {
        return false;
    }

    squares[position.row][position.col].reset();

    return true;
}

bool Board::movePiece(
    Position from,
    Position to
) {
    if (!isValidPosition(from) || !isValidPosition(to)) {
        return false;
    }

    if (squares[from.row][from.col] == nullptr) {
        return false;
    }

    if (squares[to.row][to.col] != nullptr) {
        return false;
    }

    squares[to.row][to.col] = std::move(
        squares[from.row][from.col]
    );

    return true;
}

bool Board::executeMove(const Move& move) {

    Position from = move.from;
    Position to = move.to;

    if (!isValidPosition(from) ||
        !isValidPosition(to)) {
        return false;
    }

    if (squares[from.row][from.col] == nullptr) {
        return false;
    }

    if (squares[to.row][to.col] != nullptr) {
        return false;
    }

    squares[to.row][to.col] = std::move(
        squares[from.row][from.col]
    );

    return true;
}

void Board::setup() {

    // White back rank
    placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 0}
    );

    placePiece(
        std::make_unique<Knight>(Color::WHITE),
        Position{0, 1}
    );

    placePiece(
        std::make_unique<Bishop>(Color::WHITE),
        Position{0, 2}
    );

    placePiece(
        std::make_unique<Queen>(Color::WHITE),
        Position{0, 3}
    );

    placePiece(
        std::make_unique<King>(Color::WHITE),
        Position{0, 4}
    );

    placePiece(
        std::make_unique<Bishop>(Color::WHITE),
        Position{0, 5}
    );

    placePiece(
        std::make_unique<Knight>(Color::WHITE),
        Position{0, 6}
    );

    placePiece(
        std::make_unique<Rook>(Color::WHITE),
        Position{0, 7}
    );

    // White pawns
    for (int col = 0; col < 8; col++) {
        placePiece(
            std::make_unique<Pawn>(Color::WHITE),
            Position{1, col}
        );
    }


    // Black back rank
    placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{7, 0}
    );

    placePiece(
        std::make_unique<Knight>(Color::BLACK),
        Position{7, 1}
    );

    placePiece(
        std::make_unique<Bishop>(Color::BLACK),
        Position{7, 2}
    );

    placePiece(
        std::make_unique<Queen>(Color::BLACK),
        Position{7, 3}
    );

    placePiece(
        std::make_unique<King>(Color::BLACK),
        Position{7, 4}
    );

    placePiece(
        std::make_unique<Bishop>(Color::BLACK),
        Position{7, 5}
    );

    placePiece(
        std::make_unique<Knight>(Color::BLACK),
        Position{7, 6}
    );

    placePiece(
        std::make_unique<Rook>(Color::BLACK),
        Position{7, 7}
    );

    // Black pawns
    for (int col = 0; col < 8; col++) {
        placePiece(
            std::make_unique<Pawn>(Color::BLACK),
            Position{6, col}
        );
    }
}

std::unique_ptr<Piece> Board::takePiece(Position position) {

    if (!isValidPosition(position)) {
        return nullptr;
    }

    if (squares[position.row][position.col] == nullptr) {
        return nullptr;
    }

    return std::move(
        squares[position.row][position.col]
    );
}