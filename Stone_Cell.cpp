#include "Stone_Cell.h"

Stone_Cell::Stone_Cell(Sandbox* sandbox, Pos pos) : Solid_Cell::Solid_Cell(sandbox, pos)
{
	density = 2.5;
}

void Stone_Cell::update() {
	Cell* top_left_cell = get_cell(-1, -1);
	Cell* top_right_cell = get_cell(1, -1);
	

	auto two_neighboor = [](Cell* c1, Cell* c2) {return c1&& c1->state == state::solid && c2 && c2->state == state::solid;};
	if (!two_neighboor(top_left_cell, top_right_cell))
		sink_into(get_cell(0, 1));
}

sf::Color Stone_Cell::get_color() {
	return sf::Color(149, 148, 139);
}

std::string Stone_Cell::str()
{
	return "4";
}
