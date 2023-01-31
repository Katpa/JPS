#pragma once

class Quad;

class Clip
{
public:
	enum Type
	{
		END, LOOP, PINGPONG
	};

public:
	Clip(vector<Frame*> frames, Type type = LOOP, float delayTime = 0.1f);
	~Clip();

	void Update();
	void Render();

	void Play();
	void Stop();

	//eventTimeRate : 0~1
	void SetEvent(float eventTimeRate, CallBack Event);
private:
	vector<Frame*> frames;

	Type repeatType;	

	UINT curFrameNum = 0;

	float frameTime = 0.0f;
	float delayTime = 0.0f;
	float playTime = 0.0f;
	float durationScale = 0.0f;

	bool isPlay = false;
	bool isReverse = false;

	map<float, CallBack> Events;
	map<float, CallBack>::iterator eventIter;
};