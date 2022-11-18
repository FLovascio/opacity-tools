#pragma once

#include "Conductivity.hxx"
#include "FileIO.hxx"
#include "constants.hxx"
#include "integrals.hxx"
#include "roots.hxx"
#include "utils.hxx"
#include <cmath>
#include <complex>
#include <functional>
#include <utility>
#include <vector>
#include <iostream>

namespace dust {
template <class T> class dustDistribution {
public:
  T smin;
  T smax;
  T rhograin;
  T epsilon;
  int nbin;
  std::vector<T> dustSizeBins;
  std::vector<T> dustSizeDensity;

  dustDistribution(const T &sMin, const T &sMax, const T &rhoGrain,
                   const int &nBin, const T &Epsilon,
                   const std::function<T(T)> &dustSizeFunction)
      : smin(sMin), smax(sMax), nbin(nBin), rhograin(rhoGrain),
        epsilon(Epsilon) {
    dustSizeBins = makeSizeBins(smin, smax, nbin);
    dustSizeDensity = makeSizeDensity(dustSizeFunction);
  };
  dustDistribution(std::string sFile, std::string epsFile) {
    if (delimitedFiles::readColumnToVector<T>(dustSizeBins, sFile)) {
    }
    if (delimitedFiles::readColumnToVector<T>(dustSizeDensity, epsFile)) {
    }
    smin = dustSizeBins[0];
    smax = dustSizeBins[dustSizeBins.size()];
    nbin = dustSizeBins.size();
    rhograin = 3.0;
  };
  dustDistribution(T *s, T *rho, int len) {
    dustSizeBins = std::move(std::vector<T>(s, s + len));
    dustSizeDensity = std::move(std::vector<T>(rho, rho + len));
    smin = dustSizeBins[0];
    smax = dustSizeBins[dustSizeBins.size()-1];
    nbin = dustSizeBins.size();
    rhograin = 3.0;
  }
  std::vector<T> makeSizeBins(T &smin, T &smax, int &nbin) {
    std::vector<T> retVec(nbin, 0.0);
    for (int i = 0; i < nbin; ++i) {
      retVec[i] = smin + (smax - smin) * double(i) / double(nbin);
    }
    return retVec;
  }
  std::vector<T> makeSizeDensity(const std::function<T(T)> &dustSizeFunction) {
    std::vector<T> dustDensity = dustSizeBins;
    for (auto bin = std::begin(dustDensity); bin < std::end(dustDensity);
         ++bin) {
      *bin = epsilon * dustSizeFunction(*bin);
    }
    return dustDensity;
  }
};

template <class T>
std::function<T(T)> MRN_Pollack = [](T r) {
  T P0 = 0.005e-4;
  T r3 = r * r * r;
  T retVal = 0.0;
  if (r >= 5e-4) {
    retVal = 0.0;
  }
  if (r >= 1e-4) {
    retVal = (pow(1.0 / P0, 2.0) * pow(P0 / r, 5.5));
  }
  if (r >= P0) {
    retVal = pow(P0 / r, 3.5);
  }
  if (r < P0) {
    retVal = 1.0;
  }
  return retVal * r3;
};

}; // namespace dust

namespace opacity {
template <class T> T H_j(T &xj, T &e1, T &e2) {
  return 1.0 + (xj * xj * ((e1 + 2.0) * (e1 + 2.0) + (e2 * e2))) / 90.0;
}

template <class T> T xj(T lambda, T sigma) {
  return 2.0 * (M_PI / lambda) * sigma;
}

template <class T> T sigma_jk(T &lambdak, T &e1, T &e2, const T &ljk) {
  return 2.0 * M_PI * e2 /
         ((lambdak * ljk * ljk) *
          (((e1 + 1.0 / ljk - 1.0) * (e1 + 1.0 / ljk - 1.0)) + (e2 * e2)));
}

template <class T> T e1(std::complex<T> &n) {
  return (n.real() * n.real()) - (n.imag() * n.imag());
}

template <class T> T e2(std::complex<T> &n) {
  return 2.0 * n.real() * n.imag();
}

template <class T>
T Kappa_j(int i, T &H, dust::dustDistribution<T> &dustDist, T sigma) {
  T Kappa = dustDist.dustSizeDensity[i] * H * sigma / dustDist.rhograin;
  return Kappa;
}

template <class T>
void KappaDust_fast(std::vector<T> &output, conductivity::mixedGrain<T> &grain,
                    dust::dustDistribution<T> &dustDist) {
#ifdef WARN_FAST
  std::cerr
      << 'Warning: Fast methods do not boundscheck and may unexpectedly cause crashes and out of bound access\n'
      << 'Hint: output (passed as an arg to this function may have different length than lambda_k (also passed as an arg)\n';
#endif
  T fillValue = (T)0.0;
  std::fill(std::begin(output), std::end(output), fillValue);
  T lambda = 0.0;
  T e1Var = 0.0;
  T e2Var = 0.0;
  T sigma = 0.0;
  T xVar = 0.0;
  T HVar = 0.0;
  std::cout << "looping " << output.size() << " times\n";
  for (int k = 0; k < output.size(); ++k) {
    lambda = grain.lambda_k[k];
    e1Var = e1(grain.sigma_eff_j[k]);
    e2Var = e2(grain.sigma_eff_j[k]);
    sigma = sigma_jk(lambda, e1Var, e2Var, 0.3333333333333333);
    xVar = xj(sigma, lambda);
    HVar = H_j(xVar, e1Var, e2Var);
    for (int idust = 0; idust < dustDist.nbin; ++idust) {
      xVar = xj<T>(lambda, dustDist.dustSizeBins[idust]);
      HVar = H_j<T>(xVar, e1Var, e2Var);
      output[k] += Kappa_j(idust, HVar, dustDist, sigma);
    }
    std::cout << output[k] << "\n";
  }
}

template <class T>
void KappaDust_fast_Array(T *output, conductivity::mixedGrain<T> &grain,
                          dust::dustDistribution<T> &dustDist) {
#ifdef WARN_FAST
  std::cerr
      << 'Warning: Fast methods do not boundscheck and may unexpectedly cause crashes and out of bound access\n'
      << 'Hint: output (passed as an arg to this function may have different length than lambda_k (also passed as an arg)\n';
#endif
  T fillValue = (T)0.0;
  T lambda = 0.0;
  T e1Var = 0.0;
  T e2Var = 0.0;
  T sigma = 0.0;
  T xVar = 0.0;
  T HVar = 0.0;
  // std::cout<<"looping "<<grain.lambda_k.size()<<" times\n";
  for (int k = 0; k < grain.lambda_k.size(); ++k) {
    output[k]=fillValue;
    lambda = grain.lambda_k[k];
    e1Var = e1(grain.sigma_eff_j[k]);
    e2Var = e2(grain.sigma_eff_j[k]);
    sigma = sigma_jk(lambda, e1Var, e2Var, 0.3333333333333333);
    xVar = xj(sigma, lambda);
    HVar = H_j(xVar, e1Var, e2Var);
    // std::cout<<k<<"\n"; //debugging print
    for (int idust = 0; idust < dustDist.nbin; ++idust) {
      xVar = xj<T>(lambda, dustDist.dustSizeBins[idust]);
      HVar = H_j<T>(xVar, e1Var, e2Var);
      output[k] += Kappa_j(idust, HVar, dustDist, sigma);
    }
    // std::cout<<output[k]<<"\n";
  }
}

template <class T>
void KappaDust_fast_Array(T *output, conductivity::grainHandler<T> grain,
                          dust::dustDistribution<T> &dustDist) {
#ifdef WARN_FAST
  std::cerr
      << 'Warning: Fast methods do not boundscheck and may unexpectedly cause crashes and out of bound access\n'
      << 'Hint: output (passed as an arg to this function may have different length than lambda_k (also passed as an arg)\n';
#endif
  T fillValue = (T)0.0;
  T lambda = 0.0;
  T e1Var = 0.0;
  T e2Var = 0.0;
  T sigma = 0.0;
  T xVar = 0.0;
  T HVar = 0.0;
  // std::cout<<"looping "<<grain.lambda_k.size()<<" times\n";
  for (int k = 0; k < grain.lambda_k.size(); ++k) {
    output[k]=fillValue;
    lambda = grain.lambda_k[k];
    e1Var = e1(grain.sigma_k[k]);
    e2Var = e2(grain.sigma_k[k]);
    sigma = sigma_jk(lambda, e1Var, e2Var, 0.3333333333333333);
    xVar = xj(sigma, lambda);
    HVar = H_j(xVar, e1Var, e2Var);
    // std::cout<<k<<"\n"; //debugging print
    for (int idust = 0; idust < dustDist.nbin; ++idust) {
      xVar = xj<T>(lambda, dustDist.dustSizeBins[idust]);
      HVar = H_j<T>(xVar, e1Var, e2Var);
      output[k] += Kappa_j(idust, HVar, dustDist, sigma);
    }
    // std::cout<<output[k]<<"\n";
  }
}

template <class T>
std::vector<T> KappaDust(std::vector<T> lambda_k,
                         std::vector<std::complex<T>> sigma_eff_j,
                         dust::dustDistribution<T> &dustDist) {
  T fillValue = (T)0.0;
  T lambda = 0.0;
  T e1Var = 0.0;
  T e2Var = 0.0;
  T sigma = 0.0;
  T xVar = 0.0;
  T HVar = 0.0;
  std::vector<T> output(lambda_k.size(), fillValue);
  for (int k = 0; k < lambda_k.size(); ++k) {
    lambda = lambda_k[k];
    e1Var = e1<T>(sigma_eff_j[k]);
    e2Var = e2<T>(sigma_eff_j[k]);
    sigma = sigma_jk<T>(lambda, e1Var, e2Var, 0.3333333333333333);
    for (int idust = 0; idust < dustDist.nbin; ++idust) {
      xVar = xj<T>(lambda, dustDist.dustSizeBins[idust]);
      HVar = H_j<T>(xVar, e1Var, e2Var);
      output[k] += Kappa_j(idust, HVar, dustDist, sigma);
      // std::cout << output[k] <<"\n";
    }
  }
  return output;
}

template <class numType> numType B_nu(numType nu, numType T) {
  numType hnu = constants::h * nu;
  return 2 * nu * nu * constants::one_over_c_light *
         constants::one_over_c_light * hnu * 1.0 /
         (exp(hnu / (constants::k * T)) - 1.0);
}

template <class numType> numType dBdT_nu(numType nu, numType T) {
  numType hnu = constants::h * nu;
  numType hnukt = hnu / (constants::k * T);
  numType ehnukt = exp(hnukt);
  return hnukt / ((constants::k * T) * (ehnukt - (numType)1.0)) * ehnukt;
}

template <class numType> numType B_lambda(numType lambda, numType T) {
  numType nu = constants::c_light / lambda;
  return B_nu(nu, T);
}

template <class numType> numType dBdT_lambda(numType lambda, numType T) {
  numType nu = constants::c_light / lambda;
  return dBdT_nu(nu, T);
}

template <class T> class meanOpacity {
private:
  std::vector<T> BKappa_nu;
  std::vector<T> U_nu;

public:
  T* kappa_nu;
  std::vector<T> lambda;
  int length;
  T planck;
  T rosseland;
  T Temperature;
  meanOpacity(T* k_in, T* l_in,
              T Temperature, int len) {
    kappa_nu = k_in;
    int length = len;
    lambda=std::move(std::vector<T>(l_in, l_in + len));
    BKappa_nu=std::move(std::vector<T>((T)0.0, length));
    Planck();
    Rosseland();
  }
  void Planck() {
    for (int i = 0; i < this->length; ++i) {
      BKappa_nu[i] = kappa_nu[i] * B_lambda(lambda[i], Temperature);
    }
    integrals::CompositeSimpson<T> integral(lambda);
    planck = integrals::computeIntegral(BKappa_nu, integral);
  };
  void Rosseland() {
    for (int i = 0; i < this->length; ++i) {
      BKappa_nu[i] = dBdT_lambda(lambda[i], Temperature) / kappa_nu[i];
    }
    for (int i = 0; i < this->length; ++i) {
      U_nu[i] = dBdT_lambda(lambda[i], Temperature);
    }
    integrals::CompositeSimpson<T> integral(lambda);
    rosseland = integrals::computeIntegral(U_nu, integral);
    rosseland /= integrals::computeIntegral(BKappa_nu, integral);
  };
  void setTemperature(T Temp){
    Temperature = Temp;
  }
  void setKappa_nu(T* kappa_nu_temp){
    kappa_nu=kappa_nu_temp;
  }
  template<bool memSafe>
  void setLambda(std::vector<T> &lambda_temp){
    if constexpr(memSafe){
      if(lambda_temp.size()!=length){
        std::cerr<<"MEMORY ERROR: new lambda vector length is not equal to original. All library instantiations are malloc-ed with fixed size, this assignment would lead to undefined behaviour.\n";
        return (void)NULL;
      }
    }
    lambda=lambda_temp;
  }
};

}; // namespace opacity
