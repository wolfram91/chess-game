#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece{
public:
    Queen (Color color) :
        Piece(color){}
    
    bool isValidMovement(
        Position from,
        Position to
    )const override;
};

#endif