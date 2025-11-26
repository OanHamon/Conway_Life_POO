#include "Game.h"
#include "Rule.h"
#include <iostream>
#include <limits>
#include <ctime>

using namespace std;

Game::Game() {}

void Game::run()
{
    int mode = MainMenu();
    int maxIter = 0;

    if (mode == 0) {
        maxIter = askIterations();
        //runConsole(maxIter);
    }
    else {
        maxIter = 100000;
        runGraphical(maxIter);
    }
}

int Game::MainMenu()
{
    cout << R"(
+==================================================+
                  GAME OF LIFE
+==================================================+

Choisissez le mode :
0 - Console
1 - Graphique
)";

    int mode = -1;
    while (!(cin >> mode) || (mode != 0 && mode != 1)) {
        cout << "Erreur. Entrer 0 (console) ou 1 (graphique): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return mode;
}

void Game::resetGrid(Grid*& grid, int gridWidth, int gridHeight)
{
    delete grid;
    Rule* conway = new ConwayRule();
    grid = new Grid(gridWidth, gridHeight, conway);
}

int Game::askIterations()
{
    int maxIter = 0;
    cout << "Execution limitee a combien d'iterations ? ";

    while (!(cin >> maxIter) || maxIter <= 0) {
        cout << "Nombre invalide, recommence : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return maxIter;
}

void Game::runGraphical(int maxIter)
{
    srand(time(0));

    const int cellSize = 10;
    const int gridWidth = 80;
    const int gridHeight = 80;

    Rule* conway = new ConwayRule();
    Grid* grid = new Grid(gridWidth, gridHeight, conway);

    GraphicalDisplay* display = new GraphicalDisplay(
        gridWidth * cellSize,
        gridHeight * cellSize,
        cellSize
    );

    int iterationsDone = 0;
    int currentRuleIndex = 0;

    while (display->isOpen()) {

        display->handleEvents(grid);

        if (display->restartRequested) {

            int ruleIndex = display->getRequestedRuleIndex();
            if (ruleIndex != -1) {
                currentRuleIndex = ruleIndex;
                display->resetRequestedRuleIndex();
            }

            Rule* newRule = nullptr;
            switch (currentRuleIndex) {
            case 0:
                newRule = new ConwayRule();
                cout << "Règle : Conway's Game of Life\n";
                break;
            case 1:
                newRule = new HighLifeRule();
                cout << "Règle : High Life\n";
                break;
            case 2:
                newRule = new DayAndNight();
                cout << "Règle : Day and Night\n";
                break;
            default:
                newRule = new ConwayRule();
            }

            delete grid;
            grid = new Grid(gridWidth, gridHeight, newRule);
            iterationsDone = 0;
            display->setIterationCounter(0);
            display->restartRequested = false;
            display->state = PAUSED;
        }

        if (display->state == RUNNING) {
            grid->computeNextGen();
            iterationsDone++;
            display->setIterationCounter(iterationsDone);
        }
        else if (display->state == STEP) {
            grid->computeNextGen();
            iterationsDone++;
            display->setIterationCounter(iterationsDone);
            display->state = PAUSED;
        }
        else if(display->state == CLEARED)
        {
            grid = new Grid(gridWidth, gridHeight, conway,true);
            iterationsDone = 0;
            display->setIterationCounter(0);
            display->state = PAUSED;
        }

        display->show(grid);

        if (iterationsDone >= maxIter) {
            cout << "Limite d'iterations atteinte (" << maxIter << ").\n";
            break;
        }

        sf::sleep(sf::milliseconds(display->getDelay()));
    }

    delete display;
    delete grid;
}

void Game::runConsole(int _maxIter)
{
    cout << "ererere";
}