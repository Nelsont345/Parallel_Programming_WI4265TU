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
include openmp/CMakeFiles/05-dyadic-product-openmp.dir/depend.make

# Include the progress variables for this target.
include openmp/CMakeFiles/05-dyadic-product-openmp.dir/progress.make

# Include the compile flags for this target's objects.
include openmp/CMakeFiles/05-dyadic-product-openmp.dir/flags.make

openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o: openmp/CMakeFiles/05-dyadic-product-openmp.dir/flags.make
openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o: /home/nelson/Documents/WI4265TU\ Parallel\ Programming/examples/openmp/05-dyadic-product-openmp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nelson/Documents/WI4265TU Parallel Programming/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o   -c "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp/05-dyadic-product-openmp.c"

openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.i"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp/05-dyadic-product-openmp.c" > CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.i

openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.s"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp/05-dyadic-product-openmp.c" -o CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.s

openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.requires:

.PHONY : openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.requires

openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.provides: openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.requires
	$(MAKE) -f openmp/CMakeFiles/05-dyadic-product-openmp.dir/build.make openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.provides.build
.PHONY : openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.provides

openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.provides.build: openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o


# Object files for target 05-dyadic-product-openmp
05__dyadic__product__openmp_OBJECTS = \
"CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o"

# External object files for target 05-dyadic-product-openmp
05__dyadic__product__openmp_EXTERNAL_OBJECTS =

openmp/05-dyadic-product-openmp: openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o
openmp/05-dyadic-product-openmp: openmp/CMakeFiles/05-dyadic-product-openmp.dir/build.make
openmp/05-dyadic-product-openmp: openmp/CMakeFiles/05-dyadic-product-openmp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nelson/Documents/WI4265TU Parallel Programming/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 05-dyadic-product-openmp"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/05-dyadic-product-openmp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
openmp/CMakeFiles/05-dyadic-product-openmp.dir/build: openmp/05-dyadic-product-openmp

.PHONY : openmp/CMakeFiles/05-dyadic-product-openmp.dir/build

openmp/CMakeFiles/05-dyadic-product-openmp.dir/requires: openmp/CMakeFiles/05-dyadic-product-openmp.dir/05-dyadic-product-openmp.c.o.requires

.PHONY : openmp/CMakeFiles/05-dyadic-product-openmp.dir/requires

openmp/CMakeFiles/05-dyadic-product-openmp.dir/clean:
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" && $(CMAKE_COMMAND) -P CMakeFiles/05-dyadic-product-openmp.dir/cmake_clean.cmake
.PHONY : openmp/CMakeFiles/05-dyadic-product-openmp.dir/clean

openmp/CMakeFiles/05-dyadic-product-openmp.dir/depend:
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nelson/Documents/WI4265TU Parallel Programming/examples" "/home/nelson/Documents/WI4265TU Parallel Programming/examples/openmp" "/home/nelson/Documents/WI4265TU Parallel Programming/build" "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp" "/home/nelson/Documents/WI4265TU Parallel Programming/build/openmp/CMakeFiles/05-dyadic-product-openmp.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : openmp/CMakeFiles/05-dyadic-product-openmp.dir/depend

