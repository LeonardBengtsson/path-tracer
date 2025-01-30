//
// Created by Leonard on 2025-01-24.
//

#include "Box.h"

const Box Box::UNIT = {Vec3::ZERO, Vec3::ONE};

Box::Box(const Vec3 min, const Vec3 max) : min(min), max(max) {}

bool Box::contains(const Vec3 &v) const {
    auto w = v - min;
    return w.x >= 0 && w.y >= 0 && w.z >= 0 && w.x <= max.x && w.y <= max.y && w.z <= max.z;
}

bool Box::intersects(const Ray &r) const {
    // TODO
    return true;
}
