cmake_minimum_required(VERSION 3.20.0)
project(OpacityTools VERSION 0.1.0)

include(CTest)
enable_testing()

#set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-12")
#set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-12")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS  "-O3 -g")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_subdirectory(src)
