#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Color color)
        : Piece(color) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;
};

#endif