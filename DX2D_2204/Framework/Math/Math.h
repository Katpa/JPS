#pragma once

namespace GameMath
{
	int Random(const int& min, const int& max);
	float Random(const float& min, const float& max);

	float Clamp(float value, const float& min, const float& max);

	bool Equal(const float& value, const float& compare);
}