#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

//**************** Types declarations **********************//
class Cell;
class Sandbox;
typedef std::vector<Cell*> Cell_Array;
typedef std::vector<Cell_Array> Cell_Matrix;
typedef sf::Vector2i Pos;
typedef sf::Vector2f fPos;
enum class state {
	liquid = 0,
	solid = 1,
	gazeous = 2
};