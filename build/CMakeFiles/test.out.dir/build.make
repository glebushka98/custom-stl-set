# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/glebone/Set

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/glebone/Set/build

# Include any dependencies generated for this target.
include CMakeFiles/test.out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.out.dir/flags.make

CMakeFiles/test.out.dir/test.cpp.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/test.cpp.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/glebone/Set/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.out.dir/test.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.out.dir/test.cpp.o -c /Users/glebone/Set/test.cpp

CMakeFiles/test.out.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.out.dir/test.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/glebone/Set/test.cpp > CMakeFiles/test.out.dir/test.cpp.i

CMakeFiles/test.out.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.out.dir/test.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/glebone/Set/test.cpp -o CMakeFiles/test.out.dir/test.cpp.s

CMakeFiles/test.out.dir/test.cpp.o.requires:

.PHONY : CMakeFiles/test.out.dir/test.cpp.o.requires

CMakeFiles/test.out.dir/test.cpp.o.provides: CMakeFiles/test.out.dir/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/test.cpp.o.provides.build
.PHONY : CMakeFiles/test.out.dir/test.cpp.o.provides

CMakeFiles/test.out.dir/test.cpp.o.provides.build: CMakeFiles/test.out.dir/test.cpp.o


CMakeFiles/test.out.dir/commons/catch_main.cpp.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/commons/catch_main.cpp.o: ../commons/catch_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/glebone/Set/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.out.dir/commons/catch_main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.out.dir/commons/catch_main.cpp.o -c /Users/glebone/Set/commons/catch_main.cpp

CMakeFiles/test.out.dir/commons/catch_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.out.dir/commons/catch_main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/glebone/Set/commons/catch_main.cpp > CMakeFiles/test.out.dir/commons/catch_main.cpp.i

CMakeFiles/test.out.dir/commons/catch_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.out.dir/commons/catch_main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/glebone/Set/commons/catch_main.cpp -o CMakeFiles/test.out.dir/commons/catch_main.cpp.s

CMakeFiles/test.out.dir/commons/catch_main.cpp.o.requires:

.PHONY : CMakeFiles/test.out.dir/commons/catch_main.cpp.o.requires

CMakeFiles/test.out.dir/commons/catch_main.cpp.o.provides: CMakeFiles/test.out.dir/commons/catch_main.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.out.dir/build.make CMakeFiles/test.out.dir/commons/catch_main.cpp.o.provides.build
.PHONY : CMakeFiles/test.out.dir/commons/catch_main.cpp.o.provides

CMakeFiles/test.out.dir/commons/catch_main.cpp.o.provides.build: CMakeFiles/test.out.dir/commons/catch_main.cpp.o


# Object files for target test.out
test_out_OBJECTS = \
"CMakeFiles/test.out.dir/test.cpp.o" \
"CMakeFiles/test.out.dir/commons/catch_main.cpp.o"

# External object files for target test.out
test_out_EXTERNAL_OBJECTS =

test.out: CMakeFiles/test.out.dir/test.cpp.o
test.out: CMakeFiles/test.out.dir/commons/catch_main.cpp.o
test.out: CMakeFiles/test.out.dir/build.make
test.out: CMakeFiles/test.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/glebone/Set/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.out.dir/build: test.out

.PHONY : CMakeFiles/test.out.dir/build

CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/test.cpp.o.requires
CMakeFiles/test.out.dir/requires: CMakeFiles/test.out.dir/commons/catch_main.cpp.o.requires

.PHONY : CMakeFiles/test.out.dir/requires

CMakeFiles/test.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.out.dir/clean

CMakeFiles/test.out.dir/depend:
	cd /Users/glebone/Set/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/glebone/Set /Users/glebone/Set /Users/glebone/Set/build /Users/glebone/Set/build /Users/glebone/Set/build/CMakeFiles/test.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.out.dir/depend
