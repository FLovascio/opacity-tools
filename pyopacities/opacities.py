from ctypes import cdll
import os
import platform
import warnings

if platform.system()=='Linux':
  lib_name="libpyopacities.so"
elif platform.system()=='Darwin':
  lib_name="libpyopacities.dyl"
elif platform.system()=='Windows':
  lib_name="libpyopacities.dll"
  warnings.warn("Windows is not officially supported, the package may not work, or worse, quietly do the wrong thing.")

lib = cdll.LoadLibrary('./')
