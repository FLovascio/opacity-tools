#pragma once

typedef void* conductivityObj;
    
void calculateConductivity(conductivityObj);
conductivityObj buildConductivity(char*);
void deallocateConductivityObject(conductivityObj);
double lambda(conductivityObj, int);