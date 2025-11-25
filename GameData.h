#pragma once
#include <vector>
#include <cstdlib>
#include <omp.h>
using namespace std;

struct Pattern {
    string name;
    vector<pair<int, int>> cells;  // Coordonnées relatives (dx, dy)

    Pattern(const string& n) : name(n) {}

    void addCell(int dx, int dy) {
        cells.push_back({ dx, dy });
    }
};

