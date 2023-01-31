#pragma once

class Device : public Singleton<Device>
{
public:
	Device();
	~Device();
	
	void Clear();
	void Present();

	void SetRenderTarget();	
		
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

private:
	void InitDevice();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;	
};