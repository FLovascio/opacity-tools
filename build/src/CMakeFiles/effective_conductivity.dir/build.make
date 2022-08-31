# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.23.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fra/Code/opacity-tools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fra/Code/opacity-tools/build

# Include any dependencies generated for this target.
include src/CMakeFiles/effective_conductivity.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/effective_conductivity.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/effective_conductivity.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/effective_conductivity.dir/flags.make

src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o: src/CMakeFiles/effective_conductivity.dir/flags.make
src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o: ../src/ConductivityTools.cxx
src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o: src/CMakeFiles/effective_conductivity.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fra/Code/opacity-tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o"
	cd /Users/fra/Code/opacity-tools/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o -MF CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o.d -o CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o -c /Users/fra/Code/opacity-tools/src/ConductivityTools.cxx

src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.i"
	cd /Users/fra/Code/opacity-tools/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fra/Code/opacity-tools/src/ConductivityTools.cxx > CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.i

src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.s"
	cd /Users/fra/Code/opacity-tools/build/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fra/Code/opacity-tools/src/ConductivityTools.cxx -o CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.s

# Object files for target effective_conductivity
effective_conductivity_OBJECTS = \
"CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o"

# External object files for target effective_conductivity
effective_conductivity_EXTERNAL_OBJECTS =

../bin/effective_conductivity: src/CMakeFiles/effective_conductivity.dir/ConductivityTools.cxx.o
../bin/effective_conductivity: src/CMakeFiles/effective_conductivity.dir/build.make
../bin/effective_conductivity: src/CMakeFiles/effective_conductivity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fra/Code/opacity-tools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/effective_conductivity"
	cd /Users/fra/Code/opacity-tools/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/effective_conductivity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/effective_conductivity.dir/build: ../bin/effective_conductivity
.PHONY : src/CMakeFiles/effective_conductivity.dir/build

src/CMakeFiles/effective_conductivity.dir/clean:
	cd /Users/fra/Code/opacity-tools/build/src && $(CMAKE_COMMAND) -P CMakeFiles/effective_conductivity.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/effective_conductivity.dir/clean

src/CMakeFiles/effective_conductivity.dir/depend:
	cd /Users/fra/Code/opacity-tools/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fra/Code/opacity-tools /Users/fra/Code/opacity-tools/src /Users/fra/Code/opacity-tools/build /Users/fra/Code/opacity-tools/build/src /Users/fra/Code/opacity-tools/build/src/CMakeFiles/effective_conductivity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/effective_conductivity.dir/depend

