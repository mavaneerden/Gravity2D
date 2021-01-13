#include "vertex.h"

Vertex::Vertex(Vec2 position, Color color) : position(position), color(color)
{

}

Vertex::Vertex(float x, float y, Color color) : position(Vec2(x, y)), color(color)
{

}

bool Vertex::operator==(const Vertex& v)
{
    return this->position == v.position;
}

Vertex Vertex::operator-(const Vertex& v)
{
    return Vertex(this->position - v.position, this->color);
}

Vertex Vertex::operator+(const Vertex& v)
{
    return Vertex(this->position + v.position, this->color);
}

Vertex Vertex::operator*(const Vertex& v)
{
    return Vertex(this->position * v.position, this->color);
}

// bool Vertex::operator==(const Vertex& v) const
// {
//     return this->position == v.position;
// }