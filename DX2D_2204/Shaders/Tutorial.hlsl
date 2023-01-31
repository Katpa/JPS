//Sementic : 매개변수 및 반환값 정보를 어떻게 사용할지 이름 붙이는 것
//SV : System Value

struct VertexInput
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

PixelInput VS( VertexInput input )
{    
    PixelInput output;
    output.pos = input.pos;
    output.color = input.color;
    
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return input.color;
}