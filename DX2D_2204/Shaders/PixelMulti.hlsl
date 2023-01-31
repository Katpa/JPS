cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer OptionBuffer : register(b1)
{
    int select;
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
Texture2D secondMap : register(t1);

SamplerState samp : register(s0);

float4 Modulate(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    return tex1 * tex2;
}

float4 Modulate2X(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    return tex1 * tex2 * 2.0f;
}

float4 Add(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    return tex1 + tex2;
}

float4 AddSmooth(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    return tex1 + tex2 - tex1 * tex2;
}

float4 AddSigned(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    return tex1 + tex2 - 0.5f;
}

float4 Subtract(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    return tex1 - tex2;
}

float4 RevSubtract(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    float4 result = tex2 - tex1;
    result.a = 1.0f;
    
    return result;
}

float4 AddSigned2X(float2 uv)
{
    float4 tex1 = map.Sample(samp, uv);
    float4 tex2 = secondMap.Sample(samp, uv);
    
    return (tex1 + tex2 - 0.5f) * 2.0f;
}

float4 PS(PixelInput input) : SV_TARGET
{
    if(select == 1)
        return Modulate(input.uv);
    if (select == 2)
        return Modulate2X(input.uv);
    if (select == 3)
        return Add(input.uv);
    if (select == 4)
        return AddSmooth(input.uv);
    if (select == 5)
        return AddSigned(input.uv);
    if (select == 6)
        return AddSigned2X(input.uv);
    if (select == 7)
        return Subtract(input.uv);
    if (select == 8)
        return RevSubtract(input.uv);
    
    return map.Sample(samp, input.uv);
}