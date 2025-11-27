#include "Rule.h"
#include "Grid.h"

// 1) Conway's Life (B3/S23)
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

// 2) HighLife (B36/S23)
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

CellState* SeedsRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Aucune survie (S0 = survie avec 0 voisins, impossible)
        return new DeadState(isObstacle);
    }
    else {
        // Naissance avec 2 voisins
        return (aliveNeighbors == 2)
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
        // Naissance avec 3, 6, 7, ou 8 voisins
        return (aliveNeighbors == 3 || aliveNeighbors == 6 ||
            aliveNeighbors == 7 || aliveNeighbors == 8)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
}

CellState* TectonicRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Survie avec 1, 3, 5, ou 7 voisins
        return (aliveNeighbors == 1 || aliveNeighbors == 3 ||
            aliveNeighbors == 5 || aliveNeighbors == 7)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
    else {
        // Naissance avec 2 voisins
        return (aliveNeighbors == 2)
            ? static_cast<CellState*>(new AliveState(isObstacle))
            : static_cast<CellState*>(new DeadState(isObstacle));
    }
}



CellState* MazeRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Survie avec 1, 2, 3, 4, ou 5 voisins
        return (aliveNeighbors >= 1 && aliveNeighbors <= 5)
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

CellState* CoralRule::computeNextState(Cell* cell, Grid* grid) {
    bool isCurrentlyAlive = cell->isAlive();
    bool isObstacle = cell->getCurrentState()->isObstacle();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        // Survie avec 4, 5, 6, 7, ou 8 voisins
        return (aliveNeighbors >= 4 && aliveNeighbors <= 8)
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