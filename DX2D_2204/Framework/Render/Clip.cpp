#include "Framework.h"

Clip::Clip(vector<Frame*> frames, Type type, float delayTime)
	: frames(frames), repeatType(type), delayTime(delayTime)
{	
	durationScale = 1.0f / (delayTime * frames.size());
}

Clip::~Clip()
{
	for (Frame* frame : frames)
		delete frame;
}

void Clip::Update()
{
	if (!isPlay) return;

	frameTime += DELTA;
	playTime += DELTA;

	float playTimeRate = playTime * durationScale;

	if (!Events.empty() && eventIter != Events.end() && eventIter->first <= playTimeRate)
	{
		eventIter->second();
		eventIter++;
	}

	if (frameTime < delayTime) return;

	switch (repeatType)
	{
	case Clip::END:
		curFrameNum++;
		if (curFrameNum >= frames.size())
		{
			curFrameNum--;
			Stop();
		}
		break;
	case Clip::LOOP:
		++curFrameNum %= frames.size();
		if (curFrameNum == 0)
		{
			playTime = 0.0f;
			eventIter = Events.begin();
		}
		break;
	case Clip::PINGPONG:
		if (isReverse)
		{
			curFrameNum--;
			if (curFrameNum <= 0)
			{
				isReverse = false;
				playTime = 0.0f;
			}
		}
		else
		{
			curFrameNum++;
			if (curFrameNum >= frames.size() - 1)
			{
				isReverse = true;
				playTime = 0.0f;
			}
		}
		break;	
	}

	frameTime -= delayTime;
}

void Clip::Render()
{
	frames[curFrameNum]->Render();
}

void Clip::Play()
{
	isPlay = true;
	isReverse = false;
	frameTime = 0.0f;
	playTime = 0.0f;
	curFrameNum = 0;

	eventIter = Events.begin();
}

void Clip::Stop()
{
	isPlay = false;

	frameTime = 0.0f;
	playTime = 0.0f;	
}

void Clip::SetEvent(float eventTimeRate, CallBack Event)
{
	if (Events.count(eventTimeRate) > 0)
		return;

	Events[eventTimeRate] = Event;
}
