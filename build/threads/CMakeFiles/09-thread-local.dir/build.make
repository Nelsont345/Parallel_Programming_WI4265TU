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
include threads/CMakeFiles/09-thread-local.dir/depend.make

# Include the progress variables for this target.
include threads/CMakeFiles/09-thread-local.dir/progress.make

# Include the compile flags for this target's objects.
include threads/CMakeFiles/09-thread-local.dir/flags.make

threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o: threads/CMakeFiles/09-thread-local.dir/flags.make
threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o: /home/nelson/Documents/WI4265TU\ Parallel\ Programming/examples/threads/09-thread-local.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nelson/Documents/WI4265TU Parallel Programming/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/threads" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/09-thread-local.dir/09-thread-local.c.o   -c "/home/nelson/Documents/WI4265TU Parallel Programming/examples/threads/09-thread-local.c"

threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/09-thread-local.dir/09-thread-local.c.i"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/threads" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/nelson/Documents/WI4265TU Parallel Programming/examples/threads/09-thread-local.c" > CMakeFiles/09-thread-local.dir/09-thread-local.c.i

threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/09-thread-local.dir/09-thread-local.c.s"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/threads" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/nelson/Documents/WI4265TU Parallel Programming/examples/threads/09-thread-local.c" -o CMakeFiles/09-thread-local.dir/09-thread-local.c.s

threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.requires:

.PHONY : threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.requires

threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.provides: threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.requires
	$(MAKE) -f threads/CMakeFiles/09-thread-local.dir/build.make threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.provides.build
.PHONY : threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.provides

threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.provides.build: threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o


# Object files for target 09-thread-local
09__thread__local_OBJECTS = \
"CMakeFiles/09-thread-local.dir/09-thread-local.c.o"

# External object files for target 09-thread-local
09__thread__local_EXTERNAL_OBJECTS =

threads/09-thread-local: threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o
threads/09-thread-local: threads/CMakeFiles/09-thread-local.dir/build.make
threads/09-thread-local: threads/CMakeFiles/09-thread-local.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nelson/Documents/WI4265TU Parallel Programming/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 09-thread-local"
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/threads" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/09-thread-local.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
threads/CMakeFiles/09-thread-local.dir/build: threads/09-thread-local

.PHONY : threads/CMakeFiles/09-thread-local.dir/build

threads/CMakeFiles/09-thread-local.dir/requires: threads/CMakeFiles/09-thread-local.dir/09-thread-local.c.o.requires

.PHONY : threads/CMakeFiles/09-thread-local.dir/requires

threads/CMakeFiles/09-thread-local.dir/clean:
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build/threads" && $(CMAKE_COMMAND) -P CMakeFiles/09-thread-local.dir/cmake_clean.cmake
.PHONY : threads/CMakeFiles/09-thread-local.dir/clean

threads/CMakeFiles/09-thread-local.dir/depend:
	cd "/home/nelson/Documents/WI4265TU Parallel Programming/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nelson/Documents/WI4265TU Parallel Programming/examples" "/home/nelson/Documents/WI4265TU Parallel Programming/examples/threads" "/home/nelson/Documents/WI4265TU Parallel Programming/build" "/home/nelson/Documents/WI4265TU Parallel Programming/build/threads" "/home/nelson/Documents/WI4265TU Parallel Programming/build/threads/CMakeFiles/09-thread-local.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : threads/CMakeFiles/09-thread-local.dir/depend

