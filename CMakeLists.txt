cmake_minimum_required(VERSION 3.15)
project(CGProject)
set(CMAKE_CXX_STANDARD 14)

add_executable(CGProject main.cpp src/headers/Shape.h src/headers/Sphere.h src/headers/Plane.h src/headers/LightSource.h src/headers/Camera.h src/headers/Ray.h src/headers/film/Pixel.h src/headers/film/FrameBuffer.h src/headers/film/RGB.h)
