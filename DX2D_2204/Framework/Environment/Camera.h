#pragma once

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();
	void RenderUI();

	void SetView();

	void SetLeftBottom(float left, float bottom) { leftBottom = { left, bottom }; }
	void SetLeftBottom(Vector2 leftBottom) { this->leftBottom = leftBottom; }
	void SetRightTop(float right, float top) { rightTop = { right, top }; }
	void SetRightTop(Vector2 rightTop) { this->rightTop = rightTop; }
	void SetTargetOffset(float x, float y) { targetOffset = { x, y }; }

	void SetTarget(Transform* target) { this->target = target; }

	Vector2 ScreenToWorld(Vector2 pos);
	Vector2 WorldToScreen(Vector2 pos);

private:
	void FreeMode();
	void FollowMode();
	
	void FixPosition(Vector2& position);
private:
	MatrixBuffer* viewBuffer;
	Matrix invView;

	float speed = 200;

	Vector2 leftBottom;
	Vector2 rightTop = { WIN_WIDTH, WIN_HEIGHT };

	Transform* target = nullptr;

	Vector2 targetOffset = { CENTER_X, CENTER_Y };
};