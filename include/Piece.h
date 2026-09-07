#ifndef PIECE_H
#define PIECE_H

#include <memory>

#include "PieceState.h"
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

    virtual void onMove() {}

    virtual std::unique_ptr<PieceState> saveState() const {
    return nullptr;
    }

    virtual void restoreState(
        const PieceState& state
    ) {}

    Color getColor() const {
        return color;
    }

    virtual ~Piece() = default;
};

#endif