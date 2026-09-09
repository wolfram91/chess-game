#include "Pawn.h"
#include "PawnState.h"

#include <cstdlib>

bool Pawn::isValidMovement(
    Position from,
    Position to
) const {

    int direction;

    if (color == Color::WHITE) {
        direction = 1;
    } else {
        direction = -1;
    }

    bool oneSquareMove =
        to.row == from.row + direction &&
        to.col == from.col;

    bool isStartingRank =
        (color == Color::WHITE && from.row == 1) ||
        (color == Color::BLACK && from.row == 6);

    bool twoSquareMove =
        !hasMovedFlag &&
        isStartingRank &&
        to.col == from.col &&
        to.row == from.row + 2 * direction;

    return oneSquareMove || twoSquareMove;
}

bool Pawn::canCapture(
    Position from,
    Position to
) const {

    int direction;

    if (color == Color::WHITE) {
        direction = 1;
    } else {
        direction = -1;
    }

    int rowDifference = to.row - from.row;
    int colDifference = std::abs(to.col - from.col);

    return rowDifference == direction &&
           colDifference == 1;
}

void Pawn::onMove() {
    hasMovedFlag = true;
}

std::unique_ptr<PieceState> Pawn::saveState() const {
    return std::make_unique<PawnState>(hasMovedFlag);
}

void Pawn::restoreState(
    const PieceState& state
) {
    const PawnState& pawnState =
        static_cast<const PawnState&>(state);

    hasMovedFlag = pawnState.hasMoved;
}