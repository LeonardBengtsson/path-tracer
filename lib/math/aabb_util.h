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
    /**
     * @return The smallest @c Aabb containing all points.
     */
    Aabb wrap_aabb(std::span<const Vec3> points);

    /**
     * @return The smallest @c Aabb containing all objects.
     */
    Aabb wrap_aabb(std::span<std::unique_ptr<SceneObject>> objects);

    /**
     * @return The smallest @c Aabb containing all points.
     */
    Aabb wrap_aabb(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);

    /**
     * Calculates and returns the optimal parameters for a BVH tree, given its size.
     * @param size The number of objects in the tree.
     */
    inline void get_optimal_bvh_parameters(const size_t size, uint32_t &out_max_tree_height,
        uint32_t &out_min_leaf_size)
    {
        out_min_leaf_size = 2;
        out_max_tree_height = static_cast<uint32_t>(log2(size));
    }
}



#endif //AABB_UTIL_H
