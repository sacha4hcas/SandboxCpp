#pragma once
#include "Types_Declarations.h"

class Base_Cell {
public:
	int x = 0;
	int y = 0;
	Sandbox* sandbox = nullptr;
	bool checked = false;
	bool fluid = true;
	float viscosity = 0;
	float mass = 0;

	Base_Cell(Sandbox* sandbox = nullptr, Pos pos = Pos(0, 0));
	virtual sf::Color get_color();
	Pos get_pos();
	virtual void update();
	void update_color(sf::VertexArray& cell_vertex, int);
	virtual bool sink_into(Base_Cell* cell);
	Base_Cell* get_cell(int i, int j);
	virtual std::string str();
};
