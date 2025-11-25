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
    CellState() : Obstacle(false) {};
    CellState(bool _ObsState) : Obstacle(_ObsState) {};
    virtual ~CellState() {}
    virtual bool isAlive() const = 0;
    virtual bool isObstacle() const = 0;

protected :
    bool Obstacle;
};

class AliveState : public CellState
{
public:
    AliveState() : CellState(false) {}
    AliveState(bool _ObsState) : CellState(_ObsState) {}
    bool isAlive() const override { return true; }
    bool isObstacle() const override { return Obstacle; }

};

class DeadState : public CellState
{
public:
    DeadState() : CellState(false) {}
    DeadState(bool _ObsState) : CellState(_ObsState) {}
    bool isAlive() const override { return false; }
    bool isObstacle() const override { return Obstacle; }

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

class GridData {
    int rows;
    int cols;
    vector<vector<bool>> initialStates;
};

struct Pattern {
    string name;
    vector<pair<int, int>> cells;  // Coordonnées relatives (dx, dy)

    Pattern(const string& n) : name(n) {}

    void addCell(int dx, int dy) {
        cells.push_back({ dx, dy });
    }
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
    Grid(int _rows, int _cols, Rule* _rule, vector<vector<int>> _data)
        : rows(_rows), cols(_cols), rule(_rule)
    {
        cells.resize(rows);
        for (int i = 0; i < rows; i++) {
            cells[i].resize(cols);
            for (int j = 0; j < cols; j++) {
                
                if (_data[i][j] == 1) {
                    cells[i][j] = new Cell(i, j, new AliveState(false));
                    
                }
                else {
                    cells[i][j] = new Cell(i, j, new DeadState(false));
                    
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

    int getRows()const { return rows; }
    int getCols()const { return cols; }
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

                int neighborRow = (x + i + rows) % rows;
                int neighborCol = (y + n + cols) % cols;

               
               
               if (cells[neighborRow][neighborCol]->isAlive()) {
                   cmpt++;
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
                if(!cell->getCurrentState()->isObstacle()){ cell->setNextState(nxtState); }


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
class HardcoreRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid)
    {
        bool isCurrentlyAlive = cell->isAlive();
        int aliveNeighbors = grid->countAliveNeighbors(cell);

        if (isCurrentlyAlive) {
            // Cellule vivante : survit avec 2 ou 3 voisins
            if (aliveNeighbors == 7 || aliveNeighbors == 8) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
        else {
            // Cellule morte : naît avec exactement 3 voisins
            if (aliveNeighbors == 8) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
    }

};  
class LowSocialLifeRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid)
    {
        bool isCurrentlyAlive = cell->isAlive();
        int aliveNeighbors = grid->countAliveNeighbors(cell);

        if (isCurrentlyAlive) {
            // Cellule vivante : survit avec 2 ou 3 voisins
            if (aliveNeighbors ==1 ) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
        else {
            // Cellule morte : naît avec exactement 3 voisins
            if (aliveNeighbors == 1) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
    }

};  
class HighLifeRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid)
    {
        bool isCurrentlyAlive = cell->isAlive();
        int aliveNeighbors = grid->countAliveNeighbors(cell);

        if (isCurrentlyAlive) {
            // Cellule vivante : survit avec 2 ou 3 voisins
            if (aliveNeighbors ==1 || aliveNeighbors == 2 || aliveNeighbors == 3 || aliveNeighbors == 4 || aliveNeighbors == 5 || aliveNeighbors == 8) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
        else {
            // Cellule morte : naît avec exactement 3 voisins
            if (aliveNeighbors == 1 || aliveNeighbors == 2 || aliveNeighbors == 3|| aliveNeighbors == 4|| aliveNeighbors == 5|| aliveNeighbors == 6) {
                return new AliveState();
            }
            else {
                return new DeadState();
            }
        }
    }

};  
