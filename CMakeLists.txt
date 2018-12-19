cmake_minimum_required(VERSION 3.13)
project(raytracing_in_a_weekend)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracing_in_a_weekend main.cpp vec3.h ray.h hitable.h sphere.h hitable_list.h camera.h)