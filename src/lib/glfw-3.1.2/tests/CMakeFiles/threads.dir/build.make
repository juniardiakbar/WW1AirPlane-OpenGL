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

# Include any dependencies generated for this target.
include lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/depend.make

# Include the progress variables for this target.
include lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/progress.make

# Include the compile flags for this target's objects.
include lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/flags.make

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o: lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/flags.make
lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o: ../lib/glfw-3.1.2/tests/threads.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/willy/Documents/Github/WW1AirPlane-OpenGL/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o"
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/threads.dir/threads.c.o   -c /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2/tests/threads.c

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/threads.c.i"
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2/tests/threads.c > CMakeFiles/threads.dir/threads.c.i

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/threads.c.s"
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2/tests/threads.c -o CMakeFiles/threads.dir/threads.c.s

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/flags.make
lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o: ../lib/glfw-3.1.2/deps/tinycthread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/willy/Documents/Github/WW1AirPlane-OpenGL/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o"
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/threads.dir/__/deps/tinycthread.c.o   -c /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2/deps/tinycthread.c

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/threads.dir/__/deps/tinycthread.c.i"
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2/deps/tinycthread.c > CMakeFiles/threads.dir/__/deps/tinycthread.c.i

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/threads.dir/__/deps/tinycthread.c.s"
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2/deps/tinycthread.c -o CMakeFiles/threads.dir/__/deps/tinycthread.c.s

# Object files for target threads
threads_OBJECTS = \
"CMakeFiles/threads.dir/threads.c.o" \
"CMakeFiles/threads.dir/__/deps/tinycthread.c.o"

# External object files for target threads
threads_EXTERNAL_OBJECTS =

lib/glfw-3.1.2/tests/threads: lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/threads.c.o
lib/glfw-3.1.2/tests/threads: lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/__/deps/tinycthread.c.o
lib/glfw-3.1.2/tests/threads: lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/build.make
lib/glfw-3.1.2/tests/threads: lib/glfw-3.1.2/src/libglfw3.a
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/librt.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libm.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libX11.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXrandr.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXinerama.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXi.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXcursor.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libGL.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/librt.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libm.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libX11.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXrandr.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXinerama.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXi.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libXcursor.so
lib/glfw-3.1.2/tests/threads: /usr/lib/x86_64-linux-gnu/libGL.so
lib/glfw-3.1.2/tests/threads: lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/willy/Documents/Github/WW1AirPlane-OpenGL/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable threads"
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/build: lib/glfw-3.1.2/tests/threads

.PHONY : lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/build

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/clean:
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/threads.dir/cmake_clean.cmake
.PHONY : lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/clean

lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/depend:
	cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/willy/Documents/Github/WW1AirPlane-OpenGL /home/willy/Documents/Github/WW1AirPlane-OpenGL/lib/glfw-3.1.2/tests /home/willy/Documents/Github/WW1AirPlane-OpenGL/src /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw-3.1.2/tests/CMakeFiles/threads.dir/depend

