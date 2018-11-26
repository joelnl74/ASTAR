#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
enum direction
{
	right = 0x08,
	left = 0x02,
	up = 0x01,
	bottem = 0x04,
	visited = 0x10,
	initial = up | right | left | bottem,
};

struct Node
{
	int x, y;										 //Coordinates
	bool bObstacle = false;							 //Is the node an obstruction?
	bool bVisited = false;						     //Have we searched this node?
	float fGlobalGoal;							     //Distance to goal so far
	float fLocalGoal;							     //Distance to goal if we took
	std::unordered_map<direction, Node*> neighBours; //Neighbours
	Node * parent;                                   //Node connecting to this node

	float spritePositionX, spritePositionY;

	bool visitedMazeGeneration = false;
	
	//sfml stuff
	sf::Color color;
	sf::RectangleShape shape;
};
