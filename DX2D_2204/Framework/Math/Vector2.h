#pragma once

#include "Math.h"

using namespace GameMath;

class Vector2 : public Float2
{
public:
	Vector2() : Float2(0, 0) {}
	Vector2(float x, float y) : Float2(x, y) {}
	Vector2(Float2 value) : Float2(value) {}

	Vector2 operator+ (const Vector2& value) const
	{
		return Vector2(x + value.x, y + value.y);
	}
	Vector2 operator- (const Vector2& value) const
	{
		return Vector2(x - value.x, y - value.y);
	}
	Vector2 operator* (const Vector2& value) const
	{
		return Vector2(x * value.x, y * value.y);
	}
	Vector2 operator/ (const Vector2& value) const
	{
		return Vector2(x / value.x, y / value.y);
	}

	Vector2 operator+ (const float& value) const
	{
		return Vector2(x + value, y + value);
	}
	Vector2 operator- (const float& value) const
	{
		return Vector2(x - value, y - value);
	}
	Vector2 operator* (const float& value) const
	{
		return Vector2(x * value, y * value);
	}
	Vector2 operator/ (const float& value) const
	{
		return Vector2(x / value, y / value);
	}

	Vector2 operator* (const Matrix& value) const
	{
		XMVECTOR temp = XMLoadFloat2(this);

		temp = XMVector2TransformCoord(temp, value);

		Vector2 tempPos;
		XMStoreFloat2(&tempPos, temp);

		return tempPos;
	}

	void operator+= (const Vector2& value)
	{
		x += value.x;
		y += value.y;
	}
	void operator-= (const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
	}
	void operator*= (const Vector2& value)
	{
		x *= value.x;
		y *= value.y;
	}
	void operator/= (const Vector2& value)
	{
		x /= value.x;
		y /= value.y;
	}

	void operator+= (const float& value)
	{
		x += value;
		y += value;
	}
	void operator-= (const float& value)
	{
		x -= value;
		y -= value;
	}
	void operator*= (const float& value)
	{
		x *= value;
		y *= value;
	}
	void operator/= (const float& value)
	{
		x /= value;
		y /= value;
	}

	bool operator== (const Vector2& value)
	{
		if (Equal(x, value.x) && Equal(y, value.y))
			return true;

		return false;
	}

	float Length() const
	{
		return sqrt(x * x + y * y);
	}
	float SqrLength() const
	{
		return x * x + y * y;
	}
	float Angle() const
	{
		return atan2(y, x);
	}

	Vector2 Normalized() const
	{
		float length = Length();

		if (length == 0.0f)
			return Vector2();

		return Vector2(x / length, y / length);
	}

	static float Dot(const Vector2& v1, const Vector2& v2)
	{		
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float Cross(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	static float Distance(const Vector2& v1, const Vector2& v2)
	{
		return (v1 - v2).Length();
	}
};