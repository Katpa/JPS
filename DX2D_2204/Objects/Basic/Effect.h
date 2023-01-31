#pragma once

class Effect : public Quad
{
private:
	class FrameBuffer : public ConstBuffer
	{
	public:
		FrameBuffer() : ConstBuffer(&data, sizeof(Data))
		{
		}

		struct Data
		{
			Vector2 maxFrame;
			Vector2 curFrame;
		}data;
	};

public:
	Effect(wstring textureFile, Vector2 maxFrame, float delayTime, bool isAdditive = false);
	~Effect();

	void Update();
	void Render();

	void Play(Vector2 position);
	void End();

private:
	FrameBuffer* frameBuffer;

	float delayTime = 0.0f;
	float frameTime = 0.0f;

	UINT curFrameNum = 0;
	UINT maxFrameNum = 0;

	bool isAdditive;
};