# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/pablo/linuks2/Ucze_sie/lab2/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/pablo/linuks2/Ucze_sie/lab2/build

# Include any dependencies generated for this target.
include ramie/CMakeFiles/parser.dir/depend.make

# Include the progress variables for this target.
include ramie/CMakeFiles/parser.dir/progress.make

# Include the compile flags for this target's objects.
include ramie/CMakeFiles/parser.dir/flags.make

ramie/CMakeFiles/parser.dir/src/parser.cpp.o: ramie/CMakeFiles/parser.dir/flags.make
ramie/CMakeFiles/parser.dir/src/parser.cpp.o: /media/pablo/linuks2/Ucze_sie/lab2/src/ramie/src/parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/pablo/linuks2/Ucze_sie/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ramie/CMakeFiles/parser.dir/src/parser.cpp.o"
	cd /media/pablo/linuks2/Ucze_sie/lab2/build/ramie && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/parser.dir/src/parser.cpp.o -c /media/pablo/linuks2/Ucze_sie/lab2/src/ramie/src/parser.cpp

ramie/CMakeFiles/parser.dir/src/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/parser.dir/src/parser.cpp.i"
	cd /media/pablo/linuks2/Ucze_sie/lab2/build/ramie && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/pablo/linuks2/Ucze_sie/lab2/src/ramie/src/parser.cpp > CMakeFiles/parser.dir/src/parser.cpp.i

ramie/CMakeFiles/parser.dir/src/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/parser.dir/src/parser.cpp.s"
	cd /media/pablo/linuks2/Ucze_sie/lab2/build/ramie && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/pablo/linuks2/Ucze_sie/lab2/src/ramie/src/parser.cpp -o CMakeFiles/parser.dir/src/parser.cpp.s

ramie/CMakeFiles/parser.dir/src/parser.cpp.o.requires:

.PHONY : ramie/CMakeFiles/parser.dir/src/parser.cpp.o.requires

ramie/CMakeFiles/parser.dir/src/parser.cpp.o.provides: ramie/CMakeFiles/parser.dir/src/parser.cpp.o.requires
	$(MAKE) -f ramie/CMakeFiles/parser.dir/build.make ramie/CMakeFiles/parser.dir/src/parser.cpp.o.provides.build
.PHONY : ramie/CMakeFiles/parser.dir/src/parser.cpp.o.provides

ramie/CMakeFiles/parser.dir/src/parser.cpp.o.provides.build: ramie/CMakeFiles/parser.dir/src/parser.cpp.o


# Object files for target parser
parser_OBJECTS = \
"CMakeFiles/parser.dir/src/parser.cpp.o"

# External object files for target parser
parser_EXTERNAL_OBJECTS =

/media/pablo/linuks2/Ucze_sie/lab2/devel/lib/ramie/parser: ramie/CMakeFiles/parser.dir/src/parser.cpp.o
/media/pablo/linuks2/Ucze_sie/lab2/devel/lib/ramie/parser: ramie/CMakeFiles/parser.dir/build.make
/media/pablo/linuks2/Ucze_sie/lab2/devel/lib/ramie/parser: ramie/CMakeFiles/parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/pablo/linuks2/Ucze_sie/lab2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /media/pablo/linuks2/Ucze_sie/lab2/devel/lib/ramie/parser"
	cd /media/pablo/linuks2/Ucze_sie/lab2/build/ramie && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ramie/CMakeFiles/parser.dir/build: /media/pablo/linuks2/Ucze_sie/lab2/devel/lib/ramie/parser

.PHONY : ramie/CMakeFiles/parser.dir/build

ramie/CMakeFiles/parser.dir/requires: ramie/CMakeFiles/parser.dir/src/parser.cpp.o.requires

.PHONY : ramie/CMakeFiles/parser.dir/requires

ramie/CMakeFiles/parser.dir/clean:
	cd /media/pablo/linuks2/Ucze_sie/lab2/build/ramie && $(CMAKE_COMMAND) -P CMakeFiles/parser.dir/cmake_clean.cmake
.PHONY : ramie/CMakeFiles/parser.dir/clean

ramie/CMakeFiles/parser.dir/depend:
	cd /media/pablo/linuks2/Ucze_sie/lab2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/pablo/linuks2/Ucze_sie/lab2/src /media/pablo/linuks2/Ucze_sie/lab2/src/ramie /media/pablo/linuks2/Ucze_sie/lab2/build /media/pablo/linuks2/Ucze_sie/lab2/build/ramie /media/pablo/linuks2/Ucze_sie/lab2/build/ramie/CMakeFiles/parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ramie/CMakeFiles/parser.dir/depend

