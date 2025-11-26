#include "Cell.h"


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
        delete currentState;
        currentState = nextState;
        nextState = nullptr;
    }
}

void Cell::setNextState(CellState* _state)
{
    if (nextState != nullptr) {
        delete nextState;
    }
    nextState = _state;
}
