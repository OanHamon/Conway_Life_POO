#include "GraphicalDisplay.h"
#include <iostream>

GraphicalDisplay::GraphicalDisplay(int _windowWidth, int _windowHeight, int cellSize)
    : cellSize(cellSize), delay(100), windowWidth(_windowWidth), windowHeight(_windowHeight),
    iterationCounter(0), requestedRuleIndex(-1)
{
    window = new RenderWindow(VideoMode(windowWidth + 200, windowHeight + 200), "Game of Life");
    window->setFramerateLimit(60);

    if (!font.loadFromFile(R"(Fonts\NotoSans.ttf)")) {
        // gestion d'erreur
    }

#pragma region Bouton de Gestion
    int buttonHeight = 60;
    int buttonWidth = 180;
    int spacing = 20;
    vector<string> names = { "Pause", "Next", "Clear", "Rule1", "Rule2", "Rule3" };

    for (int i = 0; i < 6; i++) {
        sf::RectangleShape* button = new sf::RectangleShape();
        button->setSize(sf::Vector2f(buttonWidth, buttonHeight));
        button->setFillColor(sf::Color(100, 100, 200));

        int row = i / 3;
        int col = i % 3;
        float x = spacing + col * (buttonWidth + spacing);
        float y = windowHeight + 20.f + row * (buttonHeight + spacing);

        button->setPosition(x, y);
        buttons.push_back(button);

        sf::Text* label = new sf::Text();
        label->setFont(font);
        label->setString(names[i]);
        label->setCharacterSize(20);
        label->setFillColor(sf::Color::White);

        sf::FloatRect textBounds = label->getLocalBounds();
        label->setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        label->setPosition(x + buttonWidth / 2.0f, y + buttonHeight / 2.0f);
        labels.push_back(label);
    }
#pragma endregion

#pragma region Bouton de Vitesse
    int speedButtonHeight = 40;
    int speedButtonWidth = 120;
    vector<string> speeds = { "1", "20", "50", "100" };

    for (int i = 0; i < 4; i++) {
        sf::RectangleShape* button = new sf::RectangleShape();
        button->setSize(sf::Vector2f(speedButtonWidth, speedButtonHeight));
        button->setFillColor(sf::Color(100, 100, 200));

        int row = i / 2;
        int col = i % 2;
        float x = 20 + (3 * (buttonWidth + 20)) + col * (speedButtonWidth + spacing);
        float y = 50 + windowHeight + 20.f + row * (speedButtonHeight + spacing);

        button->setPosition(x, y);
        buttons.push_back(button);

        sf::Text* label = new sf::Text();
        label->setFont(font);
        label->setString(speeds[i]);
        label->setCharacterSize(20);
        label->setFillColor(sf::Color::White);

        sf::FloatRect textBounds = label->getLocalBounds();
        label->setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        label->setPosition(x + speedButtonWidth / 2.0f, y + speedButtonHeight / 2.0f);
        labels.push_back(label);
    }
#pragma endregion

#pragma region Bouton de Paternes

    patterns = PatternLibrary::getAllPatterns();

    int patButtonHeight = 100;
    int patButtonWidth = 100;
    //vector<string> paterne = { "Paterne 1", "Paterne 2","Paterne 3","Paterne 4","Paterne 5","Paterne 6" };

    for (int i = 0; i < 6; i++) {
        sf::RectangleShape* button = new sf::RectangleShape();
        button->setSize(sf::Vector2f(patButtonWidth, patButtonHeight));
        button->setFillColor(sf::Color(100, 100, 200));

        float x = windowWidth + 40;
        float y = 50 + i * (patButtonHeight + spacing);

        button->setPosition(x, y);
        buttons.push_back(button);

        sf::Text* label = new sf::Text();
        label->setFont(font);
        label->setString(patterns[i].name);
        label->setCharacterSize(20);
        label->setFillColor(sf::Color::White);

        sf::FloatRect textBounds = label->getLocalBounds();
        label->setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        label->setPosition(x + patButtonWidth / 2.0f, y + patButtonHeight / 2.0f);
        labels.push_back(label);
    }
#pragma endregion

    iterationText.setFont(font);
    iterationText.setCharacterSize(22);
    iterationText.setFillColor(sf::Color::White);
    iterationText.setString("Iterations : 0");
    iterationText.setPosition(20 + (3 * (buttonWidth + 20)), windowHeight + 20);
}

GraphicalDisplay::~GraphicalDisplay()
{
    for (auto button : buttons) {
        delete button;
    }
    for (auto label : labels) {
        delete label;
    }
    delete window;
}

void GraphicalDisplay::setIterationCounter(int value)
{
    iterationCounter = value;
    iterationText.setString("Iterations : " + std::to_string(value));
}

int GraphicalDisplay::getDelay() const
{
    return delay;
}

int GraphicalDisplay::getRequestedRuleIndex() const
{
    return requestedRuleIndex;
}

void GraphicalDisplay::resetRequestedRuleIndex()
{
    requestedRuleIndex = -1;
}

void GraphicalDisplay::show(Grid* grid)
{
    clear();
    drawGrid(grid);

    float width = grid->getRows() * cellSize;
    float height = grid->getCols() * cellSize;

    sf::RectangleShape border(sf::Vector2f(width, height));
    border.setPosition(0, 0);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(5.f);
    border.setOutlineColor(sf::Color::White);
    window->draw(border);

    for (int i = 0; i < buttons.size(); i++) {
        if (patternMode && i >= 10 && i - 10 == selectedPatternIndex) {
            buttons[i]->setFillColor(sf::Color(150, 255, 150));
        }
        else if (i >= 10) {
            buttons[i]->setFillColor(sf::Color(100, 100, 200));
        }
        window->draw(*buttons[i]);
        window->draw(*labels[i]);
    }
    window->draw(iterationText);

    window->display();
}



void GraphicalDisplay::setDelay(int milliseconds)
{
    delay = milliseconds;
}

void GraphicalDisplay::clear()
{
    window->clear(Color(20, 20, 20));
}

bool GraphicalDisplay::isOpen() const
{
    return window->isOpen();
}

void GraphicalDisplay::drawGrid(Grid* grid)
{
    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    cell.setFillColor(Color(255, 0, 255));

    for (int x = 0; x < grid->getRows(); x++) {
        for (int y = 0; y < grid->getCols(); y++) {
            Cell* currentCell = grid->getCell(x, y);

            if (currentCell != nullptr && currentCell->isAlive()) {
                cell.setPosition(x * cellSize, y * cellSize);
                window->draw(cell);
            }
        }
    }
}

void GraphicalDisplay::handleButtonClick(int buttonIndex) {
    if (buttonIndex < 10) {
        // Boutons de contrôle (0-9)
        switch (buttonIndex) {
        case 0:  // Pause
            state = (state == RUNNING ? PAUSED : RUNNING);
            break;
        case 1:  // Next
            state = STEP;
            break;
        case 2:  // Restart
            state = CLEARED;
            patternMode = false;
            selectedPatternIndex = -1;
            break;
        case 3: // Rule1
            requestedRuleIndex = 0;
            restartRequested = true;
            break;
        case 4: // Rule2
            requestedRuleIndex = 1;
            restartRequested = true;
            break;
        case 5: // Rule3
            requestedRuleIndex = 2;
            restartRequested = true;
            break;
        case 6: // Speed 1
            setDelay(1);
            break;
        case 7: // Speed 20
            setDelay(20);
            break;
        case 8: // Speed 50
            setDelay(50);
            break;
        case 9: // Speed 100
            setDelay(100);
            break;
        }
    }
    else {
        // Boutons de patterns (10+)
        int patternIndex = buttonIndex - 10;
        if (patternIndex >= 0 && patternIndex < patterns.size()) {
            patternMode = true;
            selectedPatternIndex = patternIndex;
            cout << "Pattern sélectionné : " << patterns[patternIndex].name << "\n";
        }
    }
}

void GraphicalDisplay::handleEvents(Grid* grid) {
    Event event;
    while (window->pollEvent(event)) {
        if (event.type == Event::Closed) {
            window->close();
        }

        if (event.type == Event::MouseButtonPressed &&
            event.mouseButton.button == Mouse::Left) {

            Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (patternMode && mousePos.x < windowWidth && mousePos.y < windowHeight) {
                int gridX = mousePos.x / cellSize;
                int gridY = mousePos.y / cellSize;

                if (selectedPatternIndex >= 0 && selectedPatternIndex < patterns.size()) {
                    grid->placePattern(patterns[selectedPatternIndex], gridX, gridY);
                    cout << "Pattern '" << patterns[selectedPatternIndex].name
                        << "' place a (" << gridX << ", " << gridY << ")\n";
                }

                patternMode = false;
                selectedPatternIndex = -1;
                continue;
            }


            for (int i = 0; i < buttons.size(); i++) {
                if (buttons[i]->getGlobalBounds().contains(mousePos))             // Vérifier les boutons
                {
                    handleButtonClick(i);
                }
            }
        }
    }
}
