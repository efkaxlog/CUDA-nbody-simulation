#include "particle.h"
#include "utils.h"
#include <iostream>
using std::cout;

Particle::Particle()
{
    mass = 50.0f;
    dx = dy = dz = 0.05f;
    xPos = yPos = zPos = 0.0f;
    size = 5.0f;
    r = g = b = 1.0f;
}

Particle::Particle(float mass, float dx, float dy, float dz,
                    float xPos, float yPos, float zPos, float size,
                    float r, float g, float b)
{
    this->mass = mass;
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
    this->xPos = xPos;
    this->yPos = yPos;
    this->zPos = zPos;
    this->size = size;
    this->r = r;
    this->g = g;
    this->b = b;
}

std::array<float, 3> Particle::getPosition()
{
    return {dx, dy, dz};
}

std::array<float, 3> Particle::getColours()
{
    return {r, g, b};
}

Particle generateRandomParticle()
{
    float mass = 1.0f;
    //float mass = generateRandomPositiveNumber(1000.0f);
    float dx = 0.0f;
    float dy = 0.0f;
    float dz = 0.0f;
    //float dx = generateRandomNumber(0.05f);
    //float dy = generateRandomNumber(0.05f);
    //float dz = generateRandomNumber(0.05f);
    float xPos = generateRandomNumber(10.0f); 
    float yPos = generateRandomNumber(10.0f);
    float zPos = generateRandomNumber(10.0f);
    float size = generateRandomPositiveNumber(5.0f);
    float r = generateRandomPositiveNumber(1.0f);
    float g = generateRandomPositiveNumber(1.0f);
    float b = generateRandomPositiveNumber(1.0f);
    return Particle(mass, dx, dy, dz, xPos, yPos, zPos,
                    size, r, g, b);
}

bool Particle::operator==(const Particle &otherParticle)
{
    return  !(*this == otherParticle);
}

void Particle::printPos()
{
    cout << "---------------\n";
    //cout << "x: " << xPos << "\n";
    //cout << "y: " << yPos << "\n";
    //cout << "z: " << zPos << "\n";
    cout << "dx: " << dx << "\n";
    cout << "dy: " << dy << "\n";
    cout << "dz: " << dz << "\n";
    
}
