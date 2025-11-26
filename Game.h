#pragma once
#include "Grid.h"
#include "GraphicalDisplay.h"

class Game {
public:
    Game();
    void run();
    int MainMenu();
    void resetGrid(Grid*& grid, int gridWidth, int gridHeight);
    int askIterations();
    void runGraphical(int maxIter);
    void runConsole(int _maxIter);
};