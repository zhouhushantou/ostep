# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/126/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/126/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hushantou/ostep-projects/initial-utilities/wcat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/wcat.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wcat.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wcat.dir/flags.make

CMakeFiles/wcat.dir/wcat.c.o: CMakeFiles/wcat.dir/flags.make
CMakeFiles/wcat.dir/wcat.c.o: ../wcat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/wcat.dir/wcat.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wcat.dir/wcat.c.o   -c /home/hushantou/ostep-projects/initial-utilities/wcat/wcat.c

CMakeFiles/wcat.dir/wcat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wcat.dir/wcat.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hushantou/ostep-projects/initial-utilities/wcat/wcat.c > CMakeFiles/wcat.dir/wcat.c.i

CMakeFiles/wcat.dir/wcat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wcat.dir/wcat.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hushantou/ostep-projects/initial-utilities/wcat/wcat.c -o CMakeFiles/wcat.dir/wcat.c.s

CMakeFiles/wcat.dir/wgrep.c.o: CMakeFiles/wcat.dir/flags.make
CMakeFiles/wcat.dir/wgrep.c.o: ../wgrep.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/wcat.dir/wgrep.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wcat.dir/wgrep.c.o   -c /home/hushantou/ostep-projects/initial-utilities/wcat/wgrep.c

CMakeFiles/wcat.dir/wgrep.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wcat.dir/wgrep.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hushantou/ostep-projects/initial-utilities/wcat/wgrep.c > CMakeFiles/wcat.dir/wgrep.c.i

CMakeFiles/wcat.dir/wgrep.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wcat.dir/wgrep.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hushantou/ostep-projects/initial-utilities/wcat/wgrep.c -o CMakeFiles/wcat.dir/wgrep.c.s

# Object files for target wcat
wcat_OBJECTS = \
"CMakeFiles/wcat.dir/wcat.c.o" \
"CMakeFiles/wcat.dir/wgrep.c.o"

# External object files for target wcat
wcat_EXTERNAL_OBJECTS =

wcat: CMakeFiles/wcat.dir/wcat.c.o
wcat: CMakeFiles/wcat.dir/wgrep.c.o
wcat: CMakeFiles/wcat.dir/build.make
wcat: CMakeFiles/wcat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable wcat"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wcat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wcat.dir/build: wcat

.PHONY : CMakeFiles/wcat.dir/build

CMakeFiles/wcat.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wcat.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wcat.dir/clean

CMakeFiles/wcat.dir/depend:
	cd /home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hushantou/ostep-projects/initial-utilities/wcat /home/hushantou/ostep-projects/initial-utilities/wcat /home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug /home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug /home/hushantou/ostep-projects/initial-utilities/wcat/cmake-build-debug/CMakeFiles/wcat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wcat.dir/depend

