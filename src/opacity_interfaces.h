#pragma once

#include <stdlib.h>

typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;
typedef void* meanOpacity;

extern "C" dustDist makeDustDist(double* size, double* density, int len);
extern "C" opacityVector makeOpacityVector(int len);
extern "C" void setDustSize(double* size, dustDist dist, int len);
extern "C" void setDensity( double* rho, dustDist dist, int len);
extern "C" void calculateOpacity(dustDist dist, conductivityObj conductivity, opacityVector opacities);
extern "C" void deallocateDust(dustDist distribution);
extern "C" meanOpacity makeMeanOpacity(const double* k_in, const double* l_in, double Temperature,int len);
extern "C" void setKappa_nu(double* k_nu,meanOpacity meanOpacityObject);
extern "C" void setTemperature(double T,meanOpacity meanOpacityObject);
extern "C" void computePlanck(meanOpacity meanOpacityObject);
extern "C" void computeRosseland(meanOpacity meanOpacityObject);
extern "C" double getPlanck(meanOpacity meanOpacityObject);
extern "C" double getRosseland(meanOpacity meanOpacityObject);