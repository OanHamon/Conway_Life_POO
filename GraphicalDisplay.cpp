#include "Display.h"

GraphicalDisplay::GraphicalDisplay(int _windowWidth, int _windowHeight, int cellSize)
    : cellSize(cellSize), delay(100), windowWidth(_windowWidth), windowHeight(_windowHeight)
{
    window = new RenderWindow(VideoMode(windowWidth + 200, windowHeight + 200), "Game of Life");
    window->setFramerateLimit(60);

    if (!font.loadFromFile(R"(Fonts\NotoSans.ttf)")) {
        cerr << "Erreur chargement police" << endl;
    }

    int buttonHeight = 60;
    int buttonWidth = 180;
    int spacing = 20;
    vector<string> names = { "Pause", "Next", "Restart", "Rule1", "Rule2", "Rule3" };

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

    iterationText.setFont(font);
    iterationText.setCharacterSize(22);
    iterationText.setFillColor(sf::Color::White);
    iterationText.setString("Iterations : 0");
    iterationText.setPosition(20 + (3 * (buttonWidth + 20)), windowHeight + 20);
}

GraphicalDisplay::~GraphicalDisplay() {
    delete window;
    for (auto b : buttons) delete b;
    for (auto l : labels) delete l;
}

void GraphicalDisplay::setIterationCounter(int value) {
    iterationCounter = value;
    iterationText.setString("Iterations : " + std::to_string(value));
}

int GraphicalDisplay::getDelay() const { return delay; }
int GraphicalDisplay::getRequestedRuleIndex() const { return requestedRuleIndex; }
void GraphicalDisplay::resetRequestedRuleIndex() { requestedRuleIndex = -1; }

void GraphicalDisplay::show(Grid* grid) {
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
        window->draw(*buttons[i]);
        window->draw(*labels[i]);
    }
    window->draw(iterationText);
    window->display();
}

void GraphicalDisplay::handleEvents() {
    Event event;
    while (window->pollEvent(event)) {
        if (event.type == Event::Closed) {
            window->close();
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < buttons.size(); i++) {
                if (buttons[i]->getGlobalBounds().contains(mousePos)) {
                    switch (i) {
                    case 0: state = (state == RUNNING ? PAUSED : RUNNING); break;
                    case 1: state = STEP; break;
                    case 2: restartRequested = true; break;
                    case 3: requestedRuleIndex = 0; restartRequested = true; break;
                    case 4: requestedRuleIndex = 1; restartRequested = true; break;
                    case 5: requestedRuleIndex = 2; restartRequested = true; break;
                    }
                }
            }
        }
    }
}

void GraphicalDisplay::setDelay(int milliseconds) { delay = milliseconds; }
void GraphicalDisplay::clear() { window->clear(Color(20, 20, 20)); }
bool GraphicalDisplay::isOpen() const { return window->isOpen(); }

void GraphicalDisplay::drawGrid(Grid* grid) {
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
