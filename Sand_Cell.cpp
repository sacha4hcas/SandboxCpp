#include "Sand_Cell.h"

//**************** Sand_Cell method definition **********************//
Sand_Cell::Sand_Cell(Sandbox* sandbox, Pos pos) : Solid_Cell::Solid_Cell(sandbox, pos) {
	density = 1.6;
	fluid = true;
}


sf::Color Sand_Cell::get_color() {
	return sf::Color(76, 70, 50);
}

std::string Sand_Cell::str()
{
	return "1";
}

void Sand_Cell::check()
{
	checked = true;
}
