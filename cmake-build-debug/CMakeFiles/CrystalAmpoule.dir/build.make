# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/bs/DFiles/clion-2017.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/bs/DFiles/clion-2017.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bs/CLionProjects/CrystalAmpoule

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bs/CLionProjects/CrystalAmpoule/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CrystalAmpoule.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CrystalAmpoule.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CrystalAmpoule.dir/flags.make

CMakeFiles/CrystalAmpoule.dir/library.cpp.o: CMakeFiles/CrystalAmpoule.dir/flags.make
CMakeFiles/CrystalAmpoule.dir/library.cpp.o: ../library.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bs/CLionProjects/CrystalAmpoule/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CrystalAmpoule.dir/library.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CrystalAmpoule.dir/library.cpp.o -c /home/bs/CLionProjects/CrystalAmpoule/library.cpp

CMakeFiles/CrystalAmpoule.dir/library.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CrystalAmpoule.dir/library.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bs/CLionProjects/CrystalAmpoule/library.cpp > CMakeFiles/CrystalAmpoule.dir/library.cpp.i

CMakeFiles/CrystalAmpoule.dir/library.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CrystalAmpoule.dir/library.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bs/CLionProjects/CrystalAmpoule/library.cpp -o CMakeFiles/CrystalAmpoule.dir/library.cpp.s

CMakeFiles/CrystalAmpoule.dir/library.cpp.o.requires:

.PHONY : CMakeFiles/CrystalAmpoule.dir/library.cpp.o.requires

CMakeFiles/CrystalAmpoule.dir/library.cpp.o.provides: CMakeFiles/CrystalAmpoule.dir/library.cpp.o.requires
	$(MAKE) -f CMakeFiles/CrystalAmpoule.dir/build.make CMakeFiles/CrystalAmpoule.dir/library.cpp.o.provides.build
.PHONY : CMakeFiles/CrystalAmpoule.dir/library.cpp.o.provides

CMakeFiles/CrystalAmpoule.dir/library.cpp.o.provides.build: CMakeFiles/CrystalAmpoule.dir/library.cpp.o


# Object files for target CrystalAmpoule
CrystalAmpoule_OBJECTS = \
"CMakeFiles/CrystalAmpoule.dir/library.cpp.o"

# External object files for target CrystalAmpoule
CrystalAmpoule_EXTERNAL_OBJECTS =

libCrystalAmpoule.so: CMakeFiles/CrystalAmpoule.dir/library.cpp.o
libCrystalAmpoule.so: CMakeFiles/CrystalAmpoule.dir/build.make
libCrystalAmpoule.so: CMakeFiles/CrystalAmpoule.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bs/CLionProjects/CrystalAmpoule/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libCrystalAmpoule.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CrystalAmpoule.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CrystalAmpoule.dir/build: libCrystalAmpoule.so

.PHONY : CMakeFiles/CrystalAmpoule.dir/build

CMakeFiles/CrystalAmpoule.dir/requires: CMakeFiles/CrystalAmpoule.dir/library.cpp.o.requires

.PHONY : CMakeFiles/CrystalAmpoule.dir/requires

CMakeFiles/CrystalAmpoule.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CrystalAmpoule.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CrystalAmpoule.dir/clean

CMakeFiles/CrystalAmpoule.dir/depend:
	cd /home/bs/CLionProjects/CrystalAmpoule/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bs/CLionProjects/CrystalAmpoule /home/bs/CLionProjects/CrystalAmpoule /home/bs/CLionProjects/CrystalAmpoule/cmake-build-debug /home/bs/CLionProjects/CrystalAmpoule/cmake-build-debug /home/bs/CLionProjects/CrystalAmpoule/cmake-build-debug/CMakeFiles/CrystalAmpoule.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CrystalAmpoule.dir/depend

