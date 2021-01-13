#ifndef VEC2_H_
#define VEC2_H_

#include <iostream>
#include <array>

class Vec2
{
public:
    double x;
    double y;
    static const Vec2 zero;

public:
    Vec2();
    Vec2(double x, double y);

public:
    std::array<double, 2> get_iterable() const;
    bool operator==(const Vec2& v) const;
    bool operator!=(const Vec2& v) const;
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(const Vec2& v) const;
    Vec2 operator*(const double d) const;
    Vec2 operator/(const double d) const;
    double dot(const Vec2& v) const;
    double length() const;
    double distance(const Vec2& v) const;
    double angle(const Vec2& v) const;
    Vec2 normalize();

public:
    friend std::ostream& operator<<(std::ostream& stream, const Vec2& v);
};

#endif /* VEC2_H_ */
