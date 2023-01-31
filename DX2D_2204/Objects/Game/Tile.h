#pragma once

class Tile : public Button
{
public:
	enum Type
	{
		BG, OBJ
	};

	struct Data
	{
		wstring textureFile;
		Vector2 pos;
		Type type;
	};

public:
	Tile(Data data);
	~Tile();

	void SetTile(wstring file);

	Data GetData() { return data; }	

private:
	Data data;
};