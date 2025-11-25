#include "Cell.h"

// AliveState
bool AliveState::isAlive() const { return true; }
bool AliveState::isObstacle() const { return Obstacle; }

// DeadState
bool DeadState::isAlive() const { return false; }
bool DeadState::isObstacle() const { return Obstacle; }

// Cell
Cell::Cell(int _row, int _col, CellState* _state)
    : row(_row), col(_col), currentState(_state), nextState(nullptr) {
}

Cell::~Cell() {
    delete currentState;
    if (nextState) delete nextState;
}

int Cell::getRow() const { return row; }
int Cell::getCol() const { return col; }
CellState* Cell::getCurrentState() const { return currentState; }
bool Cell::isAlive() const { return currentState->isAlive(); }

void Cell::setNextState(CellState* _state) {
    if (nextState != nullptr) {
        delete nextState;
    }
    nextState = _state;
}

void Cell::updateState() {
    if (nextState != nullptr) {
        delete currentState;
        currentState = nextState;
        nextState = nullptr;
    }
}
