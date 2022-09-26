# opacity-tools
The ```opacity-tools``` package aims to provide a portable library for calculating opacities with multilanguage support.
Target applications are on-the-fly dust opacities in multi-dust hydrocodes and radiative transfer codes. The library offers support for different grain compositions (currently) using Brugemann effective medium approximation, and arbitrary dust grain size distributions. Both integrated Rosseland & Planck opacities and wavelength dependant opacities (for use with multigroup radiadive transfer codes) can be calculated.

## Installing the library and CLI
To install this library you will (most likely) have to build it from source. To obtain the source code run
```
git clone https://github.com/FLovascio/opacity-tools
```
in your terminal.
To then make, you need to first generate a makefile and then make:
```
cd </path/to/oapacity-tools/>
cmake .
make -j <NCore>
```
To change compiler, run cmake as following:
```
cmake  -D CMAKE_C_COMPILER=<c-compiler>  -D CMAKE_CXX_COMPILER=<c++-compiler> .
```
In many cases this will not really matter, except when linking the library. The library build linkage should be done with the same compiler as the one used to build the code calling the library, or rather the same C++ standard library needs to be linked. Compiling the library with LLVM libs to then link it to a code compiled with GCC is an excellent way to generate cryptic linker errors. This will be of special importance when calling from a FORTRAN code, as there is still no support for FORTRAN in LLVM.
## Using the package