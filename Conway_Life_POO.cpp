#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "GameData.h"

using namespace std;
using namespace sf;

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

Grid* grid;



void renderGrid(RenderWindow& window) {

    window.clear();
    RectangleShape visual_cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            Cell* currentCell = grid->getCell(x, y);
            if (currentCell != nullptr && currentCell->isAlive())
            {
                visual_cell.setPosition(x * cellSize, y * cellSize);
                window.draw(visual_cell);
            }
        }
    }
    window.display();
};

int main() {
    srand(time(0));
    Rule* conway = new ConwayRule();

    grid = new Grid(gridWidth, gridHeight, conway);

    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        renderGrid(window);
        grid->computeNextGen();
        sleep(milliseconds(100));
    }
    delete grid;
    return 0;
};