# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/build

# Include any dependencies generated for this target.
include CMakeFiles/pp2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pp2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pp2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pp2.dir/flags.make

CMakeFiles/pp2.dir/src/main.cc.o: CMakeFiles/pp2.dir/flags.make
CMakeFiles/pp2.dir/src/main.cc.o: /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/src/main.cc
CMakeFiles/pp2.dir/src/main.cc.o: CMakeFiles/pp2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pp2.dir/src/main.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pp2.dir/src/main.cc.o -MF CMakeFiles/pp2.dir/src/main.cc.o.d -o CMakeFiles/pp2.dir/src/main.cc.o -c /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/src/main.cc

CMakeFiles/pp2.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pp2.dir/src/main.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/src/main.cc > CMakeFiles/pp2.dir/src/main.cc.i

CMakeFiles/pp2.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pp2.dir/src/main.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/src/main.cc -o CMakeFiles/pp2.dir/src/main.cc.s

# Object files for target pp2
pp2_OBJECTS = \
"CMakeFiles/pp2.dir/src/main.cc.o"

# External object files for target pp2
pp2_EXTERNAL_OBJECTS =

pp2: CMakeFiles/pp2.dir/src/main.cc.o
pp2: CMakeFiles/pp2.dir/build.make
pp2: CMakeFiles/pp2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pp2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pp2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pp2.dir/build: pp2
.PHONY : CMakeFiles/pp2.dir/build

CMakeFiles/pp2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pp2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pp2.dir/clean

CMakeFiles/pp2.dir/depend:
	cd /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/build /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/build /Users/andre_portella/Desktop/PG/PP2_PG/PP2-PG/build/CMakeFiles/pp2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pp2.dir/depend

