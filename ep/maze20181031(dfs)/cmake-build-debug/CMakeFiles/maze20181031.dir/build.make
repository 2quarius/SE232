# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "/Applications/CLion 2018.3 EAP.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Applications/CLion 2018.3 EAP.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liujia/CLionProjects/maze20181031

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liujia/CLionProjects/maze20181031/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/maze20181031.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maze20181031.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maze20181031.dir/flags.make

CMakeFiles/maze20181031.dir/main.cpp.o: CMakeFiles/maze20181031.dir/flags.make
CMakeFiles/maze20181031.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liujia/CLionProjects/maze20181031/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/maze20181031.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maze20181031.dir/main.cpp.o -c /Users/liujia/CLionProjects/maze20181031/main.cpp

CMakeFiles/maze20181031.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maze20181031.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liujia/CLionProjects/maze20181031/main.cpp > CMakeFiles/maze20181031.dir/main.cpp.i

CMakeFiles/maze20181031.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maze20181031.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liujia/CLionProjects/maze20181031/main.cpp -o CMakeFiles/maze20181031.dir/main.cpp.s

# Object files for target maze20181031
maze20181031_OBJECTS = \
"CMakeFiles/maze20181031.dir/main.cpp.o"

# External object files for target maze20181031
maze20181031_EXTERNAL_OBJECTS =

maze20181031: CMakeFiles/maze20181031.dir/main.cpp.o
maze20181031: CMakeFiles/maze20181031.dir/build.make
maze20181031: CMakeFiles/maze20181031.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liujia/CLionProjects/maze20181031/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable maze20181031"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maze20181031.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maze20181031.dir/build: maze20181031

.PHONY : CMakeFiles/maze20181031.dir/build

CMakeFiles/maze20181031.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maze20181031.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maze20181031.dir/clean

CMakeFiles/maze20181031.dir/depend:
	cd /Users/liujia/CLionProjects/maze20181031/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liujia/CLionProjects/maze20181031 /Users/liujia/CLionProjects/maze20181031 /Users/liujia/CLionProjects/maze20181031/cmake-build-debug /Users/liujia/CLionProjects/maze20181031/cmake-build-debug /Users/liujia/CLionProjects/maze20181031/cmake-build-debug/CMakeFiles/maze20181031.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/maze20181031.dir/depend

