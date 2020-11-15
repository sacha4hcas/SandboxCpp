#include <SFML/Graphics.hpp>
#include "Simulation.h"


int main()
{
	Simulation(new Sandbox(400, 200), 1600, 800, 144).run();

	return 0;
}




