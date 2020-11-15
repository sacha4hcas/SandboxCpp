#include "Sandbox.h"
#include <iostream>
#include "Air_Cell.h"

using namespace std;

//**************** Sandbox method definition **********************//
Sandbox::Sandbox(int w, int h) : w(w), h(h),
cell_array(Cell_Matrix(w, Cell_Array(h, nullptr))),
cell_vertex(sf::VertexArray(sf::Quads, w* h * 4)),
grid(sf::VertexArray(sf::Lines, 2 * w + 2 * h))
{

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			cell_array[i][j] = new Air_Cell(this, Pos(i, j));

	int k = 0;
	scale_to(w, h);

	image.create(w, h);
	texture.loadFromImage(image);
	texture.setSmooth(true);
	world_sprite.setTexture(texture);
}

void Sandbox::swap_cells(Cell* cell1, Cell* cell2) {
	Cell* temp = cell1;
	cell_array[cell1->x][cell1->y] = cell2;
	cell_array[cell2->x][cell2->y] = temp;
	swap(cell1->x, cell2->x);
	swap(cell1->y, cell2->y);

	cell1->check();
	cell2->check();

	update_cell_color(cell1);
	update_cell_color(cell2);
}


void Sandbox::insert_cell(Cell* cell, Pos pos)
{
	cell->x = pos.x;
	cell->y = pos.y;
	cell->sandbox = this;
	delete cell_array[pos.x][pos.y];
	cell_array[pos.x][pos.y] = cell;
	update_cell_color(cell);
}

void Sandbox::resync()
{
	for (auto& cells : cell_array)
		for (auto cell : cells)
			update_cell_color(cell);
}

void Sandbox::update_cell_color(Cell* cell) {
	switch (draw_technique) {
	case 0:
		cell->update_color(cell_vertex, h);
		break;
	case 1:
		cell->update_color(image, h);
		break;
	}
}

void Sandbox::update_cell(Cell* cell)
{
	if (!cell->checked) {
		cell->update();
	}
}

void Sandbox::update_cells() {
	switch (scan_technique) {
	case 0: update_cells_1();
		break;
	case 1: update_cells_2();
		break;
	case 2: update_cells_3();
		break;
	}
}

void Sandbox::update_cells_1()
{
	int cycle = scan++ % 4;

	if (cycle == 0) {
		for (auto it = cell_array.begin(); it != cell_array.end(); it++)
			for (auto jt = it->begin(); jt != it->end(); jt++)
				update_cell((*jt));
	}
	else if (cycle == 1) {
		for (auto it = cell_array.begin(); it != cell_array.end(); it++)
			for (auto jt = it->rbegin(); jt != it->rend(); jt++)
				update_cell((*jt));
	}
	else if (cycle == 2) {
		for (auto it = cell_array.rbegin(); it != cell_array.rend(); it++)
			for (auto jt = it->begin(); jt != it->end(); jt++)
				update_cell((*jt));
	}
	else {
		for (auto it = cell_array.rbegin(); it != cell_array.rend(); it++)
			for (auto jt = it->rbegin(); jt != it->rend(); jt++)
				update_cell((*jt));
	}

	uncheck_cells();
}

void Sandbox::update_cells_2()
{
	int cycle = scan++ % 2;
	if (cycle == 0) {
		for (auto it = cell_array.begin(); it != cell_array.end(); it++)
			for (auto jt = it->begin(); jt != it->end(); jt++)
				update_cell((*jt));
	}
	else {
		for (auto it = cell_array.begin(); it != cell_array.end(); it++)
			for (auto jt = it->rbegin(); jt != it->rend(); jt++)
				update_cell((*jt));
	}
	uncheck_cells();
}

void Sandbox::update_cells_3()
{
	int cycle = scan++ % 2;
	if (cycle == 0) {
		for (auto it = cell_array.begin(); it != cell_array.end(); it++)
			for (auto jt = it->begin(); jt != it->end(); jt++)
				update_cell((*jt));
	}
	else if (cycle == 2) {
		for (auto it = cell_array.rbegin(); it != cell_array.rend(); it++)
			for (auto jt = it->begin(); jt != it->end(); jt++)
				update_cell((*jt));
	}
	uncheck_cells();
}

void Sandbox::update_cells_4() {
	int i = 0;
	int j = 0;
	
	int checked_i = 0;
	int checked_j = 1;

	int cycle_ij = 0;

	while (true) {
		if (cycle_ij % 2 == 0)
			for (i=checked_i;i<w;i++)
				update_cell(cell_array[i][j]);
		
		else
			for (j = checked_j; j < h; j++)
				update_cell(cell_array[i][j]);

		cycle_ij++;
	}
}

void Sandbox::uncheck_cells() {
	for (auto& cells : cell_array)
		for (auto cell : cells)
			cell->checked = false;
}

Cell* Sandbox::get_cell_by_pixel(Pos pos, float x_scale, float y_scale)
{
	int x_cell = pos.x / x_scale;
	int y_cell = pos.y / y_scale;

	return cell_array[x_cell][y_cell];
}

void Sandbox::scale_to(int _w, int _h)
{
	int k = 0;
	float scale_x = _w / float(w);
	float scale_y = _h / float(h);

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			float x_step = i * scale_x;
			float y_step = j * scale_y;
			cell_vertex[k].position = fPos(x_step, y_step); k++;
			cell_vertex[k].position = fPos(x_step, y_step + scale_y); k++;
			cell_vertex[k].position = fPos(x_step + scale_x, y_step + scale_y); k++;
			cell_vertex[k].position = fPos(x_step + scale_x, y_step); k++;
		}
	}
	for (int i = 0; i < w * 2; i += 2) {
		grid[i].position = fPos(i / 2 * scale_x, 0);
		grid[i + 1].position = fPos(i / 2 * scale_x, h * scale_y);
	}

	for (int i = 0; i < h * 2; i += 2) {
		grid[i + w * 2].position = fPos(0, i / 2 * scale_y);
		grid[i + w * 2 + 1].position = fPos(w * scale_y, i / 2 * scale_y);
	}

	world_sprite.scale(scale_x, scale_y);

}