#pragma once
#include "Sandbox.h"
#include <functional>

class Simulation {
public:
	Sandbox* sandbox = nullptr;
	int screen_w = 10;
	int screen_h = 10;
	sf::RenderWindow* window;
	int max_fps = 60;
	int frames = 0;
	sf::Clock one_second_clock;
	sf::Clock delta_clock;
	bool pause = false;
	std::function<Base_Cell* (void)> cell_maker;
	bool draw_grid = true;
	float saved_time_ms;
	float frame_time_ms;

	Simulation(Sandbox* sandbox, int screen_w = 420, int screen_h = 420, int max_fps = 60);
	void run();
	void update_window();
	void insert_new_cell();

};