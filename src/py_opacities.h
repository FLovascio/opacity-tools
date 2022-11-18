#include <stdlib.h>
#include "Conductivity.hxx"
#include "Opacity.hxx"
#include "allocators.hxx"

typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;
typedef void* meanOpacity;
typedef void* mixedGrainPointer;
typedef void* coatedGrainPointer;

// general methods
extern "C" void conductivitiesHelp();
// mixedGrain methods
extern "C" mixedGrainPointer makeMixedGrain(char *dir);
extern "C" void solveBreugmannSystem(mixedGrainPointer grain);
extern "C" void deleteMixedGrain(mixedGrainPointer grain);
// coatedGrain methods
extern "C" coatedGrainPointer makeCoatedGrain(mixedGrainPointer inner_, mixedGrainPointer outer_, double r1_, double r2_);
extern "C" void solveCoatedGrainSystem(coatedGrainPointer grain);
extern "C" void setOuter(coatedGrainPointer grain, mixedGrainPointer outer_, double r1_,double r2_);
extern "C" void setInner(coatedGrainPointer grain, mixedGrainPointer inner_, double r1_,double r2_);
extern "C" void addLayer(coatedGrainPointer grain, mixedGrainPointer coating_, double thickness);
// legacy methods
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