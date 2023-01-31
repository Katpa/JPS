#include "Framework.h"

DNode::DNode(Vector2 pos)
	: pos(pos)
{
	collider = new CircleCollider(30);
	collider->Position() = pos;
	collider->UpdateWorld();
}

DNode::~DNode()
{
	delete collider;

	for (Edge* edge : edges)
		delete edge;
}

void DNode::Render()
{
	collider->Render();

	for (Edge* edge : edges)
		edge->line->Render();
}

void DNode::AddEdge(DNode* node)
{
	Edge* edge = new Edge(node->pos, pos);
	edge->node = node;
	edge->cost = Vector2::Distance(node->pos, pos);

	edges.push_back(edge);
}
