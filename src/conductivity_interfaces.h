#pragma once
//#include "Conductivity.hxx"
#include <stdlib.h>

typedef void* conductivityObj;
    
void calculateConductivity(conductivityObj cl);
conductivityObj buildConductivity(char* dir);
void deallocateObject(conductivityObj);