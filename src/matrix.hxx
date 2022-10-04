#pragma once

#include <array>
#include <tuple>
#include <functional>
#include <iostream>

namespace containers{
template <class T, int Rows, int Cols>
class static2Matrix{
  private:
  std::array<T, Rows*Cols> data;
  int rows=Rows;
  int columns=Cols;
  
  public:
  static2Matrix(){
    data.fill((T)0);
  }
  static2Matrix(T fillV){
    data.fill(fillV);
  }
  static2Matrix(std::array<std::array<T,Rows>,Cols> input){
    data.fill((T)0);
    for(int i=0;i<Rows;++i){
      for(int j=0;j<Cols;++j){
        data[j+i*Cols]=input[i][j];
      }
    }
  }
  static2Matrix(const static2Matrix<T,Rows,Cols>&& a){
    data=a.data;
    rows=Rows;
    columns=Cols;
  }
  static2Matrix(const static2Matrix<T,Rows,Cols>& a){
    data=a.data;
    rows=Rows;
    columns=Cols;
  }
  static2Matrix<T,Rows,Cols>& operator=(const static2Matrix<T,Rows,Cols>&& a){
    data=a.data;
    return *this;
  }
  static2Matrix<T,Rows,Cols>& operator=(const static2Matrix<T,Rows,Cols>& a){
    data=a.data;
    return *this;
  }
  T& operator()(int i, int j){
    return *data[j+i*Cols];
  }
  static2Matrix<T,Rows,Cols> operator*(const static2Matrix<T,Rows,Cols>& a){
    static2Matrix<T,Rows,Cols> retMatrix;

  } 
  static2Matrix<T,Rows,Cols> operator*(const static2Matrix<T,Rows,1>& v){
    static2Matrix<T,Rows,1> retVector;

  } 
};
template<class T,int Rows,int Cols>
std::tuple<static2Matrix<T,Rows,Cols>,static2Matrix<T,Rows,Cols>> LU(static2Matrix<T,Rows,Cols>& A){
  static2Matrix<T,Rows,Cols> L;
  static2Matrix<T,Rows,Cols> U;
  if constexpr(Rows != Cols){
    std::cerr<< "SHAPE ERROR: Rows != Cols. Aborting!\n";
    return std::make_tuple(L,U);;
  }
  for (int i = 0; i < Rows; i++){
    // Upper Triangular
    for (int k = i; k < Rows; k++){
      // Summation of L(i, j) * U(j, k)
      T sum = (T)0;
      for (int j = 0; j < i; j++){
        sum += (L(i,j) * U(j,k));
      }
      // Evaluating U(i, k)
      U(i,k) = A(i,k) - sum;
    }
    // Lower Triangular
    for (int k = i; k < Rows; k++){
      if (i == k)
        L(i,i) = 1; // Diagonal as 1
      else{
        // Summation of L(k, j) * U(j, i)
        int sum = 0;
        for (int j = 0; j < i; j++){
          sum += (L(k,j) * U(j,i));
        }
        // Evaluating L(k, i)
        L(k,i) = (A(k,i) - sum) / U(i,i);
      }
    }
  }
  return std::make_tuple(L,U);
}

template<class T,int Rows,int Cols>
static2Matrix<T,Rows,1> LUsolve(static2Matrix<T,Rows,Cols>& A, static2Matrix<T,Rows,1> &v){
  auto LUmat = LU(A);
  static2Matrix<T,Rows,1> z;
  static2Matrix<T,Rows,1> x;
  
}
};