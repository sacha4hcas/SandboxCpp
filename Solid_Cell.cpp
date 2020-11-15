#include "Solid_Cell.h"

Solid_Cell::Solid_Cell(Sandbox* sandbox, Pos pos) : Cell(sandbox, pos)
{
	state = state::solid;
}


void Solid_Cell::update() {
	if (sink_into(get_cell(0, 1))) return;

	if (!fluid) return;
	int x = 1;
	if (rand() % 100 < 50) x = -1;
	if (sink_into(get_cell(x, 1))) return;
	//if (sink_into(get_cell(-x, 1))) return;
}

