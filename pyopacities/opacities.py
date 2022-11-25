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

cdll.LoadLibrary('./'+lib_name)
lib = ctypes.CDLL('./'+lib_name)

def make_nd_array(c_pointer, shape, dtype=np.float64, order='C', own_data=True):
  arr_size = np.prod(shape[:]) * np.dtype(dtype).itemsize 
  buf_from_mem = ctypes.pythonapi.PyMemoryView_FromMemory
  buf_from_mem.restype = ctypes.py_object
  buf_from_mem.argtypes = (ctypes.c_void_p, ctypes.c_int, ctypes.c_int)
  buffer = buf_from_mem(c_pointer, arr_size, 0x100)
  arr = np.ndarray(tuple(shape[:]), dtype, buffer, order=order)
  if own_data and not arr.flags.owndata:
    return arr.copy()
  else:
    return arr
class mixedGrain:
  # __del__(self) has been overloaded so that if GC tries to clean up the object,
  # the correct thing is done
  def __init__(self,setupDir):
    dirString = setupDir.encode('utf-8')
    alocate=lib.makeMixedGrain
    alocate.restype=ctypes.c_void_p
    get_handler=lib.mixedGrainHandler
    get_handler.restype=ctypes.c_void_p
    get_lambda=lib.get_lambdaMixed
    get_lambda.restype=ctypes.c_void_p
    get_cond=lib.get_conductivitiesMixed
    get_cond.restype=ctypes.c_void_p
    get_delta=lib.get_delta
    get_delta.restype=ctypes.c_void_p
    self.grain_pointer=alocate(ctypes.c_char_p(dirString))
    lambdaPoint=get_lambda(ctypes.c_void_p(self.grain_pointer))
    condPoint=get_cond(ctypes.c_void_p(self.grain_pointer))
    deltaPoint=get_delta(ctypes.c_void_p(self.grain_pointer))
    self.nMaterials=lib.get_nmaterials(ctypes.c_void_p(self.grain_pointer))
    self.length=lib.get_lengthMixed(ctypes.c_void_p(self.grain_pointer))
    self.lambdas = make_nd_array(lambdaPoint, shape=(self.length,),dtype=np.float64,own_data=False) 
    self.rawConductivities = make_nd_array(condPoint,shape=(2*self.length,),dtype=np.float64,own_data=False)
    self.conductivities= self.rawConductivities[0::2]+1.0j*self.rawConductivities[1::2]
    self.conductivities.setflags(write=False)
    self.deltas= make_nd_array(deltaPoint,shape=(self.nMaterials,),dtype=np.float64,own_data=False)
    self.handler=get_handler(ctypes.c_void_p(self.grain_pointer))
  def compute_conductivity(self):
    lib.calculateConductivity(ctypes.c_void_p(self.grain_pointer))
    self.conductivities= self.rawConductivities[0::2]+1.0j*self.rawConductivities[1::2]
    self.conductivities.setflags(write=False)
  def __del__(self):
    lib.deleteMixedGrain(ctypes.c_char_p(self.grain_pointer))
    del(self.grain_pointer) 
class coatedGrain:
  # __del__(self) has been overloaded so that if GC tries to clean up the object,
  # the correct thing is done
  def __init__(self,core,shell,r1,r2):
    alocate=lib.makeCoatedGrain
    alocate.restype=ctypes.c_void_p
    get_lambda=lib.get_lambdaCoated
    get_lambda.restype=ctypes.c_void_p
    get_handler=lib.coatedGrainHandler
    get_handler.restype=ctypes.c_void_p
    get_cond=lib.get_conductivitiesCoated
    get_cond.restype=ctypes.c_void_p
    self.grain_pointer=alocate(ctypes.c_void_p(core.grain_pointer),ctypes.c_void_p(shell.grain_pointer),ctypes.c_double(r1),ctypes.c_double(r2))
    lambdaPoint=get_lambda(ctypes.c_void_p(self.grain_pointer))
    condPoint=get_cond(ctypes.c_void_p(self.grain_pointer))
    self.length=lib.get_lengthCoated(ctypes.c_void_p(self.grain_pointer))
    self.lambdas = make_nd_array(lambdaPoint, shape=(self.length,),dtype=np.float64,own_data=False) 
    self.rawConductivities = make_nd_array(condPoint,shape=(2*self.length,),dtype=np.float64,own_data=False)
    self.conductivities= self.rawConductivities[0::2]+1.0j*self.rawConductivities[1::2]
    self.conductivities.setflags(write=False)
    self.handler=get_handler(ctypes.c_void_p(self.grain_pointer))
  def add_layer(self,shell,thickness):
    addLayer=lib.addLayer
    addLayer(ctypes.c_void_p(self.grain_pointer),ctypes.c_void_p(shell.grain_pointer),ctypes.c_double(thickness)) 
  def compute_conductivity(self):
    lib.calculateConductivity(ctypes.c_void_p(self.grain_pointer))
    self.conductivities= self.rawConductivities[0::2]+1.0j*self.rawConductivities[1::2]
    self.conductivities.setflags(write=False)
  def __del__(self):
    lib.deleteCoatedGrain(ctypes.c_char_p(self.grain_pointer))
    del(self.grain_pointer)

class percolatedMixedGrain:
  # __del__(self) has been overloaded so that if GC tries to clean up the object,
  # the correct thing is done
  def __init__(self,setupDir):
    dirString = setupDir.encode('utf-8')
    alocate=lib.makePercolatedMixedGrain
    alocate.restype=ctypes.c_void_p
    get_handler=lib.mixedPercolatedGrainHandler
    get_handler.restype=ctypes.c_void_p
    get_lambda=lib.get_lambdaPercolated
    get_lambda.restype=ctypes.c_void_p
    get_cond=lib.get_conductivitiesPercolated
    get_cond.restype=ctypes.c_void_p
    get_delta=lib.get_deltaPercolated
    get_delta.restype=ctypes.c_void_p
    self.grain_pointer=alocate(ctypes.c_char_p(dirString))
    lambdaPoint=get_lambda(ctypes.c_void_p(self.grain_pointer))
    condPoint=get_cond(ctypes.c_void_p(self.grain_pointer))
    deltaPoint=get_delta(ctypes.c_void_p(self.grain_pointer))
    self.nMaterials=lib.get_nmaterials(ctypes.c_void_p(self.grain_pointer))
    self.length=lib.get_lengthMixed(ctypes.c_void_p(self.grain_pointer))
    self.lambdas = make_nd_array(lambdaPoint, shape=(self.length,),dtype=np.float64,own_data=False) 
    self.rawConductivities = make_nd_array(condPoint,shape=(2*self.length,),dtype=np.float64,own_data=False)
    self.conductivities= self.rawConductivities[0::2]+1.0j*self.rawConductivities[1::2]
    self.conductivities.setflags(write=False)
    self.deltas= make_nd_array(deltaPoint,shape=(self.nMaterials,),dtype=np.float64,own_data=False)
    self.handler=get_handler(ctypes.c_void_p(self.grain_pointer))
  def compute_conductivity(self):
    lib.calculateConductivity(ctypes.c_void_p(self.grain_pointer))
    self.conductivities= self.rawConductivities[0::2]+1.0j*self.rawConductivities[1::2]
    self.conductivities.setflags(write=False)
  def __del__(self):
    lib.deleteMixedGrain(ctypes.c_char_p(self.grain_pointer))
    del(self.grain_pointer) 
class dustDistribution:
  # __del__(self) has been overloaded so that if GC tries to clean up the object,
  # the correct thing is done
  def __init__(self,grainSize,sizeDensity):
    alocate=lib.makeDustDist
    alocate.restype=ctypes.c_void_p
    self.length=len(grainSize)
    self.dust_object=alocate(grainSize.ctypes.data_as(ctypes.c_void_p),sizeDensity.ctypes.data_as(ctypes.c_void_p),self.length)
  def set_grainSize(self,grainSize):
    if self.length==len(grainSize):
      lib.setDustSize(grainSize.ctypes.data_as(ctypes.c_void_p), ctypes.c_void_p(self.dust_object), self.length)
    else:
      raise ValueError("array lengths don't match, do you want to segfault? \nMake a new object instead or use an array of the same length as the one used to init the object.")
  def set_sizeDensity(self,sizeDensity):
    if self.length==len(sizeDensity):
      lib.setDensity(sizeDensity.ctypes.data_as(ctypes.c_void_p), ctypes.c_void_p(self.dust_object), self.length)
    else:
      raise ValueError("array lengths don't match, do you want to segfault? \nMake a new object instead or use an array of the same length as the one used to init the object.")
  def __del__(self):
    lib.deallocateDust(ctypes.c_void_p(self.dust_object))
    del(self.dust_object)
    del(self.length)
class opacity:
  # __del__(self) has been overloaded so that if GC tries to clean up the object,
  # the correct thing is done
  def __init__(self,length,buffer=16):
    alocate=libc.malloc
    alocate.restype=ctypes.c_void_p
    self.buffer=buffer
    self.opacity_data_pointer=alocate((length+buffer)*ctypes.sizeof(ctypes.c_double))
    self.data = make_nd_array(ctypes.c_void_p(self.opacity_data_pointer),shape=(length,),dtype=np.float64,own_data=False)
    self.length=length
  def calculate_opacity(self,grainProperties,dustDistribution):
    lib.calculateOpacity(ctypes.c_void_p(dustDistribution.dust_object),ctypes.c_void_p(grainProperties.handler),ctypes.c_void_p(self.opacity_data_pointer))
    self.data = make_nd_array(ctypes.c_void_p(self.opacity_data_pointer),shape=(self.length,),dtype=np.float64,own_data=False)
  def __del__(self):
    libc.free(ctypes.c_void_p(self.opacity_data_pointer), (self.buffer+self.length) * ctypes.sizeof(ctypes.c_double))

opacity_import="success"