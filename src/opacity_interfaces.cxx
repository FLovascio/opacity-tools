#include <stdlib.h>
#include "Conductivity.hxx"
#include "Opacity.hxx"

extern "C"{
typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;

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
void setDustSize(double* size, dustDist distribution, int len){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (distribution); 
  thisDistribution->dustSizeBins=std::vector<double>(size,size+len);
}
void setDensity(double* density, dustDist distribution,int len){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (distribution); 
  thisDistribution->dustSizeDensity=std::vector<double>(density,density+len);
}
void calculateOpacity(dustDist distribution,conductivityObj grain,opacityVector opacities){
  dust::dustDistribution<double> &thisDistribution = *static_cast<dust::dustDistribution<double> *> (distribution); 
  conductivity::mixedGrain<double> &thisGrain = *static_cast<conductivity::mixedGrain<double> *> (grain); 
  std::vector<double> &thisOpacity = *static_cast<std::vector<double>*> (opacities);
  opacity::KappaDust_fast<double>(thisOpacity, thisGrain, thisDistribution);  
}
void deallocateDust(dustDist distribution){
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (distribution); 
  delete thisDistribution; 
}
#endif
};