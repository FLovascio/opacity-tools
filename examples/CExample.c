/*
All of the C linkable functions exposed by the opacity and conductivity libraries are contained in the 
headder files provided in the /lib directory. Including the headers will give you access to autocomplete
in your editor, etc.. You still need to link the opacity and conductivity static libs yourself. 
A CMake example is provided and a simple example may be found in the documentation.
*/

#include <stdio.h>
#include "../lib/opacities.h"
#include "../lib/conductivities.h"


int main(){
  double s[]={0.001,0.002,0.003,0.004,0.005,0.006,0.007,0.008,0.009,0.01};
  double e[]={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
  opacityVector op=(opacityVector)malloc(113*sizeof(double));
  double* opacityValues=(double*)op;
  conductivityObj grain=buildConductivity((char*)"/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/");
  calculateConductivity(grain);
  dustDist distribution=makeDustDist(s,e,10);
  calculateOpacity(distribution,grain,op);
  printf("element one of the opacity array is %f",opacityValues[1]);
  deallocateDust(distribution);
  deallocateConductivityObject(grain);
  return 0;
}