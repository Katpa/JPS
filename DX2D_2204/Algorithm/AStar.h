#pragma once

class AStar//A*
{
public:
	AStar(class GameTileMap* map);
	~AStar();

	void Update();
	void Render();
		
	int FindCloseNode(Vector2 pos);

	void GetPath(IN int start,IN int end, OUT vector<Vector2>& path);

private:
	void Reset();

	float GetDistance(int start, int end);

	void Extend(int center, int end);
	int GetMinNode();	

	void SetEdge(UINT width);

private:
	vector<Node*> nodes;
	//vector<int> openNodes;
	Heap* heap;
};