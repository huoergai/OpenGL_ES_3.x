# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Declares and names the project.
project("gles")

add_library(utils

        SHARED

        util.h
        util.cpp
        gles_util.h
        gles_util.cpp)

add_library(native_sensor

        SHARED

        native_sensor.cpp
        sensor_graph.h
        sensor_graph.cpp)

add_library(native_triangle

        SHARED

        native_triangle.cpp
        simple_triangle.h
        simple_triangle.cpp)

add_library(native_texture SHARED native_texture.cpp texture_map.h texture_map.cpp)

find_library(log-lib log)

target_link_libraries(
        utils

        android
        GLESv3
        ${log-lib})

target_link_libraries(native_sensor utils)

target_link_libraries(native_triangle utils)

target_link_libraries(native_texture utils)
