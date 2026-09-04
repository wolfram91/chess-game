#include "Board.h"
#include "Knight.h"

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

void Board::setup() {

    placePiece(
        std::make_unique<Knight>(Color::WHITE),
        Position{0, 1}
    );

    placePiece(
        std::make_unique<Knight>(Color::WHITE),
        Position{0, 6}
    );

    placePiece(
        std::make_unique<Knight>(Color::BLACK),
        Position{7, 1}
    );

    placePiece(
        std::make_unique<Knight>(Color::BLACK),
        Position{7, 6}
    );
}