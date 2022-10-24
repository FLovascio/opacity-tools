import ctypes
from ctypes import cdll
import os
import platform
import warnings
import numpy as np

if platform.system()=='Linux':
  lib_name="libpyopacities.so"
elif platform.system()=='SunOS':
  lib_name="libpyopacities.so"
  warnings.warn("Solaris is not tested, the package may not work, or worse, quietly do the wrong thing.") 
elif platform.system()=='Darwin':
  lib_name="libpyopacities.dyl"
elif platform.system()=='Windows':
  lib_name="libpyopacities.dll"
  warnings.warn("Windows is not tested, the package may not work, or worse, quietly do the wrong thing.")

lib = cdll.LoadLibrary('./'+lib_name)
class conductivity:
  def __init__(self,setupDir):
    dirString = setupDir.encode('utf-8')
    self.conductivity_pointer=lib.buildConductivity(ctypes.c_char_p(dirString))
  def compute_conductivity(self):
    lib.calculateConductivity(self.conductivity_pointer)
  def get_conductivity(self,i):
    return complex(lib.realConductivity(self.conductivity_pointer,i),lib.imagConductivity(self.conductivity_pointer,i))
  def get_lambda(self,i):
    return lib.lambdaValue(self.conductivity_pointer,i)