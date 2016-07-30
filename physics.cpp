#include "physics.h"
#include "math.h"
#include <cmath>
#include <iostream>

Physics::Physics(float G, float softening) {
    this->G = G;
    this->softening = softening;
}

float Physics::getDistance(float xPos, float xPosOther,
                  float yPos, float yPosOther,
                  float zPos, float zPosOther) {
    float distx = xPos - xPosOther;
    float disty = yPos - yPosOther;
    float distz = zPos - zPosOther;
    return sqrt(distx*distx + disty*disty + distz*distz);
}

float Physics::getForce(float pos, float otherPos, float mass, float distance) {
    return G * mass / distance * (pos - otherPos) * softening;
}
