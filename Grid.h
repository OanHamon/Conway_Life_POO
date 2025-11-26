#pragma once
#include <vector>
#include <cstdlib>
#include "Cell.h"
#include "Rule.h"
#include <string>
#include "Patern.h"

using namespace std;


class Grid
{
public:
    Grid(int _rows, int _cols, Rule* _rule);
    Grid(int _rows, int _cols, Rule* _rule, bool _zero);
    Grid(int _rows, int _cols, Rule* _rule, vector<vector<int>> _data);
    ~Grid();

    int getRows() const;
    int getCols() const;
    Cell* getCell(int _row, int _col);
    void setRule(Rule* newRule);
    int countAliveNeighbors(Cell* cell);
    void computeNextGen();
    void UpdateCells();
    vector<vector<int>> getGridInt();
    void placePattern(const Patern& pattern, int centerRow, int centerCol);

    Cell* getCellFromPixel(int pixelX, int pixelY, int cellSize);


private:
    int rows;
    int cols;
    vector<vector<Cell*>> cells;
    Rule* rule;
};