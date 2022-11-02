# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

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

find_library(
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

target_link_libraries(
        utils

        android
        GLESv3
        ${log-lib})

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native_sensor

        utils
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

target_link_libraries(native_triangle

        utils
        ${log-lib}
        )