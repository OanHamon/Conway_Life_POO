#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include "Grid.h"

namespace fs = std::filesystem;
using namespace std;

class Display
{
public:
    virtual ~Display() = default;
    virtual void show(Grid* _grid) = 0;
    virtual void clear() = 0;

    virtual string askPath() {
        string path;
        cout << "chemin vers le fichier d'entree : ";

        while (!(cin >> path) || !fs::exists(path)) {
            cerr << "Erreur : Chemin invalide ou introuvable\n";
            cin.clear();
            cout << "chemin vers le fichier d'entree : ";
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