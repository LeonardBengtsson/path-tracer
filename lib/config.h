//
// Created by Leonard on 2025-02-03.
//

#ifndef CONFIG_H
#define CONFIG_H

// OUTPUT QUALITY
inline constexpr size_t OUTPUT_WIDTH = 1920;
inline constexpr size_t OUTPUT_HEIGHT = 1080;
inline constexpr size_t SAMPLE_GRID_SIZE = 1;

// CAMERA SETTINGS
inline constexpr size_t V_FOV_DEGREES = 60;

// PATH TRACING COMPLEXITY
inline constexpr size_t DEPTH_LIMIT = 10;
inline constexpr double MIN_LIGHT_FACTOR = 0.01;
inline constexpr size_t MAX_INTERNAL_REFLECTIONS = 8;

// FEATURES
inline constexpr bool ENABLE_POLARIZATION = false;
inline constexpr bool ENABLE_DISPERSION = false;

// OPTIMIZATION
inline constexpr bool ENABLE_BVH_OPTIMIZATION = true;

// DEBUG
inline constexpr bool DEBUG_ASSERTS = true;
inline constexpr bool DEBUG_SHADE_NORMALS = false;

#endif //CONFIG_H
