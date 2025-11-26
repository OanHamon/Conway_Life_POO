#pragma once
#include "Grid.h"

class Display
{
public:
    virtual ~Display() {}
    virtual void show(Grid* _grid) = 0;
    virtual void clear() = 0;
};