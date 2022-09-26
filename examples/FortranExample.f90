
program example
   use iso_c_binding
   implicit none

   integer :: calculateConductivity, setDustSize, setDensity, calculateOpacity, deallocateDust
   type(c_ptr):: buildConductivity, testInterface, makeDustDist
   character(len=128, kind=c_char)::file
   real(kind=c_double)::lambda
   real(kind=c_double)::dusts(10)
   real(kind=c_double)::dustd(10)
   real(kind=c_double),allocatable::opacities(:)
   type(c_ptr) :: cond, ret1, dist1
   integer :: placeHolder
   external :: buildConductivity, testInterface, calculateConductivity, setDustSize, setDensity
   external :: calculateOpacity, deallocateDust, makeDustDist
   allocate(opacities(113))
   dusts = (/0.001,0.002,0.003,0.004,0.005,0.006,0.007,0.008,0.009,0.01/)
   dustd = (/0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1/)
   file = "/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/"
   cond = buildConductivity(trim(file))
   print *, "Built conductivity object at:", cond
   ret1 = testInterface(trim(file))
   print *, "lambda[1] found at address ", ret1, ":", lambda(ret1, int(1))
   placeHolder = calculateConductivity(cond)
   dist1 = makeDustDist(dusts,dustd,10)
   placeHolder = calculateOpacity(dist1,cond,opacities)
   print *,"calculated opacities"
   print *,"opacities[112]= ",opacities(112)

end program example
