#include "Base_Cell.h"
#include "Sandbox.h"

//**************** Base_Cell method definition **********************//
Base_Cell::Base_Cell(Sandbox* sandbox, Pos pos) :
	sandbox(sandbox), x(pos.x), y(pos.y) {}

Pos Base_Cell::get_pos() {
	return Pos(x, y);
}

sf::Color Base_Cell::get_color() {
	return sf::Color(0, 0, 0);
}

void Base_Cell::update() {
	//do nothing
}
void Base_Cell::update_color(sf::VertexArray& cell_vertex, int h) {
	sf::Color color = this->get_color();
	int k = 4 * (x * h + y);
	cell_vertex[k].color = color;
	cell_vertex[k + 1].color = color;
	cell_vertex[k + 2].color = color;
	cell_vertex[k + 3].color = color;
}

bool Base_Cell::sink_into(Base_Cell* cell) {
	if (cell && cell->fluid && cell->mass < this->mass) {
		sandbox->swap_cells(this, cell);
		return true;
	}
	return false;
}

Base_Cell* Base_Cell::get_cell(int i, int j) {
	if (0 <= x + i && x + i < sandbox->w && 0 <= y + j && y + j < sandbox->h)
		return sandbox->cell_array[x + i][y + j];
	return nullptr;
}

std::string Base_Cell::str()
{
	return "0";
}
