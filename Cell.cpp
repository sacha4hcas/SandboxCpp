#include "Cell.h"
#include "Sandbox.h"

Cell::Cell(Sandbox* sandbox, Pos pos) :
	sandbox(sandbox), x(pos.x), y(pos.y) {}

Pos Cell::get_pos()
{
	return Pos(x, y);
}

void Cell::update_color(sf::VertexArray& cell_vertex, int h)
{
	sf::Color color = this->get_color();
	int k = 4 * (x * h + y);
	cell_vertex[k].color = color;
	cell_vertex[k + 1].color = color;
	cell_vertex[k + 2].color = color;
	cell_vertex[k + 3].color = color;
}

void Cell::update_color(sf::Image& cell_image, int)
{
	cell_image.setPixel(x, y, get_color());
}

bool Cell::sink_into(Cell* cell)
{
	if (cell && !cell->checked && cell->fluid && cell->state != state::solid && cell->density < this->density) {
		sandbox->swap_cells(this, cell);
		return true;
	}
	return false;
}

void Cell::check()
{
	checked = true;
}

Cell* Cell::get_cell(int i, int j)
{
	if (0 <= x + i && x + i < sandbox->w && 0 <= y + j && y + j < sandbox->h)
		return sandbox->cell_array[x + i][y + j];
	return nullptr;
}
