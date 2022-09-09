#pragma once

#include "opacity_interfaces.h"

#include <stdlib.h>
#include "Conductivity.hxx"
#include "Opacity.hxx"

extern "C"{
typedef void* dustDist;
typedef void* dustDist;
#ifdef FP32
typedef float* opacityVector;
#else
typedef double* opacityVector;
#endif

dustDist makeDustDist();
void setDustSize();
void setDensity();
opacityVector calculateOpacity();
};