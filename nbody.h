#ifndef NBODY_H
#define NBODY_H

#include "simulation.h"

__global__ void calculateForcesCuda(float *deviceXpos, float *deviceYpos, float *deviceZpos, 
       float *deviceXforces, float *deviceYforces, float *deviceZforces,
       float *deviceMasses, int particlesNumber);
void cudaCalculate();
void setupCuda(Simulation *sim, int threads);
void prepareCuda();
void updateData();
void cleanupCuda();

#endif /* NBODY_H */
