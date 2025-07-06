//
// Created by Leonard on 2025-03-27.
//

#ifndef AABB_UTIL_H
#define AABB_UTIL_H

#include <span>
#include <cassert>
#include <cmath>

#include "../math/Aabb.h"
#include "../scene/scene_objects/SceneObject.h"

inline Aabb wrap_aabb(const std::span<const Vec3> points) {
    if (points.empty())
        return {Vec3::ZERO, Vec3::ZERO};
    Vec3 min = Vec3::MAX;
    Vec3 max = Vec3::MIN;
    for (const Vec3 &point : points) {
        min = Vec3::min(min, point);
        max = Vec3::max(max, point);
    }
    return {min, max};
}

inline Aabb wrap_aabb(const std::span<const SceneObject *const> objects) {
    if (objects.empty())
        return {Vec3::ZERO, Vec3::ZERO};
    Vec3 min = Vec3::MAX;
    Vec3 max = Vec3::MIN;
    for (const SceneObject* o : objects) {
        Aabb aabb = o->aabb;
        min = Vec3::min(min, aabb.min);
        max = Vec3::max(max, aabb.max);
    }
    return {min, max};
}

inline Aabb wrap_aabb(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2) {
    return {
        Vec3::min(Vec3::min(v0, v1), v2),
        Vec3::max(Vec3::max(v0, v1), v2)
    };
}

inline void get_optimal_bvh_parameters(const size_t size, uint32_t &max_tree_height, uint32_t &min_leaf_size) {
    min_leaf_size = 2;
    max_tree_height = static_cast<uint32_t>(log2(size));
}

#endif //AABB_UTIL_H
