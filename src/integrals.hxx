#pragma once

#include <vector>
#include <functional>
#include <complex>
#include <numeric>

namespace integrals{
  template<class T>
  class Simpson{
    std::vector<T> weights;
    Simpson(){
      weights=std::vector<T>((T)0,4);
      computeWeights<T>(*this);
    };
    Simpson(int N){
      weights=std::vector<T>((T)0,N);
      computeWeights<T>(*this);
    }
  };
  template<class T>
  class Simpson38{
    std::vector<T> weights;
    Simpson38(){
      weights=std::vector<T>((T)0,6);
      computeWeights<T>(*this);
    };
    Simpson38(int N){
      weights=std::vector<T>((T)0,N);
      computeWeights<T>(*this);
    }
  };
  template<class T>
  class Trapezoid{
    std::vector<T> weights;
    Trapezoid(){
      weights=std::vector<T>((T)0,6);
      computeWeights<T>(*this);
    };
    Trapezoid(int N){
      weights=std::vector<T>((T)0,N);
      computeWeights<T>(*this);
    }
  };
  template<class T>
  void computeWeights(Simpson<T> &v){
    v.weights[0]=(T)1;
    for(int i=0;i<v.weights.size();++i){
      
    }
  };
  template<class T>
  void computeWeights(Simpson38<T> &v){

  };
  template<class T>
  void computeWeights(Trapezoid<T> &v){

  };
};

namespace polynomials{

};