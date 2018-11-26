#pragma once
#include <vector>
#include "Node.h"
class Grid
{
public:
	Grid(int height, int width);
	void DrawGrid(sf::RenderWindow *window);
	inline const std::vector<Node*> returnGrid() const { return nodes; }
	Node * returnNode(int x, int y);
	~Grid();
private:
	void CalculateNeighbours();
	void CreateGrid();
	void GenerateMaze();
	int _height, _width;
	std::vector<Node*> nodes;
	std::vector<sf::RectangleShape> walls;
};

