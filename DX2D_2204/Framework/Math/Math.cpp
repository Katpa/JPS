#include "Framework.h"
#include "Math.h"

int GameMath::Random(const int& min, const int& max)
{
    return rand() % (max - min) + min;
}

float GameMath::Random(const float& min, const float& max)
{
    float normal = (float)rand() / (float)RAND_MAX;

    return min + (max - min) * normal;
}

float GameMath::Clamp(float value, const float& min, const float& max)
{
    if (value < min)
        value = min;

    if (value > max)
        value = max;

    return value;
}

bool GameMath::Equal(const float& value, const float& compare)
{
    return abs(value - compare) < FLT_EPSILON;
}
