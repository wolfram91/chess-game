#include "Knight.h"
#include <cstdlib>

bool Knight::isValidMovement(
    Position from,
    Position to
) const {

    int rowDifference = std::abs(to.row - from.row);
    int colDifference = std::abs(to.col - from.col);

    return (rowDifference == 2 && colDifference == 1) ||
           (rowDifference == 1 && colDifference == 2);
}