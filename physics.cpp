#include "physics.h"
#include "math.h"
#include <cmath>
#include <iostream>

Physics::Physics(float G, float softening) {
    this->G = G;
    this->softening = softening;
}

float Physics::getDistance(Particle *p1, Particle *p2)
{
    float distx = p1->xPos - p2->xPos;
    float disty = p1->yPos - p2->yPos;
    float distz = p1->zPos - p2->zPos;
    return sqrt(distx*distx + disty*disty + distz*distz);
}

float Physics::getAccX(Particle *p1, Particle *p2, float d)
{
    return G * p1->mass / d * (p1->xPos - p2->xPos) * softening;
}


float Physics::getAccY(Particle *p1, Particle *p2, float d)
{

    return G * p1->mass / d * (p1->yPos - p2->yPos) * softening;
}

float Physics::getAccZ(Particle *p1, Particle *p2, float d)
{

    return G * p1->mass / d * (p1->zPos - p2->zPos) * softening;
}
