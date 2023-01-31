#include "Framework.h"

JPSHeap::JPSHeap()
{
}

JPSHeap::~JPSHeap()
{
}

void JPSHeap::Insert(JPSNode* node)
{
	if (node->GetState() != JPSNode::NONE &&
		node->GetState() != JPSNode::OPEN) return;

	node->SetState(JPSNode::OPEN);
	openList.push(node);
}

JPSNode* JPSHeap::GetMinCostNode()
{
	JPSNode* tmp = openList.top();
	openList.pop();
	return tmp;
}

void JPSHeap::Clear()
{
	while (openList.size() > 0)
		openList.pop();
}