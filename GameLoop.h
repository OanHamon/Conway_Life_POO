#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "GameData.h"

using namespace std;
using namespace sf;


enum GameState { RUNNING, PAUSED, STEP };

class Display
{
public:
    virtual ~Display() {}
    virtual void show(Grid* grid)  = 0;
    virtual void clear() = 0;

};

class ConsoleDisplay : public Display {
public:

private:

};



class GraphicalDisplay : public Display{
public:
    GameState state = RUNNING;
    bool restartRequested = false;
    GraphicalDisplay(int _windowWidth, int _windowHeight, int cellSize)
        : cellSize(cellSize), delay(100), windowWidth(_windowWidth), windowHeight(_windowHeight)
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


        int patButtonHeight = 100;
        int patButtonWidth = 100;
        vector<string> paterne = { "Paterne 1", "Paterne 2","Paterne 3","Paterne 4","Paterne 5","Paterne 6" };

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
            label->setString(paterne[i]);
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

        iterationText.setPosition( 20 +(3 * (buttonWidth + 20) ) , windowHeight + 20);


    }
    void setIterationCounter(int value) {
        iterationCounter = value;
        iterationText.setString("Iterations : " + std::to_string(value));
    }

   
    int getDelay() const {return delay;}
    int getRequestedRuleIndex() const { return requestedRuleIndex; }
    void resetRequestedRuleIndex() { requestedRuleIndex = -1; }

    void show(Grid* grid) override {
        clear();
        drawGrid(grid);


        float width = grid->getRows() * cellSize;
        float height = grid->getCols() * cellSize;

        //Bordure
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


    void handleEvents()
    {
        Event event;
        while (window->pollEvent(event)) {

            if (event.type == Event::Closed) {
                window->close();
            }

            if (event.type == Event::MouseButtonPressed &&
                event.mouseButton.button == Mouse::Left) {

                Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (int i = 0; i < buttons.size(); i++) {
                    if (buttons[i]->getGlobalBounds().contains(mousePos)) {

                        switch (i) {
                        case 0:  // Pause
                            state = (state == RUNNING ? PAUSED : RUNNING);
                            break;

                        case 1:  // Next
                            state = STEP;
                            break;

                        case 2:  // Restart
                            restartRequested = true;
                            break;

                        case 3: cout << "Rule1\n"; 
                            requestedRuleIndex = 0;
                            restartRequested = true;
                            break;
                        case 4: cout << "Rule2\n";
                            requestedRuleIndex = 1;
                            restartRequested = true;
                            break;
                        case 5: cout << "Rule3\n";
                            requestedRuleIndex = 2;
                            restartRequested = true;
                            break;
                        case 6: cout << "1\n";
                            setDelay(1);
                            break;
                        case 7: cout << "5\n";
                            setDelay(20);
                            break;
                        case 8: cout << "10\n";
                            setDelay(50);
                            break;
                        case 9: cout << "100\n";
                            setDelay(100);
                            break;
                        }
                    }
                }
            }
        }
    }

    
    void setDelay(int milliseconds) {delay = milliseconds;}

    void clear() override {window->clear(Color(20, 20, 20));}    
    bool isOpen() const { return window->isOpen(); }
    
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



    void drawGrid( Grid* grid) {
        //window->clear(Color(50, 50, 80));
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
};


class Game {
public:
    Game() {}

    void run() {
        int mode = MainMenu();
        int maxIter = 0;

        if (mode == 0) {
            // Mode console → poser la question
            maxIter = askIterations();
            //runConsole(maxIter);
        }
        else {
            // Mode graphique → FICÉ à 5000
            maxIter = 1000;
            runGraphical(maxIter);
        }
    }

    int  MainMenu() {
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


    void resetGrid(Grid*& grid, int gridWidth, int gridHeight) {
        delete grid;  // Libérer l'ancienne grille
        Rule* conway = new ConwayRule();
        grid = new Grid(gridWidth, gridHeight, conway);
    }


    int askIterations()
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

    void runGraphical(int maxIter) {
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

            display->handleEvents();

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
                    newRule = new HardcoreRule();
                    cout << "Règle : Hardcore\n";
                    break;
                case 2:
                    newRule = new HighLifeRule();
                    cout << "Règle : Low Social Life\n";
                    break;
                default:
                    newRule = new ConwayRule();
                }

                delete grid;
                grid = new Grid(gridWidth, gridHeight, newRule);
                iterationsDone = 0;
                display->setIterationCounter(0);
                display->restartRequested = false;
                display->state = PAUSED;  // Optionnel : pause après restart
            }

            // Game state
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

    void runConsole(int _maxIter)
    {
        cout << "ererere";
    }
};

