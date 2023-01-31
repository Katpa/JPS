#pragma once

class Button : public Quad
{
private:
	enum State
	{
		NONE, DOWN, OVER
	};

public:
	Button(wstring file);
	Button(Vector2 size);
	~Button();

	void Update();
	void Render();

	void SetEvent(CallBack Event) { this->Event = Event; }
	void SetIntEvent(CallBackInt Event) { IntEvent = Event; }

	void SetIntParam(int param) { intParam = param; }

	Collider* GetCollider() { return collider; }
protected:
	Collider* collider;

	State state = NONE;

	CallBack Event = nullptr;
	CallBackInt IntEvent = nullptr;

	int intParam = 0;

	Float4 noneColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	Float4 downColor = { 0.5f, 0.5f, 0.5f, 1.0f };
	Float4 overColor = { 0.9f, 0.9f, 0.9f, 1.0f };

	bool isDownCheck = false;
};