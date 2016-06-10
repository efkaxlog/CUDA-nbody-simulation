#ifndef PARTICLE_H
#define PARTICLE_H
#include <array>

class Particle {
    public:
        float mass;
        float dx, dy, dz; // velocity x, y, z
        float xPos, yPos, zPos;
        float size;
        float r, g, b; // colours
        Particle();
        Particle(float mass, float dx, float dy, float dz,
                 float xPos, float yPos, float zPos, float size,
                 float r, float g, float b);
        bool operator==(const Particle &otherParticle);
        std::array<float, 3> getPosition();
        std::array<float, 3> getColours();
        void printPos();
};

Particle generateRandomParticle();

#endif /* PARTICLE_H */
