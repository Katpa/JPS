#include "Framework.h"

Collider::Collider()
{
	vertexShader = Shader::AddVS(L"Shaders/VertexCollider.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/PixelCollider.hlsl");

	worldBuffer = new MatrixBuffer();
	colorBuffer = new ColorBuffer();
	colorBuffer->Set(0, 1, 0);
}

Collider::~Collider()
{
	delete vertexBuffer;

	delete colorBuffer;
	delete worldBuffer;
}

void Collider::Render()
{
	if (!isActive) return;

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	colorBuffer->SetPS(0);

	vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	vertexShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);
}

bool Collider::IsCollision(Collider* collider)
{
	if (!isActive) return false;

	switch (collider->type)
	{
	case Collider::Type::RECT:
		return IsRectCollision((RectCollider*)collider);		
	case Collider::Type::CIRCLE:
		return IsCircleCollision((CircleCollider*)collider);	
	}

    return false;
}
