
#pragma once
#include "Cell.h"
#include "Grid.h"

class Rule {
public:
    virtual ~Rule() {}
    virtual CellState* computeNextState(Cell* cell, Grid* grid) = 0;
};

class ConwayRule : public Rule {
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class HardcoreRule : public Rule {
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class LowSocialLifeRule : public Rule {
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};

class HighLifeRule : public Rule {
public:
    CellState* computeNextState(Cell* cell, Grid* grid) override;
};