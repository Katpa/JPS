#include "Framework.h"

Button::Button(wstring file)
	: Quad(file)
{
	collider = new RectCollider(Size());
	collider->SetParent(this);
}

Button::Button(Vector2 size)
	: Quad(size)
{
	collider = new RectCollider(size);
	collider->SetParent(this);
}

Button::~Button()
{
	delete collider;
}

void Button::Update()
{
	if (collider->IsPointCollision(mousePos))
	{
		if (KEY_DOWN(VK_LBUTTON))
			isDownCheck = true;

		if (KEY_PRESS(VK_LBUTTON))
			state = DOWN;
		else
			state = OVER;

		if (isDownCheck && KEY_UP(VK_LBUTTON))
		{
			if (Event != nullptr)
				Event();

			if (IntEvent != nullptr)
				IntEvent(intParam);

			isDownCheck = false;
		}
	}
	else
	{
		state = NONE;

		if (KEY_UP(VK_LBUTTON))
			isDownCheck = false;
	}

	switch (state)
	{
	case Button::NONE:
		GetColorBuffer()->Set(noneColor);
		break;
	case Button::DOWN:
		GetColorBuffer()->Set(downColor);
		break;
	case Button::OVER:
		GetColorBuffer()->Set(overColor);
		break;	
	}

	UpdateWorld();
	collider->UpdateWorld();	
}

void Button::Render()
{
	Quad::Render();
	collider->Render();
}
