
program example
  use iso_c_binding
  implicit none

  integer :: calculateConductivity
  type(c_ptr):: buildConductivity, testInterface
  real :: lambda
  character(len=128,kind=c_char)::file,file2
  type(c_ptr) :: ret, ret1
  integer :: placeHolder

  file = "/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/"
  ret = buildConductivity(trim(file))
  print *,ret , file
  file2 = "/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/"
  ret1 = testInterface(trim(file2), int(1), 2.0)
  !print *,ret1
  !print *,ret,int(1) 
  print *,lambda(ret1,int(1)) 
  !placeHolder=calculateConductivity(ret)
end program example
