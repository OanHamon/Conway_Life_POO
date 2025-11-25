#include "Rules.h"

// Conway's Game of Life
CellState* ConwayRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        return (aliveNeighbors == 2 || aliveNeighbors == 3)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
    else {
        return (aliveNeighbors == 3)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
}

// Hardcore Rule
CellState* HardcoreRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        return (aliveNeighbors == 7 || aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
    else {
        return (aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
}

// Low Social Life Rule
CellState* LowSocialLifeRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        return (aliveNeighbors == 1)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
    else {
        return (aliveNeighbors == 1)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
}

// High Life Rule
CellState* HighLifeRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        return (aliveNeighbors == 1 || aliveNeighbors == 2 || aliveNeighbors == 3 ||
            aliveNeighbors == 4 || aliveNeighbors == 5 || aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
    else {
        return (aliveNeighbors == 1 || aliveNeighbors == 2 || aliveNeighbors == 3 ||
            aliveNeighbors == 4 || aliveNeighbors == 5 || aliveNeighbors == 6)
            ? static_cast<CellState*>(new AliveState())
            : static_cast<CellState*>(new DeadState());
    }
}
