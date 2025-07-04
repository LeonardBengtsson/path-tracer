//
// Created by Leonard on 2025-01-24.
//

#ifndef AABB_H
#define AABB_H

#include "Ray.h"
#include "Vec3.h"


class Aabb {
public:
    static const Aabb UNIT;

    const Vec3 min, max;

    Aabb(const Vec3 &min, const Vec3 &max);

    bool contains(const Vec3 &pos) const;

    bool intersects(const Ray &ray) const;

    // return closest distance from ray to aabb, or infinity if there's no intersection
    double ray_dist(const Ray &ray) const;
};



#endif //AABB_H
