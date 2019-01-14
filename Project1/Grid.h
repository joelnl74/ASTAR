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
	void CreateRandomPathWay(Grid &grid);
	~Grid();
private:
	void CalculateNeighbours();
	void CreateGrid();
	void GenerateMaze();
	void CreateVisual(direction dir, Node *currentNode, Node *neighbour, sf::Color color);
	void CreateNewPathWays(Node* node);
	Node *getRandomNeighbour(Node *node);
	int _height, _width;
	std::vector<Node*> nodes;
	std::vector<sf::RectangleShape> walls;
};

