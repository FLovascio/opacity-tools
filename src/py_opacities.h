#include <stdlib.h>
#include "Conductivity.hxx"
#include "Opacity.hxx"
#include "allocators.hxx"

typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;
typedef void* meanOpacity;
typedef void* conductivityObj;

extern "C" conductivityObj buildConductivity(char *dir);
extern "C" void calculateConductivity(conductivityObj grain);
extern "C" double lambda(conductivityObj grain, int i);
extern "C" void deallocateConductivityObject(conductivityObj grain);
extern "C" dustDist makeDustDist(double* size, double* density, int len);
extern "C" opacityVector makeOpacityVector(int len);
extern "C" void setDustSize(double* size, dustDist distribution, int len);
extern "C" void setDensity(double* density, dustDist distribution,int len);
extern "C" void calculateOpacity(dustDist distribution,conductivityObj grain,double* opacities);
extern "C" void deallocateDust(dustDist distribution);
extern "C" meanOpacity makeMeanOpacity(double* k_in, double* l_in, double Temperature,int len);
extern "C" void setKappa_nu(double* k_nu,meanOpacity meanOpacityObject);
extern "C" void setTemperature(double T,meanOpacity meanOpacityObject);
extern "C" void computePlanck(meanOpacity meanOpacityObject);
extern "C" void computeRosseland(meanOpacity meanOpacityObject);
extern "C" double getPlanck(meanOpacity meanOpacityObject);
extern "C" double getRosseland(meanOpacity meanOpacityObject);
extern "C" void deallocateMeanOpacity(meanOpacity meanOpacityObject);