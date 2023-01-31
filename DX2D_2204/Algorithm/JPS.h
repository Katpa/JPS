#pragma once

class JPS
{
public:
	JPS(class GameTileMap* map);
	~JPS();

	void Update();
	void Render();

	POINT FindCloseNode(Vector2 pos);
	void GetPath(IN POINT start, IN POINT end, OUT vector<Vector2>& path);

private:
	void Reset();

	float GetDistance(POINT start, POINT end);

	void DefaultSearch();

	void StraightSearch(JPSNode* node);
	void DiagonalSearch(JPSNode* node);
	
	bool VerticalSearch(JPSNode* curNode, Vector2 dir, vector<JPSNode*>& forcedNeighbors);
	bool HorizentalSearch(JPSNode* curNode, Vector2 dir, vector<JPSNode*>& forcedNeighbors);
	bool SubSearch(JPSNode* node);

	bool IsPossible(JPSNode* node);

private:
	vector<vector<JPSNode*>> nodes;
	JPSNode* target = nullptr;
	bool isEnd = false;
	JPSHeap* openList;
	POINT mapSize;

	vector<Vector2> allDir = { {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {-1, 0}, {0, -1}, {-1, -1}, {1, -1} };
};