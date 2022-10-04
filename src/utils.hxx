#pragma once

#include <functional>
#include <vector>
#include <array>
#include "matrix.hxx"

namespace utils{
  template<class T,class... argType>
  std::vector<T>& brodcast(std::function<T(T,argType...)>& f_in,const std::vector<T> &x, std::vector<T> &y, argType... args){
    auto f = std::move(f_in);
    for(int i=0;i<x.size();++i){
      y[i]=f(x[i],args...);
    }
    return *y;
  }
  template<class T,class... argType>
  std::vector<T> brodcast(std::function<T(T,argType...)>& f_in,std::vector<T> &x, argType... args){
    auto f = std::move(f_in);
    std::vector<T> y((T)0,x.size());
    for(int i=0;i<x.size();++i){
      y[i]=f(x[i],args...);
    }
    return y;
  }
};
