#include "conductivity_interfaces.h"

#include "Conductivity.hxx"
#include <stdlib.h>
#include <utility>

extern "C" {
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
  std::cout << thisGrain <<"\n";
uint32_t tmp = 2;
float d_CC = *((float*)&tmp);  

std::cout << d_CC << std::endl;

return thisGrain->lambda_k[i]; 
}
void deallocateConductivityObject(conductivityObj grain){
  conductivity::mixedGrain<double> *thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain); 
  delete thisGrain;
}
void calculateconductivity_(conductivityObj grain){
  calculateConductivity(grain); 
}
conductivityObj buildconductivity_(char *dir){
  return buildConductivity(dir);
}
double lambda_(conductivityObj* grain, int* i){
  conductivityObj gptr = *grain;
  return lambda(gptr,*i);
}
void deallocateconductivityObject_(conductivityObj grain){
  deallocateConductivityObject(grain);
}
conductivityObj testinterface_( char *dir, int* i, float* d){
uint32_t ii = *((uint32_t*)i);
uint32_t dd = *((uint32_t*)d);
float d_C = 2.0;
uint32_t d_CC = *((uint32_t*)&d_C);
std::cout << std::hex <<  i << " " << d << " " << ii << " " << dd << " " << d_CC << "\n";
  std::string fileDir=std::string(dir);
  std::cout<< "reading from " <<fileDir << "\n";
  conductivity::mixedGrain<double> *thisGrain =
    new conductivity::mixedGrain<double>(std::move(
        conductivity::readGrainFromSetup<double>(fileDir, 1e-4)));
  std::cout << thisGrain <<"\n";
  return (void*) thisGrain;
}
}