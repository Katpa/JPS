#pragma once

class VertexShader : public Shader
{
	friend class Shader;

private:
	VertexShader(wstring file);
	~VertexShader();

public:
	virtual void Set() override;

private:
	void CreateInputLayout();

private:
	ID3D11VertexShader* vertexShader;
	ID3D11InputLayout* inputLayout;

	ID3D11ShaderReflection* reflection;
};