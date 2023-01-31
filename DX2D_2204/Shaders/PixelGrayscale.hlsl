cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

cbuffer IndexBuffer : register(b1)
{
    int index;
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 Grayscale(float4 albedo)
{
    float scale = (albedo.r + albedo.g + albedo.b) / 3;
    
    return float4(scale.xxx, albedo.a);
}

float4 Grayscale2(float4 albedo)
{
    //float3 grayColor;
    //grayColor.r = albedo.r * 0.3f;
    //grayColor.g = albedo.g * 0.59f;
    //grayColor.b = albedo.b * 0.11f;
    //
    //float scale = grayColor.r + grayColor.g + grayColor.b;
    float scale = dot(albedo.rgb, float3(0.3f, 0.59f, 0.11));
        
    return float4(scale.xxx, albedo.a);
}

float4 Sepia(float4 albedo)
{
    float4 sepia;
    
    sepia.a = albedo.a;
    
    sepia.r = dot(albedo.rgb, float3(0.393f, 0.769f, 0.189f));
    sepia.g = dot(albedo.rgb, float3(0.349f, 0.686f, 0.168f));
    sepia.b = dot(albedo.rgb, float3(0.272f, 0.534f, 0.131f));
    
    return sepia;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 albedo = map.Sample(samp, input.uv);
        
    if(index == 1)
        return Grayscale(albedo) * color;
    else if(index == 2)
        return Grayscale2(albedo) * color;
    else if (index == 3)
        return Sepia(albedo) * color;
    
    return albedo * color;
}