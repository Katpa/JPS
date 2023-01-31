#pragma once

class JPSHeap
{
public:
	JPSHeap();
	~JPSHeap();

	void Insert(JPSNode* node);
	JPSNode* GetMinCostNode();
	void Clear();

	bool Empty() { return openList.empty(); }

private:
	priority_queue<JPSNode*, vector<JPSNode*>, greater<JPSNode*>> openList;
};