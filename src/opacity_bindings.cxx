/*#define PY_SSIZE_T_CLEAN

#ifdef __linux__ // Should compile under linux -will test-
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#elif __APPLE__ 
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#else // I do not have a windows machine so will not support win32_64 in the forseable future
#error "Unsupported compiler"
#endif

#include <iostream>
#include <cstdlib>
#include "Conductivity.hxx"
#include "FileIO.hxx"
#include "Opacity.hxx"

namespace py = pybind11;

PYBIND11_PLUGIN(opacity_bindings, m){
    m.doc() = "Opacity calculations using effective medium approximation accellerated in c++";
    

}
*/