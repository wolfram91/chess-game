#include "Rook.h"

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