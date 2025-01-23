cmake_minimum_required(VERSION 3.30)
project(path_tracer_2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(path_tracer_2025
        src/main.cpp
        src/stb_image_write.h
        src/stb_image_write.cpp
        lib/math/Vec3.cpp
        lib/math/Vec3.h
        lib/math/Vec2.cpp
        lib/math/Vec2.h
        lib/math/Ray.cpp
        lib/math/Ray.h
        lib/math/Matrix3x3.cpp
        lib/math/Matrix3x3.h
        lib/math/math_util.cpp
        lib/math/math_util.h
        lib/math/Matrix4x4.cpp
        lib/math/Matrix4x4.h
)
