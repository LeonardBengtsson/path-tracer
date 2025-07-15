//
// Created by Leonard on 2025-03-27.
//

#ifndef AABB_UTIL_H
#define AABB_UTIL_H

#include <span>
#include <cassert>
#include <cmath>
#include <memory>

#include "Aabb.h"
#include "../scene/scene_objects/SceneObject.h"


class SceneObject;

namespace aabb_util {
    Aabb wrap_aabb(std::span<const Vec3> points);

    Aabb wrap_aabb(std::span<std::unique_ptr<SceneObject>> objects);

    Aabb wrap_aabb(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);

    inline void get_optimal_bvh_parameters(const size_t size, uint32_t &max_tree_height, uint32_t &min_leaf_size) {
        min_leaf_size = 2;
        max_tree_height = static_cast<uint32_t>(log2(size));
    }
}

#endif //AABB_UTIL_H
