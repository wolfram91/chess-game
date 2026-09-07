#ifndef KINGSTATE_H
#define KINGSTATE_H

#include "PieceState.h"

class KingState : public PieceState {
public:
    bool hasMoved;

    KingState(bool hasMoved)
        : hasMoved(hasMoved) {}
};

#endif