#pragma once

struct Vertex
{
    Float3 pos;
    Float2 uv;

    Vertex()
    {
        pos = { 0, 0, 0 };
        uv = { 0, 0 };
    }

    Vertex(float x, float y, float u, float v)
    {
        pos = { x, y, 0.0f };
        uv = { u, v };
    }
};

struct VertexPos
{
    Float3 pos;    

    VertexPos() : pos(0, 0, 0)
    {       
    }

    VertexPos(float x, float y) : pos(x, y, 0)
    {                
    }
};

struct VertexColor
{
    Float3 pos;
    Float4 color;

    VertexColor(float x, float y)
    {
        pos = { x, y, 0.0f };
        color = { 1, 1, 1, 1 };
    }

    VertexColor(float x, float y, float r, float g, float b)
    {
        pos = { x, y, 0.0f };
        color = { r, g, b, 1.0f };
    }
};