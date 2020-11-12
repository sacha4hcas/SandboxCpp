#include "Sand_Cell.h"

//**************** Sand_Cell method definition **********************//
Sand_Cell::Sand_Cell(Sandbox* sandbox, Pos pos) :
	Base_Cell::Base_Cell(sandbox, pos) {
	mass = 0.8;
}

void Sand_Cell::update() {
	if (sink_into(get_cell(0, 1))) return;
	int x = 1;
	if (rand() % 100 < 50) x = -1;
	if (sink_into(get_cell(x, 1))) return;
	if (sink_into(get_cell(-x, 1))) return;
}

sf::Color Sand_Cell::get_color() {
	return sf::Color(76, 70, 50);
}

std::string Sand_Cell::str()
{
	return "1";
}