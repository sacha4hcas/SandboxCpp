#pragma once
#include "Cell.h"

class Sandbox {
public:
	int w = 10;
	int h = 10;
	Cell_Matrix cell_array;
	sf::VertexArray cell_vertex;
	sf::VertexArray grid;

	sf::Image image;
	sf::Texture texture;
	sf::Sprite world_sprite;

	int draw_technique = 0;
	int scan = 0;
	int scan_technique = 2;

	Sandbox(int w, int h);
	void swap_cells(Cell*, Cell*);
	void insert_cell(Cell*, Pos pos);
	void resync();
	void update_cell_color(Cell* cell);
	void update_cell(Cell*);
	void update_cells_1();
	void update_cells();
	void update_cells_2();
	void update_cells_3();
	void update_cells_4();
	void uncheck_cells();
	Cell* get_cell_by_pixel(Pos pos, float x_scale, float y_scale);
	void scale_to(int, int);
};