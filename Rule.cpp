#include "Rule.h"
#include "Grid.h"

CellState* ConwayRule::computeNextState(Cell* cell, Grid* grid)
{
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        if (aliveNeighbors == 2 || aliveNeighbors == 3) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
    else {
        if (aliveNeighbors == 3) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
}

CellState* HardcoreRule::computeNextState(Cell* cell, Grid* grid)
{
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        if (aliveNeighbors == 7 || aliveNeighbors == 8) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
    else {
        if (aliveNeighbors == 8) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
}

CellState* LowSocialLifeRule::computeNextState(Cell* cell, Grid* grid)
{
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        if (aliveNeighbors == 1) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
    else {
        if (aliveNeighbors == 1) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
}

CellState* HighLifeRule::computeNextState(Cell* cell, Grid* grid)
{
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        if (aliveNeighbors == 1 || aliveNeighbors == 2 || aliveNeighbors == 3 ||
            aliveNeighbors == 4 || aliveNeighbors == 5 || aliveNeighbors == 8) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
    else {
        if (aliveNeighbors == 1 || aliveNeighbors == 2 || aliveNeighbors == 3 ||
            aliveNeighbors == 4 || aliveNeighbors == 5 || aliveNeighbors == 6) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
}

CellState* DayAndNight::computeNextState(Cell* cell, Grid* grid)
{
    bool isCurrentlyAlive = cell->isAlive();
    int aliveNeighbors = grid->countAliveNeighbors(cell);

    if (isCurrentlyAlive) {
        if (aliveNeighbors == 3 || aliveNeighbors == 4 || aliveNeighbors == 6 ||
            aliveNeighbors == 7 || aliveNeighbors == 8) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
    else {
        if (aliveNeighbors == 3 || aliveNeighbors == 6 ||
            aliveNeighbors == 7 || aliveNeighbors == 8) {
            return new AliveState();
        }
        else {
            return new DeadState();
        }
    }
}