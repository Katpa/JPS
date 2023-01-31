#pragma once

class RectCollider : public Collider
{
public:
	struct ObbDesc
	{
		Vector2 position;
		Vector2 axis[2];
		Vector2 halfSize;
	};

public:
	RectCollider(Vector2 size);

	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap = nullptr) override;
	virtual bool IsCircleCollision(CircleCollider* circle) override;

	ObbDesc GetObb();

	Vector2 Size() { return size * GlobalScale(); }

	float R() { return GlobalPosition().x + Size().x * 0.5f; }
	float L() { return GlobalPosition().x - Size().x * 0.5f; }
	float T() { return GlobalPosition().y + Size().y * 0.5f; }
	float B() { return GlobalPosition().y - Size().y * 0.5f; }
private:
	void CreateLine();

	bool IsAABB(RectCollider* rect, Vector2* overlap);
	bool IsOBB(RectCollider* rect);

	float ProjLength(Vector2 separate, Vector2 e1, Vector2 e2);
	bool IsSeparate(Vector2 sperateAxis, ObbDesc box1, ObbDesc box2);
private:
	Vector2 size;

	ObbDesc obbDesc;
};