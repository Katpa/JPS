#pragma once

class Frame
{
public:
	Frame(wstring file, Vector2 startUV = Vector2(0, 0), Vector2 endUV = Vector2(1, 1), Vector2 pos = Vector2());
	Frame(wstring file, float x, float y, float width, float height);
	~Frame();

	void Render();

	Vector2 Size() { return texture->GetSize(); }

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

	Texture* texture;
};