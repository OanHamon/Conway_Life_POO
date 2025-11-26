#pragma once
#include "CellState.h"

class Cell
{
public:
    Cell(int _row, int _col, CellState* _state)
        : row(_row), col(_col), currentState(_state), nextState(nullptr) {
    }

    int getRow() const { return row; }
    int getCol() const { return col; }
    CellState* getCurrentState() const { return currentState; }
    bool isAlive() const { return currentState->isAlive(); }

    void setNextState(CellState* _state);
    void updateState();

private:
    int row;
    int col;
    CellState* currentState;
    CellState* nextState;
};
