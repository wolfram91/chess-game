#include "King.h"
#include "KingState.h"

#include <cstdlib>

bool King::isValidMovement(
    Position from,
    Position to
) const {

    int rowDifference = std::abs(to.row - from.row);
    int colDifference = std::abs(to.col - from.col);

    if (from.row == to.row &&
        from.col == to.col) {
        return false;
    }

    return rowDifference <= 1 &&
           colDifference <= 1;
}

void King::onMove() {
    hasMovedFlag = true;
}

bool King::hasMoved() const {
    return hasMovedFlag;
}

std::unique_ptr<PieceState> King::saveState() const {
    return std::make_unique<KingState>(hasMovedFlag);
}

void King::restoreState(
    const PieceState& state
) {
    const KingState& kingState =
        static_cast<const KingState&>(state);

    hasMovedFlag = kingState.hasMoved;
}