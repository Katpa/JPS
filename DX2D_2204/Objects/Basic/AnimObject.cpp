#include "Framework.h"

AnimObject::AnimObject() : curClip(nullptr)
{
	vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

	worldBuffer = new MatrixBuffer();
	colorBuffer = new ColorBuffer();
}

AnimObject::~AnimObject()
{
	for (pair<int, Clip*> clip : clips)
		delete clip.second;

	delete worldBuffer;
	delete colorBuffer;
}

void AnimObject::Update()
{
	if (curClip == nullptr) return;

	curClip->Update();
	UpdateWorld();
}

void AnimObject::Render()
{
	if (curClip == nullptr) return;

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	colorBuffer->SetPS(0);

	vertexShader->Set();
	pixelShader->Set();

	curClip->Render();
}
