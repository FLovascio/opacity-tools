#pragma once

#include <stdlib.h>

typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;


dustDist makeDustDist(double* size, double* density, int len);
void setDustSize(double* size, dustDist dist, int len);
void setDensity( double* rho, dustDist dist, int len);
void calculateOpacity(dustDist dist, conductivityObj conductivity, opacityVector opacities);
