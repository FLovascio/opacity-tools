////////////////////////////////////////////////
// This file implements tests for the c++    //
// implementation of the opacity calculator  //
///////////////////////////////////////////////
#include "Conductivity.hxx"
#include "FileIO.hxx"
#include "Opacity.hxx"
#include "roots.hxx"

#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <vector>

double quadraticRoot(double x, double Solution) { return x * x - Solution; }
double quadraticDerivative(double x, double Solution) { return 2.0 * x; }

std::complex<double> quadraticComplexRoot(std::complex<double> x,
                                          std::complex<double> offset) {
  return x * x + offset;
}
std::complex<double> quadraticComplexDerivative(std::complex<double> x,
                                                std::complex<double> offset) {
  return 2.0 * x;
}

int main() {
  // simple code integrity test//
  std::cout << "compiled ok\n";
  // root-finder test//
  // real roots//
  std::function<double(double, double)> f = quadraticRoot;
  std::function<double(double, double)> fprime = quadraticDerivative;
  double solutionVal = 1.0;
  double Thresh = 1e-4;
  auto solved =
      rootFind::solve<double, double>(0.1, Thresh, f, fprime, solutionVal);
  std::cout << "real root found: " << solved << "  expected: " << solutionVal
            << "\n";
  if (solved > solutionVal - Thresh && solved < solutionVal + Thresh) {
    std::cout << "real solver ok :) \n";
  } else {
    std::cout << "real solver bugged :( \n";
  }
  // complex roots
  std::function<std::complex<double>(std::complex<double>,
                                     std::complex<double>)>
      fC = quadraticComplexRoot;
  std::function<std::complex<double>(std::complex<double>,
                                     std::complex<double>)>
      fCprime = quadraticComplexDerivative;
  std::complex<double> offset(1.0, 0.0);
  auto solvedC = complexRootFind::solve<double, std::complex<double>>(
      std::complex<double>(0.1, 0.1), Thresh, fC, fCprime, solutionVal);
  std::cout << "complex root found: " << solvedC
            << "  expected: " << std::complex<double>(0.0, 1.0) << "\n";
  if (abs(fC(solvedC, offset)) < Thresh) {
    std::cout << "complex solver ok :) \n";
  } else {
    std::cout << "abs(f(x))=" << abs(fC(solvedC, offset))
              << ": complex solver bugged :( \n";
  }
  // conductivity solver tests//
  conductivity::mixedGrain<double> testGrain(conductivity::readGrain<double>(
      "/Users/fra/Code/Opacity/new_cons/Normal_silicates/",1.0e-4));
  std::cout << "read grain ok!\n";
  std::cout << "testGrain delta_i[0]=" << testGrain.delta_i[0] << "\n";
  std::cout << "lambda[0],sigma_ij[0][0]=" << testGrain.lambda_k[0] << ","
            << testGrain.sigma_ij[0][0]
            << "should be:  0.10000E+00,(0.14453E+01,0.89017E+00)\n";
  conductivity::solveSystem<double>(testGrain);
  std::cout << "lambda[0],sigma_eff_j[0]=" << testGrain.lambda_k[0] << ","
            << testGrain.sigma_eff_j[0] << "\n";
  
  // testing binary file output //
  std::cout<<"length of array is "<<testGrain.sigma_eff_j.size()<<"\n";
  std::cout<<testGrain.sigma_eff_j[0].real()<<","<<testGrain.sigma_eff_j[0].imag()<<"\n";
  std::cout<<testGrain.sigma_eff_j[1].real()<<","<<testGrain.sigma_eff_j[1].imag()<<"\n";
  std::cout<<testGrain.sigma_eff_j[2].real()<<","<<testGrain.sigma_eff_j[2].imag()<<"\n";
  if(binaryFiles::writeComplexVectorToBinary<double>(testGrain.sigma_eff_j,"EffectiveConductivities.bin")){
    std::cout << "complex write successfull \n";
  };
  if(binaryFiles::writeRealVectorToBinary<double>(testGrain.lambda_k,"Lambda.bin")){
    std::cout << "real write successfull \n";
  };
  if(delimitedFiles::writeComplexVectorToFile<double>(testGrain.sigma_eff_j,"EffectiveConductivities.csv")){
    std::cout << "complex file write successfull \n";
  };
  if(delimitedFiles::writeRealVectorToFile<double>(testGrain.lambda_k,"Lambda.csv")){
    std::cout << "real file write successfull \n";
  };

  // testing opacity calculation //
  //dust::dustDistribution<double> testDistribution(2.5e-7,5e-4,1.0,500,0.013986,dust::MRN_Pollack<double>);
  dust::dustDistribution<double> testDistribution("/Users/fra/Code/Opacity/OpacityTools/ReferenceValues/reference_data_dust_s.csv","/Users/fra/Code/Opacity/OpacityTools/ReferenceValues/reference_data_dust.csv");
  std::vector<double> KDust=opacity::KappaDust<double>(testGrain.lambda_k,testGrain.sigma_eff_j,testDistribution);
  std::cout<<KDust[1]<<"\n";
  if(binaryFiles::writeRealVectorToBinary<double>(KDust,"KDust.bin")){
    std::cout << "K-Dust write successfull \n";
  };
  if(delimitedFiles::writeRealVectorToFile<double>(KDust,"KDust.csv")){
    std::cout << "real file write successfull \n";
  }; 
  if(delimitedFiles::writeRealVectorToFile<double>(testDistribution.dustSizeDensity,"Dust.csv")){
  };
  if(delimitedFiles::writeRealVectorToFile<double>(testDistribution.dustSizeBins,"Dust_size.csv")){
  };
  return 0;
}
