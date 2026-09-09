#include "MoveValidator.h"
#include "King.h"
#include "Rook.h"
#include "Knight.h"
#include <cstdlib>

bool MoveValidator::isValidMove(
    const Board& board,
    const Move& move
) {
    if (move.type == MoveType::CASTLING) {
        return isValidCastling(board, move);
    }

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

bool MoveValidator::isValidCastling(
    const Board& board,
    const Move& move
) {
    Position kingPosition = move.from;
    Position destination = move.to;

    Piece* piece = board.getPiece(kingPosition);

    King* king = dynamic_cast<King*>(piece);

    if (king == nullptr) {
        return false;
    }

    if (king->hasMoved()) {
        return false;
    }

    int row = kingPosition.row;
    int direction;

    if (destination.col > kingPosition.col) {
        direction = 1;
    } else {
        direction = -1;
    }

    Position rookPosition{
        row,
        direction == 1 ? 7 : 0
    };

    Piece* rookPiece = board.getPiece(rookPosition);

    Rook* rook = dynamic_cast<Rook*>(rookPiece);

    if (rook == nullptr) {
        return false;
    }

    if (rook->getColor() != king->getColor()) {
        return false;
    }

    if (rook->hasMoved()) {
        return false;
    }

    Position betweenOne{
        row,
        kingPosition.col + direction
    };

    Position betweenTwo{
        row,
        kingPosition.col + 2 * direction
    };

    if (!board.isEmpty(betweenOne) ||
        !board.isEmpty(betweenTwo)) {
        return false;
    }

    Color attackingColor =
        oppositeColor(king->getColor());

    if (isSquareAttacked(
            board,
            kingPosition,
            attackingColor)) {
        return false;
    }

    if (isSquareAttacked(
            board,
            betweenOne,
            attackingColor)) {
        return false;
    }

    if (isSquareAttacked(
            board,
            betweenTwo,
            attackingColor)) {
        return false;
    }

    return true;
}

bool MoveValidator::isSquareAttacked(
    const Board& board,
    Position position,
    Color attackingColor
) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            Position from{row, col};

            Piece* piece = board.getPiece(from);

            if (piece == nullptr) {
                continue;
            }

            if (piece->getColor() != attackingColor) {
                continue;
            }

            Pawn* pawn = dynamic_cast<Pawn*>(piece);

            if (pawn != nullptr) {
                if (pawn->canCapture(from, position)) {
                    return true;
                }

                continue;
            }

            if (piece->canJump()) {
                if (piece->isValidMovement(from, position)) {
                    return true;
                }

                continue;
            }

            if (piece->isValidMovement(from, position)) {
                if (isPathClear(board, from, position)) {
                    return true;
                }
            }

            King* king = dynamic_cast<King*>(piece);

            if (king != nullptr) {
                if (king->isValidMovement(from, position)) {
                    return true;
                }

                continue;
            }
        }
    }

    return false;
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

Position MoveValidator::findKing(
    const Board& board,
    Color color
) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            Position position{row, col};

            Piece* piece =
                board.getPiece(position);

            if (piece == nullptr) {
                continue;
            }

            if (piece->getColor() != color) {
                continue;
            }

            King* king =
                dynamic_cast<King*>(piece);

            if (king != nullptr) {
                return position;
            }
        }
    }

    return Position{-1, -1};
}

bool MoveValidator::isKingInCheck(
    const Board& board,
    Color color
) {
    Position kingPosition =
        findKing(board, color);

    if (!board.isValidPosition(kingPosition)) {
        return false;
    }

    Color attackingColor = oppositeColor(color);

    return isSquareAttacked(
        board,
        kingPosition,
        attackingColor
    );
}

Color MoveValidator::oppositeColor(Color color) {
    if (color == Color::WHITE) {
        return Color::BLACK;
    }

    return Color::WHITE;
}