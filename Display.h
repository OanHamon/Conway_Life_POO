#pragma once
#include <iostream>
#include <string>
#include "Grid.h"

using namespace std;

class Display
{
public:
    virtual ~Display() = default;
    virtual void show(Grid* _grid) = 0;
    virtual void clear() = 0;

    virtual string askPath() {
        string path;
        cout << "chemin vers le fichier d'entree\n";

        while (!(cin >> path)) {
            cout << "Chemin invalide";
            cin.clear();
        }

        return path;
    }

    virtual int askIterations() {
        int maxIter;
        cout << "Execution limitee a combien d'iterations ?\n";

        while (!(cin >> maxIter) || maxIter <= 0) {
            cout << "Nombre invalide, recommence : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        return maxIter;
    }
};