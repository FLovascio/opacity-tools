#pragma once

#include <stdlib.h>

typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;


extern "C" dustDist makeDustDist(double* size, double* density, int len);
extern "C" void setDustSize(double* size, dustDist dist, int len);
extern "C" void setDensity( double* rho, dustDist dist, int len);
extern "C" void calculateOpacity(dustDist dist, conductivityObj conductivity, opacityVector opacities);
extern "C" void deallocateDust(dustDist distribution);