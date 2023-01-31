#pragma once

class DNode
{
public:
	struct Edge
	{
		DNode* node;
		float cost;
		LineCollider* line;

		Edge(Vector2 start, Vector2 end)
		{
			line = new LineCollider(start, end);
		}
		~Edge()
		{
			delete line;
		}
	};

public:
	DNode(Vector2 pos);
	~DNode();

	void Render();

	void AddEdge(DNode* node);

	void SetIndex(int index) { this->index = index; }	

	bool& Closed() { return isClosed; }
	int& Via() { return via; }
	float& Cost() { return cost; }

	Vector2 GetPos() { return pos; }
	Collider* GetCollider() { return collider; }
	vector<Edge*> GetEdges() { return edges; }
private:
	Vector2 pos;
	bool isClosed = false;
	int via = -1;
	float cost = FLT_MAX;

	int index = 0;

	vector<Edge*> edges;

	Collider* collider;
};