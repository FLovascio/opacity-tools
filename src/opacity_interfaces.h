#pragma once

#include <stdlib.h>

typedef void* dustDist;
typedef void* conductivityObj;
#ifdef FP32
typedef float* opacityVector;
#else
typedef double* opacityVector;
#endif

dustDist makeDustDist(double* size, double* density, int len);
void setDustSize(dustDist dist, double* size);
void setDensity(dustDist dist, double* rho);
void calculateOpacity(dustDist dist, conductivityObj conductivity);
