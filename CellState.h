#pragma once


class CellState
{
public:
    CellState() : Obstacle(false) {};
    CellState(bool _ObsState) : Obstacle(_ObsState) {};
    virtual ~CellState() = default;
    virtual bool isAlive() const = 0;
    virtual bool isObstacle() const = 0;

protected:
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
