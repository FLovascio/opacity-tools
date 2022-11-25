#pragma once

#include "FileIO.hxx"
#include "allocators.hxx"
#include "roots.hxx"
#include <cmath>
#include <complex>
#include <functional>
#include <memory>
#include <numeric>
#include <vector>

namespace conductivity {
template <class T, template <class> class AllocatorType = std::allocator>
class mixedGrain {
public:
  std::vector<std::vector<std::complex<T>, AllocatorType<std::complex<T>>>>
      sigma_ij;
  std::vector<T, AllocatorType<T>> delta_i;
  std::vector<T, AllocatorType<T>> lambda_k;
  std::vector<std::complex<T>, AllocatorType<std::complex<T>>> sigma_eff_j;

  mixedGrain(std::vector<std::vector<std::complex<T>>> sigma_ij_input,
             std::vector<T> delta_i_input, std::vector<T> lambda_k_input) {
    sigma_ij = sigma_ij_input;
    delta_i = delta_i_input;
    lambda_k = lambda_k_input;
    sigma_eff_j = sigma_ij[0];
  }

  mixedGrain(const mixedGrain<T, AllocatorType> &a) {
    sigma_ij = a.sigma_ij;
    delta_i = a.delta_i;
    lambda_k = a.lambda_k;
    sigma_eff_j = a.sigma_eff_j;
  }
};

template <class T>
class mixedFluffyGrain {
public:
  std::vector<std::vector<std::complex<T>>> sigma_ij;
  std::vector<T> delta_i;
  std::vector<T> lambda_k;
  std::vector<std::complex<T>> sigma_eff_j;

  mixedFluffyGrain(std::vector<std::vector<std::complex<T>>> sigma_ij_input,
             std::vector<T> delta_i_input, std::vector<T> lambda_k_input) {
    sigma_ij = sigma_ij_input;
    delta_i = delta_i_input;
    lambda_k = lambda_k_input;
    sigma_eff_j = sigma_ij[0];
  }

  mixedFluffyGrain(const mixedFluffyGrain<T> &a) {
    sigma_ij = a.sigma_ij;
    delta_i = a.delta_i;
    lambda_k = a.lambda_k;
    sigma_eff_j = a.sigma_eff_j;
  }
};

template <class T> class coatedGrain {
public:
  std::vector<T> lambda_k;
  std::vector<std::complex<T>> sigmaHollowSphere_k;
  std::vector<std::complex<T>> sigmaInnerSphere_k;
  std::vector<std::complex<T>> sigma_eff_k;
  T r1; //inner radius
  T r2; //outer radius
  coatedGrain(std::vector<T> lambda_k_,
               std::vector<std::complex<T>> sigmaHollowSphere_k_,
               std::vector<std::complex<T>> sigmaInnerSphere_k_, T r1_, T r2_) {
    lambda_k = lambda_k_;
    sigmaHollowSphere_k = sigmaHollowSphere_k_;
    sigmaInnerSphere_k = sigmaInnerSphere_k_;
    sigma_eff_k = sigmaInnerSphere_k_;
    r1 = r1_;
    r2 = r2_;
  }
  coatedGrain(mixedGrain<T>&inner_,mixedGrain<T>&outer_, T r1_, T r2_){
    lambda_k = inner_.lambda_k;
    sigmaHollowSphere_k=outer_.sigma_eff_j;
    sigmaInnerSphere_k=inner_.sigma_eff_j;
    sigma_eff_k=outer_.sigma_eff_j;
    r1=r1_;
    r2=r2_;
  }
  coatedGrain(mixedGrain<T>*inner_,mixedGrain<T>*outer_, T r1_, T r2_){
    lambda_k = inner_->lambda_k;
    sigmaHollowSphere_k=outer_->sigma_eff_j;
    sigmaInnerSphere_k=inner_->sigma_eff_j;
    sigma_eff_k=outer_->sigma_eff_j;
    r1=r1_;
    r2=r2_;
  }
};

template<class T>
class aggregateGrain{
  public:
  std::vector<T> lambda_k;
  std::vector<std::complex<T>> sigma_1_k;
  std::vector<std::complex<T>> sigma_2_k;
  std::vector<std::complex<T>> sigma_eff_k;
  T f0; //
  T f1; //
  T g0; 
  aggregateGrain(){;}
};

template<class T>
class grainHandler{
public:
  std::vector<T> &lambda_k; 
  std::vector<std::complex<T>> &sigma_k;
  grainHandler(mixedGrain<T>& grain_):lambda_k(grain_.lambda_k),sigma_k(grain_.sigma_eff_j){;}
  grainHandler(coatedGrain<T>& grain_):lambda_k(grain_.lambda_k),sigma_k(grain_.sigma_eff_k){;}
};

template <class T>
std::complex<T> BrugemannSumFunction(std::complex<T> sigma_eff, int lambda_k_i,
                                     const mixedGrain<T> &grain) {
  std::complex<T> sum_value(0.0, 0.0);
  int n = grain.delta_i.size();
  T n_minus_1 = n - 1.0;
  for (int i = 0; i < n; ++i) {
    sum_value += grain.delta_i[i] *
                 (grain.sigma_ij[i][lambda_k_i] - sigma_eff) /
                 (grain.sigma_ij[i][lambda_k_i] + ((T)2.0 * sigma_eff));//(grain.sigma_ij[i][lambda_k_i] + (n_minus_1 * sigma_eff));
  }
  return sum_value;
}

template <class T>
std::complex<T> BrugemannSumDerivativeFunction(std::complex<T> sigma_eff,
                                               int lambda_k_i,
                                               const mixedGrain<T> &grain) {
  std::complex<T> sum_value(0.0, 0.0);
  int n = grain.delta_i.size();
  T n_minus_1 = n - 1.0;
  for (int i = 0; i < n; ++i) {
    sum_value += grain.delta_i[i] *
                 ((-grain.sigma_ij[i][lambda_k_i] - ((T)2.0 * sigma_eff)) -
                  (T)2.0 * (grain.sigma_ij[i][lambda_k_i] - sigma_eff)) /
                 ((grain.sigma_ij[i][lambda_k_i] + ((T)2.0 * sigma_eff)) *
                  (grain.sigma_ij[i][lambda_k_i] + ((T)2.0 * sigma_eff)));
  }
  return sum_value;
}

template<class T>
std::complex<T> EMT_O(std::complex<T> sigma_eff,int lambda_k_i,const mixedFluffyGrain<T> &grain){
  std::complex<T> sum_value(0.0, 0.0);
  int n = grain.delta_i.size();
  T n_minus_1 = n - 1.0;
  T over9 = 0.1111111111111111;
  T over3 = 0.3333333333333333;
  for (int i = 0; i < n; ++i) {
    T f0=5.0*over9*grain.delta_i[i]*sin(M_PI*grain.delta_i[i])*sin(M_PI*grain.delta_i[i]);
    T f1=2.0*over9*grain.delta_i[i]*sin(M_PI*grain.delta_i[i])*sin(M_PI*grain.delta_i[i]);
    T f2=2.0*over9*grain.delta_i[i]*sin(M_PI*grain.delta_i[i])*sin(M_PI*grain.delta_i[i]);
    T f3=grain.delta_i[i]*sin(M_PI*grain.delta_i[i])*sin(M_PI*grain.delta_i[i]);
    sum_value += f0 * ((grain.sigma_ij[i][lambda_k_i]-sigma_eff)/(sigma_eff));
    sum_value += f1 * ((grain.sigma_ij[i][lambda_k_i]-sigma_eff)/(sigma_eff+0.5*(grain.sigma_ij[i][lambda_k_i]-sigma_eff)));
    sum_value += f2 * ((grain.sigma_ij[i][lambda_k_i]-sigma_eff)/(sigma_eff+1.0*(grain.sigma_ij[i][lambda_k_i]-sigma_eff)));
    sum_value += f3 * ((grain.sigma_ij[i][lambda_k_i]-sigma_eff)/(sigma_eff+over3*(grain.sigma_ij[i][lambda_k_i]-sigma_eff)));
  }
  return sum_value; 
}

template <class T> void coatedGrainConductivity(coatedGrain<T> &grain, int i) {
  grain.sigma_eff_k[i] =
      grain.sigmaHollowSphere_k[i] *
      ((grain.r2 * grain.r2 * grain.r2) *
           (grain.sigmaInnerSphere_k[i] + 2.0 * grain.sigmaHollowSphere_k[i]) +
       2.0 * (grain.r1 * grain.r1 * grain.r1) *
           (grain.sigmaInnerSphere_k[i] - grain.sigmaHollowSphere_k[i])) /
      ((grain.r2 * grain.r2 * grain.r2) *
           (grain.sigmaInnerSphere_k[i] + 2.0 * grain.sigmaHollowSphere_k[i]) -
       (grain.r1 * grain.r1 * grain.r1) *
           (grain.sigmaInnerSphere_k[i] - grain.sigmaHollowSphere_k[i]));
}

template <class T>
mixedGrain<T> readGrain(std::string dir, T unit_conversion = 1e-4) {
  std::vector<std::vector<std::complex<T>>> materialProperties;
  std::vector<std::string> materials = {"iron", "olivine", "orthopyroxene",
                                        "volatile_organics", "water_ice"};
  T totalcon = 1.26e-4 + 2.64e-3 + 7.70e-4 + 6.02e-4 + 5.55e-3;
  std::vector<T> concentrations = {1.26e-4 / totalcon, 2.64e-3 / totalcon,
                                   7.70e-4 / totalcon, 6.02e-4 / totalcon,
                                   5.55e-3 / totalcon};
  T rho = 1.26e-4 * 7.87 + 2.64e-3 * 3.49 + 7.70e-4 * 3.4 + 6.02e-4 * 1.0 +
          5.55e-3 * 0.92;
  std::vector<std::complex<T>> condV = {std::complex<T>{0.0, 0.0}};
  std::vector<T> lambdas;
  for (int i = 0; i < materials.size(); ++i) {
    delimitedFiles::readDatToComplexVector<T>(condV, dir + "n_" + materials[i] +
                                                         ".dat");
    materialProperties.push_back(condV);
  }
  delimitedFiles::readDatToVector<T>(lambdas,
                                     dir + "n_" + materials[0] + ".dat");
  for (int i = 0; i < lambdas.size(); ++i) {
    lambdas[i] = lambdas[i] * unit_conversion;
  }
  mixedGrain<T> returnGrain(materialProperties, concentrations, lambdas);
  return returnGrain;
}

template <class T>
mixedGrain<T> readGrainFromSetup(std::string dir, T unit_conversion = 1e-4) {
  std::vector<std::vector<std::complex<T>>> materialProperties;
  std::vector<std::string> materials;
  T totalcon = 0;
  std::vector<T> concentration;
  std::vector<std::complex<T>> condV = {std::complex<T>{0.0, 0.0}};
  std::vector<T> lambdas;
  setupFiles::readMaterialsFile(materials, concentration, dir);
  totalcon = std::accumulate(std::begin(concentration), std::end(concentration),
                             T(0.0));
  for (auto &n : concentration) {
    n /= totalcon;
  }
  for (int i = 0; i < materials.size(); ++i) {
    delimitedFiles::readDatToComplexVector<T>(condV, dir + "n_" + materials[i] +
                                                         ".dat");
    materialProperties.push_back(condV);
  }
  delimitedFiles::readDatToVector<T>(lambdas,
                                     dir + "n_" + materials[0] + ".dat");
  for (int i = 0; i < lambdas.size(); ++i) {
    lambdas[i] = lambdas[i] * unit_conversion;
  }
  mixedGrain<T> returnGrain(materialProperties, concentration, lambdas);
  return returnGrain;
}

template <class T> void solveSystem(mixedGrain<T> &grain) {
  std::complex<T> current_best_guess(1.0, 1.0);
  std::function<std::complex<T>(std::complex<T>, int)> BrugemannSum =
      [grain](std::complex<T> sigma_eff, int lambda_k_i) {
        return BrugemannSumFunction<T>(sigma_eff, lambda_k_i, grain);
      };
  std::function<std::complex<T>(std::complex<T>, int)> BrugemannSumDerivative =
      [grain](std::complex<T> sigma_eff, int lambda_k_i) {
        return BrugemannSumDerivativeFunction<T>(sigma_eff, lambda_k_i, grain);
      };
  for (int i = 0; i < grain.lambda_k.size(); ++i) {
    grain.sigma_eff_j[i] = complexRootFind::solve<T, int>(
        current_best_guess, 1e-8, BrugemannSum, BrugemannSumDerivative, i);
    current_best_guess = grain.sigma_eff_j[i];
  }
}

template <class T> void solveSystem(mixedFluffyGrain<T> &grain) {
  std::complex<T> current_best_guess(1.0, 1.0);
  std::function<std::complex<T>(std::complex<T>, int)> EMT_O_ =
      [grain](std::complex<T> sigma_eff, int lambda_k_i) {
        return EMT_O<T>(sigma_eff, lambda_k_i, grain);
      };
  for (int i = 0; i < grain.lambda_k.size(); ++i) {
    grain.sigma_eff_j[i] = complexRootFind::solve<T, int>(
        current_best_guess, 1e-8, EMT_O_, i);
    current_best_guess = grain.sigma_eff_j[i];
  }
}

template <class T> void solveSystem(coatedGrain<T> &grain) {
  for (int i = 0; i < grain.lambda_k.size(); ++i) {
    coatedGrainConductivity(grain, i);
  }
}

}; // namespace conductivity
