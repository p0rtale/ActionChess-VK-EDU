# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/nurik/Рабочий стол/2022/c++/client"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/nurik/Рабочий стол/2022/c++/client/build"

# Include any dependencies generated for this target.
include server/CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include server/CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include server/CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include server/CMakeFiles/main.dir/flags.make

server/CMakeFiles/main.dir/main.cpp.o: server/CMakeFiles/main.dir/flags.make
server/CMakeFiles/main.dir/main.cpp.o: ../server/main.cpp
server/CMakeFiles/main.dir/main.cpp.o: server/CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nurik/Рабочий стол/2022/c++/client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/CMakeFiles/main.dir/main.cpp.o"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/server" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c "/home/nurik/Рабочий стол/2022/c++/client/server/main.cpp"

server/CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/server" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nurik/Рабочий стол/2022/c++/client/server/main.cpp" > CMakeFiles/main.dir/main.cpp.i

server/CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/server" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nurik/Рабочий стол/2022/c++/client/server/main.cpp" -o CMakeFiles/main.dir/main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

server/main: server/CMakeFiles/main.dir/main.cpp.o
server/main: server/CMakeFiles/main.dir/build.make
server/main: common/libcommon.a
server/main: /usr/lib/libboost_system.so.1.78.0
server/main: /usr/lib/x86_64-linux-gnu/libssl.so
server/main: /usr/lib/x86_64-linux-gnu/libcrypto.so
server/main: server/CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nurik/Рабочий стол/2022/c++/client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/server" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/CMakeFiles/main.dir/build: server/main
.PHONY : server/CMakeFiles/main.dir/build

server/CMakeFiles/main.dir/clean:
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/server" && $(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : server/CMakeFiles/main.dir/clean

server/CMakeFiles/main.dir/depend:
	cd "/home/nurik/Рабочий стол/2022/c++/client/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nurik/Рабочий стол/2022/c++/client" "/home/nurik/Рабочий стол/2022/c++/client/server" "/home/nurik/Рабочий стол/2022/c++/client/build" "/home/nurik/Рабочий стол/2022/c++/client/build/server" "/home/nurik/Рабочий стол/2022/c++/client/build/server/CMakeFiles/main.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : server/CMakeFiles/main.dir/depend

