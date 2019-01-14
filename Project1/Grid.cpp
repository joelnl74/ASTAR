#include "Grid.h"       // grid
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stack>        //stack
#include "Astar.h"      //astar

//Const variables
const int tileWdith = 25;
const int tileHeight = 25;

//Constructor
Grid::Grid(int width, int height)
{
	_width = width;
	_height = height;
	//Create a grid
	CreateGrid();
	//Calculate neighbours for all tiles
	CalculateNeighbours();
	//generate a maze
	GenerateMaze();
}
//Destructor
Grid::~Grid()
{
	for (auto node : nodes)
	{
		delete node;
	}
	nodes.clear();
}
//Create a grid and there visuals
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
//Calculate the neighbours of each node in the grid
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
//Draw the grid onto the screen
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
//Return a node on the grid
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
Node * Grid::getRandomNeighbour(Node *node)
{
	std::srand(time(NULL));
	int randomNumber = rand() % node->neighBours.size() + 0;

	return  node;
}
//Generate a random maze
void Grid::GenerateMaze()
{
	std::srand(time(NULL));
	int randomNumber = rand() % nodes.size() + 0;

	std::stack<Node*> nodesToCheck;

	Node *n = nodes[randomNumber];
	Node *a = nullptr;

	std::unordered_map<direction, Node*> NotVisited; //Not visited neighbours
	
	nodesToCheck.push(n);

	while (!nodesToCheck.empty())
	{
		n->visitedMazeGeneration = true;
		direction dir;

		NotVisited.clear();

		//Get a collection of all the nodes that have not been visited so we can select one at random from this list
		for (auto node : n->neighBours)
		{
			if (node.second->visitedMazeGeneration == false)
				NotVisited.emplace(node);
		}
		//Visit a random neighbour
		if (NotVisited.size() > 0)
		{
			int counter = 0;
			randomNumber = rand() % NotVisited.size() + 0;
			for (auto x : NotVisited)
			{
				if (counter == randomNumber)
				{
					a = x.second;
					dir = x.first;
					nodesToCheck.push(a);
				}
				counter++;
			}
		}
		else
		{
			a = nullptr;
		}
		//if current node has no neighbour pop it from the stack and check the new node
		if (a == nullptr)
		{
			nodesToCheck.pop();
			if (nodesToCheck.size() > 0)
				n = nodesToCheck.top();
			else
				break;
		}
		else
		{
			//Create a pathway between 2 nodes
			n->pathWays.emplace(dir, a);
			//Create the visual
			CreateVisual(dir, n, a, sf::Color::Green);

		n = a;
		}

		if (nodesToCheck.empty())
			break;
	}
}
//Create one or more extra random path in the maze so we have multiple paths that lead to rome :P
void Grid::CreateRandomPathWay(Grid &grid)
{
	//get all nodes that from a path
	std::vector<Node*> astarPath;

	direction dir;

	Node* nextNode = nullptr;
	Node* neighbour = nullptr;

	Astar astar;
	astar.SolveAStar(&grid);

	Node *currentNode = astar.end;

	//Get the astar path trough the maze
	while (currentNode->parent != nullptr)
	{
		astarPath.push_back(currentNode);
		currentNode = currentNode->parent;
	}
	int randomNumber = rand() % astarPath.size()  + 0;
	//get a random node on the grid
	Node *node = astarPath[randomNumber];

	//Get a neighbour node to the random selected node
	if (randomNumber < astarPath.size() - 1)
		nextNode = astarPath[randomNumber + 1];
	else
		nextNode = astarPath[randomNumber - 1];

	//Caculate last node for creating a L shaped room
	Node * lastNode = nullptr;
	if (nextNode->x < _height - 1 && node->x == nextNode->x)
	{
		lastNode = returnNode(nextNode->x + 1, nextNode->y);
	}
	else if(nextNode->x >= _height - 1 && node->x == nextNode->x)
	{
		lastNode = returnNode(nextNode->x - 1, nextNode->y);
	}
	else if (nextNode->y < _width - 1 && node->y == nextNode->y)
	{
		lastNode = returnNode(nextNode->x, nextNode->y + 1);
	}
	else if (nextNode->y >= _width - 1  && node->y == nextNode->y)
	{
		lastNode = returnNode(nextNode->x, nextNode->y - 1);
	}
	//Create pathways for each direction
	CreateNewPathWays(node);
	CreateNewPathWays(nextNode);
	CreateNewPathWays(lastNode);
}
void Grid::CreateNewPathWays(Node* node)
{
	//All neighbours of a node that are not a pathway
	std::unordered_map<direction, Node*> NonePathWays;

	for (auto x : node->neighBours)
	{
			x.second->bObstacle = false;
			NonePathWays.emplace(x);
	}
	//create a tile that has all his neighbours as pathways
	for (auto x : NonePathWays)
	{
		//break wall between 2 nodes
		node->pathWays.emplace(x.first, x.second);
		//Create the visual between 2 nodes
		CreateVisual(x.first, node, x.second, sf::Color::Blue);
	}
}
//Creates the visual between 2 nodes
void Grid::CreateVisual(direction dir, Node *currentNode, Node *neighbour, sf::Color color)
{
	sf::RectangleShape shape;

	int posX = 0;
	int posY = 0;

	//Create connection and visual between 2 nodes
	switch (dir)
	{
	case direction::bottem:
		posY = currentNode->spritePositionY + 25;
		posX = currentNode->spritePositionX;
		shape.setSize(sf::Vector2f(25, 5));
		neighbour->pathWays.emplace(direction::up, currentNode);
		break;
	case direction::up:
		posY = currentNode->spritePositionY - 5;
		posX = currentNode->spritePositionX;
		shape.setSize(sf::Vector2f(25, 5));
		neighbour->pathWays.emplace(direction::bottem, currentNode);
		break;
	case direction::left:
		posY = currentNode->spritePositionY;
		posX = currentNode->spritePositionX - 5;
		shape.setSize(sf::Vector2f(5, 25));
		neighbour->pathWays.emplace(direction::right, currentNode);
		break;
	case direction::right:
		posY = currentNode->spritePositionY;
		posX = currentNode->spritePositionX + 25;
		shape.setSize(sf::Vector2f(5, 25));
		neighbour->pathWays.emplace(direction::left, currentNode);
		break;
	}

	shape.setPosition(sf::Vector2f(posX, posY));
	shape.setFillColor(color);
	walls.push_back(shape);
}