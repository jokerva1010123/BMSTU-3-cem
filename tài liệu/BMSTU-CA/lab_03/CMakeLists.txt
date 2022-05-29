project(ca)

cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 99)

include_directories(inc/)

add_executable(lab_03_c
        src/interp.c
        inc/io.h
        src/io.c
        src/main.c
        )

add_executable(lab_03
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