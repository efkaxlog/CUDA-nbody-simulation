#include "nbody.h"
#include <iostream>
#include <math.h>

namespace cuda {
    float *deviceXpos, *deviceYpos, *deviceZpos;
    float *deviceXforces, *deviceYforces, *deviceZforces;
    float *deviceMasses;
    int particlesMemorySize;
    int blocks;
    const int threads = 64;
    int particlesNumber;
    Simulation *sim;
}

using namespace cuda;

void cudaCalculate() {
    calculateForcesCuda<<<blocks, threads>>>(
        deviceXpos, deviceYpos, deviceZpos,
        deviceXforces, deviceYforces, deviceZforces,
        particlesNumber);
}

__global__ void calculateForcesCuda(float *deviceXpos, float *deviceYpos, float *deviceZpos, 
                                    float *deviceXforces, float *deviceYforces, float *deviceZforces,
                                    int particlesNumber) {

    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    __shared__ float localPosX[threads];
    __shared__ float localPosY[threads];
    __shared__ float localPosZ[threads];
    float3 body = {deviceXpos[tid],
                   deviceYpos[tid],
                   deviceZpos[tid]};
    float3 force = {0.0f, 0.0f, 0.0f};
    const float mass = 0.0001f;
    const float G = 2.0f;

    for (unsigned int i=0; i<particlesNumber; i+=threads) {
        localPosX[threadIdx.x] = deviceXpos[i + threadIdx.x]; 
        localPosY[threadIdx.x] = deviceYpos[i + threadIdx.x]; 
        localPosZ[threadIdx.x] = deviceZpos[i + threadIdx.x]; 
        __syncthreads();

        for (unsigned int index=0; index<threads; index++) {
            float3 other = {localPosX[index], 
                            localPosY[index],
                            localPosZ[index]};
            float3 r = {body.x - other.x,
                        body.y - other.y,
                        body.z - other.z};
            float distance = sqrtf((r.x*r.x + r.y*r.y + r.z*r.z) + 0.01f);
            force.x += G * mass / distance * (other.x - body.x); 
            force.y += G * mass / distance * (other.y - body.y); 
            force.z += G * mass / distance * (other.z - body.z); 
        }
        __syncthreads();
    }
    deviceXforces[tid] += force.x; 
    deviceYforces[tid] += force.y;           
    deviceZforces[tid] += force.z;
}


void setupCuda(Simulation *simulation) {
    sim = simulation;
    particlesNumber = sim->particlesNumber;
    particlesMemorySize = particlesNumber * sizeof(float);
    blocks = particlesNumber / threads;
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
