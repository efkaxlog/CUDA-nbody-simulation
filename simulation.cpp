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
        p.mass = 0.000001f;
        addParticle(p);
        index ++;
    }
}

/**
    Only creates a cube correctly if the cube root of the 
    number of particles is a whole integer.
*/
void Simulation::makeCube() {
    int index = 0;
    float xPos, yPos, zPos;
    xPos = yPos = zPos = 30.0f * 30.0f;
    int side = 30;
    float inc = xPos / side;
    for(int i=0; i < side; i++) {
        for(int j=0; j< side; j++) {
            for(int k=0; k<side; k++) {
                Particle particle(0.0001f, 0.0f, 0.0f, 0.0f, xPos, yPos, zPos, 1.0f, 1.0f, 1.0f);
                addParticle(particle);
                xPos -= inc;
            }
        xPos = 10.0f;
        yPos -= inc;
        }
    yPos = 10.0f;
    zPos -= inc;
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

void Simulation::addParticle(Particle p) {
    xPositions.push_back(p.xPos);
    yPositions.push_back(p.yPos);
    zPositions.push_back(p.zPos);
    xForces.push_back(p.xForce);
    yForces.push_back(p.yForce);
    zForces.push_back(p.zForce);
    masses.push_back(p.mass);
    reds.push_back(p.red);
    greens.push_back(p.green);
    blues.push_back(p.blue);
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
