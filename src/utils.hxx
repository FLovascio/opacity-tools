#pragma once

#include <functional>
#include <vector>
#include <array>
#include "matrix.hxx"

namespace utils{
  template<class T,class... argType>
  std::vector<T>& brodcast(std::function<T(T,argType...)>,std::vector<T> &x, std::vector<T> &y){

  }
  template<class T,class... argType>
  std::vector<T> brodcast(std::function<T(T,argType...)>,std::vector<T> &x){

  }
}