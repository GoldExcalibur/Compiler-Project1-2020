# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hjh/CompilerProject-2020Spring-Part1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug

# Include any dependencies generated for this target.
include project1/CMakeFiles/solution.dir/depend.make

# Include the progress variables for this target.
include project1/CMakeFiles/solution.dir/progress.make

# Include the compile flags for this target's objects.
include project1/CMakeFiles/solution.dir/flags.make

project1/CMakeFiles/solution.dir/solution/example_solution.cc.o: project1/CMakeFiles/solution.dir/flags.make
project1/CMakeFiles/solution.dir/solution/example_solution.cc.o: ../project1/solution/example_solution.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object project1/CMakeFiles/solution.dir/solution/example_solution.cc.o"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solution.dir/solution/example_solution.cc.o -c /home/hjh/CompilerProject-2020Spring-Part1/project1/solution/example_solution.cc

project1/CMakeFiles/solution.dir/solution/example_solution.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/solution/example_solution.cc.i"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hjh/CompilerProject-2020Spring-Part1/project1/solution/example_solution.cc > CMakeFiles/solution.dir/solution/example_solution.cc.i

project1/CMakeFiles/solution.dir/solution/example_solution.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/solution/example_solution.cc.s"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hjh/CompilerProject-2020Spring-Part1/project1/solution/example_solution.cc -o CMakeFiles/solution.dir/solution/example_solution.cc.s

# Object files for target solution
solution_OBJECTS = \
"CMakeFiles/solution.dir/solution/example_solution.cc.o"

# External object files for target solution
solution_EXTERNAL_OBJECTS =

project1/solution: project1/CMakeFiles/solution.dir/solution/example_solution.cc.o
project1/solution: project1/CMakeFiles/solution.dir/build.make
project1/solution: libboost.so
project1/solution: project1/CMakeFiles/solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable solution"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project1/CMakeFiles/solution.dir/build: project1/solution

.PHONY : project1/CMakeFiles/solution.dir/build

project1/CMakeFiles/solution.dir/clean:
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 && $(CMAKE_COMMAND) -P CMakeFiles/solution.dir/cmake_clean.cmake
.PHONY : project1/CMakeFiles/solution.dir/clean

project1/CMakeFiles/solution.dir/depend:
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hjh/CompilerProject-2020Spring-Part1 /home/hjh/CompilerProject-2020Spring-Part1/project1 /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1/CMakeFiles/solution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project1/CMakeFiles/solution.dir/depend

