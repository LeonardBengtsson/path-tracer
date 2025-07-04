//
// Created by Leonard on 2025-03-27.
//

#ifndef BVH_UTIL_H
#define BVH_UTIL_H

#include <span>
#include <cassert>
#include <cmath>

#include "../math/Aabb.h"
#include "../scene/scene_objects/SceneObject.h"

inline Aabb wrap_aabb(const std::span<const SceneObject*> objects) {
    if (objects.size() == 0)
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

inline void get_optimal_bvh_parameters(const size_t size, uint32_t &max_tree_height, uint32_t &min_leaf_size) {
    min_leaf_size = 2;
    max_tree_height = static_cast<uint32_t>(log2(size));
}

#endif //BVH_UTIL_H
