#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "Board.h"
#include "Move.h"
#include "Pawn.h"

class MoveValidator {
public:
    static bool isValidMove(
        const Board& board,
        const Move& move
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
};

#endif