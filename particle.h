#ifndef PARTICLE_H
#define PARTICLE_H
#include <array>

class Particle {
    public:
        float mass;
        float xForce, yForce, zForce; // velocity x, y, z
        float xPos, yPos, zPos;
        float red, green, blue; // colours
        Particle();
        Particle(float mass, float xForce, float yForce, float zForce,
                 float xPos, float yPos, float zPos, 
                 float red, float green, float blue);
        void printPos();
};

Particle generateRandomParticle(float range, bool canBeNegative);

#endif /* PARTICLE_H */
