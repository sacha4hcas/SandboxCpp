#pragma once
#include "Types_Declarations.h"

class Cell
{
public:
	int x = 0;
	int y = 0;
	Sandbox* sandbox = nullptr;
	bool checked = false;

	bool fluid = true;
	float viscosity = 0;
	float density = 0;
	state state;


	Cell(Sandbox* sandbox = nullptr, Pos pos = Pos(0, 0));
	
	Pos get_pos();
	void update_color(sf::VertexArray& cell_vertex, int);
	void update_color(sf::Image& cell_image, int);
	bool sink_into(Cell* cell);
	Cell* get_cell(int i, int j);

	virtual void update() = 0;
	virtual void check();
	virtual std::string str() = 0;
	virtual sf::Color get_color() = 0;
};

