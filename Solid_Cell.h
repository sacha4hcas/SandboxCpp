#pragma once
#include "Cell.h"
class Solid_Cell : public Cell
{
public:
	Solid_Cell(Sandbox*, Pos);
	void update();
};

