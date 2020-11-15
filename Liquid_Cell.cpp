#include "Liquid_Cell.h"

Liquid_Cell::Liquid_Cell(Sandbox* sandbox, Pos pos) : Cell(sandbox, pos)
{
	state = state::liquid;
}

void Liquid_Cell::update()
{
	if (viscosity > 0)
		if (viscosity * 100 > rand()%100)
			return;
	
	if (sink_into(get_cell(0, 1))) return;
	int x = 1;
	if (rand() % 100 < 50) x = -1;
	if (sink_into(get_cell(x, 1))) return;
	//if (sink_into(get_cell(-x, 1))) return;
	if (sink_into(get_cell(x, 0))) return;
	//if (sink_into(get_cell(-x, 0))) return;
}
