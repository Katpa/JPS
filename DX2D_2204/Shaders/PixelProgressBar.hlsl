cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer ValueBuffer : register(b1)
{
    float value;
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Texture2D frontImage : register(t0);
Texture2D backImage : register(t1);

SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    if(input.uv.x < value)
        return frontImage.Sample(samp, input.uv);
            
    return backImage.Sample(samp, input.uv);
}