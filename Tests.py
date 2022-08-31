import os
import numpy as np
import matplotlib.pyplot as plt
import scipy.constants as spc

os.system("./bin/OpacityTests")
refValues=np.genfromtxt("./ReferenceValues/reference_data.csv",delimiter=",")
refValue_dusts=np.genfromtxt("./ReferenceValues/reference_data_dust.csv",delimiter=",")
refValue_dustsize=np.genfromtxt("./ReferenceValues/reference_data_dust_s.csv",delimiter=",")
resultsKappa=np.fromfile("./bin/KDust.bin",dtype="double")
resultsLambda = np.genfromtxt("./bin/Lambda.csv",delimiter=" ")
resultsDust = np.genfromtxt("./bin/Dust.csv",delimiter=" ")
resultsDustSize = np.genfromtxt("./bin/Dust_size.csv",delimiter=" ")
tpe = np.dtype([('i','<i2'), ('q','<i2')])
resultsNu = np.genfromtxt("./bin/EffectiveConductivities.csv",delimiter=" ")
resultsNu = np.asarray([np.complex(arV[0],arV[1]) for arV in resultsNu])
refValues_nu = np.loadtxt("./ReferenceValues/reference_data_nu.csv").view(complex)

plt.figure()
plt.title(r"($\kappa$) comparison")
plt.xlabel(r"$\lambda$")
plt.ylabel(r"$\kappa$")
plt.loglog(refValues[:,0],refValues[:,1],label="Python")
plt.loglog((spc.speed_of_light*1e2)/(resultsLambda),resultsKappa,label="C++")
plt.legend()
plt.show()

plt.figure()
plt.title(r"Re($\nu$) comparison")
plt.xlabel(r"$\lambda$")
plt.ylabel(r"Re($\nu$)")
plt.loglog(refValues[:,0],refValues_nu.real,label="Python")
plt.loglog(refValues[:,0],resultsNu.real,label="OpacityTools")
plt.legend()
plt.show()


plt.figure() 
plt.title(r"Im($\nu$) comparison")
plt.xlabel(r"$\lambda$")
plt.ylabel(r"Im($\nu$)")
plt.loglog(refValues[:,0],refValues_nu.imag,label="Python")
plt.loglog(refValues[:,0],resultsNu.imag,label="OpacityTools")
plt.legend()
plt.show() 