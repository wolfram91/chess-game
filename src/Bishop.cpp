#include "Bishop.h"
#include <cstdlib>

bool Bishop::isValidMovement(
    Position from,
    Position to
) const {

    int rowDifference = std::abs(to.row - from.row);
    int colDifference = std::abs(to.col - from.col);

    if (from.row == to.row &&
        from.col == to.col) {
        return false;
    }

    return rowDifference == colDifference;
}