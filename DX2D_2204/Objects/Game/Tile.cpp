#include "Framework.h"

Tile::Tile(Data data)
	: Button(data.textureFile), data(data)
{
	localPosition = data.pos;

	if (data.type == BG)
		collider->Active() = false;
}

Tile::~Tile()
{
}

void Tile::SetTile(wstring file)
{
	SetTexture(Texture::Add(file));
	data.textureFile = file;
}
