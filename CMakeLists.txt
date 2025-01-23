cmake_minimum_required(VERSION 3.30)
project(path_tracer_2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(path_tracer_2025
        src/main.cpp
        src/stb_image_write.h
        src/stb_image_write.cpp
)
