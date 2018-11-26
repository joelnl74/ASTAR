#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Astar.h"
int main()
{
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SFML works!");
	window->setFramerateLimit(30);
	Grid *grid = new Grid(5,5);
	Astar astar;
	astar.SolveAStar(grid);
	astar.SetNodeColor();
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		//Render here
		grid->DrawGrid(window);
		window->display();
	}
	delete grid;
	delete window;
	return 0;
}