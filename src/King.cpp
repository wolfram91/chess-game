#include "King.h"
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