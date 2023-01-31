#pragma once

class PixelShader : public Shader
{
	friend class Shader;

private:
	PixelShader(wstring file);
	~PixelShader();

public:
	virtual void Set() override;

private:
	ID3D11PixelShader* pixelShader;	
};
