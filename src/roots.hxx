#pragma once

#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

namespace complexRootFind {
template <class T, class... argType>
std::complex<T>
newtonStep(std::complex<T> x_0,
           std::function<std::complex<T>(std::complex<T>, argType...)> &f,
           std::function<std::complex<T>(std::complex<T>, argType...)> &f_prime,
           argType... args) {
  std::complex<T> x_1 = x_0 - f(x_0, args...) / f_prime(x_0, args...);
  return x_1;
}
template <class T, class... argType>
std::complex<T>
solve(std::complex<T> x_0, T threshold,
      std::function<std::complex<T>(std::complex<T>, argType...)> &f,
      std::function<std::complex<T>(std::complex<T>, argType...)> &f_prime,
      argType... args) {
  std::complex<T> x_n = x_0;
  for (int i = 0; i < 1000; ++i) {
    x_n = newtonStep(x_n, f, f_prime, args...);
    if (std::abs(f(x_n, args...)) < threshold) {
      return x_n;
    }
  }
  std::cerr << "ROOTFINDER WARNING: The root finder did not converge in 1000 "
               "steps: returned x at last step"
            << std::endl;
  return x_n;
}
} // namespace complexRootFind

namespace rootFind {
template <class T, class... argType>
T newtonStep(T x_0, std::function<T(T, argType...)> &f,
             std::function<T(T, argType...)> &f_prime, argType... args) {
  T x_1 = x_0 - (f(x_0, args...) / f_prime(x_0, args...));
  return x_1;
}
template <class T, class... argType>
T solve(T x_0, T threshold, std::function<T(T, argType...)> &f,
        std::function<T(T, argType...)> &f_prime, argType... args) {
  T x_n = x_0;
  for (int i = 0; i < 1000; ++i) {
    x_n = newtonStep(x_n, f, f_prime, args...);
    if (std::abs(f(x_n, args...)) < threshold) {
      return x_n;
    }
  }
  std::cerr << "ROOTFINDER WARNING: The root finder did not converge in 1000 "
               "steps: returned x at last step"
            << std::endl;
  return x_n;
}
} // namespace rootFind