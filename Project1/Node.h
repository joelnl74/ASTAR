#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum direction
{
	right,
	left,
	up,
	bottem
};

struct Node
{
	int x, y;               //Coordinates
	bool bObstacle = false; //Is the node an obstruction?
	bool bVisited = false;  //Have we searched this node?
	float fGlobalGoal;      //Distance to goal so far
	float fLocalGoal;       //Distance to goal if we took
	std::unordered_map<direction, Node*> neighBours; //Neighbours
	Node * parent;                                   //Node connecting to this node
	
	//sfml stuff
	sf::Color color;
	sf::RectangleShape shape;
};
