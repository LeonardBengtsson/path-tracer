//
// Created by Leonard on 2025-01-24.
//

#include "Aabb.h"

#include <cassert>
#include <cmath>

#include "math_util.h"
#include "../config.h"



const Aabb Aabb::UNIT = {Vec3::ZERO, Vec3::ONE};

Aabb::Aabb(const Vec3 &min, const Vec3 &max) : min(min), max(max) {
    if constexpr (DEBUG_ASSERTS)
        assert(min.x <= max.x && min.y <= max.y && min.z <= max.z);
}

bool Aabb::contains(const Vec3 &pos) const {
    return
        pos.x >= min.x && pos.x <= max.x &&
        pos.y >= min.y && pos.y <= max.y &&
        pos.z >= min.z && pos.z <= max.z;
}

bool Aabb::intersects(const Ray &ray) const {
    // same algorithm as described in Aabb::ray_length, but this time we don't care about the actual value of t
    double tx0 = (min.x - ray.from.x) / ray.dir.x;
    double tx1 = (max.x - ray.from.x) / ray.dir.x;
    if (tx0 > tx1)
        std::swap(tx0, tx1);

    double ty0 = (min.y - ray.from.y) / ray.dir.y;
    double ty1 = (max.y - ray.from.y) / ray.dir.y;
    if (ty0 > ty1)
        std::swap(ty0, ty1);

    if (tx0 > ty1 || ty0 > tx1)
        return false;

    double tz0 = (min.z - ray.from.z) / ray.dir.z;
    double tz1 = (max.z - ray.from.z) / ray.dir.z;
    if (tz0 > tz1)
        std::swap(tz0, tz1);

    if (tx0 < 0 && ty0 < 0 && tz0 < 0)
        return false;

    return tz0 <= ty1 && tz0 <= tx1 && tx0 <= tz1 && ty0 <= tz1;
}

double Aabb::ray_length(const Ray &ray) const {
    // if ray starts inside, distance is 0
    if (contains(ray.from))
        return 0;

    // this algrorithm works by determining the distance from the ray's origin to its intersection with any of the six
    // planes which the box's sides lie in, and determining which of these intersections is the closest

    double tx0 = (min.x - ray.from.x) / ray.dir.x;
    double tx1 = (max.x - ray.from.x) / ray.dir.x;
    // store lowest distance in tx0
    if (tx0 > tx1)
        std::swap(tx0, tx1);

    double ty0 = (min.y - ray.from.y) / ray.dir.y;
    double ty1 = (max.y - ray.from.y) / ray.dir.y;
    if (ty0 > ty1)
        std::swap(ty0, ty1);

    // if the ray has to travel further to reach the first plane along one axis than to reach the second plane along
    // another axis, then it must have missed the box
    if (tx0 > ty1 || ty0 > tx1)
        return -1;

    double tz0 = (min.z - ray.from.z) / ray.dir.z;
    double tz1 = (max.z - ray.from.z) / ray.dir.z;
    if (tz0 > tz1)
        std::swap(tz0, tz1);

    if (tz0 > ty1 || tz0 > tx1 || tx0 > tz1 || ty0 > tz1)
        return -1;

    const double t = std::max(std::max(tx0, ty0), tz0);
    // test if box is behind ray
    if (t < 0)
        return -1;

    return t;
}
