#pragma once
#include "Grid.h"
#include "GraphicalDisplay.h"

enum GameState { RUNNING, PAUSED, STEP };

class Game {
public:
    Game();
    void run();
    int MainMenu();
    void resetGrid(Grid*& grid, int gridWidth, int gridHeight);
    int askIterations();
    void resetGrid(Grid*& grid, int gridWidth, int gridHeight);
    int askIterations();
    void runGraphical(int maxIter);
    void runConsole(int _maxIter);
};
