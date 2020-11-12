#include "Sandbox.h"


using namespace std;

//**************** Sandbox method definition **********************//
Sandbox::Sandbox(int w, int h) : w(w), h(h),
cell_array(Cell_Matrix(w, Cell_Array(h, nullptr))),
cell_vertex(sf::VertexArray(sf::Quads, w* h * 4)),
grid(sf::VertexArray(sf::Lines, 2 * w + 2 * h))
{

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			cell_array[i][j] = new Base_Cell(this, Pos(i, j));

	int k = 0;
	scale_to(w, h);
}

void Sandbox::swap_cells(Base_Cell* cell1, Base_Cell* cell2) {
	Base_Cell* temp = cell1;
	cell_array[cell1->x][cell1->y] = cell2;
	cell_array[cell2->x][cell2->y] = temp;
	swap(cell1->x, cell2->x);
	swap(cell1->y, cell2->y);

	cell1->update_color(this->cell_vertex, this->h);
	cell2->update_color(this->cell_vertex, this->h);
}

void Sandbox::insert_cell(Base_Cell* cell, Pos pos)
{
	cell->x = pos.x;
	cell->y = pos.y;
	cell->sandbox = this;
	cell_array[pos.x][pos.y] = cell;
	cell->update_color(this->cell_vertex, this->h);
}

void Sandbox::sync_vertex()
{
	for (auto& cells : cell_array)
		for (auto cell : cells)
			cell->update_color(cell_vertex, this->h);
}

void Sandbox::update_cell(Base_Cell* cell)
{
	if (!cell->checked) {
		cell->update();
		cell->checked = true;
	}
}

void Sandbox::update_cells()
{
	int rand = std::rand() % 101;
	if (rand > 75) {
		for (auto it = cell_array.begin(); it != cell_array.end(); it++)
			for (auto jt = it->begin(); jt != it->end(); jt++)
				update_cell((*jt));
	}
	else if (rand > 50) {
		for (auto it = cell_array.begin(); it != cell_array.end(); it++)
			for (auto jt = it->rbegin(); jt != it->rend(); jt++)
				update_cell((*jt));
	}
	else if (rand > 25) {
		for (auto it = cell_array.rbegin(); it != cell_array.rend(); it++)
			for (auto jt = it->begin(); jt != it->end(); jt++)
				update_cell((*jt));
	}
	else {
		for (auto it = cell_array.rbegin(); it != cell_array.rend(); it++)
			for (auto jt = it->rbegin(); jt != it->rend(); jt++)
				update_cell((*jt));
	}

	for (auto& cells : cell_array)
		for (auto cell : cells)
			cell->checked = false;
}

Base_Cell* Sandbox::get_cell_by_pixel(Pos pos, float x_scale, float y_scale)
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

}