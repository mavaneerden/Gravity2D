#include <GL/glut.h>
#include "mouse.h"

void MouseState::changePosition(double x, double y)
{
    this->position.x = x;
    this->position.y = y;
}

void MouseState::changeState(int button, int state)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        this->leftButtonPressed = !state;
        break;
    case GLUT_RIGHT_BUTTON:
        this->rightButtonPressed = !state;
        break;
    case GLUT_MIDDLE_BUTTON:
        this->middleButtonPressed = !state;
        break;
    }
}