#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <functional>
#include <time.h>
#include <iostream>
class Sandbox_Shape : sf::Transformable {
public:
    sf::VertexArray vertex_array;
    int w;
    int h;
    float scale_x;
    float scale_y;

    Sandbox_Shape(int w, int h, float scale_x = 1, float scale_y = 1);
    void set_cell_color(sf::Vector2i pos, sf::Color);
    void scale_to(int w_, int h_);

};

Sandbox_Shape::Sandbox_Shape(int w, int h, float scale_x, float scale_y)
    : vertex_array(sf::Quads, w* h * 4), w(w), h(h), scale_x(scale_x), scale_y(scale_y)
{

}

void Sandbox_Shape::set_cell_color(sf::Vector2i pos, sf::Color color)
{
    int k = 4 * (pos.x + w * pos.y);
    vertex_array[k].color = color;
    vertex_array[k + 1].color = color;
    vertex_array[k + 2].color = color;
    vertex_array[k + 3].color = color;
}



void Sandbox_Shape::scale_to(int _w, int _h)
{
    int k = 0;
    scale_x = _w / float(w);
    scale_y = _h / float(h);

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            float x_step = i * scale_x;
            float y_step = j * scale_y;
            vertex_array[k].position = sf::Vector2f(x_step, y_step); k++;
            vertex_array[k].position = sf::Vector2f(x_step, y_step + scale_y); k++;
            vertex_array[k].position = sf::Vector2f(x_step + scale_x, y_step + scale_y); k++;
            vertex_array[k].position = sf::Vector2f(x_step + scale_x, y_step); k++;
        }
    }
}