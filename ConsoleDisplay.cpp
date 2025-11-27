#include <iostream>
#include "ConsoleDisplay.h"
#include "Grid.h"

using namespace std;

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

int ConsoleDisplay::askIterations()
{
    int maxIter = 0;
    cout << "Execution limitee a combien d'iterations ?\n";

    while (!(cin >> maxIter) || maxIter <= 0) {
        cout << "Nombre invalide, recommence : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return maxIter;
}

string ConsoleDisplay::askPath() {
    string path = "";
    cout << "chemin vers le fichier d'entree\n";

    while (!(cin >> path)) {
        cout << "Chemin invalide";
        cin.clear();
    }

    return path;
}