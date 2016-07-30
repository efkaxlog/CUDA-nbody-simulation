#include "particle.h"
#include "utils.h"
#include <iostream>
using std::cout;

Particle::Particle() {
    mass = 50.0f;
    xForce = yForce = zForce = 0.05f;
    xPos = yPos = zPos = 0.0f;
    red = green = blue = 1.0f;
}

Particle::Particle(float mass, float xForce, float yForce, float zForce,
                    float xPos, float yPos, float zPos,
                    float red, float green, float blue) {
    this->mass = mass;
    this->xForce = xForce;
    this->yForce = yForce;
    this->zForce = zForce;
    this->xPos = xPos;
    this->yPos = yPos;
    this->zPos = zPos;
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Particle generateRandomParticle(float range, bool canBeNegative) {
    float mass = 1.0f;
    float xForce = 0.0f;
    float yForce = 0.0f;
    float zForce = 0.0f;
    float xPos = generateRandomNumber(range, canBeNegative); 
    float yPos = generateRandomNumber(range, canBeNegative);
    float zPos = generateRandomNumber(range, canBeNegative);
    float red = generateRandomNumber(1.0f, false);
    float green = generateRandomNumber(1.0f, false);
    float blue = generateRandomNumber(1.0f, false);
    return Particle(mass, xForce, yForce, zForce, xPos, yPos, zPos,
        red, green, blue);
}

void Particle::printPos() {
    cout << "---------------\n";
    //cout << "x: " << xPos << "\n";
    //cout << "y: " << yPos << "\n";
    //cout << "z: " << zPos << "\n";
    cout << "force X: " << xForce << "\n";
    cout << "force Y: " << yForce << "\n";
    cout << "force Z: " << zForce << "\n";
    
}
