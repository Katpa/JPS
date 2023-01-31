#include "Framework.h"

RectCollider::RectCollider(Vector2 size) : size(size)
{
    type = Type::RECT;

    CreateLine();
}

bool RectCollider::IsPointCollision(Vector2 point)
{
    Matrix invWorld = XMMatrixInverse(nullptr, world);

    Vector2 tempPos = point * invWorld;

    Vector2 half = size * 0.5f;

    if (abs(tempPos.x) < half.x && abs(tempPos.y) < half.y)
        return true;

    return false;
}

bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    if (overlap)
        return IsAABB(rect, overlap);

    return IsOBB(rect);
}

bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
    ObbDesc obb = GetObb();

    Vector2 nea1 = obb.axis[0];
    Vector2 ea1 = nea1 * obb.halfSize.x;
    Vector2 nea2 = obb.axis[1];
    Vector2 ea2 = nea2 * obb.halfSize.y;

    Vector2 distance = circle->GlobalPosition() - obb.position;

    float lengthA = abs(Vector2::Dot(distance, nea1));
    float lengthB = abs(Vector2::Dot(distance, nea2));

    float radius = circle->Radius();

    if (lengthA > obb.halfSize.x + radius) return false;
    if (lengthB > obb.halfSize.y + radius) return false;

    if (lengthA < obb.halfSize.x) return true;
    if (lengthB < obb.halfSize.y) return true;

    float x = lengthA - obb.halfSize.x;
    float y = lengthB - obb.halfSize.y;

    float edgeToCircle = sqrt(x * x + y * y);

    return edgeToCircle < radius;
}

RectCollider::ObbDesc RectCollider::GetObb()
{
    obbDesc.position = GlobalPosition();

    obbDesc.halfSize = Size() * 0.5f;

    obbDesc.axis[0] = Right();
    obbDesc.axis[1] = Up();

    return obbDesc;
}

void RectCollider::CreateLine()
{
    Vector2 half = size * 0.5f;

    vertices.emplace_back(-half.x, +half.y);
    vertices.emplace_back(+half.x, +half.y);
    vertices.emplace_back(+half.x, -half.y);
    vertices.emplace_back(-half.x, -half.y);
    vertices.emplace_back(-half.x, +half.y);

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    float minRight = min(R(), rect->R());
    float maxLeft = max(L(), rect->L());
    float minTop = min(T(), rect->T());
    float maxBottom = max(B(), rect->B());

    Vector2 temp = Vector2(minRight - maxLeft, minTop - maxBottom);

    if (overlap != nullptr)
        *overlap = temp;

    if (temp.x > 0 && temp.y > 0)
        return true;

    return false;
}

//bool RectCollider::IsOBB(RectCollider* rect)
//{
//    ObbDesc obbA = GetObb();
//    ObbDesc obbB = rect->GetObb();
//
//    if (IsSeparate(obbA.axis[0], obbA, obbB)) return false;
//    if (IsSeparate(obbA.axis[1], obbA, obbB)) return false;
//    if (IsSeparate(obbB.axis[0], obbA, obbB)) return false;
//    if (IsSeparate(obbB.axis[1], obbA, obbB)) return false;
//
//    return true;
//}

bool RectCollider::IsOBB(RectCollider* rect)
{
    ObbDesc obbA = GetObb();
    ObbDesc obbB = rect->GetObb();

    Vector2 nea1 = obbA.axis[0];
    Vector2 ea1 = nea1 * obbA.halfSize.x;
    Vector2 nea2 = obbA.axis[1];
    Vector2 ea2 = nea2 * obbA.halfSize.y;

    Vector2 neb1 = obbB.axis[0];
    Vector2 eb1 = neb1 * obbB.halfSize.x;
    Vector2 neb2 = obbB.axis[1];
    Vector2 eb2 = neb2 * obbB.halfSize.y;

    Vector2 distance = obbA.position - obbB.position;

    //분리축 : nea1;
    float d = abs(Vector2::Dot(distance, nea1));
    float x = ea1.Length();
    float y = ProjLength(nea1, eb1, eb2);
    if (d > x + y)
        return false;

    //분리축 : nea2;
    d = abs(Vector2::Dot(distance, nea2));
    x = ea2.Length();
    y = ProjLength(nea2, eb1, eb2);
    if (d > x + y)
        return false;

    //분리축 : neb1;
    d = abs(Vector2::Dot(distance, neb1));
    x = eb1.Length();
    y = ProjLength(neb1, ea1, ea2);
    if (d > x + y)
        return false;

    //분리축 : neb2;
    d = abs(Vector2::Dot(distance, neb2));
    x = eb2.Length();
    y = ProjLength(neb2, ea1, ea2);
    if (d > x + y)
        return false;

    return true;
}

float RectCollider::ProjLength(Vector2 separate, Vector2 e1, Vector2 e2)
{
    float r1 = abs(Vector2::Dot(separate, e1));
    float r2 = abs(Vector2::Dot(separate, e2));
    
    return r1 + r2;
}

bool RectCollider::IsSeparate(Vector2 sperateAxis, ObbDesc box1, ObbDesc box2)
{
    float d = abs(Vector2::Dot(box1.position - box2.position, sperateAxis));

    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float x = ProjLength(sperateAxis, right, up);

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float y = ProjLength(sperateAxis, right, up);

    if (d > x + y)
        return true;

    return false;
}
