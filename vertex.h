#ifndef VERTEX_H_
#define VERTEX_H_

#include "vec2.h"
#include "color.h"

class Vertex
{
public:
    Vec2 position;
    Color color;

public:
    Vertex(Vec2 position, Color color);
    Vertex(float x, float y, Color color);

public:
    bool operator==(const Vertex& v);
    Vertex operator+(const Vertex& v);
    Vertex operator-(const Vertex& v);
    Vertex operator*(const Vertex& v);
    // bool operator==(const Vertex& v) const;
};

#endif /* VERTEX_H_ */
