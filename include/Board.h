#ifndef BOARD_H
#define BOARD_H

#include <memory>

#include "Piece.h"
#include "Move.h"

class Board {
private:
    std::unique_ptr<Piece> squares[8][8];

    void getCastlingRookPositions(
        const Move& move,
        Position& rookFrom,
        Position& rookTo
    ) const;

public:
    Board();

    void setup();

    bool placePiece(
        std::unique_ptr<Piece> piece,
        Position position
    );

    Piece* getPiece(Position position) const;

    std::unique_ptr<Piece> takePiece(Position position);

    bool isEmpty(Position position) const;

    bool isValidPosition(Position position) const;

    bool removePiece(Position position);

    bool movePiece(
        Position from,
        Position to
    );

    bool executeMove(const Move& move);

    bool executeCastling(const Move& move);
};

#endif