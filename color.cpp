#include "color.h"

const Color Color::white = Color(1, 1, 1);

Color::Color(float red, float green, float blue, float alpha)
    : red(red), green(green), blue(blue), alpha(alpha)
{

}