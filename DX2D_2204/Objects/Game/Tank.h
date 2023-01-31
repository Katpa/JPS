#pragma once

class Tank : public AnimObject
{
public:
	Tank();
	~Tank();

	void Update();
	void Render();

	void SetPath(vector<Vector2> path);
	vector<Vector2>& GetPath() { return path; }

	Collider* GetCollider() { return collider; }
private:
	void Control();	
	void MovePath();

private:
	float speed = 300;

	Collider* collider;

	vector<Vector2> path;
};