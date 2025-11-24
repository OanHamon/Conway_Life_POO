#pragma once
#include "File_manager.h"

bool File_manager::write(string _msg) {
    ofstream f(path);
    if (!f) {
        cerr << "Erreur lors de l'ouverture du fichier !" << endl;
        return false;
    }
    f << _msg;
    f.close();
    return true;
}

bool File_manager::read(string* _output) {
    ifstream f(path, ios::in);
    if (!f) {
        cerr << "Erreur : impossible d'ouvrir le fichier !" << endl;
        return false;
    }
    string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    *_output = content;
    f.close();
    return true;
}

bool File_manager::clearFile() {
    return write("");
}

File_manager::File_manager(string _path) : path(_path) {
    ifstream infile(path);
    if (!infile.good()) {
        write("");
    }
}

string File_manager::getPath() {
    return path;
}

void File_manager::setPath(string _path) {
    this->path = _path;
}

vector<vector<int>> File_manager::getGrid() {
    string data;
    if (read(&data)) {
        stringstream ss(data);
        int rows, cols;

        if (!(ss >> rows >> cols)) {
            cerr << "Erreur: dimensions invalides." << endl;
            return {};
        }
        if (rows <= 0 || cols <= 0) {
            cerr << "Erreur: dimensions négatives ou nulles." << endl;
            return {};
        }

        vector<vector<int>> grid(rows, vector<int>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!(ss >> grid[i][j])) {
                    cerr << "Erreur: données insuffisantes ou invalides à la position (" << i << "," << j << ")." << endl;
                    return {};
                }
            }
        }

        return grid;
    }
    return {};
}

bool File_manager::saveGrid(const vector<vector<int>>& _grid) {
    if (_grid.empty()) {
        cerr << "Erreur: la grille est vide." << endl;
        return false;
    }

    int row = _grid.size();
    int col = _grid[0].size();
    if (col == 0) {
        cerr << "Erreur: la grille n'a pas de colonnes." << endl;
        return false;
    }

    for (const auto& r : _grid) {
        if ((int)r.size() != col) {
            cerr << "Erreur: lignes de tailles différentes." << endl;
            return false;
        }
    }

    string data;
    data += to_string(row) + " " + to_string(col) + "\n";

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data += to_string(_grid[i][j]) + " ";
        }
        data += "\n";
    }

    return write(data);
}
