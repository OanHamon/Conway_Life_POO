#pragma once
#include <vector>
#include <cstdlib>
#include "Cell.h"
#include "Rule.h"
#include <string>

using namespace std;

struct Pattern {
    string name;
    vector<pair<int, int>> cells;

    Pattern(const string& n) : name(n) {}

    void addCell(int dx, int dy) {
        cells.push_back({ dx, dy });
    }
};

class Grid
{
public:
    Grid(int _rows, int _cols, Rule* _rule);
    Grid(int _rows, int _cols, Rule* _rule, vector<vector<int>> _data);
    ~Grid();

    int getRows() const;
    int getCols() const;
    Cell* getCell(int _row, int _col);
    void setRule(Rule* newRule);
    int countAliveNeighbors(Cell* cell);
    void computeNextGen();
    void UpdateCells();

private:
    int rows;
    int cols;
    vector<vector<Cell*>> cells;
    Rule* rule;
};
