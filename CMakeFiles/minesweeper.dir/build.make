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
CMAKE_COMMAND = /home/dasker/anaconda3/lib/python3.9/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/dasker/anaconda3/lib/python3.9/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dasker/source/repos/curses/minesweeper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dasker/source/repos/curses/minesweeper

# Include any dependencies generated for this target.
include CMakeFiles/minesweeper.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/minesweeper.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/minesweeper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minesweeper.dir/flags.make

CMakeFiles/minesweeper.dir/main.c.o: CMakeFiles/minesweeper.dir/flags.make
CMakeFiles/minesweeper.dir/main.c.o: main.c
CMakeFiles/minesweeper.dir/main.c.o: CMakeFiles/minesweeper.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dasker/source/repos/curses/minesweeper/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/minesweeper.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minesweeper.dir/main.c.o -MF CMakeFiles/minesweeper.dir/main.c.o.d -o CMakeFiles/minesweeper.dir/main.c.o -c /home/dasker/source/repos/curses/minesweeper/main.c

CMakeFiles/minesweeper.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minesweeper.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dasker/source/repos/curses/minesweeper/main.c > CMakeFiles/minesweeper.dir/main.c.i

CMakeFiles/minesweeper.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minesweeper.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dasker/source/repos/curses/minesweeper/main.c -o CMakeFiles/minesweeper.dir/main.c.s

CMakeFiles/minesweeper.dir/game.c.o: CMakeFiles/minesweeper.dir/flags.make
CMakeFiles/minesweeper.dir/game.c.o: game.c
CMakeFiles/minesweeper.dir/game.c.o: CMakeFiles/minesweeper.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dasker/source/repos/curses/minesweeper/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/minesweeper.dir/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minesweeper.dir/game.c.o -MF CMakeFiles/minesweeper.dir/game.c.o.d -o CMakeFiles/minesweeper.dir/game.c.o -c /home/dasker/source/repos/curses/minesweeper/game.c

CMakeFiles/minesweeper.dir/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minesweeper.dir/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dasker/source/repos/curses/minesweeper/game.c > CMakeFiles/minesweeper.dir/game.c.i

CMakeFiles/minesweeper.dir/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minesweeper.dir/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dasker/source/repos/curses/minesweeper/game.c -o CMakeFiles/minesweeper.dir/game.c.s

# Object files for target minesweeper
minesweeper_OBJECTS = \
"CMakeFiles/minesweeper.dir/main.c.o" \
"CMakeFiles/minesweeper.dir/game.c.o"

# External object files for target minesweeper
minesweeper_EXTERNAL_OBJECTS =

minesweeper: CMakeFiles/minesweeper.dir/main.c.o
minesweeper: CMakeFiles/minesweeper.dir/game.c.o
minesweeper: CMakeFiles/minesweeper.dir/build.make
minesweeper: /usr/lib/x86_64-linux-gnu/libncurses.so
minesweeper: /usr/lib/x86_64-linux-gnu/libform.so
minesweeper: CMakeFiles/minesweeper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dasker/source/repos/curses/minesweeper/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable minesweeper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minesweeper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minesweeper.dir/build: minesweeper
.PHONY : CMakeFiles/minesweeper.dir/build

CMakeFiles/minesweeper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minesweeper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minesweeper.dir/clean

CMakeFiles/minesweeper.dir/depend:
	cd /home/dasker/source/repos/curses/minesweeper && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dasker/source/repos/curses/minesweeper /home/dasker/source/repos/curses/minesweeper /home/dasker/source/repos/curses/minesweeper /home/dasker/source/repos/curses/minesweeper /home/dasker/source/repos/curses/minesweeper/CMakeFiles/minesweeper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minesweeper.dir/depend

