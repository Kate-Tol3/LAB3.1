# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.2.0.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.2.0.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Docs\Documents\GitHub\LAB3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Docs\Documents\GitHub\LAB3.1\cmake-build-debug

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	"C:\Program Files\JetBrains\CLion 2024.2.0.1\bin\cmake\win\x64\bin\cmake.exe" -E echo "No interactive CMake dialog available."
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\JetBrains\CLion 2024.2.0.1\bin\cmake\win\x64\bin\cmake.exe" --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Docs\Documents\GitHub\LAB3.1\cmake-build-debug\CMakeFiles D:\Docs\Documents\GitHub\LAB3.1\cmake-build-debug\\CMakeFiles\progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start D:\Docs\Documents\GitHub\LAB3.1\cmake-build-debug\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named 3_1LAB

# Build rule for target.
3_1LAB: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 3_1LAB
.PHONY : 3_1LAB

# fast build rule for target.
3_1LAB/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/build
.PHONY : 3_1LAB/fast

Atomic_Pointers/ShrdPtrAtomicTest.obj: Atomic_Pointers/ShrdPtrAtomicTest.cpp.obj
.PHONY : Atomic_Pointers/ShrdPtrAtomicTest.obj

# target to build an object file
Atomic_Pointers/ShrdPtrAtomicTest.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Atomic_Pointers/ShrdPtrAtomicTest.cpp.obj
.PHONY : Atomic_Pointers/ShrdPtrAtomicTest.cpp.obj

Atomic_Pointers/ShrdPtrAtomicTest.i: Atomic_Pointers/ShrdPtrAtomicTest.cpp.i
.PHONY : Atomic_Pointers/ShrdPtrAtomicTest.i

# target to preprocess a source file
Atomic_Pointers/ShrdPtrAtomicTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Atomic_Pointers/ShrdPtrAtomicTest.cpp.i
.PHONY : Atomic_Pointers/ShrdPtrAtomicTest.cpp.i

Atomic_Pointers/ShrdPtrAtomicTest.s: Atomic_Pointers/ShrdPtrAtomicTest.cpp.s
.PHONY : Atomic_Pointers/ShrdPtrAtomicTest.s

# target to generate assembly for a file
Atomic_Pointers/ShrdPtrAtomicTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Atomic_Pointers/ShrdPtrAtomicTest.cpp.s
.PHONY : Atomic_Pointers/ShrdPtrAtomicTest.cpp.s

Atomic_Pointers/WeakPtrAtomicTest.obj: Atomic_Pointers/WeakPtrAtomicTest.cpp.obj
.PHONY : Atomic_Pointers/WeakPtrAtomicTest.obj

# target to build an object file
Atomic_Pointers/WeakPtrAtomicTest.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Atomic_Pointers/WeakPtrAtomicTest.cpp.obj
.PHONY : Atomic_Pointers/WeakPtrAtomicTest.cpp.obj

Atomic_Pointers/WeakPtrAtomicTest.i: Atomic_Pointers/WeakPtrAtomicTest.cpp.i
.PHONY : Atomic_Pointers/WeakPtrAtomicTest.i

# target to preprocess a source file
Atomic_Pointers/WeakPtrAtomicTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Atomic_Pointers/WeakPtrAtomicTest.cpp.i
.PHONY : Atomic_Pointers/WeakPtrAtomicTest.cpp.i

Atomic_Pointers/WeakPtrAtomicTest.s: Atomic_Pointers/WeakPtrAtomicTest.cpp.s
.PHONY : Atomic_Pointers/WeakPtrAtomicTest.s

# target to generate assembly for a file
Atomic_Pointers/WeakPtrAtomicTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Atomic_Pointers/WeakPtrAtomicTest.cpp.s
.PHONY : Atomic_Pointers/WeakPtrAtomicTest.cpp.s

LinkedListTest.obj: LinkedListTest.cpp.obj
.PHONY : LinkedListTest.obj

# target to build an object file
LinkedListTest.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/LinkedListTest.cpp.obj
.PHONY : LinkedListTest.cpp.obj

LinkedListTest.i: LinkedListTest.cpp.i
.PHONY : LinkedListTest.i

# target to preprocess a source file
LinkedListTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/LinkedListTest.cpp.i
.PHONY : LinkedListTest.cpp.i

LinkedListTest.s: LinkedListTest.cpp.s
.PHONY : LinkedListTest.s

# target to generate assembly for a file
LinkedListTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/LinkedListTest.cpp.s
.PHONY : LinkedListTest.cpp.s

LoadTest.obj: LoadTest.cpp.obj
.PHONY : LoadTest.obj

# target to build an object file
LoadTest.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/LoadTest.cpp.obj
.PHONY : LoadTest.cpp.obj

LoadTest.i: LoadTest.cpp.i
.PHONY : LoadTest.i

# target to preprocess a source file
LoadTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/LoadTest.cpp.i
.PHONY : LoadTest.cpp.i

LoadTest.s: LoadTest.cpp.s
.PHONY : LoadTest.s

# target to generate assembly for a file
LoadTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/LoadTest.cpp.s
.PHONY : LoadTest.cpp.s

ShrdPtrTest.obj: ShrdPtrTest.cpp.obj
.PHONY : ShrdPtrTest.obj

# target to build an object file
ShrdPtrTest.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/ShrdPtrTest.cpp.obj
.PHONY : ShrdPtrTest.cpp.obj

ShrdPtrTest.i: ShrdPtrTest.cpp.i
.PHONY : ShrdPtrTest.i

# target to preprocess a source file
ShrdPtrTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/ShrdPtrTest.cpp.i
.PHONY : ShrdPtrTest.cpp.i

ShrdPtrTest.s: ShrdPtrTest.cpp.s
.PHONY : ShrdPtrTest.s

# target to generate assembly for a file
ShrdPtrTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/ShrdPtrTest.cpp.s
.PHONY : ShrdPtrTest.cpp.s

Test.obj: Test.cpp.obj
.PHONY : Test.obj

# target to build an object file
Test.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Test.cpp.obj
.PHONY : Test.cpp.obj

Test.i: Test.cpp.i
.PHONY : Test.i

# target to preprocess a source file
Test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Test.cpp.i
.PHONY : Test.cpp.i

Test.s: Test.cpp.s
.PHONY : Test.s

# target to generate assembly for a file
Test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/Test.cpp.s
.PHONY : Test.cpp.s

UnqPtrTest.obj: UnqPtrTest.cpp.obj
.PHONY : UnqPtrTest.obj

# target to build an object file
UnqPtrTest.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/UnqPtrTest.cpp.obj
.PHONY : UnqPtrTest.cpp.obj

UnqPtrTest.i: UnqPtrTest.cpp.i
.PHONY : UnqPtrTest.i

# target to preprocess a source file
UnqPtrTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/UnqPtrTest.cpp.i
.PHONY : UnqPtrTest.cpp.i

UnqPtrTest.s: UnqPtrTest.cpp.s
.PHONY : UnqPtrTest.s

# target to generate assembly for a file
UnqPtrTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/UnqPtrTest.cpp.s
.PHONY : UnqPtrTest.cpp.s

WeakPtrTest.obj: WeakPtrTest.cpp.obj
.PHONY : WeakPtrTest.obj

# target to build an object file
WeakPtrTest.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/WeakPtrTest.cpp.obj
.PHONY : WeakPtrTest.cpp.obj

WeakPtrTest.i: WeakPtrTest.cpp.i
.PHONY : WeakPtrTest.i

# target to preprocess a source file
WeakPtrTest.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/WeakPtrTest.cpp.i
.PHONY : WeakPtrTest.cpp.i

WeakPtrTest.s: WeakPtrTest.cpp.s
.PHONY : WeakPtrTest.s

# target to generate assembly for a file
WeakPtrTest.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/WeakPtrTest.cpp.s
.PHONY : WeakPtrTest.cpp.s

main.obj: main.cpp.obj
.PHONY : main.obj

# target to build an object file
main.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/main.cpp.obj
.PHONY : main.cpp.obj

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\3_1LAB.dir\build.make CMakeFiles/3_1LAB.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... rebuild_cache
	@echo ... 3_1LAB
	@echo ... Atomic_Pointers/ShrdPtrAtomicTest.obj
	@echo ... Atomic_Pointers/ShrdPtrAtomicTest.i
	@echo ... Atomic_Pointers/ShrdPtrAtomicTest.s
	@echo ... Atomic_Pointers/WeakPtrAtomicTest.obj
	@echo ... Atomic_Pointers/WeakPtrAtomicTest.i
	@echo ... Atomic_Pointers/WeakPtrAtomicTest.s
	@echo ... LinkedListTest.obj
	@echo ... LinkedListTest.i
	@echo ... LinkedListTest.s
	@echo ... LoadTest.obj
	@echo ... LoadTest.i
	@echo ... LoadTest.s
	@echo ... ShrdPtrTest.obj
	@echo ... ShrdPtrTest.i
	@echo ... ShrdPtrTest.s
	@echo ... Test.obj
	@echo ... Test.i
	@echo ... Test.s
	@echo ... UnqPtrTest.obj
	@echo ... UnqPtrTest.i
	@echo ... UnqPtrTest.s
	@echo ... WeakPtrTest.obj
	@echo ... WeakPtrTest.i
	@echo ... WeakPtrTest.s
	@echo ... main.obj
	@echo ... main.i
	@echo ... main.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

