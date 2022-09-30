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
  class Composite{
    std::vector<T> *data_x;
    Composite(std::vector<T> &dx){
      data_x=*dx;
    }
  };
  template<class T>
  class CompositeTrapezoid{
    std::vector<T> *data_x;
    CompositeTrapezoid(std::vector<T> &dx){
      data_x=*dx;
    }
  }; 
  template<class T>
  class CompositeSimpson{
    std::vector<T> *data_x;
    CompositeSimpson(std::vector<T> &dx){
      data_x=*dx;
    }
  }; 
  template<class T>
  void computeWeights(Simpson<T> &v){
    v.weights[0]=(T)1.0;
    for(int i=1;i<v.weights.size();i+=2){
      v.weights[i]=(T)4.0;
    }
    for(int i=2;i<v.weights.size();i+=2){
      v.weights[i]=(T)2.0;
    }
    v.weights[v.weights.size()-1]=(T)1.0;
  };
  template<class T>
  void computeWeights(Simpson38<T> &v){
    v.weights[0]=(T)1.0;
    for(int i=1;i<v.weights.size();i+=3){
      v.weights[i]=(T)3.0;
    }
    for(int i=2;i<v.weights.size();i+=3){
      v.weights[i]=(T)3.0;
    }
    for(int i=3;i<v.weights.size();i+=3){
      v.weights[i]=(T)2.0;
    }
    v.weights[v.weights.size()-1]=(T)1.0;
  };
  template<class T>
  void computeWeights(Trapezoid<T> &v){
    v.weights[0]=(T)0.5;
    for(int i=1;i<v.weights.size();++i){
      v.weights[i]=(T)1.0;
    }
    v.weights[v.weights.size()-1]=(T)0.5;
  };
  template<class T>
  T computeIntegral(const std::vector<T> &data, Simpson<T> weights){

  }
  template<class T>
  T computeIntegral(const std::vector<T> &data, Simpson38<T> weights){

  }
  template<class T>
  T computeIntegral(const std::vector<T> &data, Trapezoid<T> weights){

  }
  template<class T>
  T computeIntegral(const std::vector<T> &data, Composite<T> method){
    T integral=std::accumulate(std::begin(data), std::end(data), decltype(data)::value_type(0));
    T H= method.data_x[0]-method.data_x[data.size()];
    return integral/H;
  }
  template<class T>
  T computeIntegral(std::vector<T> data, CompositeTrapezoid<T> method){
    T integral=(T)0.0;
    for(int i=1;i<data.size();++i){
      integral+=0.5*(method.data_x[i]-method.data_x[i-1])*(data[i]+data(i-1));
    }
    return integral;
  }
  template<class T>
  T computeIntegral(std::vector<T> data, CompositeSimpson<T> method){
    T integral=(T)0.0;
    T sixth=(T)0.166666666666666666;
    for(int i=1;i<((data.size()/2)-2);++i){
      T hi=method.data_x[2*i]-method.data_x[(2*i)-1];
      T hip=method.data_x[(2*i)+1]-method.data_x[2*i];
      integral+=sixth*(hi+hip)
                        *((2.0-hi/hip)*data[2*i] +
                         (((hi+hip)*(hi+hip)/(hi*hip)))*data[2*i+1] +
                         (2.0-hi/hip)*data[2*i+2]);
    }
    if(data.size()%2){
      T hn=method.data_x[data.size()-1]-method.data_x[data.size()-2];
      T hnm=method.data_x[data.size()-2]-method.data_x[data.size()-3];
      integral+=data[data.size()-1]*((2.0*hn*hn)+(3.0*hn*hnm))/(6.0*(hnm+hn));
    } 
  }
};

namespace polynomials{

};