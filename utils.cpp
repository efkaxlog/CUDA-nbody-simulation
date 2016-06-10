#include "utils.h"
#include <cstdlib>
#include <time.h>

float generateRandomPositiveNumber(float range)
{
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / range));
}

float generateRandomNumber(float range)
{
    float number = generateRandomPositiveNumber(range); 
    if(number > range / 2)
    {
        return -number;
    }
    return number;
}
