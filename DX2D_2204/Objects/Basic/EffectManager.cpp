#include "Framework.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (pair<string, vector<Effect*>> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			delete effect;
	}
}

void EffectManager::Update()
{
	for (pair<string, vector<Effect*>> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Update();
	}
}

void EffectManager::Render()
{
	for (pair<string, vector<Effect*>> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Render();
	}
}

void EffectManager::Add(string key, UINT poolCount, wstring textureFile, Vector2 maxFrame, float delayTime, bool isAdditive)
{
	if (totalEffect.count(key) > 0) return;

	vector<Effect*> effects(poolCount);

	for (Effect*& effect : effects)
	{
		effect = new Effect(textureFile, maxFrame, delayTime, isAdditive);		
	}

	totalEffect[key] = effects;
	//totalEffect.insert({ key, effects });
	//totalEffect.insert(make_pair(key, effects));
	//totalEffect.insert(pair<string, vector<Effect*>>(key, effects));
}

void EffectManager::Play(string key, Vector2 pos)
{
	if (totalEffect.count(key) == 0) return;

	for (Effect* effect : totalEffect[key])
	{
		if (!effect->Active())
		{
			effect->Play(pos);
			return;
		}
	}
}

void EffectManager::Stop(string key)
{
	if (totalEffect.count(key) == 0) return;

	for (Effect* effect : totalEffect[key])
	{
		effect->Active() = false;
	}
}

void EffectManager::AllStop()
{
	for (pair<string, vector<Effect*>> effects : totalEffect)
	{
		Stop(effects.first);
	}
}
