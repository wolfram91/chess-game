#ifndef PAWNSTATE_H
#define PAWNSTATE_H

#include "PieceState.h"

class PawnState : public PieceState {
public:
    bool hasMoved;

    PawnState(bool hasMoved)
        : hasMoved(hasMoved) {}
};

#endif