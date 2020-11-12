#include <SFML/Graphics.hpp>
#include "Simulation.h"


int main()
{
	Simulation(new Sandbox(1000, 500), 1600, 800, 10000).run();

	return 0;
}




