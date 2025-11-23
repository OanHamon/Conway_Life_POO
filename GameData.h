#pragma once
#include <vector>
#include <cstdlib>  
using namespace std;


class Cell;
class Grid;
class CellState;
class Rule;


class CellState
{
public:
    virtual ~CellState() {}
    virtual bool isAlive() const = 0;
    virtual CellState* clone() const = 0;
};

class AliveState : public CellState
{
public:
    bool isAlive() const override { return true; }
    CellState* clone() const override { return new AliveState(); }
};

class DeadState : public CellState
{
public:
    bool isAlive() const override { return false; }
    CellState* clone() const override { return new DeadState(); }
};


class Cell
{
public:
    Cell(int _row, int _col, CellState* _state)
        : row(_row), col(_col), currentState(_state), nextState(nullptr) {
    }

    int getRow() const { return row; }
    int getCol() const { return col; }
    CellState* getCurrentState() const { return currentState; }
    bool isAlive() const { return currentState->isAlive(); }

    void setNextState(CellState* _state)
    {
        if (nextState != nullptr) {
            delete nextState;
        }
        nextState = _state;
    }

    void updateState()
    {
        if (nextState != nullptr) {
            delete currentState;
            currentState = nextState;
            nextState = nullptr;
        }
    }

private:
    int row;
    int col;
    CellState* currentState;
    CellState* nextState;
};


class Rule
{
public:
    virtual ~Rule() {}
    virtual CellState* computeNextState(Cell* cell, Grid* grid) = 0;
};



class Grid
{
public:
    Grid(int _rows, int _cols, Rule* _rule)
        : rows(_rows), cols(_cols), rule(_rule)
    {
        cells.resize(rows);
        for (int i = 0; i < rows; i++) {
            cells[i].resize(cols);
            for (int j = 0; j < cols; j++) {
                // CORRECTION : 1 = vivante, 0 = morte
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

    ~Grid() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                delete cells[i][j];
            }
        }
        delete rule;
    }

    Cell* getCell(int _row, int _col)
    {
        if (_row < 0 || _row >= rows || _col < 0 || _col >= cols) {
            return nullptr;
        }
        return cells[_row][_col];
    }

    void setRule(Rule* newRule) {
        delete rule;
        rule = newRule;
    }

    int countAliveNeighbors(Cell* cell)
    {
        int x = cell->getRow();
        int y = cell->getCol();
        int cmpt = 0;

        for (int i = -1; i <= 1; i++) {
            for (int n = -1; n <= 1; n++) {
                if (i == 0 && n == 0) continue;

                int neighborRow = x + i;
                int neighborCol = y + n;

                if (neighborRow >= 0 && neighborRow < rows &&
                    neighborCol >= 0 && neighborCol < cols)
                {
                    if (cells[neighborRow][neighborCol]->isAlive()) {
                        cmpt++;
                    }
                }
            }
        }

        return cmpt;
    }

    void computeNextGen()
    {

        for (int i = 0; i < rows; i++)
        {
            for (int n = 0; n < cols; n++)
            {
                Cell* cell = cells[i][n];
                CellState* nxtState = rule->computeNextState(cell, this);
                cell->setNextState(nxtState);
            }
        }


        UpdateCells();
    }

    void UpdateCells()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int n = 0; n < cols; n++)
            {
                cells[i][n]->updateState();
            }
        }
    }

private:
    int rows;
    int cols;
    vector<vector<Cell*>> cells;
    Rule* rule;
};


class ConwayRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid)
    {
        bool isCurrentlyAlive = cell->isAlive();
        int aliveNeighbors = grid->countAliveNeighbors(cell);

        if (isCurrentlyAlive) {
            // Cellule vivante : survit avec 2 ou 3 voisins
            if (aliveNeighbors == 2 || aliveNeighbors == 3) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
        else {
            // Cellule morte : naît avec exactement 3 voisins
            if (aliveNeighbors == 3) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
    }

};  
