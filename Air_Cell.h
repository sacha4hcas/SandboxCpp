#pragma once
#include "Types_Declarations.h"
#include "Gazeous_Cell.h"

class Air_Cell : public Gazeous_Cell {
public:

	Air_Cell(Sandbox* sandbox = nullptr, Pos pos = Pos(0, 0));
	sf::Color get_color();
	void update();
	void check();
	std::string str();
};
