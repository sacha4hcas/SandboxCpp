#include "Simulation.h"
#include "Str.h"
#include "Sand_Cell.h"
#include "Water_Cell.h"
#include <iostream>

using namespace std;

Simulation::Simulation(Sandbox* sandbox, int screen_w, int screen_h, int max_fps) :
	sandbox(sandbox), screen_w(screen_w), screen_h(screen_h), max_fps(max_fps) {
	window = new sf::RenderWindow(sf::VideoMode(screen_w, screen_h), "SFML works!");

	sandbox->scale_to(screen_w, screen_h);
	sandbox->sync_vertex();

	saved_time_ms = 0;
	frame_time_ms = 1 / float(max_fps) * 1000;

	cell_maker = []() {return new Sand_Cell(); };

	cout << str(sandbox->cell_vertex, sandbox->w, sandbox->h) << endl << endl;
	cout << str(sandbox->cell_array) << endl << endl;
}




void Simulation::update_window()
{
	window->clear();
	window->draw(sandbox->cell_vertex);
	if (draw_grid)
		window->draw(sandbox->grid);
	window->display();


}

void Simulation::insert_new_cell()
{
	Pos mouse_pos = sf::Mouse::getPosition(*window);
	//cout << window->getSize().x << "," << window->getSize().y << endl;
	float scale_x = window->getSize().x / float(sandbox->w);
	float scale_y = window->getSize().y / float(sandbox->h);
	Pos cell = sandbox->get_cell_by_pixel(mouse_pos, scale_x, scale_y)->get_pos();
	sandbox->insert_cell(cell_maker(), cell);
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

				case sf::Keyboard::Numpad1:
					cell_maker = []() {return new Sand_Cell(); };
					break;
				case sf::Keyboard::Numpad2:
					cell_maker = []() {return new Water_Cell(); };
					break;
				case sf::Keyboard::Numpad3:
					sandbox->update_cells();
					update_window();
					cout << str(sandbox->cell_array) << endl;
					sandbox->sync_vertex();
					cout << str(sandbox->cell_vertex, sandbox->w, sandbox->h) << endl;
					break;
				}

			}

		}


		if (mouse_pressed)
			insert_new_cell();
		//update_window();

		if (!pause && one_second_clock.getElapsedTime().asMilliseconds() >= 1000) {
			cout << frames << endl;
			frames = 0;
			one_second_clock.restart();
		}
		if (!pause && delta_clock.getElapsedTime().asMilliseconds() - saved_time_ms >= frame_time_ms) {
			saved_time_ms += frame_time_ms;
			sandbox->update_cells();
			update_window();
			frames++;
		}


	}
}