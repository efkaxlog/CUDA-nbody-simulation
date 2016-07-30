#include "simulation.h"

Simulation::Simulation(int particlesNumber, Physics *physics) {
    this->particlesNumber = particlesNumber;
    simulationPaused = true;
    this->physics = physics;

} 

void Simulation::togglePause() {
    simulationPaused = !simulationPaused;
}

void Simulation::generateRandomParticles(float range, bool canBeNegative) {
    int index = 0;
    while(index < particlesNumber) {
        Particle p = generateRandomParticle(range, canBeNegative);
        p.mass = 0.0001f;
        addParticle(p.xPos, p.yPos, p.zPos, p.xForce, p.yForce, p.zForce,
            p.mass, p.red, p.green, p.blue);
        index ++;
    }
}

void Simulation::calculateForces() {
    for(int i=0; i<particlesNumber; i++) {
        float particleX = xPositions[i];
        float particleY = yPositions[i];
        float particleZ = zPositions[i];
        for(int j=0; j<particlesNumber;j++) {
            if(i==j) {
                continue;
            }
            float otherParticleX = xPositions[j];
            float otherParticleY = yPositions[j];
            float otherParticleZ = zPositions[j];
            float otherParticleMass = masses[j];
            float distance = physics->getDistance(
                otherParticleX, particleX,
                otherParticleY, particleY,
                otherParticleZ, particleZ);
            xForces[i] += physics->getForce(otherParticleX, particleX, otherParticleMass, distance);
            yForces[i] += physics->getForce(otherParticleY, particleY, otherParticleMass, distance);
            zForces[i] += physics->getForce(otherParticleZ, particleZ, otherParticleMass, distance);
        }
        xPositions[i] += xForces[i];
        yPositions[i] += yForces[i];
        zPositions[i] += zForces[i];
    }
}

void Simulation::addParticle(
        float xPos, float yPos, float zPos,
        float xForce, float yForce, float zForce,
        float mass, float red, float green, float blue) {
    xPositions.push_back(xPos);
    yPositions.push_back(yPos);
    zPositions.push_back(zPos);
    xForces.push_back(xForce);
    yForces.push_back(yForce);
    zForces.push_back(zForce);
    masses.push_back(mass);
    reds.push_back(red);
    greens.push_back(green);
    blues.push_back(blue);
}

Particle Simulation::getParticleAt(int i) {
    return Particle(masses[i], xForces[i], yForces[i], zForces[i],
        xPositions[i], yPositions[i], zPositions[i], reds[i], greens[i], blues[i]);
}

void Simulation::updatePositions() {
    for (int i=0; i<particlesNumber; i++) {
        xPositions[i] += xForces[i];
        yPositions[i] += yForces[i];
        zPositions[i] += zForces[i];
    }
}
