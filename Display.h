#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"
#include "Game.h"

using namespace std;
using namespace sf;

class Display {
public:
    virtual ~Display() {}
    virtual void show(Grid* grid) = 0;
    virtual void clear() = 0;
};

class ConsoleDisplay : public Display {
public:
    void show(Grid* grid) override {};
    void clear() override {};
};

class GraphicalDisplay : public Display {
public:
    GraphicalDisplay(int _windowWidth, int _windowHeight, int cellSize);
    ~GraphicalDisplay();

    void show(Grid* grid) override;
    void clear() override;
    void handleEvents();
    bool isOpen() const;

    void setIterationCounter(int value);
    void setDelay(int milliseconds);
    int getDelay() const;
    int getRequestedRuleIndex() const;
    void resetRequestedRuleIndex();

    GameState state;
    bool restartRequested = false;

private:
    RenderWindow* window;
    int cellSize;
    int delay;
    int windowWidth;
    int windowHeight;
    vector<sf::RectangleShape*> buttons;
    vector<sf::Text*> labels;
    sf::Font font;

    int iterationCounter = 0;
    sf::Text iterationText;
    int requestedRuleIndex = -1;

    void drawGrid(Grid* grid);
};