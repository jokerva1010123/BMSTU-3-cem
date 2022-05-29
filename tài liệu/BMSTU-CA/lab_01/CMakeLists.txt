project(ca)

cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    inc/
)

add_executable(lab_01
        src/main.cpp
        inc/Matrix.h
        src/Menu.cpp
        inc/Menu.h
        src/interpolate.cpp
        inc/interpolate.h
        src/MyErrors.cpp
        inc/MyErrors.h
        inc/CppConsoleTable.hpp
        src/Matrix.cpp
        )