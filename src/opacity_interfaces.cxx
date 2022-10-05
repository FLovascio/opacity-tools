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
meanOpacity makeMeanOpacity(){}
void setKappa_nu(){}
void setLambda(){}
void computePlanck(){}
void computeRosseland(){}
double getPlanck(){}
double getRosseland(){}

dustDist makedustdist_(double* size, double* density, int* len){
  auto dustDistribution=new dust::dustDistribution<double>(std::move(dust::dustDistribution<double>(size,density,*len)));
  return (void*) dustDistribution;
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
#endif
};