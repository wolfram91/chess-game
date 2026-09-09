#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "Board.h"
#include "Move.h"
#include "Pawn.h"

#include <vector>

class MoveValidator {
public:
    static bool isValidMove(
        const Board& board,
        const Move& move
    );

    static bool isSquareAttacked(
        const Board& board,
        Position position,
        Color attackingColor
    );

    static bool isKingInCheck(
        const Board& board,
        Color color
    );

    static bool leavesKingInCheck(
        Board& board,
        const Move& move,
        Color movingColor
    );

    static std::vector<Move> getPseudoLegalMoves(
        const Board& board,
        Position from
    );

    static std::vector<Move> getLegalMoves(
        Board& board,
        Position from
    );

private:
    static bool isPathClear(
        const Board& board,
        Position from,
        Position to
    );

    static bool isValidCastling(
        const Board& board,
        const Move& move
    );

    static Position findKing(
        const Board& board,
        Color color
    );

    static Color oppositeColor(Color color);

    static bool leavesKingInCheck(
        Board& board,
        const Move& move
    );
};

#endif