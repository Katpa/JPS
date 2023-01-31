#pragma once

class Quad : public Transform
{
public:
	Quad(wstring file, Vector2 startUV = Vector2(0, 0), Vector2 endUV = Vector2(1, 1), Vector2 pos = Vector2());	
	Quad(Vector2 size, Vector2 pos = Vector2());	
	~Quad();

	void Render();

	void SetTexture(Texture* texture) { this->texture = texture; }
	void SetPixelShader(wstring file);

	Vector2 Size() { return texture->GetSize(); }
	ColorBuffer* GetColorBuffer() { return colorBuffer; }

private:
	void Init();

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	MatrixBuffer* worldBuffer;
	ColorBuffer* colorBuffer;

	vector<Vertex> vertices;
	vector<UINT> indices;

	Texture* texture;
};