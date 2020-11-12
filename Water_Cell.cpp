#include "Water_Cell.h"

//**************** Water_Cell method definition **********************//
Water_Cell::Water_Cell(Sandbox* sandbox, Pos pos) :
	Base_Cell::Base_Cell(sandbox, pos) {
	mass = 0.2;
}

void Water_Cell::update()
{
	if (sink_into(get_cell(0, 1))) return;
	int x = 1;
	if (rand() % 100 < 50) x = -1;
	if (sink_into(get_cell(x, 1))) return;
	if (sink_into(get_cell(-x, 1))) return;
	if (sink_into(get_cell(x, 0))) return;
	if (sink_into(get_cell(-x, 0))) return;
}

sf::Color Water_Cell::get_color()
{
	return sf::Color(35, 137, 218);
}

std::string Water_Cell::str()
{
	return "2";
}