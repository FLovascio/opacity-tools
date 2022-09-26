
program example
   use iso_c_binding
   implicit none

   integer :: calculateConductivity, setDustSize, setDensity, calculateOpacity, deallocateDust
   type(c_ptr):: buildConductivity, testInterface, makeDustDist, makeOpacityVector
   character(len=128, kind=c_char)::file, file2
   real(kind=c_double)::lambda
   real(kind=c_double)::dusts(10)
   real(kind=c_double)::dustd(10)
   type(c_ptr) :: ret, ret1, dist1, vec1
   integer :: placeHolder
   external :: buildConductivity, testInterface, calculateConductivity, setDustSize, setDensity
   external :: calculateOpacity, deallocateDust, makeDustDist, makeOpacityVector
   dusts = (/0.001,0.002,0.003,0.004,0.005,0.006,0.007,0.008,0.009,0.01/)
   dustd = (/0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1/)
   file = "/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/"
   ret = buildConductivity(trim(file))
   print *, "Built conductivity object at:", ret
   ret1 = testInterface(trim(file))
   print *, "lambda[1] found at address ", ret, ":", lambda(ret1, int(1))
   placeHolder = calculateConductivity(ret)
   dist1 = makeDustDist(dusts,dustd,10)
end program example
