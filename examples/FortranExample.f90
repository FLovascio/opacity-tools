
program example
  use iso_c_binding
  implicit none
  
  integer :: calculateConductivity
  type(c_ptr):: buildConductivity, testInterface
  character(len=128,kind=c_char)::file,file2
  real(kind=c_double)::lambda
  type(c_ptr) :: ret, ret1
  integer :: placeHolder
  external :: buildConductivity, testInterface, calculateConductivity

  file = "/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/"
  ret = buildConductivity(trim(file))
  print *,"Built conductivity object at:", ret
  ret1 = testInterface(trim(file))
  print *,"lambda[1] found at address ",ret,":",lambda(ret1,int(1)) 
  placeHolder=calculateConductivity(ret)

end program example
