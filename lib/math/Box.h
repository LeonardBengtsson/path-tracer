//
// Created by Leonard on 2025-01-24.
//

#ifndef BOX_H
#define BOX_H
#include "Ray.h"
#include "Vec3.h"


class Box {
public:
    static const Box UNIT;

    const Vec3 min, max;

    Box(const Vec3 &min, const Vec3 &max);

    bool contains(const Vec3&) const;

    bool intersects(const Ray&) const;
};



#endif //BOX_H
