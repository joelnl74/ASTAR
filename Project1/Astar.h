#pragma once
#include "Grid.h"
class Astar
{
public:
	Node * start;
	Node * end;

	void SetNodeColor();
	bool SolveAStar(Grid * grid);
	Astar();
	~Astar();
};

