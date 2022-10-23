#include <stdlib.h>
#include "Conductivity.hxx"
#include "Opacity.hxx"
#include "allocators.hxx"

extern "C"{
typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;
typedef void* meanOpacity;
typedef void* conductivityObj;

void calculateConductivity(conductivityObj grain) {
  conductivity::mixedGrain<double> *thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  conductivity::solveSystem<double>(*thisGrain);
}
conductivityObj buildConductivity(char *dir) {
  std::string fileDir=std::string(dir);
  //fileDir.erase(std::remove_if(std::begin(fileDir), std::end(fileDir), [](unsigned char x) { return std::isspace(x); }), std::end(fileDir));
  //fileDir.erase(std::remove_if(std::begin(fileDir), std::end(fileDir), [](unsigned char x) { return x=='\x01'; }), std::end(fileDir));
  conductivity::mixedGrain<double> *thisGrain =
      new conductivity::mixedGrain<double>(std::move(
          conductivity::readGrainFromSetup<double>(fileDir, 1e-4)));
  return (void*) thisGrain;
}
double lambda(conductivityObj grain, int i){
  conductivity::mixedGrain<double> *thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return thisGrain->lambda_k[i]; 
}
void deallocateConductivityObject(conductivityObj grain){
  conductivity::mixedGrain<double> *thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain); 
  delete thisGrain;
}
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
meanOpacity makeMeanOpacity(double* k_in, double* l_in, double Temperature,int len){
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
void deallocateMeanOpacity(meanOpacity meanOpacityObject){
  auto thisMeanOpacity = static_cast<opacity::meanOpacity<double> *> (meanOpacityObject); 
  delete thisMeanOpacity;  
}
}
