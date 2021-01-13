#include <iostream>
#include <cmath>
#include "body.h"

Body::Body(double mass, Vec2 position, Vec2 velocity) : mass(mass), position(position), velocity(velocity), acceleration{Vec2::zero}, color{Color::white}
{

}

void Body::timeStepStart(std::vector<Body> bodies)
{
    this->acceleration = Vec2::zero;
    // std::cout << "Acc Before: " << this->acceleration << std::endl;
    calculateAcceleration(bodies);
    // std::cout << "Acc After: " << this->acceleration << std::endl;
}

void Body::timeStepEnd()
{
    // std::cout << "Acc Before: " << this->acceleration << std::endl;
    // std::cout << "Vel Before: " << this->velocity << std::endl;
    // std::cout << "Pos Before: " << this->position << std::endl;
    calculateVelocity();
    calculatePosition();
    // std::cout << "Vel After: " << this->velocity << std::endl;
    // std::cout << "Pos After: " << this->position << std::endl;
}

void Body::calculateAcceleration(std::vector<Body> bodies)
{
    for (Body body : bodies)
    {
        if (body.position != this->position)
        {
            double r = this->position.distance(body.position);
            double forceMagnitude = (G * body.mass) / (r * r);
            this->acceleration = this->acceleration + (body.position - this->position).normalize() * forceMagnitude;
        }
    }
}

void Body::calculateVelocity()
{
    this->velocity = this->velocity + this->acceleration;
}

void Body::calculatePosition()
{
    this->position = this->position + this->velocity;
}

Vec2 Body::getCircularVelocity(Body parent)
{
    double magnitude = sqrt(G * parent.mass / this->getDistanceTo(parent));
    Vec2 directionNormal = (this->position - parent.position).normalize();
    Vec2 direction = Vec2::zero;
    direction.x = -directionNormal.y;
    direction.y = directionNormal.x;

    return direction * magnitude + parent.velocity;
}

void Body::setCircularVelocity(Body parent)
{
    this->velocity = this->getCircularVelocity(parent);
}

double Body::getDistanceTo(Body other)
{
    return this->position.distance(other.position);
}