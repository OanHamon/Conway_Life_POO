#pragma once
#include "Rules.h"
#include "Display.h"

enum GameState { RUNNING, PAUSED, STEP };

class Game {
public:
    Game();
    void run();

private:
    int MainMenu();
    int askIterations();
    void resetGrid(Grid*& grid, int gridWidth, int gridHeight);
    void runGraphical(int maxIter);
    void runConsole(int maxIter);
};
