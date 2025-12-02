#include <iostream>
#include "ConsoleDisplay.h"
#include "Grid.h"

using namespace std;

#pragma region MethodeJeu

void ConsoleDisplay::show(Grid* _grid) {
    for (int i = 0; i < _grid->getRows(); i++)
    {
        for (int j = 0; j < _grid->getCols(); j++)
        {
            if (_grid->getCell(i, j)->isAlive())
            {
                cout << "# ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << "\n";
    }
    cout << "\n\n";
}

void ConsoleDisplay::clear()
{
    cout << "\033[2J\033[1;1H";
}

#pragma endregion

