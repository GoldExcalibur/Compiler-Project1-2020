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
include test/CMakeFiles/conv2d.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/conv2d.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/conv2d.dir/flags.make

test/CMakeFiles/conv2d.dir/conv2d.cc.o: test/CMakeFiles/conv2d.dir/flags.make
test/CMakeFiles/conv2d.dir/conv2d.cc.o: ../test/conv2d.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/conv2d.dir/conv2d.cc.o"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/conv2d.dir/conv2d.cc.o -c /home/hjh/CompilerProject-2020Spring-Part1/test/conv2d.cc

test/CMakeFiles/conv2d.dir/conv2d.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/conv2d.dir/conv2d.cc.i"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hjh/CompilerProject-2020Spring-Part1/test/conv2d.cc > CMakeFiles/conv2d.dir/conv2d.cc.i

test/CMakeFiles/conv2d.dir/conv2d.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/conv2d.dir/conv2d.cc.s"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hjh/CompilerProject-2020Spring-Part1/test/conv2d.cc -o CMakeFiles/conv2d.dir/conv2d.cc.s

# Object files for target conv2d
conv2d_OBJECTS = \
"CMakeFiles/conv2d.dir/conv2d.cc.o"

# External object files for target conv2d
conv2d_EXTERNAL_OBJECTS =

test/conv2d: test/CMakeFiles/conv2d.dir/conv2d.cc.o
test/conv2d: test/CMakeFiles/conv2d.dir/build.make
test/conv2d: libboost.so
test/conv2d: test/CMakeFiles/conv2d.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable conv2d"
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conv2d.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/conv2d.dir/build: test/conv2d

.PHONY : test/CMakeFiles/conv2d.dir/build

test/CMakeFiles/conv2d.dir/clean:
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/conv2d.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/conv2d.dir/clean

test/CMakeFiles/conv2d.dir/depend:
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hjh/CompilerProject-2020Spring-Part1 /home/hjh/CompilerProject-2020Spring-Part1/test /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/test /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/test/CMakeFiles/conv2d.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/conv2d.dir/depend

