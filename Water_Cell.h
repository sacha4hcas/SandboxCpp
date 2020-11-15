#pragma once
#include "Liquid_Cell.h"

class Water_Cell : public Liquid_Cell {
public:
	Water_Cell(Sandbox* sandbox = nullptr, Pos pos = Pos(0, 0));
	
	sf::Color get_color();
	virtual std::string str();
	void check();
};