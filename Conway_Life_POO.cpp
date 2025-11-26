#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "GameLoop.h"

using namespace std;
using namespace sf;


Grid* grid;


//int main() {
//    Game game;
//    game.MainMenu();
//    srand(time(0));
//
//    Rule* conway = new ConwayRule();
//    Grid* grid = new Grid(gridWidth, gridHeight, conway);
//
//    GraphicalDisplay* display = new GraphicalDisplay( gridWidth * cellSize,gridHeight * cellSize,cellSize );

//    while (display->isOpen()) {
//        display->handleEvents();
//
//        display->show(grid);
//
//        grid->computeNextGen();
//
//        sleep(milliseconds(display->getDelay()));
//    }
//
//    // Nettoyage
//    delete display;
//    delete grid;
//
//    return 0;
//}

int main() {
    Game game;
    game.run();
    return 0;
}

