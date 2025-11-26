#pragma once
#include "Grid.h"
#include "GraphicalDisplay.h"

enum GameState { RUNNING, PAUSED, STEP };

class Game {
public:
    Game();
    void run();

private:
    int MainMenu();
    void resetGrid(Grid*& grid, int gridWidth, int gridHeight);
    int askIterations();
    void resetGrid(Grid*& grid, int gridWidth, int gridHeight);
    void runGraphical(int maxIter);
    void runConsole(int _maxIter);
};
