#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Display.h"
#include "Grid.h"

using namespace std;
using namespace sf;

enum GameState { RUNNING, PAUSED, STEP, CLEARED };

class GraphicalDisplay : public Display {
public:
    GameState state = RUNNING;

    bool patternMode = false;
    int selectedPatternIndex = -1;
    bool restartRequested = false;

    GraphicalDisplay(int _windowWidth, int _windowHeight, int cellSize);
    ~GraphicalDisplay();

    void setIterationCounter(int value);
    int getDelay() const;
    int getRequestedRuleIndex() const;
    void resetRequestedRuleIndex();
    void show(Grid* grid) override;
    void handleEvents(Grid* grid);
    void setDelay(int milliseconds);
    void clear() override;
    bool isOpen() const;

private:
    RenderWindow* window;
    int cellSize;
    int delay;
    int windowWidth;
    int windowHeight;
    vector<sf::RectangleShape*> buttons;
    vector<sf::Text*> labels;
    sf::Font font;
    int iterationCounter;
    sf::Text iterationText;
    int requestedRuleIndex;
    vector<Pattern> patterns;

    void drawGrid(Grid* grid);
    void handleButtonClick(int buttonIndex);

};