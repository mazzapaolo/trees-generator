# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/meraxes/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/meraxes/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/meraxes/trees-generator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/meraxes/trees-generator

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/meraxes/clion/bin/cmake/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/meraxes/clion/bin/cmake/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/meraxes/trees-generator/CMakeFiles /home/meraxes/trees-generator/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/meraxes/trees-generator/CMakeFiles 0
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
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tree_generator

# Build rule for target.
tree_generator: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tree_generator
.PHONY : tree_generator

# fast build rule for target.
tree_generator/fast:
	$(MAKE) -f CMakeFiles/tree_generator.dir/build.make CMakeFiles/tree_generator.dir/build
.PHONY : tree_generator/fast

#=============================================================================
# Target rules for targets named yocto_gl

# Build rule for target.
yocto_gl: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 yocto_gl
.PHONY : yocto_gl

# fast build rule for target.
yocto_gl/fast:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/build
.PHONY : yocto_gl/fast

tree_generator.o: tree_generator.cpp.o

.PHONY : tree_generator.o

# target to build an object file
tree_generator.cpp.o:
	$(MAKE) -f CMakeFiles/tree_generator.dir/build.make CMakeFiles/tree_generator.dir/tree_generator.cpp.o
.PHONY : tree_generator.cpp.o

tree_generator.i: tree_generator.cpp.i

.PHONY : tree_generator.i

# target to preprocess a source file
tree_generator.cpp.i:
	$(MAKE) -f CMakeFiles/tree_generator.dir/build.make CMakeFiles/tree_generator.dir/tree_generator.cpp.i
.PHONY : tree_generator.cpp.i

tree_generator.s: tree_generator.cpp.s

.PHONY : tree_generator.s

# target to generate assembly for a file
tree_generator.cpp.s:
	$(MAKE) -f CMakeFiles/tree_generator.dir/build.make CMakeFiles/tree_generator.dir/tree_generator.cpp.s
.PHONY : tree_generator.cpp.s

yocto-gl/yocto/ext/imgui/imgui.o: yocto-gl/yocto/ext/imgui/imgui.cpp.o

.PHONY : yocto-gl/yocto/ext/imgui/imgui.o

# target to build an object file
yocto-gl/yocto/ext/imgui/imgui.cpp.o:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui.cpp.o
.PHONY : yocto-gl/yocto/ext/imgui/imgui.cpp.o

yocto-gl/yocto/ext/imgui/imgui.i: yocto-gl/yocto/ext/imgui/imgui.cpp.i

.PHONY : yocto-gl/yocto/ext/imgui/imgui.i

# target to preprocess a source file
yocto-gl/yocto/ext/imgui/imgui.cpp.i:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui.cpp.i
.PHONY : yocto-gl/yocto/ext/imgui/imgui.cpp.i

yocto-gl/yocto/ext/imgui/imgui.s: yocto-gl/yocto/ext/imgui/imgui.cpp.s

.PHONY : yocto-gl/yocto/ext/imgui/imgui.s

# target to generate assembly for a file
yocto-gl/yocto/ext/imgui/imgui.cpp.s:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui.cpp.s
.PHONY : yocto-gl/yocto/ext/imgui/imgui.cpp.s

yocto-gl/yocto/ext/imgui/imgui_draw.o: yocto-gl/yocto/ext/imgui/imgui_draw.cpp.o

.PHONY : yocto-gl/yocto/ext/imgui/imgui_draw.o

# target to build an object file
yocto-gl/yocto/ext/imgui/imgui_draw.cpp.o:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_draw.cpp.o
.PHONY : yocto-gl/yocto/ext/imgui/imgui_draw.cpp.o

yocto-gl/yocto/ext/imgui/imgui_draw.i: yocto-gl/yocto/ext/imgui/imgui_draw.cpp.i

.PHONY : yocto-gl/yocto/ext/imgui/imgui_draw.i

# target to preprocess a source file
yocto-gl/yocto/ext/imgui/imgui_draw.cpp.i:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_draw.cpp.i
.PHONY : yocto-gl/yocto/ext/imgui/imgui_draw.cpp.i

yocto-gl/yocto/ext/imgui/imgui_draw.s: yocto-gl/yocto/ext/imgui/imgui_draw.cpp.s

.PHONY : yocto-gl/yocto/ext/imgui/imgui_draw.s

# target to generate assembly for a file
yocto-gl/yocto/ext/imgui/imgui_draw.cpp.s:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_draw.cpp.s
.PHONY : yocto-gl/yocto/ext/imgui/imgui_draw.cpp.s

yocto-gl/yocto/ext/imgui/imgui_extra_fonts.o: yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.o

.PHONY : yocto-gl/yocto/ext/imgui/imgui_extra_fonts.o

# target to build an object file
yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.o:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.o
.PHONY : yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.o

yocto-gl/yocto/ext/imgui/imgui_extra_fonts.i: yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.i

.PHONY : yocto-gl/yocto/ext/imgui/imgui_extra_fonts.i

# target to preprocess a source file
yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.i:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.i
.PHONY : yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.i

yocto-gl/yocto/ext/imgui/imgui_extra_fonts.s: yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.s

.PHONY : yocto-gl/yocto/ext/imgui/imgui_extra_fonts.s

# target to generate assembly for a file
yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.s:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.s
.PHONY : yocto-gl/yocto/ext/imgui/imgui_extra_fonts.cpp.s

yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.o: yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.o

.PHONY : yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.o

# target to build an object file
yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.o:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.o
.PHONY : yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.o

yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.i: yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.i

.PHONY : yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.i

# target to preprocess a source file
yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.i:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.i
.PHONY : yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.i

yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.s: yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.s

.PHONY : yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.s

# target to generate assembly for a file
yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.s:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.s
.PHONY : yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.cpp.s

yocto-gl/yocto/ext/nanosvg.o: yocto-gl/yocto/ext/nanosvg.cpp.o

.PHONY : yocto-gl/yocto/ext/nanosvg.o

# target to build an object file
yocto-gl/yocto/ext/nanosvg.cpp.o:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/nanosvg.cpp.o
.PHONY : yocto-gl/yocto/ext/nanosvg.cpp.o

yocto-gl/yocto/ext/nanosvg.i: yocto-gl/yocto/ext/nanosvg.cpp.i

.PHONY : yocto-gl/yocto/ext/nanosvg.i

# target to preprocess a source file
yocto-gl/yocto/ext/nanosvg.cpp.i:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/nanosvg.cpp.i
.PHONY : yocto-gl/yocto/ext/nanosvg.cpp.i

yocto-gl/yocto/ext/nanosvg.s: yocto-gl/yocto/ext/nanosvg.cpp.s

.PHONY : yocto-gl/yocto/ext/nanosvg.s

# target to generate assembly for a file
yocto-gl/yocto/ext/nanosvg.cpp.s:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/nanosvg.cpp.s
.PHONY : yocto-gl/yocto/ext/nanosvg.cpp.s

yocto-gl/yocto/ext/stb_image.o: yocto-gl/yocto/ext/stb_image.cpp.o

.PHONY : yocto-gl/yocto/ext/stb_image.o

# target to build an object file
yocto-gl/yocto/ext/stb_image.cpp.o:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/stb_image.cpp.o
.PHONY : yocto-gl/yocto/ext/stb_image.cpp.o

yocto-gl/yocto/ext/stb_image.i: yocto-gl/yocto/ext/stb_image.cpp.i

.PHONY : yocto-gl/yocto/ext/stb_image.i

# target to preprocess a source file
yocto-gl/yocto/ext/stb_image.cpp.i:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/stb_image.cpp.i
.PHONY : yocto-gl/yocto/ext/stb_image.cpp.i

yocto-gl/yocto/ext/stb_image.s: yocto-gl/yocto/ext/stb_image.cpp.s

.PHONY : yocto-gl/yocto/ext/stb_image.s

# target to generate assembly for a file
yocto-gl/yocto/ext/stb_image.cpp.s:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/ext/stb_image.cpp.s
.PHONY : yocto-gl/yocto/ext/stb_image.cpp.s

yocto-gl/yocto/yocto_gl.o: yocto-gl/yocto/yocto_gl.cpp.o

.PHONY : yocto-gl/yocto/yocto_gl.o

# target to build an object file
yocto-gl/yocto/yocto_gl.cpp.o:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/yocto_gl.cpp.o
.PHONY : yocto-gl/yocto/yocto_gl.cpp.o

yocto-gl/yocto/yocto_gl.i: yocto-gl/yocto/yocto_gl.cpp.i

.PHONY : yocto-gl/yocto/yocto_gl.i

# target to preprocess a source file
yocto-gl/yocto/yocto_gl.cpp.i:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/yocto_gl.cpp.i
.PHONY : yocto-gl/yocto/yocto_gl.cpp.i

yocto-gl/yocto/yocto_gl.s: yocto-gl/yocto/yocto_gl.cpp.s

.PHONY : yocto-gl/yocto/yocto_gl.s

# target to generate assembly for a file
yocto-gl/yocto/yocto_gl.cpp.s:
	$(MAKE) -f CMakeFiles/yocto_gl.dir/build.make CMakeFiles/yocto_gl.dir/yocto-gl/yocto/yocto_gl.cpp.s
.PHONY : yocto-gl/yocto/yocto_gl.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... tree_generator"
	@echo "... edit_cache"
	@echo "... yocto_gl"
	@echo "... tree_generator.o"
	@echo "... tree_generator.i"
	@echo "... tree_generator.s"
	@echo "... yocto-gl/yocto/ext/imgui/imgui.o"
	@echo "... yocto-gl/yocto/ext/imgui/imgui.i"
	@echo "... yocto-gl/yocto/ext/imgui/imgui.s"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_draw.o"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_draw.i"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_draw.s"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_extra_fonts.o"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_extra_fonts.i"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_extra_fonts.s"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.o"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.i"
	@echo "... yocto-gl/yocto/ext/imgui/imgui_impl_glfw_gl3.s"
	@echo "... yocto-gl/yocto/ext/nanosvg.o"
	@echo "... yocto-gl/yocto/ext/nanosvg.i"
	@echo "... yocto-gl/yocto/ext/nanosvg.s"
	@echo "... yocto-gl/yocto/ext/stb_image.o"
	@echo "... yocto-gl/yocto/ext/stb_image.i"
	@echo "... yocto-gl/yocto/ext/stb_image.s"
	@echo "... yocto-gl/yocto/yocto_gl.o"
	@echo "... yocto-gl/yocto/yocto_gl.i"
	@echo "... yocto-gl/yocto/yocto_gl.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

