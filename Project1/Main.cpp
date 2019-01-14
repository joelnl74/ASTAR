#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Astar.h"
int main()
{
	//1000 x 1000 grid
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SFML works!");
	//set frame limit
	window->setFramerateLimit(30);
	//Grid size can be adjusted here
	Grid *grid = new Grid(33,33);
	//Create random extra path(s)
	grid->CreateRandomPathWay(*grid);
	//A star trough the maze
	Astar astar;
	astar.SolveAStar(grid);
	astar.SetNodeColor();
	//Gameloop
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
	//cleanup
	delete grid;
	delete window;
	return 0;
}