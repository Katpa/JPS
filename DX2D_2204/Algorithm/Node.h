#pragma once

class Node
{
public:
	friend class AStar;
	friend class JPS;

	enum State
	{
		NONE, OPEN, CLOSED, USING, OBSTACLE
	};

	struct Edge
	{
		int index;
		float cost;
		LineCollider* line;

		Edge(Vector2 start, Vector2 end)
		{
			line = new LineCollider(start, end);
			line->SetColor(1, 0, 1);
		}
		~Edge()
		{
			delete line;
		}
	};

public:
	Node(Vector2 pos, int index);
	~Node();

	void Render();

	void AddEdge(Node* node);
	
	void SetState(State state) { this->state = state; }
	float GetCost() { return f; }

private:
	Vector2 pos;

	int index = 0;
	int via = -1;

	//Cost
	float f = 0, g = 0, h = 0;

	//F : 최종 코스트(G + H)
	//G : 출발점 부터 현재 노드까지의 코스트
	//H(추정가중치) : 현재 노드부터 목저지까지의 추정 코스트

	State state = NONE;

	vector<Edge*> edges;

	Collider* collider;
};