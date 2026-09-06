#include "MoveValidator.h"
#include <cstdlib>

bool MoveValidator::isValidMove(
    const Board& board,
    const Move& move
) {
    Position from = move.from;
    Position to = move.to;

    Piece* piece = board.getPiece(from);

    if (piece == nullptr) {
        return false;
    }

    Piece* destinationPiece = board.getPiece(to);

    // Pawn has special movement rules.
    Pawn* pawn = dynamic_cast<Pawn*>(piece);

    if (pawn != nullptr) {

        // Diagonal movement is only allowed when capturing.
        if (pawn->canCapture(from, to)) {

            if (destinationPiece == nullptr) {
                return false;
            }

            if (destinationPiece->getColor() ==
                piece->getColor()) {
                return false;
            }

            return true;
        }

        // Normal pawn movement.
        if (!pawn->isValidMovement(from, to)) {
            return false;
        }

        // Pawns cannot move forward onto an occupied square.
        if (destinationPiece != nullptr) {
            return false;
        }

        // A two-square pawn move must have a clear path.
        if (std::abs(to.row - from.row) == 2) {
            Position middle{
                (from.row + to.row) / 2,
                from.col
            };

            if (!board.isEmpty(middle)) {
                return false;
            }
        }

        return true;
    }

    // Normal pieces.
    if (!piece->isValidMovement(from, to)) {
        return false;
    }

    // Cannot capture your own piece.
    if (destinationPiece != nullptr &&
        destinationPiece->getColor() == piece->getColor()) {
        return false;
    }

    // Jumping pieces don't need path checking.
    if (piece->canJump()) {
        return true;
    }

    return isPathClear(board, from, to);
}

bool MoveValidator::isPathClear(
    const Board& board,
    Position from,
    Position to
) {
    int rowStep = 0;
    int colStep = 0;

    if (to.row > from.row) {
        rowStep = 1;
    } else if (to.row < from.row) {
        rowStep = -1;
    }

    if (to.col > from.col) {
        colStep = 1;
    } else if (to.col < from.col) {
        colStep = -1;
    }

    Position current{
        from.row + rowStep,
        from.col + colStep
    };

    if (current == to) {
        return true;
    }

    while (!(current == to)) {

        if (!board.isEmpty(current)) {
            return false;
        }

        current.row += rowStep;
        current.col += colStep;
    }

    return true;
}