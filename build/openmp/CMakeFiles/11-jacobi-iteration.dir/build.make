# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/nelson/Documents/WI4265TU Parallel Programming/examples"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/nelson/Documents/WI4265TU Parallel Programming/build"

# Include any dependencies generated for this target.
include openmp/CMakeFiles/11-jacobi-iteration.dir/depend.make

# Include the progress variables for this target.
include openmp/CMakeFiles/11-jacobi-iteration.dir/progress.make

# Include the compile flags for this target's objects.
include openmp/CMakeFiles/11-jacobi-iteration.dir/flags.make

openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o: openmp/CMakeFiles/11-jacobi-iteration.dir/flags.make
openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o: /home/nelson/Documents/WI4265TU\ Parallel\ Programming/examples/openmp/11-jacobi-iteration.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nelson/Documents/WI4265TU Parallel Programming/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o   -c "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp/11-jacobi-iteration.c"

openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.i"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp/11-jacobi-iteration.c" > CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.i

openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.s"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp/11-jacobi-iteration.c" -o CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.s

openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.requires:

.PHONY : openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.requires

openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.provides: openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.requires
	$(MAKE) -f openmp/CMakeFiles/11-jacobi-iteration.dir/build.make openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.provides.build
.PHONY : openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.provides

openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.provides.build: openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o


# Object files for target 11-jacobi-iteration
11__jacobi__iteration_OBJECTS = \
"CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o"

# External object files for target 11-jacobi-iteration
11__jacobi__iteration_EXTERNAL_OBJECTS =

openmp/11-jacobi-iteration: openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o
openmp/11-jacobi-iteration: openmp/CMakeFiles/11-jacobi-iteration.dir/build.make
openmp/11-jacobi-iteration: openmp/CMakeFiles/11-jacobi-iteration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nelson/Documents/WI4265TU Parallel Programming/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 11-jacobi-iteration"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/11-jacobi-iteration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
openmp/CMakeFiles/11-jacobi-iteration.dir/build: openmp/11-jacobi-iteration

.PHONY : openmp/CMakeFiles/11-jacobi-iteration.dir/build

openmp/CMakeFiles/11-jacobi-iteration.dir/requires: openmp/CMakeFiles/11-jacobi-iteration.dir/11-jacobi-iteration.c.o.requires

.PHONY : openmp/CMakeFiles/11-jacobi-iteration.dir/requires

openmp/CMakeFiles/11-jacobi-iteration.dir/clean:
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && $(CMAKE_COMMAND) -P CMakeFiles/11-jacobi-iteration.dir/cmake_clean.cmake
.PHONY : openmp/CMakeFiles/11-jacobi-iteration.dir/clean

openmp/CMakeFiles/11-jacobi-iteration.dir/depend:
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nelson/Documents/WI4265TU Parallel Programming/examples" "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp" "/home/nelson/Documents/WI4265TU Parallel Programming/build" "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp/CMakeFiles/11-jacobi-iteration.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : openmp/CMakeFiles/11-jacobi-iteration.dir/depend

