#ifndef PHYSICS_H
#define PHYSICS_H
#include "particle.h"

class Physics {
    public:
        float G;
        float softening;
        float getDistance(Particle *p1, Particle *p2);
        float getAccX(Particle *p1, Particle *p2, float distance);
        float getAccY(Particle *p1, Particle *p2, float distance);
        float getAccZ(Particle *p1, Particle *p2, float distance);
        Physics(float G, float softening);
};

#endif /* PHYSICS_H */
