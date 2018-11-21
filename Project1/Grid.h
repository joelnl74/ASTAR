#pragma once
#include <vector>
#include "Node.h"
class Grid
{
public:
	Grid(int height, int width);
	void DrawGrid(sf::RenderWindow *window);
	inline const std::vector<Node*> returnGrid() const { return nodes; }
	~Grid();
private:
	void CalculateNeighbours();
	void CreateGrid();
	int _height, _width;
	std::vector<Node*> nodes;
};

