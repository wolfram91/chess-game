#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include "MoveType.h"

struct Move {
    Position from;
    Position to;
    MoveType type;
};

#endif