#ifndef VERTEX_H
#define VERTEX_H

#include "Math.h"

struct Vertex
{
    Vector pos;
    Vector texCoords;
    Vector normal;
    Vector color;

    Vector lightning;

    Vertex(Vector pos = Vector(), Vector texCoords = Vector(), Vector normal = Vector(), Vector color = Vector(), Vector lightning = VEC(1.0f)) : pos(pos), texCoords(texCoords), normal(normal), color(color), lightning(lightning) {};
};

#endif