#include "Rule.h"
#include "Grid.h"

#pragma region Règles


CellState* ConwayRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Survie avec 2 ou 3 voisins
        return (aliveNeighbors == 2 || aliveNeighbors == 3)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
    else {
        // Naissance avec 3 voisins
        return (aliveNeighbors == 3)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
}

CellState* HighLifeRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Survie avec 2 ou 3 voisins
        return (aliveNeighbors == 2 || aliveNeighbors == 3)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
    else {
        // Naissance avec 3 ou 6 voisins
        return (aliveNeighbors == 3 || aliveNeighbors == 6)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
}

CellState* DayAndNightRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Survie avec 3, 4, 6, 7, ou 8 voisins
        return (aliveNeighbors == 3 || aliveNeighbors == 4 ||
            aliveNeighbors == 6 || aliveNeighbors == 7 || aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
    else {
        // Naissance avec 3, 6, 7, ou 8 voisinsz
        return (aliveNeighbors == 3 || aliveNeighbors == 6 ||
            aliveNeighbors == 7 || aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
}

CellState* CoagulationsRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Survie avec 2, 3, 5, 6, 7, ou 8 voisins
        return (aliveNeighbors == 2 || aliveNeighbors == 3 ||
            aliveNeighbors == 5 || aliveNeighbors == 6 ||
            aliveNeighbors == 7 || aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
    else {
        // Naissance avec 3, 7, ou 8 voisins
        return (aliveNeighbors == 3 || aliveNeighbors == 7 || aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
}


#pragma endregion
