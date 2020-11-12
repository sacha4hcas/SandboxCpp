#pragma once
#include "Base_Cell.h"

class Water_Cell : public Base_Cell {
public:
	Water_Cell(Sandbox* sandbox = nullptr, Pos pos = Pos(0, 0));
	void update();
	sf::Color get_color();
	virtual std::string str();
};