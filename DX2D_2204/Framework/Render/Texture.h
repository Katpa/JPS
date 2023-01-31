#pragma once

class Texture
{
private:
	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Add(wstring file);
	static Texture* Add(wstring key, ID3D11ShaderResourceView* srv);
	static void Delete();

	void PSSet(UINT slot = 0);

	Vector2 GetSize();

	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	ScratchImage image;
	ID3D11ShaderResourceView* srv;

	static unordered_map<wstring, Texture*> textures;
};