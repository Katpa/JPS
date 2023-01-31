#include "Framework.h"

LineCollider::LineCollider(Vector2 startPos, Vector2 endPos)
    : startPos(startPos), endPos(endPos)
{
    CreateLine();
}

LineCollider::~LineCollider()
{
}

bool LineCollider::IsPointCollision(Vector2 point)
{
    return false;
}

bool LineCollider::IsRectCollision(RectCollider* rect, Vector2* overlap )
{
    return false;
}

bool LineCollider::IsCircleCollision(CircleCollider* circle)
{
    return false;
}

void LineCollider::CreateLine()
{
    vertices.emplace_back(startPos.x, startPos.y);
    vertices.emplace_back(endPos.x, endPos.y);

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexPos), vertices.size());
}
