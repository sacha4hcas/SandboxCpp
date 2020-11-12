#pragma once
#include "Base_Cell.h"

class Sand_Cell : public Base_Cell {
public:
	Sand_Cell(Sandbox* sandbox = nullptr, Pos pos = Pos(0, 0));
	void update();
	sf::Color get_color();
	virtual std::string str();
};