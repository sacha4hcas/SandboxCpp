#include "Air_Cell.h"
#include "Sandbox.h"

//**************** Base_Cell method definition **********************//
Air_Cell::Air_Cell(Sandbox* sandbox, Pos pos) : 
	Gazeous_Cell::Gazeous_Cell(sandbox, pos) 
{
	density = 0;
}

sf::Color Air_Cell::get_color() {
	return sf::Color(0, 0, 0);
}

void Air_Cell::update() {
	//do nothing
}

void Air_Cell::check()
{
	//Air_cell don't get checked
}

std::string Air_Cell::str()
{
	return "0";
}
