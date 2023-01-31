#pragma once

class Transform
{
public:
	Transform();

	void UpdateWorld();

	void RenderUI();

	Matrix& GetWorld() { return world; }
	void SetParent(Transform* transform) { parent = &transform->GetWorld(); }

	void SetPivot(float x, float y) { pivot = { x, y }; }

	void SetTag(string tag) { this->tag = tag; }

	bool& Active() { return isActive; }
	Vector2& Position() { return localPosition; }
	Float3& Rotation() { return localRotation; }
	Vector2& Scale() { return localScale; }

	Vector2 Right() { return right.Normalized(); }
	Vector2 Up() { return up.Normalized(); }
	Vector2 Left() { return right.Normalized() * -1.0f; }
	Vector2 Down() { return up.Normalized() * -1.0f; }

	Vector2 GlobalPosition() { return globalPosition; }
	Vector2 GlobalScale() { return globalScale; }

protected:
	string tag;

	bool isActive;	

	Vector2 localPosition;
	Float3 localRotation;
	Vector2 localScale;

	Matrix world;
private:	
	Matrix* parent;

	Matrix S, R, T, P, IP;

	Vector2 pivot;
	Vector2 right, up;
	Vector2 globalPosition;	
	Vector2 globalScale;

	XMFLOAT4X4 matWorld;
};