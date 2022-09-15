#pragma once

#include <stdlib.h>

typedef void* dustDist;
typedef void* conductivityObj;
typedef void* opacityVector;


dustDist makeDustDist(double*, double*, int);
void setDustSize(double*, dustDist, int);
void setDensity( double*, dustDist, int);
void calculateOpacity(dustDist, conductivityObj, opacityVector);
void deallocateDust(dustDist);