#include "GraphicalDisplay.h"
#include <iostream>

// Constructeur 1 : avec cellSize explicite
GraphicalDisplay::GraphicalDisplay(int _windowWidth, int _windowHeight, int cellSize, windowType type)
    : cellSize(cellSize), delay(100), windowWidth(_windowWidth), windowHeight(_windowHeight),
    iterationCounter(0), requestedRuleIndex(-1), patternMode(false), selectedPatternIndex(-1),
    state(PAUSED), restartRequested(false),
    managementButtonsCount(0), speedButtonsCount(0), patternButtonsCount(0)
{
    initWindowsDimension(type);
    initWindow();
    loadResources();
    initGUI(type);
}

// Constructeur 2 : calcul automatique du cellSize
GraphicalDisplay::GraphicalDisplay(int _gridWidth, int _gridHeight, windowType type)
    : delay(100), windowWidth(800), windowHeight(800),
    iterationCounter(0), requestedRuleIndex(-1), patternMode(false), selectedPatternIndex(-1),
    state(PAUSED), restartRequested(false),
    managementButtonsCount(0), speedButtonsCount(0), patternButtonsCount(0)
{
    // Calculer la taille des cellules pour que la grille rentre dans la fenêtre
    int cellSizeByWidth = windowWidth / _gridWidth;
    int cellSizeByHeight = windowHeight / _gridHeight;
    cellSize = std::min(cellSizeByWidth, cellSizeByHeight);

    initWindowsDimension(type);
    initWindow();
    loadResources();
    initGUI(type);
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

// Méthodes privées d'initialisation
void GraphicalDisplay::initWindowsDimension(windowType type)
{
    constexpr int BOTTOM_DIV_HEIGHT = 200;
    constexpr int LEFT_DIV_WIDTH = 300;

    switch (type)
    {
    case MANAGEMENT:
        windowHeight += BOTTOM_DIV_HEIGHT;
        break;
    case PATERN:
        windowWidth += LEFT_DIV_WIDTH;
        break;
    case SPEED:
        windowWidth += LEFT_DIV_WIDTH;
        windowHeight += BOTTOM_DIV_HEIGHT;
        break;
    case FULL:
        windowWidth += LEFT_DIV_WIDTH;
        windowHeight += BOTTOM_DIV_HEIGHT;
        break;
    case FOCUSED:
    default:
        break;
    }
}

void GraphicalDisplay::initWindow()
{
    window = new RenderWindow(VideoMode(windowWidth, windowHeight), "Game of Life");
    window->setFramerateLimit(60);
}

void GraphicalDisplay::loadResources()
{
    paterns = PaternLibrary::getAllPatterns();

    if (!font.loadFromFile(R"(Fonts\NotoSans.ttf)")) {
        std::cerr << "Erreur: Impossible de charger la police NotoSans.ttf" << std::endl;
    }
}

void GraphicalDisplay::initGUI(windowType type)
{
    constexpr int BUTTON_HEIGHT = 60;
    constexpr int BUTTON_WIDTH = 180;
    constexpr int SPACING = 20;

    // Calculer la position de base de la grille (sans les extensions)
    int baseGridHeight = (type == MANAGEMENT || type == SPEED || type == FULL)
        ? windowHeight - 200 : windowHeight;
    int baseGridWidth = (type == PATERN || type == SPEED || type == FULL)
        ? windowWidth - 300 : windowWidth;

    // Boutons de gestion
    if (type == MANAGEMENT || type == FULL)
    {
        const std::vector<std::string> names = { "Pause", "Next", "Restart", "Rule1", "Rule2", "Rule3" };
        createButtonGroup(names, BUTTON_WIDTH, BUTTON_HEIGHT, SPACING,
            baseGridHeight + 20.f, 3, true, 20.f, ButtonType::MANAGEMENT);
        managementButtonsCount = names.size();
    }

    // Boutons de vitesse
    if (type == SPEED || type == FULL)
    {
        constexpr int SPEED_BUTTON_HEIGHT = 40;
        constexpr int SPEED_BUTTON_WIDTH = 120;
        const std::vector<std::string> speeds = { "1", "20", "50", "100" };

        float startX = 20.f + (3 * (BUTTON_WIDTH + 20));
        createButtonGroup(speeds, SPEED_BUTTON_WIDTH, SPEED_BUTTON_HEIGHT, SPACING,
            baseGridHeight + 70.f, 2, true, startX, ButtonType::SPEED);
        speedButtonsCount = speeds.size();
    }

    // Boutons de patterns
    if (type == PATERN || type == FULL)
    {
        constexpr int PAT_BUTTON_HEIGHT = 100;
        constexpr int PAT_BUTTON_WIDTH = 100;

        std::vector<std::string> patternNames;
        patternNames.reserve(paterns.size());
        for (const auto& pattern : paterns) {
            patternNames.push_back(pattern.name);
        }

        createButtonGroup(patternNames, PAT_BUTTON_WIDTH, PAT_BUTTON_HEIGHT, SPACING,
            50.f, 6, false, baseGridWidth + 40.f, ButtonType::PATTERN);
        patternButtonsCount = patternNames.size();
    }

    // Texte d'itération
    iterationText.setFont(font);
    iterationText.setCharacterSize(22);
    iterationText.setFillColor(sf::Color::White);
    iterationText.setString("Iterations : 0");
    iterationText.setPosition(20.f + (3 * (BUTTON_WIDTH + 20)), baseGridHeight + 20.f);
}

void GraphicalDisplay::createButtonGroup(const std::vector<std::string>& names,
    int buttonWidth, int buttonHeight, int spacing,
    float startY, int columns, bool horizontal,
    float startX, ButtonType type)
{
    size_t startIndex = buttons.size();

    for (size_t i = 0; i < names.size(); ++i)
    {
        // Calcul de position
        int row, col;
        if (horizontal) {
            row = i / columns;
            col = i % columns;
        }
        else {
            row = i % columns;
            col = i / columns;
        }

        float x = startX + col * (buttonWidth + spacing);
        float y = startY + row * (buttonHeight + spacing);

        // Créer le bouton
        sf::RectangleShape* button = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
        button->setFillColor(sf::Color(100, 100, 200));
        button->setPosition(x, y);
        buttons.push_back(button);

        // Créer le label
        sf::Text* label = new sf::Text();
        label->setFont(font);
        label->setString(names[i]);
        label->setCharacterSize(20);
        label->setFillColor(sf::Color::White);

        // Centrer le texte
        sf::FloatRect textBounds = label->getLocalBounds();
        label->setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        label->setPosition(x + buttonWidth / 2.0f, y + buttonHeight / 2.0f);
        labels.push_back(label);

        // Stocker le type et l'index relatif du bouton
        buttonTypes.push_back(type);
    }
}

// Getters/Setters
void GraphicalDisplay::setIterationCounter(int value)
{
    iterationCounter = value;
    iterationText.setString("Iterations : " + std::to_string(value));
}

int GraphicalDisplay::getDelay() const
{
    return delay;
}

void GraphicalDisplay::setDelay(int milliseconds)
{
    delay = milliseconds;
}

int GraphicalDisplay::getRequestedRuleIndex() const
{
    return requestedRuleIndex;
}

void GraphicalDisplay::resetRequestedRuleIndex()
{
    requestedRuleIndex = -1;
}

// Méthodes d'affichage
void GraphicalDisplay::show(Grid* grid)
{
    clear();
    drawGrid(grid);
    drawBorder(grid);
    drawButtons();
    window->draw(iterationText);
    window->display();
}

void GraphicalDisplay::drawBorder(Grid* grid) const
{
    float width = grid->getCols() * cellSize;
    float height = grid->getRows() * cellSize;


    sf::RectangleShape border(sf::Vector2f(width, height));
    border.setPosition(0, 0);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(5.f);
    border.setOutlineColor(sf::Color::White);
    window->draw(border);
}

void GraphicalDisplay::drawButtons() const
{
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        // Mettre en surbrillance le pattern sélectionné
        if (buttonTypes[i] == ButtonType::PATTERN)
        {
            int patternIndex = getRelativeButtonIndex(i, ButtonType::PATTERN);
            if (patternMode && patternIndex == selectedPatternIndex)
            {
                buttons[i]->setFillColor(sf::Color(150, 255, 150));
            }
            else
            {
                buttons[i]->setFillColor(sf::Color(100, 100, 200));
            }
        }

        window->draw(*buttons[i]);
        window->draw(*labels[i]);
    }
}

void GraphicalDisplay::drawGrid(Grid* grid) const
{
    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < grid->getRows(); ++x)
    {
        for (int y = 0; y < grid->getCols(); ++y)
        {
            const Cell* currentCell = grid->getCell(x, y);
            if (currentCell == nullptr) continue;

            Color cellColor = getCellColor(currentCell);
            if (cellColor != Color::Transparent)
            {
                cell.setFillColor(cellColor);
                cell.setPosition(y * cellSize, x * cellSize);
                window->draw(cell);
            }
        }
    }
}

Color GraphicalDisplay::getCellColor(const Cell* cell) const
{
    if (cell->isAlive())
    {
        return cell->getCurrentState()->isObstacle()
            ? Color(75, 67, 135)    // Vivante obstacle
            : Color(113, 96, 232);   // Vivante normale
    }
    else if (cell->getCurrentState()->isObstacle())
    {
        return Color(37, 37, 38);      // Morte obstacle
    }

    return Color::Transparent;         // Morte normale (non dessinée)
}

void GraphicalDisplay::clear()
{
    window->clear(Color(20, 20, 20));
}

bool GraphicalDisplay::isOpen() const
{
    return window->isOpen();
}


#pragma region Event
void GraphicalDisplay::handleEvents(Grid* grid)
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window->close();
        }
        else if (event.type == Event::MouseButtonPressed &&
            event.mouseButton.button == Mouse::Left)
        {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y, grid);
        }
    }
}

void GraphicalDisplay::handleMouseClick(int mouseX, int mouseY, Grid* grid)
{
    Vector2f mousePos(mouseX, mouseY);

    // Clic dans la grille en mode pattern
    if (patternMode && mouseX < windowWidth && mouseY < windowHeight)
    {
        placePattern(mouseX, mouseY, grid);
        patternMode = false;
        selectedPatternIndex = -1;
        return;
    }

    // Vérifier les boutons
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i]->getGlobalBounds().contains(mousePos))
        {
            handleButtonClick(i);
            return;
        }
    }
}

void GraphicalDisplay::placePattern(int mouseX, int mouseY, Grid* grid)
{
    int gridX = mouseX / cellSize;
    int gridY = mouseY / cellSize;

    if (selectedPatternIndex >= 0 &&
        selectedPatternIndex < static_cast<int>(paterns.size()))
    {
        grid->placePattern(paterns[selectedPatternIndex], gridX, gridY);
        std::cout << "Pattern '" << paterns[selectedPatternIndex].name
            << "' place a (" << gridX << ", " << gridY << ")\n";
    }
}

void GraphicalDisplay::handleButtonClick(int buttonIndex)
{
    ButtonType type = buttonTypes[buttonIndex];
    int relativeIndex = getRelativeButtonIndex(buttonIndex, type);

    switch (type)
    {
    case ButtonType::MANAGEMENT:
        handleManagementButton(relativeIndex);
        break;
    case ButtonType::SPEED:
        handleSpeedButton(relativeIndex);
        break;
    case ButtonType::PATTERN:
        handlePatternButton(relativeIndex);
        break;
    }
}

int GraphicalDisplay::getRelativeButtonIndex(int absoluteIndex, ButtonType type) const
{
    int relativeIndex = 0;
    for (int i = 0; i < absoluteIndex; ++i)
    {
        if (buttonTypes[i] == type)
        {
            ++relativeIndex;
        }
    }
    return relativeIndex;
}

void GraphicalDisplay::handleManagementButton(int buttonIndex)
{
    switch (buttonIndex)
    {
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
    case 3:  // Rule1
        requestedRuleIndex = 0;
        restartRequested = true;
        break;
    case 4:  // Rule2
        requestedRuleIndex = 1;
        restartRequested = true;
        break;
    case 5:  // Rule3
        requestedRuleIndex = 2;
        restartRequested = true;
        break;
    }
}

void GraphicalDisplay::handleSpeedButton(int buttonIndex)
{
    switch (buttonIndex)
    {
    case 0:  // Speed 1
        setDelay(1);
        break;
    case 1:  // Speed 20
        setDelay(20);
        break;
    case 2:  // Speed 50
        setDelay(50);
        break;
    case 3:  // Speed 100
        setDelay(100);
        break;
    }
}

void GraphicalDisplay::handlePatternButton(int patternIndex)
{
    if (patternIndex >= 0 && patternIndex < static_cast<int>(paterns.size()))
    {
        patternMode = true;
        selectedPatternIndex = patternIndex;
        std::cout << "Pattern selectionne : " << paterns[patternIndex].name << "\n";
    }
}

#pragma endregion