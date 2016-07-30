#include "nbody.h"
#include <iostream>

float *deviceXpos, *deviceYpos, *deviceZpos;
float *deviceXforces, *deviceYforces, *deviceZforces;
float *deviceMasses;
int particlesMemorySize;
Simulation *sim;

void cudaCalculate() {
    calculateForcesCuda<<<32711, 1024>>>(
        deviceXpos, deviceYpos, deviceZpos,
        deviceXforces, deviceYforces, deviceZforces,
        deviceMasses, sim->particlesNumber);
}

__global__ void calculateForcesCuda(float *deviceXpos, float *deviceYpos, float *deviceZpos, 
                                   float *deviceXforces, float *deviceYforces, float *deviceZforces,
                                   float *deviceMasses, int particlesNumber) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    if (tid < particlesNumber*particlesNumber) {
        int particleIndex = tid / particlesNumber;
        int otherParticleIndex = tid % particlesNumber;
        if (particleIndex != otherParticleIndex) {
            float particleXpos = deviceXpos[otherParticleIndex];
            float particleYpos = deviceYpos[otherParticleIndex];
            float particleZpos = deviceZpos[otherParticleIndex];
            float otherXpos = deviceXpos[particleIndex];
            float otherYpos = deviceYpos[particleIndex];
            float otherZpos = deviceZpos[particleIndex];
            float mass = deviceMasses[particleIndex];
            float distx = otherXpos - particleXpos; 
            float disty = otherYpos - particleYpos; 
            float distz = otherZpos - particleZpos;
            float distance = sqrt(distx*distx + disty*disty + distz*distz);
            float xForce = 10.0f * mass / distance * (otherXpos - particleXpos) * 0.01f; 
            float yForce = 10.0f * mass / distance * (otherYpos - particleYpos) * 0.01f; 
            float zForce = 10.0f * mass / distance * (otherZpos - particleZpos) * 0.01f; 
            deviceXforces[otherParticleIndex] += xForce;
            deviceYforces[otherParticleIndex] += yForce;
            deviceZforces[otherParticleIndex] += zForce;
        }
    }
}

void setupCuda(Simulation *simulation) {
    sim = simulation;
    particlesMemorySize = sim->particlesNumber * sizeof(float);
    prepareCuda();
}

void prepareCuda() {
    cudaMalloc((void**)&deviceXpos, particlesMemorySize);
    cudaMemcpy(deviceXpos, sim->xPositions.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);

    cudaMalloc((void**)&deviceYpos, particlesMemorySize);
    cudaMemcpy(deviceYpos, sim->yPositions.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
    
    cudaMalloc((void**)&deviceZpos, particlesMemorySize);
    cudaMemcpy(deviceZpos, sim->yPositions.data(),
    particlesMemorySize, cudaMemcpyHostToDevice);
    
    cudaMalloc((void**)&deviceXforces, particlesMemorySize);
    cudaMemcpy(deviceXforces, sim->xForces.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
    
    cudaMalloc((void**)&deviceYforces, particlesMemorySize);
    cudaMemcpy(deviceYforces, sim->yForces.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
    
    cudaMalloc((void**)&deviceZforces, particlesMemorySize);
    cudaMemcpy(deviceZforces, sim->zForces.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
    
    cudaMalloc((void**)&deviceMasses, particlesMemorySize);
    cudaMemcpy(deviceMasses, sim->masses.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
}

void updateData() {
    cudaMemcpy(sim->xForces.data(), deviceXforces,
        particlesMemorySize, cudaMemcpyDeviceToHost);
    cudaMemcpy(sim->yForces.data(), deviceYforces,
        particlesMemorySize, cudaMemcpyDeviceToHost);
    cudaMemcpy(sim->zForces.data(), deviceZforces,
        particlesMemorySize, cudaMemcpyDeviceToHost);
    
    cudaMemcpy(deviceXpos, sim->xPositions.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
    
    cudaMemcpy(deviceYpos, sim->yPositions.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
    
    cudaMemcpy(deviceZpos, sim->zPositions.data(),
        particlesMemorySize, cudaMemcpyHostToDevice);
}

void cleanupCuda() {
     cudaFree(deviceXpos);
     cudaFree(deviceYpos);
     cudaFree(deviceZpos);
     cudaFree(deviceXforces);
     cudaFree(deviceYforces);
     cudaFree(deviceZforces);
     cudaFree(deviceMasses);
}
