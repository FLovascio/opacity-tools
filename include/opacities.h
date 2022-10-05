#pragma once

#include <stdlib.h>

typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;
typedef void* meanOpacity;


dustDist makeDustDist(double*, double*, int);
opacityVector makeOpacityVector(int);
void setDustSize(double*, dustDist, int);
void setDensity( double*, dustDist, int);
void calculateOpacity(dustDist, conductivityObj, opacityVector);
void deallocateDust(dustDist);
meanOpacity makeMeanOpacity(const double*, const double*, double,int);
void setKappa_nu(double*,meanOpacity);
void setTemperature(double,meanOpacity);
void computePlanck(meanOpacity);
void computeRosseland(meanOpacity);
double getPlanck(meanOpacity);
double getRosseland(meanOpacity);