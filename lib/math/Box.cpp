//
// Created by Leonard on 2025-01-24.
//

#include "Box.h"

#include <cassert>
#include <cmath>

#include "math_util.h"
#include "../config.h"

const Box Box::UNIT = {Vec3::ZERO, Vec3::ONE};

Box::Box(const Vec3 &min, const Vec3 &max) : min(min), max(max) {
#if DEBUG_ASSERTS
    assert(min.x <= max.x && min.y <= max.y && min.z <= max.z);
#endif
}

bool Box::contains(const Vec3 &v) const {
    const auto w = v - min;
    return w.x >= 0 && w.y >= 0 && w.z >= 0 && w.x <= max.x && w.y <= max.y && w.z <= max.z;
}

bool Box::intersects(const Ray &r) const {
    double tx0 = (min.x - r.from.x) / r.dir.x;
    double tx1 = (max.x - r.from.x) / r.dir.x;
    if (tx0 > tx1)
        // possible optimization with bit-xor?
        std::swap(tx0, tx1);

    double ty0 = (min.y - r.from.y) / r.dir.y;
    double ty1 = (max.y - r.from.y) / r.dir.y;
    if (ty0 > ty1)
        std::swap(ty0, ty1);

    if (tx0 > ty1 || ty0 > tx1)
        return false;

    double tz0 = (min.z - r.from.z) / r.dir.z;
    double tz1 = (max.z - r.from.z) / r.dir.z;
    if (tz0 > tz1)
        std::swap(tz0, tz1);

    if (tx0 < 0 && ty0 < 0 && tz0 < 0)
        return false;

    return tz0 <= ty1 && tz0 <= tx1 && tx0 <= tz1 && ty0 <= tz1;
}
