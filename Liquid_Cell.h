#pragma once
#include "Cell.h"
class Liquid_Cell : public Cell
{
public:
	Liquid_Cell(Sandbox*, Pos);
	void update();
};

