#pragma once
#include "Solid_Cell.h"

class Sand_Cell : public Solid_Cell {
public:
	Sand_Cell(Sandbox* sandbox = nullptr, Pos pos = Pos(0, 0));
	sf::Color get_color();
	virtual std::string str();
	void check();
};