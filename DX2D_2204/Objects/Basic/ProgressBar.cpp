#include "Framework.h"

ProgressBar::ProgressBar(wstring frontImageFile, wstring backImageFile, float maxValue)
	: Quad(frontImageFile), maxValue(maxValue)
{
	SetPixelShader(L"Shaders/PixelProgressBar.hlsl");

	backImage = Texture::Add(backImageFile);

	valueBuffer = new FloatValueBuffer();
	valueBuffer->data.values[0] = maxValue;
}

ProgressBar::~ProgressBar()
{
	delete valueBuffer;
}

void ProgressBar::Render()
{
	valueBuffer->SetPS(1);
	backImage->PSSet(1);

	Quad::Render();
}

void ProgressBar::SetValue(float value)
{
	valueBuffer->data.values[0] = value / maxValue;
}
