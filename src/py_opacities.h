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

/// general methods
void conductivitiesHelp();
// mixedGrain methods
mixedGrainPointer makeMixedGrain(char *dir);
void solveBreugmannSystem(mixedGrainPointer grain);
int get_nmaterials(mixedGrainPointer grain);
void* get_conductivitiesMixed(mixedGrainPointer grain);
void* get_lambdaMixed(mixedGrainPointer grain);
void* get_delta(mixedGrainPointer grain);
int get_lengthMixed(mixedGrainPointer grain);
void deleteMixedGrain(mixedGrainPointer grain);
// coatedGrain methods
coatedGrainPointer makeCoatedGrain(mixedGrainPointer inner_,
                                   mixedGrainPointer outer_, double r1_,
                                   double r2_);
void solveCoatedGrainSystem(coatedGrainPointer grain);
void setOuter(coatedGrainPointer grain, mixedGrainPointer outer_, double r1_,
              double r2_);
void setInner(coatedGrainPointer grain, mixedGrainPointer inner_, double r1_,
              double r2_);
void addLayer(coatedGrainPointer grain, mixedGrainPointer coating_, double thickness);
void* get_conductivitiesCoated(mixedGrainPointer grain);
int get_lengthCoated(mixedGrainPointer grain);
void* get_lambdaCoated(mixedGrainPointer grain);
void deleteCoatedGrain(coatedGrainPointer grain);
// dust distribution methods
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