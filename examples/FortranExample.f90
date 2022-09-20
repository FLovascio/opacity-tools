
program example
  use iso_c_binding
  implicit none

  interface
    function  buildConductivityF(nme) bind(c,name="buildConductivity")
       import
       character(kind=c_char), dimension(*) :: nme
       type(c_ptr) :: buildConductivityF
    end function buildConductivityF
    function  calculateConductivityF(conductObj) bind(c,name="calculateConductivity")
       import
       type(c_ptr):: conductObj
       integer :: calculateConductivityF
    end function calculateConductivityF
    function  lambdaF(conductObj,ind) bind(c,name="lambda")
       import
       type(c_ptr):: conductObj
       integer :: ind
       real :: lambdaF
     end function lambdaF
  end interface
  character(len=128,kind=c_char)::file
  type(c_ptr) :: ret 
  integer :: placeHolder
  file = "/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/"
  ret = buildConductivityF(trim(file))
  print *,lambdaF(ret,1) 
  placeHolder=calculateConductivityF(ret)
end program example
