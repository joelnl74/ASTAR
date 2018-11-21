#include "Grid.h"

const int tileWdith = 64;
const int tileHeight = 64;

Grid::Grid(int width, int height)
{
	_width = width;
	_height = height;

	CreateGrid();
	CalculateNeighbours();
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
			node->shape.setSize(sf::Vector2f(64, 64));
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
		window->draw(node->shape);
	}
}