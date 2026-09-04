#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(Color color)
    : Piece(color) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;
};

#endif