#include "Framework.h"

Tank::Tank()
{
	wstring file = L"Textures/tank.png";
	Texture* texture = Texture::Add(file);

	Vector2 cutSize = texture->GetSize() / Vector2(8, 4);

	vector<Frame*> frames;
	frames.push_back(new Frame(file, cutSize.x * 0, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 1, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 2, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 3, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 4, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 5, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 6, cutSize.y * 2, cutSize.x, cutSize.y));
	frames.push_back(new Frame(file, cutSize.x * 7, cutSize.y * 2, cutSize.x, cutSize.y));
	clips[0] = new Clip(frames);

	curClip = clips[0];
	curClip->Stop();

	collider = new RectCollider(cutSize);
	collider->SetParent(this);
}

Tank::~Tank()
{
	delete collider;
}

void Tank::Update()
{
	//Control();
	MovePath();

	AnimObject::Update();

	collider->UpdateWorld();
}

void Tank::Render()
{
	AnimObject::Render();

	collider->Render();
}

void Tank::SetPath(vector<Vector2> path)
{
	curClip->Play();

	this->path = path;
}

void Tank::Control()
{
	if (KEY_PRESS('W'))
	{
		localPosition += Right() * speed * DELTA;
	}else if (KEY_PRESS('S'))
	{
		localPosition -= Right() * speed * DELTA;
	}

	if (KEY_PRESS('A'))
	{		
		localRotation.z += DELTA * 5;
	}else if (KEY_PRESS('D'))
	{		
		localRotation.z -= DELTA * 5;
	}

	if (KEY_DOWN('W') | KEY_DOWN('S') | KEY_DOWN('A') | KEY_DOWN('D'))
		curClip->Play();

	if (KEY_UP('W') | KEY_UP('S') | KEY_UP('A') | KEY_UP('D'))
		curClip->Stop();
}

void Tank::MovePath()
{
	if (path.empty())
	{
		curClip->Stop();
		return;
	}

	Vector2 direction = path.back() - localPosition;
	localRotation.z = direction.Angle();

	localPosition += Right() * speed * DELTA;

	if (direction.Length() < 5.0f)
		path.pop_back();
}
