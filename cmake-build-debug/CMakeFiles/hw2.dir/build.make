# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\CGProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\CGProject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hw2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw2.dir/flags.make

CMakeFiles/hw2.dir/src/Plane.cpp.obj: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/src/Plane.cpp.obj: CMakeFiles/hw2.dir/includes_CXX.rsp
CMakeFiles/hw2.dir/src/Plane.cpp.obj: ../src/Plane.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw2.dir/src/Plane.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw2.dir\src\Plane.cpp.obj -c C:\CGProject\src\Plane.cpp

CMakeFiles/hw2.dir/src/Plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/src/Plane.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CGProject\src\Plane.cpp > CMakeFiles\hw2.dir\src\Plane.cpp.i

CMakeFiles/hw2.dir/src/Plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/src/Plane.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CGProject\src\Plane.cpp -o CMakeFiles\hw2.dir\src\Plane.cpp.s

CMakeFiles/hw2.dir/src/Sphere.cpp.obj: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/src/Sphere.cpp.obj: CMakeFiles/hw2.dir/includes_CXX.rsp
CMakeFiles/hw2.dir/src/Sphere.cpp.obj: ../src/Sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw2.dir/src/Sphere.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw2.dir\src\Sphere.cpp.obj -c C:\CGProject\src\Sphere.cpp

CMakeFiles/hw2.dir/src/Sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/src/Sphere.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CGProject\src\Sphere.cpp > CMakeFiles\hw2.dir\src\Sphere.cpp.i

CMakeFiles/hw2.dir/src/Sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/src/Sphere.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CGProject\src\Sphere.cpp -o CMakeFiles\hw2.dir\src\Sphere.cpp.s

CMakeFiles/hw2.dir/src/Triangle.cpp.obj: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/src/Triangle.cpp.obj: CMakeFiles/hw2.dir/includes_CXX.rsp
CMakeFiles/hw2.dir/src/Triangle.cpp.obj: ../src/Triangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hw2.dir/src/Triangle.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw2.dir\src\Triangle.cpp.obj -c C:\CGProject\src\Triangle.cpp

CMakeFiles/hw2.dir/src/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/src/Triangle.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CGProject\src\Triangle.cpp > CMakeFiles\hw2.dir\src\Triangle.cpp.i

CMakeFiles/hw2.dir/src/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/src/Triangle.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CGProject\src\Triangle.cpp -o CMakeFiles\hw2.dir\src\Triangle.cpp.s

CMakeFiles/hw2.dir/src/TriangleMesh.cpp.obj: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/src/TriangleMesh.cpp.obj: CMakeFiles/hw2.dir/includes_CXX.rsp
CMakeFiles/hw2.dir/src/TriangleMesh.cpp.obj: ../src/TriangleMesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/hw2.dir/src/TriangleMesh.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw2.dir\src\TriangleMesh.cpp.obj -c C:\CGProject\src\TriangleMesh.cpp

CMakeFiles/hw2.dir/src/TriangleMesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/src/TriangleMesh.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CGProject\src\TriangleMesh.cpp > CMakeFiles\hw2.dir\src\TriangleMesh.cpp.i

CMakeFiles/hw2.dir/src/TriangleMesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/src/TriangleMesh.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CGProject\src\TriangleMesh.cpp -o CMakeFiles\hw2.dir\src\TriangleMesh.cpp.s

CMakeFiles/hw2.dir/src/first_hit.cpp.obj: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/src/first_hit.cpp.obj: CMakeFiles/hw2.dir/includes_CXX.rsp
CMakeFiles/hw2.dir/src/first_hit.cpp.obj: ../src/first_hit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/hw2.dir/src/first_hit.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw2.dir\src\first_hit.cpp.obj -c C:\CGProject\src\first_hit.cpp

CMakeFiles/hw2.dir/src/first_hit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/src/first_hit.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CGProject\src\first_hit.cpp > CMakeFiles\hw2.dir\src\first_hit.cpp.i

CMakeFiles/hw2.dir/src/first_hit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/src/first_hit.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CGProject\src\first_hit.cpp -o CMakeFiles\hw2.dir\src\first_hit.cpp.s

CMakeFiles/hw2.dir/src/viewing_ray.cpp.obj: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/src/viewing_ray.cpp.obj: CMakeFiles/hw2.dir/includes_CXX.rsp
CMakeFiles/hw2.dir/src/viewing_ray.cpp.obj: ../src/viewing_ray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/hw2.dir/src/viewing_ray.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw2.dir\src\viewing_ray.cpp.obj -c C:\CGProject\src\viewing_ray.cpp

CMakeFiles/hw2.dir/src/viewing_ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/src/viewing_ray.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CGProject\src\viewing_ray.cpp > CMakeFiles\hw2.dir\src\viewing_ray.cpp.i

CMakeFiles/hw2.dir/src/viewing_ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/src/viewing_ray.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CGProject\src\viewing_ray.cpp -o CMakeFiles\hw2.dir\src\viewing_ray.cpp.s

CMakeFiles/hw2.dir/src/write_ppm.cpp.obj: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/src/write_ppm.cpp.obj: CMakeFiles/hw2.dir/includes_CXX.rsp
CMakeFiles/hw2.dir/src/write_ppm.cpp.obj: ../src/write_ppm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/hw2.dir/src/write_ppm.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw2.dir\src\write_ppm.cpp.obj -c C:\CGProject\src\write_ppm.cpp

CMakeFiles/hw2.dir/src/write_ppm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw2.dir/src/write_ppm.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\CGProject\src\write_ppm.cpp > CMakeFiles\hw2.dir\src\write_ppm.cpp.i

CMakeFiles/hw2.dir/src/write_ppm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw2.dir/src/write_ppm.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\CGProject\src\write_ppm.cpp -o CMakeFiles\hw2.dir\src\write_ppm.cpp.s

# Object files for target hw2
hw2_OBJECTS = \
"CMakeFiles/hw2.dir/src/Plane.cpp.obj" \
"CMakeFiles/hw2.dir/src/Sphere.cpp.obj" \
"CMakeFiles/hw2.dir/src/Triangle.cpp.obj" \
"CMakeFiles/hw2.dir/src/TriangleMesh.cpp.obj" \
"CMakeFiles/hw2.dir/src/first_hit.cpp.obj" \
"CMakeFiles/hw2.dir/src/viewing_ray.cpp.obj" \
"CMakeFiles/hw2.dir/src/write_ppm.cpp.obj"

# External object files for target hw2
hw2_EXTERNAL_OBJECTS =

libhw2.a: CMakeFiles/hw2.dir/src/Plane.cpp.obj
libhw2.a: CMakeFiles/hw2.dir/src/Sphere.cpp.obj
libhw2.a: CMakeFiles/hw2.dir/src/Triangle.cpp.obj
libhw2.a: CMakeFiles/hw2.dir/src/TriangleMesh.cpp.obj
libhw2.a: CMakeFiles/hw2.dir/src/first_hit.cpp.obj
libhw2.a: CMakeFiles/hw2.dir/src/viewing_ray.cpp.obj
libhw2.a: CMakeFiles/hw2.dir/src/write_ppm.cpp.obj
libhw2.a: CMakeFiles/hw2.dir/build.make
libhw2.a: CMakeFiles/hw2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\CGProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libhw2.a"
	$(CMAKE_COMMAND) -P CMakeFiles\hw2.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hw2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw2.dir/build: libhw2.a

.PHONY : CMakeFiles/hw2.dir/build

CMakeFiles/hw2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hw2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hw2.dir/clean

CMakeFiles/hw2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\CGProject C:\CGProject C:\CGProject\cmake-build-debug C:\CGProject\cmake-build-debug C:\CGProject\cmake-build-debug\CMakeFiles\hw2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw2.dir/depend

