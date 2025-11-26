#include "Cell.h"

// AliveState
bool AliveState::isAlive() const { return true; }
bool AliveState::isObstacle() const { return Obstacle; }

void Cell::updateState()
{
    if (nextState != nullptr) {
        delete currentState;
        currentState = nextState;
        nextState = nullptr;
}

Cell::~Cell() {
    delete currentState;
    if (nextState) delete nextState;
}

void Cell::setNextState(CellState* _state)
{
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
