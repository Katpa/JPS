#include "Framework.h"

RenderTarget::RenderTarget(UINT width, UINT height)
	: width(width), height(height)
{
	CreateRTVTexture();
	CreateRTV();
	CreateSRV();
}

RenderTarget::~RenderTarget()
{
	rtvTexture->Release();
	rtv->Release();
}

void RenderTarget::Set()
{
	Environment::Get()->SetViewPort(width, height);
	Environment::Get()->SetOrtographic(width, height);

	DC->OMSetRenderTargets(1, &rtv, nullptr);

	float clearColor[] = { 1, 1, 0, 1 };
	DC->ClearRenderTargetView(rtv, clearColor);
}

void RenderTarget::CreateRTVTexture()
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

	DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
}

void RenderTarget::CreateRTV()
{
	D3D11_RENDER_TARGET_VIEW_DESC desc = {};
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	DEVICE->CreateRenderTargetView(rtvTexture, &desc, &rtv);
}

void RenderTarget::CreateSRV()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = 1;

	DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
}
