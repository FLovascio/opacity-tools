#pragma once
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <complex>
#include <sstream>
#include <vector>
//namespace Parser { // required for faster file io  with delimited files, will
//                   // implement
//template <class T, int realVal, int imagVal>
//std::complex<T> parseLineToComplex(char *) {
//  std::complex<T> value(0, 0);
//  return value;
//}
//}; // namespace Parser

namespace delimitedFiles {
template <class T>
bool readDatToComplexVector(std::vector<std::complex<T>> &outputVector,
                            std::string filename) {
  int number_of_lines = 0;
  std::string line;
  std::ifstream countfile(filename);
  while (std::getline(countfile, line)){
      ++number_of_lines;
  }
  countfile.close();
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename << "'\n";
    return false;
  }
  if(number_of_lines!=outputVector.size()){
    outputVector.resize(number_of_lines);
  }
  T numbers[3];
  int i = 0;
  while (input_file >> numbers[0] >> numbers[1] >> numbers[2]) {
    outputVector[i] = std::complex<T>(numbers[1], numbers[2]);
    i++;
  }
  input_file.close();
  return true;
}
template <class T>
bool readDatToVector(std::vector<T> &outputVector, std::string filename) {
  int number_of_lines = 0;
  std::string line;
  std::ifstream countfile(filename);
  while (std::getline(countfile, line)){
      ++number_of_lines;
  }
  countfile.close();
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename << "'\n";
    return false;
  }
  if(number_of_lines!=outputVector.size()){
    outputVector.resize(number_of_lines);
  }
  T numbers[3];
  int i = 0;
  while (input_file >> numbers[0] >> numbers[1] >> numbers[2]) {
    outputVector[i] = numbers[0];
    i++;
  }
  input_file.close();
  return true;
}
template <class T>
bool readColumnToVector(std::vector<T> &outputVector, std::string filename) {
  int number_of_lines = 0;
  std::string line;
  std::ifstream countfile(filename);
  while (std::getline(countfile, line)){
      ++number_of_lines;
  }
  countfile.close();
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename << "'\n";
    return false;
  }
  if(number_of_lines!=outputVector.size()){
    outputVector.resize(number_of_lines);
  }
  T number;
  int i = 0;
  while (input_file >> number) {
    outputVector[i] = number;
    i++;
  }
  input_file.close();
  return true;
}
template <class T>
bool writeComplexVectorToFile(std::vector<std::complex<T>> &inputVector,
                              std::string filename) {
  std::ofstream output_file(filename);
  if (!output_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename << "'\n";
    return false;
  }
  for(int i=0; i <inputVector.size(); ++i){
    output_file << (std::to_string(inputVector[i].real()) + " " +
                         std::to_string(inputVector[i].imag()) + "\n");
  }
  output_file.close();
  return true;
}
template <class T>
bool writeRealVectorToFile(std::vector<T> &inputVector, std::string filename) {
  std::ofstream output_file(filename);
  if (!output_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename << "'\n";
    return false;
  }
  int i = 0;
  for(int i=0; i <inputVector.size(); ++i){
    std::ostringstream s;
    s<<inputVector[i];
    output_file << s.str() + "\n";
  }
  output_file.close();
  return true;
}
}; // namespace delimitedFiles

namespace binaryFiles {
template <class T>
bool writeComplexVectorToBinary(std::vector<std::complex<T>> data,
                                std::string filename) {
  std::ofstream fout(filename, std::ios::out | std::ios::binary);
  if (!data.empty()) {
    fout.write((char*)&data[0], data.size() * sizeof(std::complex<T>));
    return true;
  }
  return false;
}
template <class T>
bool writeRealVectorToBinary(std::vector<T> data, std::string filename) {
  std::ofstream fout(filename, std::ios::out | std::ios::binary);
  if (!data.empty()) {
    fout.write((char*)&data[0], data.size() * sizeof(T));
    return true;
  }
  return false;
}
}; // namespace binaryFiles
namespace setupFiles{
template <class T>
bool readMaterialsFile(std::vector<std::string> & materialNames, std::vector<T> & abbundances, std::string dir){
  int number_of_lines = 0;
  std::string line;
  std::string filename=dir+"material_abundancies.dat";
  std::ifstream countfile(filename);
  while (std::getline(countfile, line)){
      ++number_of_lines;
  }
  countfile.close();
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename << "'\n";
    return false;
  }
  if(number_of_lines!=materialNames.size()){
    materialNames.resize(number_of_lines);
  }
  if(number_of_lines!=abbundances.size()){
    abbundances.resize(number_of_lines);
  }
  T abbundance;
  std::string Name;
  int i = 0;
  while (input_file >> Name >> abbundance) {
    materialNames[i]=Name;
    abbundances[i]=abbundance;
    i++;
  }
  input_file.close();
  return true; 
}
}// namspace setupFiles