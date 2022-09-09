#pragma once

#include "conductivity_interfaces.h"

#include <stdlib.h>
#include <utility>
#include "Conductivity.hxx"

typedef void* conductivityCls;

extern  "C"{
void calculateConductivity(conductivityCls cl){

}
conductivityCls buildConductivity(char* dir){
    conductivity::mixedGrain<double> * thisGrain = new conductivity::mixedGrain<double> (std::move(conductivity::readGrainFromSetup<double>(std::string(dir), 1e-4)));
    

}
}