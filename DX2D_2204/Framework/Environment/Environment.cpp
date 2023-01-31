#include "Framework.h"

Environment::Environment()
{
	mainCamera = new Camera();
	uiView = new MatrixBuffer();

	CreateProjection();
	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();	
}

Environment::~Environment()
{
	delete mainCamera;

	delete uiView;
	delete projection;

	samplerState->Release();
}

void Environment::SetAlphaBlend()
{
	float blendFactor[4] = {};
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}

void Environment::SetAdditiveBlend()
{
	float blendFactor[4] = {};
	DC->OMSetBlendState(additiveBlendState, blendFactor, 0xffffffff);
}

void Environment::SetUIView()
{
	uiView->SetVS(1);
}

void Environment::SetViewPort(UINT width, UINT height)
{
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewPort);
}

void Environment::SetOrtographic(UINT width, UINT height)
{
	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, width, 0.0f, height, -1.0f, 1.0f);

	projection->Set(orthographic);
	projection->SetVS(2);
}

void Environment::CreateProjection()
{
	projection = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

	projection->Set(orthographic);
	projection->SetVS(2);
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//LOD(Level Of Detail) : 카메라의 거리에 따라서 
	//퀄리티를 다르게 표현하는 방법

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&blendDesc, &alphaBlendState);

	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	DEVICE->CreateBlendState(&blendDesc, &additiveBlendState);

	float blendFactor[4] = {};
	DC->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
}

void Environment::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

	DC->RSSetState(rasterizerState);
}
