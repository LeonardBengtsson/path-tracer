//
// Created by Leonard on 2025-07-15.
//

#include "aabb_util.h"

Aabb aabb_util::wrap_aabb(const std::span<const Vec3> points) {
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

Aabb aabb_util::wrap_aabb(const std::span<std::unique_ptr<SceneObject>> objects) {
    if (objects.empty())
        return {Vec3::ZERO, Vec3::ZERO};
    Vec3 min = Vec3::MAX;
    Vec3 max = Vec3::MIN;
    for (const auto &o : objects) {
        Aabb aabb = o->aabb;
        min = Vec3::min(min, aabb.min);
        max = Vec3::max(max, aabb.max);
    }
    return {min, max};
}

Aabb aabb_util::wrap_aabb(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3) {
    return {
        Vec3::min(Vec3::min(v1, v2), v3),
        Vec3::max(Vec3::max(v1, v2), v3)
    };
}
