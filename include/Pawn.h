#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
    bool hasMoved;

public:
    Pawn(Color color)
    : Piece(color), hasMoved(false) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;

    bool canCapture(
        Position from,
        Position to) const;
};

#endif