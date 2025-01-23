//
// Created by Leonard on 2025-01-23.
//

#include "math_util.h"

namespace math_util {
    double lerp(const double t, const double a, const double b) {
        return a + (b - a) * t;
    }

    Vec2 lerp(const double t, const Vec2 &a, const Vec2 &b) {
        return {
            lerp(t, a.x, b.x),
            lerp(t, a.y, b.y)
        };
    }

    Vec3 lerp(const double t, const Vec3 &a, const Vec3 &b) {
        return {
            lerp(t, a.x, b.x),
            lerp(t, a.y, b.y),
            lerp(t, a.z, b.z)
        };
    }
}
