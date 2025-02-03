cmake_minimum_required(VERSION 3.30)
project(path_tracer_2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(path_tracer_2025
        src/main.cpp
        lib/stb_image_write.h
        lib/stb_image_write.cpp
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
        lib/material/Material.cpp
        lib/material/Material.h
        lib/scene/Scene.cpp
        lib/scene/Scene.h
        lib/render/LightSpectrum.cpp
        lib/render/LightSpectrum.h
        lib/path_tracing/RayStack.cpp
        lib/path_tracing/RayStack.h
        lib/scene/SceneObject.cpp
        lib/scene/SceneObject.h
        lib/math/Box.cpp
        lib/math/Box.h
        lib/render/color_util.cpp
        lib/render/color_util.h
        lib/path_tracing/LightTransformation.cpp
        lib/path_tracing/LightTransformation.h
        lib/scene/SphereObject.cpp
        lib/scene/SphereObject.h
        lib/render/RenderBuffer.cpp
        lib/render/RenderBuffer.h
        src/scenes.h
        src/scenes.cpp
        lib/scene/BoxObject.cpp
        lib/scene/BoxObject.h
        lib/config.h
)
