#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
private:
    bool hasMovedFlag;

public:
    King(Color color)
        : Piece(color), hasMovedFlag(false) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;

    void onMove() override;

    std::unique_ptr<PieceState> saveState() const override;

    void restoreState(
        const PieceState& state
    ) override;
};

#endif