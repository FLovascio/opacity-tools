# opacity-tools
The ```opacity-tools``` package aims to provide a portable library for calculating opacities with multilanguage support.
Target applications are on-the-fly dust opacities in multi-dust hydrocodes and radiative transfer codes. The library offers support for different grain compositions (currently) using Brugemann effective medium approximation, and arbitrary dust grain size distributions. Both integrated Rosseland & Planck opacities and wavelength dependant opacities (for use with multigroup radiadive transfer codes) can be calculated.

## Installing the library and CLI
To install this library you will (most likely) have to build it from source. To obtain the source code run
```
$git clone https://github.com/FLovascio/opacity-tools
```
in your terminal.
To then make, you need to first generate a makefile and then make:
```
$cd </path/to/oapacity-tools/>
$cmake .
$make
```

## Using the package