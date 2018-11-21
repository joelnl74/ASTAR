#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Astar.h"
int main()
{
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");
	Grid *grid = new Grid(8,8);
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

	return 0;
}