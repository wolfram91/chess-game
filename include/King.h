#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(Color color)
    : Piece(color) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;
};

#endif