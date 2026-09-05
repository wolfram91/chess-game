#include "Queen.h"
#include <cstdlib>

bool Queen::isValidMovement(
    Position from,
    Position to
) const {

    int rowDifference = std::abs(to.row - from.row);
    int colDifference = std::abs(to.col - from.col);

    if (from.row == to.row &&
        from.col == to.col) {
        return false;
    }

    return (from.row == to.row) ||
           (from.col == to.col) ||
           (rowDifference == colDifference);
}