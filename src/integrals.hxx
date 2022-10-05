#pragma once

#include <vector>
#include <functional>
#include <complex>
#include <numeric>

namespace integrals{ //composite integral methods
  template<class T>
  class Composite{
    public:
    std::vector<T> *data_x;
    Composite(std::vector<T> &dx){
      data_x= &dx;
    }
  };
  template<class T>
  class CompositeTrapezoid{
    public:
    std::vector<T> *data_x;
    CompositeTrapezoid(std::vector<T> &dx){
      data_x= &dx;
    }
  }; 
  template<class T>
  class CompositeSimpson{
    public:
    std::vector<T> *data_x;
    CompositeSimpson(std::vector<T> &dx){
      data_x= &dx;
    }
  }; 

  template<class T>
  T computeIntegral(const std::vector<T> &data, Composite<T> method){
    T integral=std::accumulate(std::begin(data), std::end(data), decltype(data)::value_type(0));
    std::vector<T> &data_x=*method.data_x;
    T H= data_x[data.size()]-data_x[0];
    return integral/H;
  }
  template<class T>
  T computeIntegral(std::vector<T> data, CompositeTrapezoid<T> method){
    T integral=(T)0.0;
    std::vector<T> &data_x=*method.data_x;
    for(int i=1;i<data.size();++i){
      integral+=0.5*(data_x[i]-data_x[i-1])*(data[i]+data(i-1));
    }
    return integral;
  }
  template<class T>
  T computeIntegral(std::vector<T> data, CompositeSimpson<T> method){
    T integral=(T)0.0;
    T sixth=(T)0.166666666666666666;
    std::vector<T> &data_x=*method.data_x;
    for(int i=1;i<((data.size()/2)-2);++i){
      T hi=data_x[2*i]-data_x[(2*i)-1];
      T hip=data_x[(2*i)+1]-data_x[2*i];
      integral+=sixth*(hi+hip)
                        *((2.0-hi/hip)*data[2*i] +
                         (((hi+hip)*(hi+hip)/(hi*hip)))*data[2*i+1] +
                         (2.0-hi/hip)*data[2*i+2]);
    }
    if(data.size()%2){
      T hn=data_x[data.size()-1]-data_x[data.size()-2];
      T hnm=data_x[data.size()-2]-data_x[data.size()-3];
      integral+=data[data.size()-1]*((2.0*hn*hn)+(3.0*hn*hnm))/(6.0*(hnm+hn));
      integral+=data[data.size()-2]*(hn*hn+3.0*hn*hnm)/(6.0*hnm);
      integral+=data[data.size()-3]*(hn*hn*hn)/(6.0*hnm*(hnm+hn));
    }
    return integral; 
  }
};

namespace polynomials{

};