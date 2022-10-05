#include <stdlib.h>
#include "Conductivity.hxx"
#include "Opacity.hxx"
#include "allocators.hxx"

extern "C"{
typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;
typedef void* meanOpacity;

#ifdef FP32
dustDist makeDustDist(float* size, float* density, int len){
  auto * dustDistribution=new dust::dustDistribution<float>(std::move(dust::dustDistribution<float>(size,density, len)));
  return (void*) dustDistribution;
}
void setDustSize(float* size, dustDist distribution, int len){
  auto thisDistribution = static_cast<dust::dustDistribution<float> *> (distribution); 
  thisDistribution->dustSizeBins=std::vector<float>(size,size+len);
}
void setDensity(float* density, dustDist distribution,int len){
  auto thisDistribution = static_cast<dust::dustDistribution<float> *> (distribution); 
  thisDistribution->dustSizeDensity=std::vector<float>(density,density+len);
}
void calculateOpacity(dustDist distribution,conductivityObj grain,opacityVector opacities){
  dust::dustDistribution<float> &thisDistribution = *static_cast<dust::dustDistribution<float> *> (distribution); 
  conductivity::mixedGrain<float> &thisGrain = *static_cast<conductivity::mixedGrain<float> *> (grain); 
  std::vector<float> &thisOpacity = *static_cast<std::vector<float>*> (opacities);
  opacity::KappaDust_fast<float>(thisOpacity, thisGrain, thisDistribution);  
}
void deallocateDust(dustDist distribution){
  auto thisDistribution = static_cast<dust::dustDistribution<float> *> (distribution); 
  delete thisDistribution; 
}
#else
dustDist makeDustDist(double* size, double* density, int len){
  auto dustDistribution=new dust::dustDistribution<double>(std::move(dust::dustDistribution<double>(size,density, len)));
  return (void*) dustDistribution;
}
opacityVector makeOpacityVector(int len){
  std::vector<double> Opacity(0.0,len);
  auto thisOpacity=new std::vector<double>(std::move(Opacity));
  return (void*) thisOpacity;
}
void setDustSize(double* size, dustDist distribution, int len){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (distribution); 
  thisDistribution->dustSizeBins=std::vector<double>(size,size+len);
}
void setDensity(double* density, dustDist distribution,int len){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (distribution); 
  thisDistribution->dustSizeDensity=std::vector<double>(density,density+len);
}
void calculateOpacity(dustDist distribution,conductivityObj grain,double* opacities){
  dust::dustDistribution<double> &thisDistribution = *static_cast<dust::dustDistribution<double> *> (distribution); 
  conductivity::mixedGrain<double> &thisGrain = *static_cast<conductivity::mixedGrain<double> *> (grain); 
  opacity::KappaDust_fast_Array<double>(opacities, thisGrain, thisDistribution);  
}
void deallocateDust(dustDist distribution){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (distribution); 
  delete thisDistribution; 
}
meanOpacity makeMeanOpacity(const double* k_in, const double* l_in, double Temperature,int len){
  auto meanOpacityObject=new opacity::meanOpacity<double>(opacity::meanOpacity<double>(k_in,l_in,Temperature,len));
  return (void*) meanOpacityObject;
}
void setKappa_nu(double* k_nu,meanOpacity meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (meanOpacityObject);
  thisMeanOpacity->setKappa_nu(k_nu);
}
void setTemperature(double T,meanOpacity meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (meanOpacityObject);
  thisMeanOpacity->setTemperature(T);
}
void computePlanck(meanOpacity meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (meanOpacityObject);
  thisMeanOpacity->Planck();
}
void computeRosseland(meanOpacity meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (meanOpacityObject);
  thisMeanOpacity->Rosseland();
}
double getPlanck(meanOpacity meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (meanOpacityObject);
  return thisMeanOpacity->planck;
}
double getRosseland(meanOpacity meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (meanOpacityObject);
  return thisMeanOpacity->rosseland;
}

dustDist makedustdist_(double* size, double* density, int* len){
  auto dustDistribution=new dust::dustDistribution<double>(std::move(dust::dustDistribution<double>(size,density,*len)));
  return (void*) dustDistribution;
}
meanOpacity makemeanopacity_(double* k_in, double* l_in, double* Temperature, int* len){
  auto meanOpacityObject=new opacity::meanOpacity<double>(opacity::meanOpacity<double>(k_in,l_in,*Temperature,*len));
  return (void*) meanOpacityObject; 
}
opacityVector makeopacityvector_(int* len){
  std::vector<double> Opacity(0.0,*len);
  auto thisOpacity=new std::vector<double>(std::move(Opacity));
  return (void*) thisOpacity;
}
void setdustsize_(double* size, dustDist* distribution, int* len){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (*distribution); 
  thisDistribution->dustSizeBins=std::vector<double>(size,(size)+(*len));
}
void setdensity_(double* density, dustDist* distribution,int* len){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (*distribution); 
  thisDistribution->dustSizeDensity=std::vector<double>(density,(density)+(*len));
}
void calculateopacity_(dustDist* distribution,conductivityObj* grain,double* opacities){
  dust::dustDistribution<double> &thisDistribution = *static_cast<dust::dustDistribution<double> *> (*distribution); 
  conductivity::mixedGrain<double> &thisGrain = *static_cast<conductivity::mixedGrain<double> *> (*grain); 
  opacity::KappaDust_fast_Array<double>(opacities, thisGrain, thisDistribution);  
}
void deallocatedust_(dustDist* distribution){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (*distribution); 
  delete thisDistribution; 
}
void setkappa_nu_(double* k_nu,meanOpacity* meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (*meanOpacityObject);
  thisMeanOpacity->setKappa_nu(k_nu);
}
void settemperature_(double* T,meanOpacity* meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (*meanOpacityObject);
  thisMeanOpacity->setTemperature(*T);
}
void computeplanck_(meanOpacity* meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (*meanOpacityObject);
  thisMeanOpacity->Planck();
}
void computerosseland_(meanOpacity* meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (*meanOpacityObject);
  thisMeanOpacity->Rosseland();
}
double getplanck_(meanOpacity* meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (*meanOpacityObject);
  return thisMeanOpacity->planck;
}
double getrosseland_(meanOpacity* meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (*meanOpacityObject);
  return thisMeanOpacity->rosseland;
}
#endif
};