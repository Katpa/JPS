#include "Framework.h"

Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
	for (DNode* node : nodes)
		delete node;
}

void Dijkstra::Update()
{
	if (KEY_DOWN(VK_F1))
	{
		CreateNode(mousePos);
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		for (DNode* node : nodes)
		{
			if (node->GetCollider()->IsPointCollision(mousePos))
			{
				selectNode = node;
				break;
			}
		}
	}

	if (KEY_UP(VK_RBUTTON))
	{
		if (selectNode == nullptr) return;

		for (DNode* node : nodes)
		{
			if (node != selectNode && node->GetCollider()->IsPointCollision(mousePos))
			{
				node->AddEdge(selectNode);
				selectNode->AddEdge(node);
				break;
			}
		}
	}
}

void Dijkstra::Render()
{
	for (DNode* node : nodes)
		node->Render();
}

int Dijkstra::FindCloseNode(Vector2 pos)
{
	float minDist = FLT_MAX;

	int index = -1;

	for (UINT i = 0; i < nodes.size(); i++)
	{
		float distance = Vector2::Distance(pos, nodes[i]->GetPos());

		if (minDist > distance)
		{
			minDist = distance;
			index = i;
		}
	}

	return index;
}

void Dijkstra::SetEdgeInfo(int curIndex)
{
	if (curIndex == -1)
		return;

	nodes[curIndex]->Closed() = true;

	float cost = nodes[curIndex]->Cost();

	for (DNode::Edge* edge : nodes[curIndex]->GetEdges())
	{
		if (edge->node->Cost() > cost + edge->cost)
		{
			edge->node->Cost() = cost + edge->cost;
			edge->node->Via() = curIndex;
		}
	}
}

int Dijkstra::FindMinCostNode()
{
	float minCost = FLT_MAX;

	int index = -1;

	for (UINT i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->Closed()) continue;

		if (minCost > nodes[i]->Cost())
		{
			minCost = nodes[i]->Cost();
			index = i;
		}
	}

	return index;
}

void Dijkstra::ResetNodes()
{
	for (DNode* node : nodes)
	{
		node->Closed() = false;
		node->Via() = -1;
		node->Cost() = FLT_MAX;
	}
}

vector<Vector2> Dijkstra::GetPath(int start, int end)
{
	ResetNodes();

	int curIndex = start;
	nodes[curIndex]->Cost() = 0;
	nodes[curIndex]->Via() = start;

	for (DNode* node : nodes)
	{
		SetEdgeInfo(curIndex);
		curIndex = FindMinCostNode();
	}

	curIndex = end;

	vector<Vector2> path;
	while (curIndex != start)
	{
		path.push_back(nodes[curIndex]->GetPos());
		curIndex = nodes[curIndex]->Via();

		if (curIndex == -1)
			break;
	}

	path.push_back(nodes[start]->GetPos());

	return path;
}

void Dijkstra::CreateNode(Vector2 pos)
{
	DNode* node = new DNode(pos);
	node->SetIndex(nodes.size());

	nodes.push_back(node);
}
