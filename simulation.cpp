#include "simulation.h"

Simulation::Simulation(int particlesNumber, Physics *physics) {
    this->particlesNumber = particlesNumber;
    simulationPaused = true;
    this->physics = physics;

} 

void Simulation::togglePause() {
    simulationPaused = !simulationPaused;
}

void Simulation::makeCube() {
    int index = 0;
    float xPos, yPos, zPos;
    xPos = yPos = zPos = 10.0f;
    int side = 10;
    float inc = xPos / side;
    for(int i=0; i < side; i++) {
        for(int j=0; j< side; j++) {
            for(int k=0; k<side; k++) {
                Particle particle(0.0001f, 0.0f, 0.0f, 0.0f, xPos, yPos, zPos, 0.1f, 1.0f, 1.0f, 1.0f);
                particles.push_back(particle);
                xPos -= inc;
            }
        xPos = 10.0f;
        yPos -= inc;
        }
    yPos = 10.0f;
    zPos -= inc;
    }
}

void Simulation::generateRandomParticles(float range, bool canBeNegative) {
    int index = 0;
    while(index < particlesNumber) {
        Particle particle = generateRandomParticle(range, canBeNegative);
        particle.mass = 0.0001f;
        particles.push_back(particle);
        index ++;
    }
}

void Simulation::calculateForces() {
    for(Particle &particle : particles) {
        for(Particle &otherParticle : particles) {
            if(&particle == &otherParticle)  
                continue;
            float distance = physics->getDistance(&otherParticle, &particle);
            particle.dx += physics->getAccX(&otherParticle, &particle, distance);
            particle.dy += physics->getAccY(&otherParticle, &particle, distance);
            particle.dz += physics->getAccZ(&otherParticle, &particle, distance);
        }
        particle.xPos += particle.dx;
        particle.yPos += particle.dy;
        particle.zPos += particle.dz;
    }
}

