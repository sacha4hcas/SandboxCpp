#include "Lava_Cell.h"

//**************** Lava_Cell method definition **********************//
Lava_Cell::Lava_Cell(Sandbox* sandbox, Pos pos) :
	Liquid_Cell::Liquid_Cell(sandbox, pos) {
	density = 3;
	viscosity = 0.5;
}



sf::Color Lava_Cell::get_color()
{
	return sf::Color(207, 16, 32);
}

std::string Lava_Cell::str()
{
	return "3";
}
