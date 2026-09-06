#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include "Color.h"
#include "Move.h"

class GameState {
private:
    Board board;
    Color currentTurn;

public:
    GameState();

    Board& getBoard();
    const Board& getBoard() const;

    Color getCurrentTurn() const;

    void switchTurn();

    bool makeMove(const Move& move);
};

#endif