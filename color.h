#ifndef COLOR_H_
#define COLOR_H_

class Color
{
public:
    float red;
    float green;
    float blue;
    float alpha;

public:
    static const Color white;

public:
    Color(float red, float green, float blue, float alpha = 1.0);
};

#endif /* COLOR_H_ */
