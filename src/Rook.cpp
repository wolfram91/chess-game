#include "Rook.h"
#include "RookState.h"
#include <cstdlib>

bool Rook::isValidMovement(
    Position from,
    Position to
) const {

    if (from.row == to.row &&
        from.col == to.col) {
        return false;
    }

    return (from.row == to.row) ||
           (from.col == to.col);
}

void Rook::onMove() {
    hasMovedFlag = true;
}

bool Rook::hasMoved() const {
    return hasMovedFlag;
}

std::unique_ptr<PieceState> Rook::saveState() const {
    return std::make_unique<RookState>(hasMovedFlag);
}

void Rook::restoreState(
    const PieceState& state
) {
    const RookState& rookState =
        static_cast<const RookState&>(state);

    hasMovedFlag = rookState.hasMoved;
}