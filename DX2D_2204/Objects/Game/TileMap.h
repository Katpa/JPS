#pragma once

class TileMap : public Transform
{
public:
	TileMap(UINT width, UINT height);
	~TileMap();

	void Update();
	void Render();

	void ClickTile(wstring file, Tile::Type type);
	void DeleteTile();

	void Save(string file);
	void Load(string file);	
private:
	void CreateTile();	

	void SetBGTile(wstring file);
	void SetOBJTile(wstring file);

	void ClearBGTile();
	void ClearOBJTile();
private:
	UINT width, height;

	Vector2 tileSize;

	vector<Tile*> bgTiles;
	vector<Tile*> objTiles;
};