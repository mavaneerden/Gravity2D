#ifndef MOUSE_H_
#define MOUSE_H_

#include "vec2.h"

class MouseState
{
public:
    Vec2 position;
    bool leftButtonPressed;
    bool rightButtonPressed;
    bool middleButtonPressed;

public:
    void changePosition(double x, double y);
    void changeState(int button, int state);
};

#endif // MOUSE_H_
