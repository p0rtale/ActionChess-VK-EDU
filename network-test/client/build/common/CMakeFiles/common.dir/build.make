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
include common/CMakeFiles/common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include common/CMakeFiles/common.dir/compiler_depend.make

# Include the progress variables for this target.
include common/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include common/CMakeFiles/common.dir/flags.make

common/CMakeFiles/common.dir/src/message/Message.cpp.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/src/message/Message.cpp.o: ../common/src/message/Message.cpp
common/CMakeFiles/common.dir/src/message/Message.cpp.o: common/CMakeFiles/common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nurik/Рабочий стол/2022/c++/client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object common/CMakeFiles/common.dir/src/message/Message.cpp.o"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT common/CMakeFiles/common.dir/src/message/Message.cpp.o -MF CMakeFiles/common.dir/src/message/Message.cpp.o.d -o CMakeFiles/common.dir/src/message/Message.cpp.o -c "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Message.cpp"

common/CMakeFiles/common.dir/src/message/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/src/message/Message.cpp.i"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Message.cpp" > CMakeFiles/common.dir/src/message/Message.cpp.i

common/CMakeFiles/common.dir/src/message/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/src/message/Message.cpp.s"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Message.cpp" -o CMakeFiles/common.dir/src/message/Message.cpp.s

common/CMakeFiles/common.dir/src/message/Request.cpp.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/src/message/Request.cpp.o: ../common/src/message/Request.cpp
common/CMakeFiles/common.dir/src/message/Request.cpp.o: common/CMakeFiles/common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nurik/Рабочий стол/2022/c++/client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object common/CMakeFiles/common.dir/src/message/Request.cpp.o"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT common/CMakeFiles/common.dir/src/message/Request.cpp.o -MF CMakeFiles/common.dir/src/message/Request.cpp.o.d -o CMakeFiles/common.dir/src/message/Request.cpp.o -c "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Request.cpp"

common/CMakeFiles/common.dir/src/message/Request.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/src/message/Request.cpp.i"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Request.cpp" > CMakeFiles/common.dir/src/message/Request.cpp.i

common/CMakeFiles/common.dir/src/message/Request.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/src/message/Request.cpp.s"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Request.cpp" -o CMakeFiles/common.dir/src/message/Request.cpp.s

common/CMakeFiles/common.dir/src/message/Response.cpp.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/src/message/Response.cpp.o: ../common/src/message/Response.cpp
common/CMakeFiles/common.dir/src/message/Response.cpp.o: common/CMakeFiles/common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nurik/Рабочий стол/2022/c++/client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object common/CMakeFiles/common.dir/src/message/Response.cpp.o"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT common/CMakeFiles/common.dir/src/message/Response.cpp.o -MF CMakeFiles/common.dir/src/message/Response.cpp.o.d -o CMakeFiles/common.dir/src/message/Response.cpp.o -c "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Response.cpp"

common/CMakeFiles/common.dir/src/message/Response.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/src/message/Response.cpp.i"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Response.cpp" > CMakeFiles/common.dir/src/message/Response.cpp.i

common/CMakeFiles/common.dir/src/message/Response.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/src/message/Response.cpp.s"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nurik/Рабочий стол/2022/c++/client/common/src/message/Response.cpp" -o CMakeFiles/common.dir/src/message/Response.cpp.s

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/src/message/Message.cpp.o" \
"CMakeFiles/common.dir/src/message/Request.cpp.o" \
"CMakeFiles/common.dir/src/message/Response.cpp.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

common/libcommon.a: common/CMakeFiles/common.dir/src/message/Message.cpp.o
common/libcommon.a: common/CMakeFiles/common.dir/src/message/Request.cpp.o
common/libcommon.a: common/CMakeFiles/common.dir/src/message/Response.cpp.o
common/libcommon.a: common/CMakeFiles/common.dir/build.make
common/libcommon.a: common/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nurik/Рабочий стол/2022/c++/client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libcommon.a"
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
common/CMakeFiles/common.dir/build: common/libcommon.a
.PHONY : common/CMakeFiles/common.dir/build

common/CMakeFiles/common.dir/clean:
	cd "/home/nurik/Рабочий стол/2022/c++/client/build/common" && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : common/CMakeFiles/common.dir/clean

common/CMakeFiles/common.dir/depend:
	cd "/home/nurik/Рабочий стол/2022/c++/client/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nurik/Рабочий стол/2022/c++/client" "/home/nurik/Рабочий стол/2022/c++/client/common" "/home/nurik/Рабочий стол/2022/c++/client/build" "/home/nurik/Рабочий стол/2022/c++/client/build/common" "/home/nurik/Рабочий стол/2022/c++/client/build/common/CMakeFiles/common.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : common/CMakeFiles/common.dir/depend

