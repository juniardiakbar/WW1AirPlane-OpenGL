# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/willy/.local/lib/python3.6/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/willy/.local/lib/python3.6/site-packages/cmake/data/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/willy/Documents/Github/WW1AirPlane-OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/willy/Documents/Github/WW1AirPlane-OpenGL/src

# Utility rule file for uninstall.

# Include the progress variables for this target.
include lib/glfw-3.1.2/CMakeFiles/uninstall.dir/progress.make

lib/glfw-3.1.2/CMakeFiles/uninstall:
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2 && /home/willy/.local/lib/python3.6/site-packages/cmake/data/bin/cmake -P /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/cmake_uninstall.cmake

uninstall: lib/glfw-3.1.2/CMakeFiles/uninstall
uninstall: lib/glfw-3.1.2/CMakeFiles/uninstall.dir/build.make

.PHONY : uninstall

# Rule to build all files generated by this target.
lib/glfw-3.1.2/CMakeFiles/uninstall.dir/build: uninstall

.PHONY : lib/glfw-3.1.2/CMakeFiles/uninstall.dir/build

lib/glfw-3.1.2/CMakeFiles/uninstall.dir/clean:
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2 && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : lib/glfw-3.1.2/CMakeFiles/uninstall.dir/clean

lib/glfw-3.1.2/CMakeFiles/uninstall.dir/depend:
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/willy/Documents/Github/WW1AirPlane-OpenGL /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2 /home/willy/Documents/Github/WW1AirPlane-OpenGL/src /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2 /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw-3.1.2/CMakeFiles/uninstall.dir/depend
