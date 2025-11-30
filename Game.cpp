#include "Game.h"
#include "Rule.h"
#include "ConsoleDisplay.h"
#include "GraphicalDisplay.h"
#include "FileManager.h"
#include <iostream>
#include <string>
#include <limits>
#include <ctime>

using namespace std;

Game::Game() {}

void Game::run()
{
    int mode = MainMenu();

    if (mode == 0) {
        runConsole();
    }
    else {
        int maxIter = 100000;
        runGraphical(maxIter);
    }
}

int Game::MainMenu()
{
    std::cout << R"(
+==================================================+
                  GAME OF LIFE
+==================================================+

Choisissez le mode :
0 - Console
1 - Graphique
)";

    int mode = -1;
    while (!(cin >> mode) || (mode != 0 && mode != 1)) {
        std::cout << "Erreur. Entrer 0 (console) ou 1 (graphique): ";
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

void Game::runGraphical(int maxIter)
{

    const int cellSize = 8;
    const int gridWidth = 100;
    const int gridHeight = 100;



    int answer;
    std::cout << "Voulez Entrez une grille ou aléatoire ?" << endl << "Réponse (0-1) : ";
    cin >> answer;


    Grid* grid;
    Rule* conway = new ConwayRule();
    GraphicalDisplay* display;

    if(answer == 1)
    {
        grid = new Grid(gridWidth, gridHeight, conway);

        display = new GraphicalDisplay(
            gridWidth * cellSize,
            gridHeight * cellSize,
            cellSize, PATERN
        );
    
    }
    else 
    {
        Display* tempDisplay = new ConsoleDisplay();
        string path_in = tempDisplay->askPath();
        delete tempDisplay;

        FileManager f_in(path_in);

        vector<vector<int>> gridInt_in = f_in.getGrid();

        int gridRows = gridInt_in.size();        // Nombre de lignes (hauteur)
        int gridCols = gridInt_in[0].size();

        display = new GraphicalDisplay(
            gridCols,
            gridRows, FULL
        );

        string path_out = path_in.substr(0, path_in.length() - 4) + "_out/generation0.txt";

        FileManager* f_out = new FileManager(path_out);
        f_out->saveGrid(gridInt_in);


         grid = new Grid(gridRows, gridCols, conway, gridInt_in);
    
    }






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
                std::cout << "Regle : Conway's Game of Life\n";
                break;
            case 1:
                newRule = new DayAndNightRule();
                std::cout << "Regle : High Life\n";
                break;
            case 2:
                newRule = new CoagulationsRule();
                std::cout << "Regle : Day and Night\n";
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
            vector<vector<int>> prevGridInt = grid->getGridInt();
            grid->computeNextGen();
            iterationsDone++;
            display->setIterationCounter(iterationsDone);
            if (grid->getGridInt() == prevGridInt)
            {
                cout << "Etat stable fin du jeux\n";
                break;
            }
        }
        else if (display->state == STEP) {
            vector<vector<int>> prevGridInt = grid->getGridInt();
            grid->computeNextGen();
            iterationsDone++;
            display->setIterationCounter(iterationsDone);
            display->state = PAUSED;
            if (grid->getGridInt() == prevGridInt)
            {
                cout << "Etat stable fin du jeux\n";
                break;
            }
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
            std::cout << "Limite d'iterations atteinte (" << maxIter << ").\n";
            break;
        }

        sleep(milliseconds(display->getDelay()));
    }

    delete display;
    delete grid;
}

void Game::runConsole()
{
    ConsoleDisplay* display = new ConsoleDisplay();

    int maxIter = display->askIterations();
    int n_iter = 0;

    string path_in = display->askPath();

    FileManager f_in(path_in);

    vector<vector<int>> gridInt_in = f_in.getGrid();

    string path_out = path_in.substr(0, path_in.length() - 4) + "_out/generationInitiale.txt";
    FileManager* f_out = new FileManager(path_out);
    f_out->saveGrid(gridInt_in);

    Rule* rule = new ConwayRule();
    Grid* grid = new Grid(gridInt_in.size(), gridInt_in[0].size(), rule, gridInt_in);

    while (n_iter<maxIter) {
        display->clear();
        display->show(grid);

        path_out = path_in.substr(0, path_in.length() - 4) +  "_out/generation" + to_string(n_iter + 1) + ".txt";
        f_out = new FileManager(path_out);

        vector<vector<int>> prevGridInt = grid->getGridInt();
        grid->computeNextGen();
        if (grid->getGridInt() == prevGridInt)
        {
            cout << "Etat stable fin du jeux\n";
            break;
        }

        vector<vector<int>> gridInt_out = grid->getGridInt();

        f_out->saveGrid(gridInt_out);

        n_iter++;
        sleep(milliseconds(100));
    }
}
