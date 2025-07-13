//
// Created by Leonard on 2025-02-03.
//

#ifndef CONFIG_H
#define CONFIG_H

//////// OUTPUT QUALITY ////////

inline constexpr size_t OUTPUT_WIDTH = 1920;

inline constexpr size_t OUTPUT_HEIGHT = 1080;

// the square of this number of samples are taken per pixel
inline constexpr size_t SAMPLE_GRID_SIZE = 1;



//////// CAMERA SETTINGS ////////

// vertical field of view
inline constexpr size_t V_FOV_DEGREES = 60;



//////// PATH TRACING COMPLEXITY ////////

// limits the recursion depth of a single light ray
inline constexpr size_t DEPTH_LIMIT = 10;

// discard light rays that contribute less than this factor to a single sample
inline constexpr double MIN_LIGHT_FACTOR = 0.01;

// limits the depth of reflections that are evaluated within an object
inline constexpr size_t MAX_INTERNAL_REFLECTIONS = 8;



//////// FEATURES ////////

// simulate light polarization state
inline constexpr bool ENABLE_POLARIZATION = false;

// simulate differences in diffraction of different frequencies of light
inline constexpr bool ENABLE_DISPERSION = false;



//////// OPTIMIZATION ////////

// enable an optimization that partitions the scene objects into a tree structure to accelerate ray intersection tests
inline constexpr bool ENABLE_BVH_OPTIMIZATION = true;



//////// DEBUG ////////

// enable state-checking asserts
inline constexpr bool DEBUG_ASSERTS = true;

// color all pixels with the normal direction of the hit surface
inline constexpr bool DEBUG_SHADE_NORMALS = false;

#endif //CONFIG_H
