#include "MoveValidator.h"
#include "King.h"
#include "Rook.h"
#include "Knight.h"

#include <iostream>
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

std::vector<Move> MoveValidator::getPseudoLegalMoves(
    const Board& board,
    Position from
) {
    std::vector<Move> moves;

    Piece* piece = board.getPiece(from);

    if (piece == nullptr) {
        return moves;
    }

    // Handle Pawn
    Pawn* pawn = dynamic_cast<Pawn*>(piece);

    if (pawn != nullptr) {

        int direction =
            pawn->getColor() == Color::WHITE ? 1 : -1;

        // One-square forward move
        Position oneStep{
            from.row + direction,
            from.col
        };

        if (board.isValidPosition(oneStep) &&
            board.isEmpty(oneStep)) {

            moves.push_back(
                Move{
                    from,
                    oneStep,
                    MoveType::NORMAL
                }
            );

            // Two-square forward move
            Position twoStep{
                from.row + 2 * direction,
                from.col
            };

            if (board.isValidPosition(twoStep) &&
                pawn->isValidMovement(from, twoStep) &&
                board.isEmpty(twoStep)) {

                moves.push_back(
                    Move{
                        from,
                        twoStep,
                        MoveType::NORMAL
                    }
                );
            }
        }

        // Diagonal captures
        int captureColumns[] = {-1, 1};

        for (int columnDirection : captureColumns) {

            Position capturePosition{
                from.row + direction,
                from.col + columnDirection
            };

            if (!board.isValidPosition(capturePosition)) {
                continue;
            }

            Piece* destinationPiece =
                board.getPiece(capturePosition);

            if (destinationPiece != nullptr &&
                destinationPiece->getColor() !=
                    pawn->getColor() &&
                pawn->canCapture(from, capturePosition)) {

                moves.push_back(
                    Move{
                        from,
                        capturePosition,
                        MoveType::NORMAL
                    }
                );
            }
        }

        return moves;
    }

    // Handle King
    King* king = dynamic_cast<King*>(piece);

    if (king != nullptr) {

        for (int rowDirection = -1;
            rowDirection <= 1;
            rowDirection++) {

            for (int colDirection = -1;
                colDirection <= 1;
                colDirection++) {

                if (rowDirection == 0 &&
                    colDirection == 0) {
                    continue;
                }

                Position to{
                    from.row + rowDirection,
                    from.col + colDirection
                };

                if (!board.isValidPosition(to)) {
                    continue;
                }

                Piece* destinationPiece =
                    board.getPiece(to);

                if (destinationPiece != nullptr &&
                    destinationPiece->getColor() ==
                        king->getColor()) {
                    continue;
                }

                moves.push_back(
                    Move{
                        from,
                        to,
                        MoveType::NORMAL
                    }
                );
            }
        }

        // Generate castling moves
        Position kingSideDestination{
            from.row,
            from.col + 2
        };

        Move kingSideCastle{
            from,
            kingSideDestination,
            MoveType::CASTLING
        };

        if (board.isValidPosition(kingSideDestination) &&
            isValidCastling(board, kingSideCastle)) {

            moves.push_back(kingSideCastle);
        }

        Position queenSideDestination{
            from.row,
            from.col - 2
        };

        Move queenSideCastle{
            from,
            queenSideDestination,
            MoveType::CASTLING
        };

        if (board.isValidPosition(queenSideDestination) &&
            isValidCastling(board, queenSideCastle)) {

            moves.push_back(queenSideCastle);
        }

        return moves;
    }

    // Handle jumping pieces such as Knight
    if (piece->canJump()) {

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {

                Position to{row, col};

                if (to == from) {
                    continue;
                }

                Piece* destinationPiece =
                    board.getPiece(to);

                if (destinationPiece != nullptr &&
                    destinationPiece->getColor() ==
                        piece->getColor()) {
                    continue;
                }

                if (piece->isValidMovement(from, to)) {
                    moves.push_back(
                        Move{
                            from,
                            to,
                            MoveType::NORMAL
                        }
                    );
                }
            }
        }

        return moves;
    }

    // Handle sliding pieces
    int rowDirections[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int colDirections[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int direction = 0; direction < 8; direction++) {

        Position current{
            from.row + rowDirections[direction],
            from.col + colDirections[direction]
        };

        while (board.isValidPosition(current)) {

            Piece* destinationPiece =
                board.getPiece(current);

            if (destinationPiece == nullptr) {

                if (piece->isValidMovement(
                        from,
                        current)) {

                    moves.push_back(
                        Move{
                            from,
                            current,
                            MoveType::NORMAL
                        }
                    );
                }

            } else {

                if (destinationPiece->getColor() !=
                    piece->getColor()) {

                    if (piece->isValidMovement(
                            from,
                            current)) {

                        moves.push_back(
                            Move{
                                from,
                                current,
                                MoveType::NORMAL
                            }
                        );
                    }
                }

                break;
            }

            current.row += rowDirections[direction];
            current.col += colDirections[direction];
        }
    }

    return moves;
}

bool MoveValidator::leavesKingInCheck(
    Board& board,
    const Move& move
) {
    Piece* piece = board.getPiece(move.from);

    if (piece == nullptr) {
        return false;
    }

    Color movingColor = piece->getColor();

    // Save the moving piece's internal state
    std::unique_ptr<PieceState> previousState =
        piece->saveState();

    // Temporarily remove the captured piece
    std::unique_ptr<Piece> capturedPiece =
        board.takePiece(move.to);

    // Temporarily move the piece
    std::unique_ptr<Piece> movedPiece =
        board.takePiece(move.from);

    board.placePiece(
        std::move(movedPiece),
        move.to
    );

    // Apply state change caused by moving
    Piece* movedPiecePointer =
        board.getPiece(move.to);

    if (movedPiecePointer != nullptr) {
        movedPiecePointer->onMove();
    }

    // Check whether our King is now attacked
    bool inCheck =
        isKingInCheck(board, movingColor);

    // Restore moved piece
    std::unique_ptr<Piece> restoredPiece =
        board.takePiece(move.to);

    board.placePiece(
        std::move(restoredPiece),
        move.from
    );

    // Restore the piece's previous state
    Piece* restoredPiecePointer =
        board.getPiece(move.from);

    if (restoredPiecePointer != nullptr &&
        previousState != nullptr) {

        restoredPiecePointer->restoreState(
            *previousState
        );
    }

    // Restore captured piece
    if (capturedPiece != nullptr) {
        board.placePiece(
            std::move(capturedPiece),
            move.to
        );
    }

    return inCheck;
}

std::vector<Move> MoveValidator::getLegalMoves(
    Board& board,
    Position from
) {
    std::vector<Move> legalMoves;

    Piece* piece = board.getPiece(from);

    if (piece == nullptr) {
        return legalMoves;
    }

    std::vector<Move> pseudoLegalMoves =
        getPseudoLegalMoves(board, from);

    for (const Move& move : pseudoLegalMoves) {

        if (!leavesKingInCheck(board, move)) {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}