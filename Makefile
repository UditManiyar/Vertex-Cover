# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = "/home/udit/Desktop/Sem_6'/pace_challenge"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/udit/Desktop/Sem_6'/pace_challenge"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/udit/Desktop/Sem_6'/pace_challenge/CMakeFiles" "/home/udit/Desktop/Sem_6'/pace_challenge/CMakeFiles/progress.marks"
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/udit/Desktop/Sem_6'/pace_challenge/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named pace

# Build rule for target.
pace: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pace
.PHONY : pace

# fast build rule for target.
pace/fast:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/build
.PHONY : pace/fast

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/main.cpp.s
.PHONY : main.cpp.s

src/bipartite.o: src/bipartite.cpp.o

.PHONY : src/bipartite.o

# target to build an object file
src/bipartite.cpp.o:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/bipartite.cpp.o
.PHONY : src/bipartite.cpp.o

src/bipartite.i: src/bipartite.cpp.i

.PHONY : src/bipartite.i

# target to preprocess a source file
src/bipartite.cpp.i:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/bipartite.cpp.i
.PHONY : src/bipartite.cpp.i

src/bipartite.s: src/bipartite.cpp.s

.PHONY : src/bipartite.s

# target to generate assembly for a file
src/bipartite.cpp.s:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/bipartite.cpp.s
.PHONY : src/bipartite.cpp.s

src/edge.o: src/edge.cpp.o

.PHONY : src/edge.o

# target to build an object file
src/edge.cpp.o:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/edge.cpp.o
.PHONY : src/edge.cpp.o

src/edge.i: src/edge.cpp.i

.PHONY : src/edge.i

# target to preprocess a source file
src/edge.cpp.i:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/edge.cpp.i
.PHONY : src/edge.cpp.i

src/edge.s: src/edge.cpp.s

.PHONY : src/edge.s

# target to generate assembly for a file
src/edge.cpp.s:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/edge.cpp.s
.PHONY : src/edge.cpp.s

src/graph.o: src/graph.cpp.o

.PHONY : src/graph.o

# target to build an object file
src/graph.cpp.o:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/graph.cpp.o
.PHONY : src/graph.cpp.o

src/graph.i: src/graph.cpp.i

.PHONY : src/graph.i

# target to preprocess a source file
src/graph.cpp.i:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/graph.cpp.i
.PHONY : src/graph.cpp.i

src/graph.s: src/graph.cpp.s

.PHONY : src/graph.s

# target to generate assembly for a file
src/graph.cpp.s:
	$(MAKE) -f CMakeFiles/pace.dir/build.make CMakeFiles/pace.dir/src/graph.cpp.s
.PHONY : src/graph.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... pace"
	@echo "... edit_cache"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/bipartite.o"
	@echo "... src/bipartite.i"
	@echo "... src/bipartite.s"
	@echo "... src/edge.o"
	@echo "... src/edge.i"
	@echo "... src/edge.s"
	@echo "... src/graph.o"
	@echo "... src/graph.i"
	@echo "... src/graph.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

