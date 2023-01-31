#include "Framework.h"

PixelShader::PixelShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
        
    D3DCompileFromFile(file.c_str(), nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreatePixelShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &pixelShader);    
}

PixelShader::~PixelShader()
{
    pixelShader->Release();    
}

void PixelShader::Set()
{
    DC->PSSetShader(pixelShader, nullptr, 0);
}
