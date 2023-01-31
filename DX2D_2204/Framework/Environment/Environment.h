#pragma once

class Environment : public Singleton<Environment>
{
public:
	Environment();
	~Environment();

	void SetAlphaBlend();
	void SetAdditiveBlend();

	Camera* GetMainCamera() { return mainCamera; }

	void SetUIView();
	void SetViewPort(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetOrtographic(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
private:
	void CreateProjection();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

private:	
	Camera* mainCamera;

	MatrixBuffer* uiView;
	MatrixBuffer* projection;

	ID3D11SamplerState* samplerState;
	ID3D11BlendState* alphaBlendState;
	ID3D11BlendState* additiveBlendState;
	ID3D11RasterizerState* rasterizerState;

	D3D11_VIEWPORT viewPort = {};
};