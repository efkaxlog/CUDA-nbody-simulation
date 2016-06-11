#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include "particle.h"
#include "physics.h"

class Simulation {
    public:
        int particlesNumber;
        std::vector<Particle> particles;
        bool simulationPaused;
        Physics *physics;
        Simulation(int particlesNumber, Physics *physics);
        void togglePause();
        void makeCube();
        void generateRandomParticles(float range, bool canBeNegative);
        void calculateForces();
};

#endif /* SIMULATION_H */
