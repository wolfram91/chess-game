#ifndef MOVERECORD_H
#define MOVERECORD_H

#include <memory>

#include "Move.h"
#include "Piece.h"
#include "PieceState.h"

struct MoveRecord {
    Move move;
    std::unique_ptr<Piece> capturedPiece;
    std::unique_ptr<PieceState> previousState;
};

#endif