#pragma once

class CellState {
public:
    CellState() : Obstacle(false) {}
    CellState(bool _ObsState) : Obstacle(_ObsState) {}
    virtual ~CellState() {}
    virtual bool isAlive() const = 0;
    virtual bool isObstacle() const = 0;

protected:
    bool Obstacle;
};

class AliveState : public CellState {
public:
    AliveState() : CellState(false) {}
    AliveState(bool _ObsState) : CellState(_ObsState) {}
    bool isAlive() const override;
    bool isObstacle() const override;
};

class DeadState : public CellState {
public:
    DeadState() : CellState(false) {}
    DeadState(bool _ObsState) : CellState(_ObsState) {}
    bool isAlive() const override;
    bool isObstacle() const override;
};

class Cell {
public:
    Cell(int _row, int _col, CellState* _state);
    ~Cell();

    int getRow() const;
    int getCol() const;
    CellState* getCurrentState() const;
    bool isAlive() const;

    void setNextState(CellState* _state);
    void updateState();

private:
    int row;
    int col;
    CellState* currentState;
    CellState* nextState;
};
