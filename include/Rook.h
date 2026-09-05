#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Color color)
        : Piece(color) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;
};

#endif