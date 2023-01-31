cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer OptionBuffer : register(b1)
{
    int weight;
}

cbuffer SizeBuffer : register(b2)
{
    float2 imageSize;
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    float4 albedo = map.Sample(samp, input.uv);
    
    if(albedo.a > 0)
        return albedo;
    
    float count = 0;
    
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 offset = (float2(x, y) / imageSize) * weight;
            albedo = map.Sample(samp, input.uv + offset);
            
            count += albedo.a;
        }
    }
    
    if(count > 0 && count < 9)
        return color;
    
    return map.Sample(samp, input.uv);
}