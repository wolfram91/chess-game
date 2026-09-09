#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
private:
    bool hasMovedFlag;

public:
    Rook(Color color)
        : Piece(color), hasMovedFlag(false) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;

    void onMove() override;

    bool hasMoved() const;

    std::unique_ptr<PieceState> saveState() const override;

    void restoreState(
        const PieceState& state
    ) override;
};

#endif