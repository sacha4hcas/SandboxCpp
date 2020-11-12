#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

//**************** Types declarations **********************//
class Sandbox; class Base_Cell; class Sand_Cell; class Water_Cell; class Simulation; class Sandbox_Shape;
typedef std::vector<Base_Cell*> Cell_Array;
typedef std::vector<Cell_Array> Cell_Matrix;
typedef sf::Vector2i Pos;
typedef sf::Vector2f fPos;