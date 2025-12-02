#include "Cell.h"

#pragma region MethodeJeu

void Cell::updateState()
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

#pragma endregion

