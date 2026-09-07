#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
    bool hasMovedFlag;

public:
    Pawn(Color color)
        : Piece(color), hasMovedFlag(false) {}

    bool isValidMovement(
        Position from,
        Position to
    ) const override;

    bool canCapture(
        Position from,
        Position to
    ) const;

    std::unique_ptr<PieceState> saveState() const override;

    void onMove() override;

    void restoreState(
        const PieceState& state
    ) override;

};

#endif