#include "Framework.h"

Effect::Effect(wstring textureFile, Vector2 maxFrame, float delayTime, bool isAdditive)
	: Quad(textureFile, Vector2(), Vector2(1 / maxFrame.x, 1 / maxFrame.y)),
	delayTime(delayTime), isAdditive(isAdditive)
{
	isActive = false;

	SetPixelShader(L"Shaders/PixelEffect.hlsl");

	frameBuffer = new FrameBuffer();
	frameBuffer->data.maxFrame = maxFrame;

	maxFrameNum = (UINT)(maxFrame.x * maxFrame.y);
}

Effect::~Effect()
{
	delete frameBuffer;
}

void Effect::Update()
{
	if (!isActive) return;

	frameTime += DELTA;

	if (frameTime > delayTime)
	{
		frameTime -= delayTime;

		frameBuffer->data.curFrame.x = (float)(curFrameNum % (UINT)frameBuffer->data.maxFrame.x);
		frameBuffer->data.curFrame.y = (float)(curFrameNum / (UINT)frameBuffer->data.maxFrame.x);

		curFrameNum++;

		if (curFrameNum >= maxFrameNum)
			End();
	}

	UpdateWorld();
}

void Effect::Render()
{
	if (!isActive) return;

	if (isAdditive)
		Environment::Get()->SetAdditiveBlend();
	else
		Environment::Get()->SetAlphaBlend();

	frameBuffer->SetPS(1);
	Quad::Render();

	Environment::Get()->SetAlphaBlend();
}

void Effect::Play(Vector2 position)
{
	isActive = true;
	localPosition = position;

	frameTime = 0.0f;
	curFrameNum = 0;
}

void Effect::End()
{
	isActive = false;
}
