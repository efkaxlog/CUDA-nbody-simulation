#ifndef PHYSICS_H
#define PHYSICS_H
#include "particle.h"

class Physics {
    public:
        float G;
        float softening;
        float getDistance(float xPos, float xPosOther,
                          float yPos, float yPosOther,
                          float zPos, float zPosOther);
        float getForce(float pos, float otherPos, float mass, float distance);
        Physics(float G, float softening);
};

#endif /* PHYSICS_H */
