#pragma once

class GameTileMap : public Transform
{
private:
	const float PUSH_SPEED = 500.0f;

	enum Direction
	{
		UP, DOWN, RIGHT, LEFT, NONE
	};

public:
	GameTileMap(string file);
	~GameTileMap();

	void Update();
	void Render();

	void PushTank(class Tank* tank);

	void GetNodes(vector<Node*>& nodes);
	void GetNodes(vector<vector<JPSNode*>>& nodes, POINT& size);

	UINT GetWidth() { return width; }
private:
	void Load(string file);

	void DrawBGTile();

	Direction GetDirection(Transform* tile, Transform* target);
private:
	UINT width, height;

	Vector2 tileSize;

	vector<Tile*> bgTiles;
	vector<Tile*> objTiles;

	RenderTarget* renderTarget;
	Quad* targetTexture;
};