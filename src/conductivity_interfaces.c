#pragma once
#include "conductivity_interfaces.h"

extern "C"{
#if FP32
void calculateConductivity(float _Complex** individualConductivities, float* fractionalAbbundancies, float _Complex* effectiveConductivities, unsigned int nMaterial, unsigned int nLambda){};
void calculateConductivityFromDir(char* dir, float _Complex* effectiveConductivities){};
#elsif FP64
void calculateConductivity(double _Complex** individualConductivities, double* fractionalAbbundancies, double _Complex* effectiveConductivities, unsigned int nMaterial, unsigned int nLambda){};
void calculateConductivityFromDir(char* dir, double _Complex* effectiveConductivities){};
#elsif FP128
void calculateConductivity(long double _Complex** individualConductivities, long double* fractionalAbbundancies, long double _Complex* effectiveConductivities,unsigned int nMaterial, unsigned int nLambda){};
void calculateConductivityFromDir(char* dir, long double _Complex* effectiveConductivities){};
#endif
};