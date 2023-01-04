#compile the project as a standalone application
add_executable(OpacityTests CodeTests.cxx Conductivity.hxx FileIO.hxx Opacity.hxx roots.hxx allocators.hxx)
add_executable(effective_conductivity ConductivityTools.cxx FileIO.hxx roots.hxx Conductivity.hxx allocators.hxx)
add_executable(opacity OpacityTools.cxx Opacity.hxx FileIO.hxx roots.hxx Conductivity.hxx allocators.hxx )
add_library(opacities opacity_interfaces.h opacity_interfaces.cxx Opacity.hxx FileIO.hxx roots.hxx Conductivity.hxx allocators.hxx integrals.hxx)
add_library(conductivities conductivity_interfaces.h conductivity_interfaces.cxx FileIO.hxx roots.hxx Conductivity.hxx allocators.hxx)
add_library(pyopacities SHARED py_opacities.h py_opacities.cxx Opacity.hxx FileIO.hxx roots.hxx Conductivity.hxx allocators.hxx integrals.hxx)
set_target_properties(pyopacities
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pyopacities/
)
pybind11_add_module(opacity_tools python_bindings.cxx)