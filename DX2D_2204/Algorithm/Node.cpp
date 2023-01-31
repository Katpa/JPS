#include "Framework.h"

Node::Node(Vector2 pos, int index)
	: pos(pos), index(index)
{
	collider = new CircleCollider(10);
	collider->Position() = pos;
	collider->UpdateWorld();
}

Node::~Node()
{
	for (Edge* edge : edges)
		delete edge;

	delete collider;
}

void Node::Render()
{
	switch (state)
	{
	case Node::NONE:
		collider->SetColor(1, 1, 1);
		break;
	case Node::OPEN:
		collider->SetColor(0, 0, 1);
		break;
	case Node::CLOSED:
		collider->SetColor(0, 0, 0);
		break;
	case Node::USING:
		collider->SetColor(0, 1, 0);
		break;
	case Node::OBSTACLE:
		collider->SetColor(1, 0, 0);
		break;	
	}

	collider->Render();

	for (Edge* edge : edges)
		edge->line->Render();
}

void Node::AddEdge(Node* node)
{
	Edge* edge = new Edge(node->pos, pos);
	edge->index = node->index;
	edge->cost = Vector2::Distance(node->pos, pos);

	edges.push_back(edge);
}
