#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include "particle.h"
#include "physics.h"

class Simulation {
    public:
        int particlesNumber;
        std::vector<float> xPositions;
        std::vector<float> yPositions;
        std::vector<float> zPositions;
        std::vector<float> xForces;
        std::vector<float> yForces;
        std::vector<float> zForces;
        std::vector<float> masses;
        std::vector<float> reds;
        std::vector<float> greens;
        std::vector<float> blues;
        bool simulationPaused;
        Physics *physics;
        Simulation(int particlesNumber, Physics *physics);
        void togglePause();
        void generateRandomParticles(float range, bool canBeNegative);
        void calculateForces();
        void addParticle(
            float xPos, float yPos, float zPos,
            float xForce, float yForce, float zForce,
            float mass, float red, float green, float blue);
        Particle getParticleAt(int index);
        void updatePositions();
};

#endif /* SIMULATION_H */
