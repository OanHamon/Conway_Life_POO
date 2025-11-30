#ifndef GRAPHICAL_DISPLAY_H
#define GRAPHICAL_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Grid.h"
#include "Patern.h"

using namespace sf;

enum windowType {
    FOCUSED,
    MANAGEMENT,
    PATERN,
    SPEED,
    FULL
};

enum GameState {
    RUNNING,
    PAUSED,
    STEP,
    CLEARED
};

enum class ButtonType {
    MANAGEMENT,
    SPEED,
    PATTERN
};

class GraphicalDisplay
{
public:
    // Constructeurs
    GraphicalDisplay(int windowWidth, int windowHeight, int cellSize, windowType type);
    GraphicalDisplay(int gridWidth, int gridHeight, windowType type);
    ~GraphicalDisplay();

    // Méthodes publiques principales
    void show(Grid* grid);
    void handleEvents(Grid* grid);
    bool isOpen() const;
    void clear();

    // Getters/Setters
    int getDelay() const;
    void setDelay(int milliseconds);
    void setIterationCounter(int value);
    int getRequestedRuleIndex() const;
    void resetRequestedRuleIndex();

    // État du jeu
    GameState state = PAUSED;
    bool restartRequested = false;

private:
    // Méthodes d'initialisation
    void initWindowsDimension(windowType type);
    void initWindow();
    void loadResources();
    void initGUI(windowType type);
    void createButtonGroup(const std::vector<std::string>& names,
        int buttonWidth, int buttonHeight, int spacing,
        float startY, int columns, bool horizontal,
        float startX, ButtonType type);

    // Méthodes de dessin
    void drawGrid(Grid* grid) const;
    void drawBorder(Grid* grid) const;
    void drawButtons() const;
    Color getCellColor(const Cell* cell) const;

    // Gestion des événements
    void handleMouseClick(int mouseX, int mouseY, Grid* grid);
    void handleButtonClick(int buttonIndex);
    void handleManagementButton(int buttonIndex);
    void handleSpeedButton(int buttonIndex);
    void handlePatternButton(int patternIndex);
    void placePattern(int mouseX, int mouseY, Grid* grid);
    int getRelativeButtonIndex(int absoluteIndex, ButtonType type) const;

    // Membres privés - Fenêtre et rendu
    RenderWindow* window;
    Font font;
    int windowWidth;
    int windowHeight;
    int cellSize;

    // Membres privés - Interface
    std::vector<RectangleShape*> buttons;
    std::vector<Text*> labels;
    std::vector<ButtonType> buttonTypes;
    Text iterationText;

    // Membres privés - Compteurs de boutons
    int managementButtonsCount;
    int speedButtonsCount;
    int patternButtonsCount;

    // Membres privés - État du jeu
    int delay;
    int iterationCounter;
    int requestedRuleIndex;

    // Membres privés - Patterns
    std::vector<Patern> paterns;
    bool patternMode = false;
    int selectedPatternIndex = -1;
};

#endif // GRAPHICAL_DISPLAY_H