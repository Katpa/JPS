#pragma once

class EffectManager : public Singleton<EffectManager>
{
public:
	EffectManager();
	~EffectManager();

	void Update();
	void Render();

	void Add(string key, UINT poolCount, wstring textureFile,
		Vector2 maxFrame, float delayTime = 0.1f, bool isAdditive = false);

	void Play(string key, Vector2 pos);
	void Stop(string key);

	void AllStop();

private:	
	map<string, vector<Effect*>> totalEffect;
};