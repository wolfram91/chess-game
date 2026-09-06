#include "Pawn.h"
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

    bool twoSquareMove =
        !hasMoved &&
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