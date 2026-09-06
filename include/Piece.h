#ifndef PIECE_H
#define PIECE_H

#include "Color.h"
#include "Position.h"

class Piece {
protected:
    Color color;

public:
    Piece(Color color)
        : color(color) {}

    virtual bool isValidMovement(
        Position from,
        Position to
    ) const = 0;

    virtual bool canJump() const {
        return false;
    }

    Color getColor() const {
        return color;
    }

    virtual ~Piece() = default;
};

#endif