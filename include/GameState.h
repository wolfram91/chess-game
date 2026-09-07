#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "Board.h"
#include "Color.h"
#include "Move.h"
#include "MoveRecord.h"

class GameState {
private:
    Board board;
    Color currentTurn;

    std::vector<MoveRecord> moveHistory;

public:
    GameState();

    Board& getBoard();
    const Board& getBoard() const;

    Color getCurrentTurn() const;

    const std::vector<MoveRecord>& getMoveHistory() const;

    void switchTurn();

    bool makeMove(const Move& move);
    bool undoMove();
};

#endif