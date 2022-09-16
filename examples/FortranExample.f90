
program example
  use iso_c_binding
  implicit none

  interface
     function  buildConductivityF(nme) bind(c,name="buildConductivity")
       import
       character(kind=c_char), dimension(*) :: nme
       type(c_ptr) :: buildConductivityF
     end function buildConductivityF
  end interface
  character(len=100,kind=c_char)::file
  type(c_ptr) :: ret 
  file = "/Users/fra/Code/opacity-tools/new_cons/Normal_silicates/"
  ret = buildConductivityF(file) 
end program example
