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
### Supported systems
Currently supported build systems are:
### macOS:
GCC&LLVM on both intel and apple silicon M1, M2 has not been tested but should work under LLVM and probably also under GCC (distributed precompiled static libs are GCC M1 mac)

### Linux:
GCC&LLVM on all x86 and ARM platforms

### Windows:
The code _should_ compile and run under MinGW and MSVC but it is not tested or supported, as I do not have any access to a Windows machine to do any testing.

## Using the package
Once built, the CLIs can be used by calling them form `opacity-tools/bin/`. The arguements taken by the CLIs are input directory `--from_dir=./`, output directory `--output_dir=./`, output format `--text_output` default output is binary, and single precision `--FP32` default is double precision.
To use the libraries what is needed depends on the language being used. If the code calling the libraries is written in C++, you can just link the headers, as in C++ opacity tools is written as a headder only library. For other languages, things are a bit more involved, but this use is supported and intended. 

### C
For C linkage, you will have to link the static libraries found in `opacity-tools/lib/`, a simple example is provided in `opacity-tools/examples/`. The exposed C functions are also declared in the headers provided in `opacity-tools/include`, including these headers will allow for type checking and autocomplete in some editors/IDEs.

### FORTRAN
For FORTRAN linkage, FORTRAN friendly functions `type functionname_(arg*, ...)` have been defined in the `*_interface.cxx` files, these functions take care of most quirks of FORTRAN arg passing quirks internally and _should_ behave to a user in the same way as their C counterparts. An example of FORTRAN usage of the libs is provided in `opacity-tools/examples/`. 

### Other
There is currently no support for other languages, though a python wrapper is on the roadmap. All languages that can call C functions should be easy to support, and this can be "left as an exercise to the user".
