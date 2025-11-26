#include <iostream>
#include "ConsoleDisplay.h"
#include "Grid.h"

using namespace std;

void ConsoleDisplay::show(Grid* _grid) {

}

void ConsoleDisplay::clear() {

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