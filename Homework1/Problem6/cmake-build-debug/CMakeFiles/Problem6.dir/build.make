# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/string/dev/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/string/dev/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/string/dev/data-structures/Homework1/Problem6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Problem6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Problem6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Problem6.dir/flags.make

CMakeFiles/Problem6.dir/main.cpp.o: CMakeFiles/Problem6.dir/flags.make
CMakeFiles/Problem6.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Problem6.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Problem6.dir/main.cpp.o -c /home/string/dev/data-structures/Homework1/Problem6/main.cpp

CMakeFiles/Problem6.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Problem6.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/string/dev/data-structures/Homework1/Problem6/main.cpp > CMakeFiles/Problem6.dir/main.cpp.i

CMakeFiles/Problem6.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Problem6.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/string/dev/data-structures/Homework1/Problem6/main.cpp -o CMakeFiles/Problem6.dir/main.cpp.s

CMakeFiles/Problem6.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Problem6.dir/main.cpp.o.requires

CMakeFiles/Problem6.dir/main.cpp.o.provides: CMakeFiles/Problem6.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Problem6.dir/build.make CMakeFiles/Problem6.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Problem6.dir/main.cpp.o.provides

CMakeFiles/Problem6.dir/main.cpp.o.provides.build: CMakeFiles/Problem6.dir/main.cpp.o


CMakeFiles/Problem6.dir/Editor.cpp.o: CMakeFiles/Problem6.dir/flags.make
CMakeFiles/Problem6.dir/Editor.cpp.o: ../Editor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Problem6.dir/Editor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Problem6.dir/Editor.cpp.o -c /home/string/dev/data-structures/Homework1/Problem6/Editor.cpp

CMakeFiles/Problem6.dir/Editor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Problem6.dir/Editor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/string/dev/data-structures/Homework1/Problem6/Editor.cpp > CMakeFiles/Problem6.dir/Editor.cpp.i

CMakeFiles/Problem6.dir/Editor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Problem6.dir/Editor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/string/dev/data-structures/Homework1/Problem6/Editor.cpp -o CMakeFiles/Problem6.dir/Editor.cpp.s

CMakeFiles/Problem6.dir/Editor.cpp.o.requires:

.PHONY : CMakeFiles/Problem6.dir/Editor.cpp.o.requires

CMakeFiles/Problem6.dir/Editor.cpp.o.provides: CMakeFiles/Problem6.dir/Editor.cpp.o.requires
	$(MAKE) -f CMakeFiles/Problem6.dir/build.make CMakeFiles/Problem6.dir/Editor.cpp.o.provides.build
.PHONY : CMakeFiles/Problem6.dir/Editor.cpp.o.provides

CMakeFiles/Problem6.dir/Editor.cpp.o.provides.build: CMakeFiles/Problem6.dir/Editor.cpp.o


# Object files for target Problem6
Problem6_OBJECTS = \
"CMakeFiles/Problem6.dir/main.cpp.o" \
"CMakeFiles/Problem6.dir/Editor.cpp.o"

# External object files for target Problem6
Problem6_EXTERNAL_OBJECTS =

Problem6: CMakeFiles/Problem6.dir/main.cpp.o
Problem6: CMakeFiles/Problem6.dir/Editor.cpp.o
Problem6: CMakeFiles/Problem6.dir/build.make
Problem6: CMakeFiles/Problem6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Problem6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Problem6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Problem6.dir/build: Problem6

.PHONY : CMakeFiles/Problem6.dir/build

CMakeFiles/Problem6.dir/requires: CMakeFiles/Problem6.dir/main.cpp.o.requires
CMakeFiles/Problem6.dir/requires: CMakeFiles/Problem6.dir/Editor.cpp.o.requires

.PHONY : CMakeFiles/Problem6.dir/requires

CMakeFiles/Problem6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Problem6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Problem6.dir/clean

CMakeFiles/Problem6.dir/depend:
	cd /home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/string/dev/data-structures/Homework1/Problem6 /home/string/dev/data-structures/Homework1/Problem6 /home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug /home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug /home/string/dev/data-structures/Homework1/Problem6/cmake-build-debug/CMakeFiles/Problem6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Problem6.dir/depend

