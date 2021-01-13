#include <cmath>
#include "vec2.h"

const Vec2 Vec2::zero = Vec2(0.0, 0.0);

Vec2::Vec2()
{

}

Vec2::Vec2(double x, double y) : x(x), y(y)
{

}

std::array<double, 2> Vec2::get_iterable() const
{
    return std::array<double, 2>{this->x, this->y};
}

bool Vec2::operator==(const Vec2& v) const
{
    return this->x == v.x && this->y == v.y;
}

bool Vec2::operator!=(const Vec2& v) const
{
    return !(*this == v);
}

Vec2 Vec2::operator-(const Vec2& v) const
{
    return Vec2(this->x - v.x, this->y - v.y);
}

Vec2 Vec2::operator+(const Vec2& v) const
{
    return Vec2(this->x + v.x, this->y + v.y);
}

Vec2 Vec2::operator*(const Vec2& v) const
{
    return Vec2(this->x * v.x, this->y * v.y);
}

Vec2 Vec2::operator/(const double d) const
{
    return Vec2(this->x / d, this->y / d);
}

Vec2 Vec2::operator*(const double d) const
{
    return Vec2(this->x * d, this->y * d);
}

std::ostream& operator<<(std::ostream& stream, const Vec2& v)
{
    return stream << "(" << v.x << ", " << v.y << ")";
}

double Vec2::dot(const Vec2& v) const
{
    return this->x * v.x + this->y * v.y;
}

double Vec2::length() const
{
    return sqrt(dot(*this));
}

double Vec2::distance(const Vec2& v) const
{
    return (*this - v).length();
}

double Vec2::angle(const Vec2& v) const
{
    return acos(this->dot(v) / (this->length() + v.length()));
}

Vec2 Vec2::normalize()
{
    return Vec2(this->x / this->length(), this->y / this->length());
}