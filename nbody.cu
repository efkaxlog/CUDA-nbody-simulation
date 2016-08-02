#include "nbody.h"
#include <iostream>
#include <math.h>

namespace cuda {
    float *deviceXpos, *deviceYpos, *deviceZpos;
    float *deviceXforces, *deviceYforces, *deviceZforces;
    float *deviceMasses;
    int particlesMemorySize;
    int blocks, threads;
    int particlesNumber;
    Simulation *sim;
}

using namespace cuda;

void cudaCalculate() {
    calculateForcesCuda<<<blocks, threads>>>(
        deviceXpos, deviceYpos, deviceZpos,
        deviceXforces, deviceYforces, deviceZforces,
        deviceMasses, particlesNumber);
}

__global__ void calculateForcesCuda(float *deviceXpos, float *deviceYpos, float *deviceZpos, 
                                   float *deviceXforces, float *deviceYforces, float *deviceZforces,
                                   float *deviceMasses, int particlesNumber) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    float particleXpos = deviceXpos[tid];
    float particleYpos = deviceYpos[tid];
    float particleZpos = deviceZpos[tid];
    if (tid <= particlesNumber) {
        for (int index=0; index<particlesNumber; index++) {
            if (tid != index) {
                float otherXpos = deviceXpos[index];
                float otherYpos = deviceYpos[index];
                float otherZpos = deviceZpos[index];
                float mass = deviceMasses[index];
                float distx = particleXpos - otherXpos; 
                float disty = particleYpos - otherYpos;
                float distz = particleZpos - otherZpos; 
                float distance = sqrt((distx*distx + disty*disty + distz*distz) + 0.01f);
                deviceXforces[tid] += 10.0f * mass / distance * (otherXpos - particleXpos); 
                deviceYforces[tid] += 10.0f * mass / distance * (otherYpos - particleYpos); 
                deviceZforces[tid] += 10.0f * mass / distance * (otherZpos - particleZpos); 
            }
        }
    }
}

void setupCuda(Simulation *simulation, int threads) {
    sim = simulation;
    particlesNumber = sim->particlesNumber;
    particlesMemorySize = particlesNumber * sizeof(float);
    cuda::threads = threads;
    blocks = particlesNumber / threads + 1;
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
    cudaMemcpy(deviceZpos, sim->zPositions.data(),
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
