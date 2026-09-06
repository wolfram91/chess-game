#ifndef BOARD_H
#define BOARD_H

#include <memory>

#include "Piece.h"
#include "Move.h"

class Board {
private:
    std::unique_ptr<Piece> squares[8][8];

public:
    Board();

    void setup();

    bool placePiece(
        std::unique_ptr<Piece> piece,
        Position position
    );

    Piece* getPiece(Position position) const;

    bool isEmpty(Position position) const;

    bool isValidPosition(Position position) const;

    bool removePiece(Position position);

    bool movePiece(
        Position from,
        Position to
    );

    bool executeMove(const Move& move);
};

#endif