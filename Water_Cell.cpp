#include "Water_Cell.h"

//**************** Water_Cell method definition **********************//
Water_Cell::Water_Cell(Sandbox* sandbox, Pos pos) :
	Liquid_Cell::Liquid_Cell(sandbox, pos) {
	density = 1;
}

sf::Color Water_Cell::get_color()
{
	return sf::Color(35, 137, 218);
}

std::string Water_Cell::str()
{
	return "2";
}

void Water_Cell::check()
{
	checked = true;
}
