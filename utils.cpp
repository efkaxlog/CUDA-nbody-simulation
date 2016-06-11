#include "utils.h"
#include <cstdlib>
#include <time.h>

float generateRandomNumber(float range, bool canBeNegative)
{
    float number = ((float(rand()) / float(RAND_MAX)) * (range - -range)) + -range;
    if (!canBeNegative && number < 0)
        number = -number;
    return number;
}
