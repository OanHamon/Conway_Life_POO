#pragma once
#include <string>
#include "Display.h"

class ConsoleDisplay :public Display
{
public:
	void show(Grid* grid) override;
	void clear() override;
	int askIterations();

};
