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
  conductivity::mixedGrain<double> *thisGrain =
      new conductivity::mixedGrain<double>(std::move(
          conductivity::readGrainFromSetup<double>(std::string(dir), 1e-4)));
  return (void*) thisGrain;
}
void deallocateConductivityObject(conductivityObj grain){
  conductivity::mixedGrain<double> *thisGrain =static_cast<conductivity::mixedGrain<double> *>(grain); 
  delete thisGrain;
}
}