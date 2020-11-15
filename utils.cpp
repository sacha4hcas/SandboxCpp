#include "utils.h"
#include "Cell.h"

//**************** Str func **********************//
std::string str(Cell_Matrix& cell_array) {
	std::string res = "";
	std::string line = "";
	for (auto i = 0; i < cell_array.size(); i++) {
		line = "";
		for (auto j = 0; j < cell_array[i].size(); j++)
			line += cell_array[i][j]->str() + "|";
		res += line + "\n";
	}
	return res;
}

std::string str(sf::VertexArray& cell_vertex, int w, int h) {
	std::string res = "";
	std::string line = "";
	sf::Vertex vertex;
	int k = 0;
	for (auto i = 0; i < w; i++) {
		line = "";
		for (auto j = 0; j < h; j++) {
			line += "[";
			for (auto l = 0; l < 4; l++) {
				vertex = cell_vertex[k++];
				line += "(" + std::to_string(vertex.position.x).substr(0, 1) + "," + std::to_string(vertex.position.y).substr(0, 1) + ")" + std::to_string(vertex.color.r) + " ";
			}
			line += "]\n";

		}
		res += line + "\n";
	}
	return res;
}