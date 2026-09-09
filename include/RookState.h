#ifndef ROOKSTATE_H
#define ROOKSTATE_H

#include "PieceState.h"

class RookState : public PieceState {
public:
    bool hasMoved;

    RookState(bool hasMoved)
        : hasMoved(hasMoved) {}
};

#endif