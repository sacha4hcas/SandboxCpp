#include "Gazeous_Cell.h"

Gazeous_Cell::Gazeous_Cell(Sandbox* sandbox, Pos pos) : Cell::Cell(sandbox, pos)
{
	state = state::gazeous;
}
