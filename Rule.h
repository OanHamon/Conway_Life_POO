#pragma once
#include "Cell.h"

class Grid;  // Forward declaration

class Rule
{
public:
    virtual ~Rule() {}
    virtual CellState* computeNextState(Cell* cell, Grid* grid) = 0;
};

class ConwayRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class HighLifeRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class SeedsRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class DayAndNightRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class TectonicRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class MazeRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class CoagulationsRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class CoralRule : public Rule
{
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};