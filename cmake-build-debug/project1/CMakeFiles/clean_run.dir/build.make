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

# Utility rule file for clean_run.

# Include the progress variables for this target.
include project1/CMakeFiles/clean_run.dir/progress.make

project1/CMakeFiles/clean_run:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "run generated clean in /home/hjh/CompilerProject-2020Spring-Part1/project1"
	cd /home/hjh/CompilerProject-2020Spring-Part1/project1 && /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1/cleanf

clean_run: project1/CMakeFiles/clean_run
clean_run: project1/CMakeFiles/clean_run.dir/build.make

.PHONY : clean_run

# Rule to build all files generated by this target.
project1/CMakeFiles/clean_run.dir/build: clean_run

.PHONY : project1/CMakeFiles/clean_run.dir/build

project1/CMakeFiles/clean_run.dir/clean:
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 && $(CMAKE_COMMAND) -P CMakeFiles/clean_run.dir/cmake_clean.cmake
.PHONY : project1/CMakeFiles/clean_run.dir/clean

project1/CMakeFiles/clean_run.dir/depend:
	cd /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hjh/CompilerProject-2020Spring-Part1 /home/hjh/CompilerProject-2020Spring-Part1/project1 /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1 /home/hjh/CompilerProject-2020Spring-Part1/cmake-build-debug/project1/CMakeFiles/clean_run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project1/CMakeFiles/clean_run.dir/depend
