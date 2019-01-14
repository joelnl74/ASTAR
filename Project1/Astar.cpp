#include "Astar.h"
#include <list>
void Astar::SetNodeColor()
{
	Node *currentNode = end;
	while (currentNode->parent != nullptr)
	{
		currentNode->shape.setFillColor(sf::Color::Yellow);
		currentNode = currentNode->parent;
	}
	end->shape.setFillColor(sf::Color::Red);
	start->shape.setFillColor(sf::Color::Green);
}
bool Astar::SolveAStar(Grid * grid)
{
	if (start == nullptr && end == nullptr)
	{
		start = grid->returnGrid().front();
		end = grid->returnGrid().back();
	}
	for (auto node : grid->returnGrid())
	{
		node->bVisited = false;
		node->fGlobalGoal = INFINITY;
		node->fLocalGoal = INFINITY;
		node->parent = nullptr;
	}
	auto distance = [](Node* a, Node* b)
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	Node *currentNode = start;
	currentNode->fLocalGoal = 0;
	currentNode->fGlobalGoal = distance(start, end);

	std::list<Node*> listNotTestedNodes;
	listNotTestedNodes.push_back(start);

	while (!listNotTestedNodes.empty())
	{
		listNotTestedNodes.sort([](const Node* lhs, const Node* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });


		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			listNotTestedNodes.pop_front();

		if (listNotTestedNodes.empty())
			break;

		currentNode = listNotTestedNodes.front();
		currentNode->bVisited = true;

		for (auto node : currentNode->pathWays)
		{
			if (!node.second->bVisited && node.second->bObstacle == 0)
				listNotTestedNodes.push_back(node.second);

			float fPossibleLowerGoal = currentNode->fLocalGoal + distance(currentNode, node.second);

			if (fPossibleLowerGoal < node.second->fLocalGoal)
			{
				node.second->parent = currentNode;
				node.second->fLocalGoal = fPossibleLowerGoal;

				node.second->fGlobalGoal = node.second->fGlobalGoal + distance(node.second, end);
			}
		}
	}
	return true;
}

Astar::Astar()
{
}


Astar::~Astar()
{

}
