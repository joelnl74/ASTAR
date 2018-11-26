#include "Grid.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stack>
const int tileWdith = 25;
const int tileHeight = 25;

Grid::Grid(int width, int height)
{
	_width = width;
	_height = height;

	CreateGrid();
	CalculateNeighbours();
	GenerateMaze();
}
Grid::~Grid()
{
	for (auto node : nodes)
	{
		delete node;
	}
	nodes.clear();
}
void Grid::CreateGrid()
{
	int i = 0;
	int j = 0;
	for (int x = 0; x < _width; x++)
	{
		for (int y = 0; y < _height; y++)
		{
			Node *node = new Node();
			node->x = x;
			node->y = y;

			node->shape.setPosition(node->x * tileWdith + j, node->y * tileHeight + i);
			node->shape.setSize(sf::Vector2f(tileWdith, tileHeight));
			node->spritePositionX = node->x * tileWdith + j;
			node->spritePositionY = node->y * tileHeight + i;
			node->shape.setFillColor(sf::Color::White);
			nodes.push_back(node);
			i += 5;
			if (y == _height - 1)
				i = 0;
		}
		j += 5;
	}
}
void Grid::CalculateNeighbours()
{
	for (Node *nodeTO : nodes)
	{
		for (Node * node : nodes)
		{
			if (node->x == nodeTO->x + 1 && node->y == nodeTO->y)
			{
				nodeTO->neighBours.emplace(direction::right, node);
			}
			else if (node->x == nodeTO->x - 1 && node->y == nodeTO->y)
			{
				nodeTO->neighBours.emplace(direction::left, node);
			}
			else if (node->y == nodeTO->y + 1 && node->x == nodeTO->x)
			{
				nodeTO->neighBours.emplace(direction::bottem, node);
			}
			else if (node->y == nodeTO->y - 1 && node->x == nodeTO->x)
			{
				nodeTO->neighBours.emplace(direction::up, node);
			}
		}
	}
}
void Grid::DrawGrid(sf::RenderWindow *window)
{
	for (auto node : nodes)
	{
		if (node->bObstacle)
			node->shape.setFillColor(sf::Color::Blue);
		window->draw(node->shape);
	}
	for (auto wall : walls)
	{
		window->draw(wall);
	}
}
Node * Grid::returnNode(int x, int y)
{
	for (Node *node : nodes)
	{
		if (node->x == x && node->y == y)
		{
			return node;
		}
	}
	return __nullptr;
}
void Grid::GenerateMaze()
{
	std::srand(time(NULL));
	int x = rand() % _width;
	int y = rand() % _height;

	std::stack<Node*> nodesToCheck;

	Node *n = returnNode(x , y);
	Node *a = nullptr;
	nodesToCheck.push(n);

	while (!nodesToCheck.empty())
	{
		n->visitedMazeGeneration = true;
		direction dir;
		for (auto node : n->neighBours)
		{
			if (node.second->visitedMazeGeneration == false)
			{
				dir = node.first;
				a = node.second;
				nodesToCheck.push(a);
				break;
			}
			else
			{
				a = nullptr;
			}
		}
		if (a == nullptr)
		{
			nodesToCheck.pop();
		}
		else
		{
			n->neighBours.clear();
			n->neighBours.emplace(dir, a);

			sf::RectangleShape shape;

			int posX = 0;
			int posY = 0;
			switch (dir)
			{
				case direction::bottem:
					posY = n->spritePositionY + 25;
					posX = n->spritePositionX;
					shape.setSize(sf::Vector2f(25, 5));
					break;
				case direction::up:
					posY = n->spritePositionY - 5;
					posX = n->spritePositionX;
					shape.setSize(sf::Vector2f(25, 5));
					break;
				case direction::left:
					posY = n->spritePositionY;
					posX = n->spritePositionX - 5;
					shape.setSize(sf::Vector2f(5, 25));
					break;
				case direction::right:
					posY = n->spritePositionY;
					posX = n->spritePositionX + 25;
					shape.setSize(sf::Vector2f(5, 25));
					break;
			}
			shape.setPosition(sf::Vector2f(posX, posY));
			shape.setFillColor(sf::Color::Green);
			walls.push_back(shape);

		n = a;
		}

		if (nodesToCheck.empty())
			break;
	}
}