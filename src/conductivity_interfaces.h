#pragma once
//#include "Conductivity.hxx"
#include <stdlib.h>

typedef void* conductivityObj;
    
extern "C" void calculateConductivity(conductivityObj cl);
extern "C" conductivityObj buildConductivity(char* dir);
extern "C" void deallocateConductivityObject(conductivityObj);
extern "C" double lambda(conductivityObj grain, int i);