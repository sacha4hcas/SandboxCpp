#pragma once
#include "Base_Cell.h"

class Sandbox {
public:
	int w = 10;
	int h = 10;
	Cell_Matrix cell_array;
	sf::VertexArray cell_vertex;
	sf::VertexArray grid;

	Sandbox(int w, int h);
	void swap_cells(Base_Cell*, Base_Cell*);
	void insert_cell(Base_Cell*, Pos pos);
	void sync_vertex();
	void update_cell(Base_Cell*);
	void update_cells();
	Base_Cell* get_cell_by_pixel(Pos pos, float x_scale, float y_scale);
	void scale_to(int, int);
};