#pragma once
#include "Grid.h"

class Display
{
public:
    virtual ~Display() {}
    virtual void show(Grid* grid) = 0;
    virtual void clear() = 0;
};

class ConsoleDisplay : public Display {
public:
    void show(Grid* grid) override;
    void clear() override;

private:
};