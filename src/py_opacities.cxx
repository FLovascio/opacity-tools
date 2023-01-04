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
typedef void *mixedGrainPointer;
typedef void *mixedPercolatedGrainPointer;
typedef void *coatedGrainPointer;
typedef void *grainHandlerPointer;

// general methods
void conductivitiesHelp(){
  std::cout<<"Info for grain types:"<<"\n"<<
  "mixedGrain: homogeneous grain made of mixed materials,\n effective medium approximation is calculated by Breugmann theory" << "\n\n" <<
  "coatedGrain: grain with a mantle, \n effective medium approximation is calculated using hollow sphere equivalent\n";
}
// mixedGrain methods
mixedGrainPointer makeMixedGrain(char *dir) {
  // New constructor function also computes effective conductivity in call. I
  // see no reason not to and this should avoid some issues.
  std::string fileDir = std::string(dir);
  auto *thisGrain = new conductivity::mixedGrain<double>(
      std::move(conductivity::readGrainFromSetup<double>(fileDir, 1e-4)));
  conductivity::solveSystem<double>(*thisGrain);
  return (mixedGrainPointer)thisGrain;
}
void solveBreugmannSystem(mixedGrainPointer grain) {
  auto thisGrain = static_cast<conductivity::mixedGrain<double> *>(grain);
  conductivity::solveSystem<double>(*thisGrain);
}
int get_nmaterials(mixedGrainPointer grain){
    auto thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return thisGrain->delta_i.size(); 
}
void* get_conductivitiesMixed(mixedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return (void *)thisGrain->sigma_eff_j.data();
}
void* get_lambdaMixed(mixedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return (void *)thisGrain->lambda_k.data();
}
void* get_delta(mixedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return (void *)thisGrain->delta_i.data();
}
int get_lengthMixed(mixedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return thisGrain->lambda_k.size();
}
void deleteMixedGrain(mixedGrainPointer grain) {
  auto *thisGrain = static_cast<conductivity::mixedGrain<double> *>(grain);
  delete thisGrain;
}
// coatedGrain methods
coatedGrainPointer makeCoatedGrain(mixedGrainPointer inner_,
                                   mixedGrainPointer outer_, double r1_,
                                   double r2_) {
  auto inner = static_cast<conductivity::mixedGrain<double> *>(inner_);
  auto outer = static_cast<conductivity::mixedGrain<double> *>(outer_);
  auto thisGrain =
      new conductivity::coatedGrain<double>(inner, outer, r1_, r2_);
  conductivity::solveSystem<double>(*thisGrain);
  return (coatedGrainPointer)thisGrain;
}
void solveCoatedGrainSystem(coatedGrainPointer grain) {
  auto thisGrain = static_cast<conductivity::coatedGrain<double> *>(grain);
  conductivity::solveSystem<double>(*thisGrain);
}
void setOuter(coatedGrainPointer grain, mixedGrainPointer outer_, double r1_,
              double r2_) {
  auto outer = static_cast<conductivity::mixedGrain<double> *>(outer_);
  auto thisGrain = static_cast<conductivity::coatedGrain<double> *>(grain);
  thisGrain->sigmaHollowSphere_k = outer->sigma_eff_j;
  thisGrain->r1 = r1_;
  thisGrain->r2 = r2_;
}
void setInner(coatedGrainPointer grain, mixedGrainPointer inner_, double r1_,
              double r2_) {
  auto inner = static_cast<conductivity::mixedGrain<double> *>(inner_);
  auto thisGrain = static_cast<conductivity::coatedGrain<double> *>(grain);
  thisGrain->sigmaHollowSphere_k = inner->sigma_eff_j;
  thisGrain->r1 = r1_;
  thisGrain->r2 = r2_;
}
void addLayer(coatedGrainPointer grain, mixedGrainPointer coating_, double thickness) {
  auto coating = static_cast<conductivity::mixedGrain<double> *>(coating_);
  auto thisGrain = static_cast<conductivity::coatedGrain<double> *>(grain);
  thisGrain->r1 = thisGrain->r2; 
  thisGrain->r2 = thisGrain->r1+thickness; 
  thisGrain->sigmaHollowSphere_k=coating->sigma_eff_j;
  conductivity::solveSystem(*thisGrain);
}
void* get_conductivitiesCoated(mixedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::coatedGrain<double> *>(grain);
  return (void *)thisGrain->sigma_eff_k.data();
}
int get_lengthCoated(mixedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return thisGrain->lambda_k.size();
}
void* get_lambdaCoated(mixedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain);
  return (void *)thisGrain->lambda_k.data();
}
void deleteCoatedGrain(coatedGrainPointer grain) {
  auto *thisGrain = static_cast<conductivity::coatedGrain<double> *>(grain);
  delete thisGrain;
}
// Percolated grains
mixedPercolatedGrainPointer makePercolatedMixedGrain(char *dir) {
  // New constructor function also computes effective conductivity in call. I
  // see no reason not to and this should avoid some issues.
  std::string fileDir = std::string(dir);
  auto *thisGrain = new conductivity::mixedPercolatedGrain<double>(
      std::move(conductivity::readPercolatedGrainFromSetup<double>(fileDir, 1e-4)));
  conductivity::solveSystem<double>(*thisGrain);
  return (mixedPercolatedGrainPointer)thisGrain;
}
void solveEMTSystem(mixedPercolatedGrainPointer grain) {
  auto thisGrain = static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  conductivity::solveSystem<double>(*thisGrain);
}
int get_nmaterialsPercolated(mixedPercolatedGrainPointer grain){
    auto thisGrain =static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  return thisGrain->delta_i.size(); 
}
void* get_conductivitiesPercolated(mixedPercolatedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  return (void *)thisGrain->sigma_eff_j.data();
}
void* get_lambdaPercolated(mixedPercolatedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  return (void *)thisGrain->lambda_k.data();
}
void* get_deltaPercolated(mixedPercolatedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  return (void *)thisGrain->delta_i.data();
}
int get_lengthPercolated(mixedPercolatedGrainPointer grain){
  auto thisGrain =static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  return thisGrain->lambda_k.size();
}
void deleteMixedPercolatedGrain(mixedPercolatedGrainPointer grain) {
  auto *thisGrain = static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  delete thisGrain;
}
// Grain handler
grainHandlerPointer mixedGrainHandler(mixedGrainPointer grain){
  auto thisGrain = static_cast<conductivity::mixedGrain<double> *>(grain);
  auto handler=new conductivity::grainHandler<double>(*thisGrain);
  return (grainHandlerPointer) handler;
}
grainHandlerPointer mixedPercolatedGrainHandler(mixedGrainPointer grain){
  auto thisGrain = static_cast<conductivity::mixedPercolatedGrain<double> *>(grain);
  auto handler=new conductivity::grainHandler<double>(*thisGrain); 
  return (grainHandlerPointer) handler;
}
grainHandlerPointer coatedGrainHandler(coatedGrainPointer grain){
  auto thisGrain = static_cast<conductivity::coatedGrain<double> *>(grain);
  auto handler=new conductivity::grainHandler<double>(*thisGrain); 
  return (grainHandlerPointer) handler;
}
// dust distribution methods
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
void calculateOpacity(dustDist distribution,grainHandlerPointer grain,double* opacities){
  //std::cout<<grain<<"\n";
  auto thisDistribution = static_cast<dust::dustDistribution<double> *> (distribution); 
  auto thisGrain = static_cast<conductivity::grainHandler<double> *> (grain); 
  //std::cout<<&(thisGrain->lambda_k)<< " " << thisGrain->lambda_k[0]<< "\n";
  //std::cout<<&(thisDistribution->dustSizeBins)<<"\n";
  opacity::KappaDust_fast_Array<double>(opacities, *thisGrain, *thisDistribution);  
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
