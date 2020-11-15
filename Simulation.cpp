#include "Simulation.h"
#include "utils.h"
#include "Sand_Cell.h"
#include "Water_Cell.h"
#include "Lava_Cell.h"
#include "Air_Cell.h"
#include "Stone_Cell.h"
#include <iostream>

using namespace std;

Simulation::Simulation(Sandbox* sandbox, int screen_w, int screen_h, int max_fps) :
	sandbox(sandbox), screen_w(screen_w), screen_h(screen_h), max_fps(max_fps) {
	window = new sf::RenderWindow(sf::VideoMode(screen_w, screen_h), "SFML works!");

	sandbox->scale_to(screen_w, screen_h);
	sandbox->resync();

	saved_time_ms = 0;
	frame_time_ms = 1 / float(max_fps) * 1000;

	cell_maker = []() {return new Sand_Cell(); };
}


void Simulation::update_window()
{
	window->clear();
	update_and_draw();
	if (draw_grid)
		window->draw(sandbox->grid);
	window->display();
}

void Simulation::update_and_draw() {
	switch (draw_technique) {
	case 0:
		window->draw(sandbox->cell_vertex);
		break;
	case 1:
		sandbox->texture.update(sandbox->image);
		window->draw(sandbox->world_sprite);
		break;
	}

}

void Simulation::insert_new_cell()
{

	Pos mouse_pos = sf::Mouse::getPosition(*window);
	//cout << window->getSize().x << "," << window->getSize().y << endl;
	float scale_x = window->getSize().x / float(sandbox->w);
	float scale_y = window->getSize().y / float(sandbox->h);

	int x = mouse_pos.x / scale_x;
	int y = mouse_pos.y / scale_y;
	for (int i = x - r; i < x + r && i < sandbox->w; i++)
		for (int j = y - r; j < y + r && j < sandbox->h; j++)
			if ((i - x) * (i - x) + (j - y) * (j - y) < r * r)
				if (i > 0 && j > 0 && i < sandbox->w && j < sandbox ->h)
					sandbox->insert_cell(cell_maker(), Pos(i, j));
}

void Simulation::change_draw_type()
{
	++draw_technique %= 2;
	sandbox->draw_technique = draw_technique;
	sandbox->resync();
	cout << "changed draw technique to " << (draw_technique == 0 ? "vertex" : "image") << endl;
}


void Simulation::run()
{
	bool running = true;
	bool mouse_pressed = false;
	pause = false;
	Pos mouse_pos;
	draw_grid = false;
	sf::Time delta_time;
	update_window();

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{

			switch (event.type) {
			case sf::Event::Closed:
				running = false;
				window->close();
				break;
			case sf::Event::MouseButtonPressed:
				mouse_pressed = true;
				mouse_pos = sf::Mouse::getPosition(*window);
				std::cout << "(" << mouse_pos.x << ", " << mouse_pos.y << ")" << endl;
				break;
			case sf::Event::MouseButtonReleased:
				mouse_pressed = false;
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::P:
					pause = !pause;
					break;
				case sf::Keyboard::G:
					draw_grid = !draw_grid;
				case sf::Keyboard::Numpad0:
					cell_maker = []() {return new Air_Cell(); };
					break;
				case sf::Keyboard::Numpad1:
					cell_maker = []() {return new Sand_Cell(); };
					break;
				case sf::Keyboard::Numpad2:
					cell_maker = []() {return new Water_Cell(); };
					break; 
				case sf::Keyboard::Numpad3:
					cell_maker = []() {return new Lava_Cell(); };
					break;
				case sf::Keyboard::Numpad4:
					cell_maker = []() {return new Stone_Cell(); };
					break;
				case sf::Keyboard::Tab:
					change_draw_type();
					break;
				case sf::Keyboard::Space:
					(++sandbox->scan_technique) %= 3;
					cout << "scan technique changed to : " << sandbox->scan_technique << endl;
					break;
				case sf::Keyboard::Enter:
					sandbox->update_cells();
					update_window();
					break;
				case sf::Keyboard::Add:
					(r%=1000)++;
					cout << "r=" << r << endl;
					break;
				case sf::Keyboard::Subtract:
					r = (r+999)%1000;
					cout << "r=" << r << endl;
					break;
				}

			}

		}


		if (mouse_pressed)
			insert_new_cell();
		

		if (one_second_clock.getElapsedTime().asMilliseconds() >= 1000) {
			cout << frames << endl;
			frames = 0;
			one_second_clock.restart();
		}
		if (delta_clock.getElapsedTime().asMilliseconds() - saved_time_ms >= frame_time_ms) {
			saved_time_ms += frame_time_ms;
			if (!pause)
				sandbox->update_cells();
			update_window();
			frames++;
		}


	}
}