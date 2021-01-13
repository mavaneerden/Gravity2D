#ifndef BODY_H_
#define BODY_H_

#include "vec2.h"
#include "vertex.h"
#include <vector>

// Factor: 1e16
#define G 6.67430

class Body
{
public:
    double mass;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    Color color;

public:
    Body(double mass, Vec2 position, Vec2 velocity = Vec2::zero);

public:
    void timeStepStart(std::vector<Body> bodies);
    void timeStepEnd();
    Vec2 getCircularVelocity(Body parent);
    void setCircularVelocity(Body parent);
    double getDistanceTo(Body other);
    void calculateVelocity();
    void calculatePosition();

private:
    void calculateAcceleration(std::vector<Body> bodies);
};

#endif /* BODY_H */
