#pragma once

class CircleCollider : public Collider
{
public:
	CircleCollider(float radius = 1.0f);

	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap = nullptr) override;
	virtual bool IsCircleCollision(CircleCollider* circle) override;

	float Radius() {
		return radius * max(GlobalScale().x, GlobalScale().y);
	}
private:
	void CreateLine();

private:
	const UINT VERTEX_COUNT = 36;

	float radius;
};