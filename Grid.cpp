#include "Grid.h"
#include <omp.h>
#include <iostream>


#pragma region Constructeurs

Grid::Grid(int _rows, int _cols, Rule* _rule)
    : rows(_rows), cols(_cols), rule(_rule)
{
    cells.resize(rows);
    for (int i = 0; i < rows; i++) {
        cells[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            int randomValue = rand() % 2;
            if (randomValue == 1) {
                cells[i][j] = new Cell(i, j, new AliveState());
            }
            else {
                cells[i][j] = new Cell(i, j, new DeadState());
            }
        }
    }
}

Grid::Grid(int _rows, int _cols, Rule* _rule, bool _zero)
    : rows(_rows), cols(_cols), rule(_rule)
{
    cells.resize(rows);
    for (int i = 0; i < rows; i++) {
        cells[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            if (!_zero)
            {
                int randomValue = rand() % 2;
                if (randomValue == 1) {
                    cells[i][j] = new Cell(i, j, new AliveState());
                }
                else {
                    cells[i][j] = new Cell(i, j, new DeadState());
                }

            }
            cells[i][j] = new Cell(i, j, new DeadState());

        }
    }
}

Grid::Grid(int _rows, int _cols, Rule* _rule, vector<vector<int>> _data)
    : rows(_rows), cols(_cols), rule(_rule)
{
    cells.resize(rows);
    for (int i = 0; i < rows; i++) {
        cells[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            if (_data[i][j] == 1) {
                cells[i][j] = new Cell(i, j, new AliveState(false));
            }
            else if (_data[i][j] == 0) {
                cells[i][j] = new Cell(i, j, new DeadState(false));
            }
            else if (_data[i][j] == 2) {
                cells[i][j] = new Cell(i, j, new AliveState(true));
            }
            else if (_data[i][j] == -1) {
                cells[i][j] = new Cell(i, j, new DeadState(true));
            }
            else { std::cerr << "valeur(" << _data[i][j] << ") de cellule invalide pour la grille\n"; }
        }
    }
}
#pragma endregion


Grid::~Grid()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete cells[i][j];
        }
    }
}

#pragma region Setters/Getters

int Grid::getRows() const
{
    return rows;
}

int Grid::getCols() const
{
    return cols;
}

Cell* Grid::getCell(int _row, int _col)
{
    if (_row < 0 || _row >= rows || _col < 0 || _col >= cols) {
        return nullptr;
    }
    return cells[_row][_col];
}

void Grid::setRule(Rule* newRule)
{
    delete rule;
    rule = newRule;
}


#pragma endregion


int Grid::countAliveNeighbors(Cell* cell)
{
    int x = cell->getRow();
    int y = cell->getCol();
    int cmpt = 0;

    for (int i = -1; i <= 1; i++) {
        for (int n = -1; n <= 1; n++) {
            if (i == 0 && n == 0) continue;

            int neighborRow = (x + i + rows) % rows;
            int neighborCol = (y + n + cols) % cols;

            if (cells[neighborRow][neighborCol]->isAlive()) {
                cmpt++;
            }
        }
    }

    return cmpt;
}

void Grid::computeNextGen()
{
#pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Cell* cell = cells[i][j];
            CellState* nxtState = rule->computeNextState(cell, this);
            if (!cell->getCurrentState()->isObstacle()) {
                cell->setNextState(nxtState);
            }
        }
    }

    UpdateCells();
}

void Grid::UpdateCells()
{
    for (int i = 0; i < rows; i++) {
        for (int n = 0; n < cols; n++) {
            cells[i][n]->updateState();
        }
    }
}

vector<vector<int>> Grid::getGridInt()
{
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int n = 0; n < cols; n++) {
            if (!cells[i][n]->getCurrentState()->isObstacle()) {
                grid[i][n] = cells[i][n]->isAlive() ? 1 : 0;
            }
            else {
                grid[i][n] = cells[i][n]->isAlive() ? 2 : -1;
            }
        }
    }
    return grid;
}


void Grid::placePattern(const Patern& pattern, int centerRow, int centerCol) {
    
    int offsetRow = centerRow - pattern.height / 2;
    int offsetCol = centerCol - pattern.width / 2;

    for (const auto& cell : pattern.cells) {
        int targetRow = (offsetRow + cell.first + rows) % rows;
        int targetCol = (offsetCol + cell.second + cols) % cols;

        if (targetRow >= 0 && targetRow < rows &&
            targetCol >= 0 && targetCol < cols) {
            
            if(pattern.isObstacle){ cells[targetRow][targetCol]->setNextState(new AliveState(true)); } else { cells[targetRow][targetCol]->setNextState(new AliveState()); }

            cells[targetRow][targetCol]->updateState();
        }
    }
}

Cell* Grid::getCellFromPixel(int pixelX, int pixelY, int cellSize) {
    int row = pixelX / cellSize;
    int col = pixelY / cellSize;
    return getCell(row, col);
}
