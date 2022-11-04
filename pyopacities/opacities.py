import ctypes
from ctypes import cdll
from ctypes.util import find_library
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
  lib_name="libpyopacities.dylib"
elif platform.system()=='Windows':
  lib_name="libpyopacities.dll"
  warnings.warn("Windows is not tested, the package may not work, or worse, quietly do the wrong thing.")

libc = ctypes.CDLL(find_library('c'))
libc.malloc.restype = ctypes.c_void_p

cdll.LoadLibrary('./'+lib_name)
lib = ctypes.CDLL('./'+lib_name)
class conductivity:
  def __init__(self,setupDir):
    dirString = setupDir.encode('utf-8')
    print("Python says: reading from:"+setupDir)
    self.conductivity_pointer=lib.buildConductivity(ctypes.c_char_p(dirString))
    print("Python says: built object at: "+str(hex(self.conductivity_pointer)))
    self.length=lib.getLen(self.conductivity_pointer)
    print("Python says: of length: "+str(self.length))
    self.lambdas = np.ctypeslib.as_array(self.opacity_data_pointer,shape=(self.length,))
    self.conductivities = np.ctypeslib.as_array(self.opacity_data_pointer,shape=(2*self.length,))[0::2]+np.ctypeslib.as_array(self.opacity_data_pointer,shape=(2*self.length,))[1::2]*1.0j
  def compute_conductivity(self):
    lib.calculateConductivity(self.conductivity_pointer)
  def get_conductivity(self,i):
    return complex(lib.realConductivity(self.conductivity_pointer,i),lib.imagConductivity(self.conductivity_pointer,i))
  def get_lambda(self,i):
    return lib.lambdaValue(self.conductivity_pointer,i)
  def __del__(self):
    lib.deallocateConductivityObject(self.conductivity_pointer)
    del(self.conductivity_pointer)
class dustDistribution:
  def __init__(self,grainSize,sizeDensity):
    self.length=len(grainSize)
    self.dust_object=lib.makeDustDist(grainSize.ctypes.data_as(ctypes.c_void_p),sizeDensity.ctypes.data_as(ctypes.c_void_p),self.length)
  def set_grainSize(self,grainSize):
    if self.length==len(grainSize):
      lib.setDustSize(grainSize.ctypes.data_as(ctypes.c_void_p), self.dust_object, self.length)
    else:
      raise ValueError("array lengths don't match, do you want to segfault? \nMake a new object instead or use an array of the same length as the one used to init the object.")
  def set_sizeDensity(self,sizeDensity):
    if self.length==len(sizeDensity):
      lib.setDensity(sizeDensity.ctypes.data_as(ctypes.c_void_p), self.dust_object, self.length)
    else:
      raise ValueError("array lengths don't match, do you want to segfault? \nMake a new object instead or use an array of the same length as the one used to init the object.")
class opacity:
  def __init__(self,length):
    self.opacity_data_pointer=libc.malloc((length * ctypes.sizeof(ctypes.c_double)))
    self.data = np.ctypeslib.as_array(self.opacity_data_pointer,shape=(length,))
    self.length=length
  def calculate_opacity(self,grainProperties,dustDistribution):
    lib.calculateOpacity(dustDistribution,grainProperties,self.opacity_data_pointer)
  def __del__(self):
    del(self.data)
    libc.free(self.opacity_data_pointer, self.length * ctypes.sizeof(ctypes.c_double))

opacity_import="success"