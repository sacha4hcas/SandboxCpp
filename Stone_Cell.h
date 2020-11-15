#pragma once
#include "Solid_Cell.h"
class Stone_Cell : public Solid_Cell
{
public:
    Stone_Cell(Sandbox* = nullptr, Pos = Pos(0,0));
    void update();
    sf::Color get_color();
    std::string str();
};

