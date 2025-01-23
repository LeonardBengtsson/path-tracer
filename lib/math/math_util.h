//
// Created by Leonard on 2025-01-23.
//

#ifndef MATH_UTIL_H
#define MATH_UTIL_H
#include "Vec2.h"
#include "Vec3.h"

namespace math_util {
    double lerp(double, double, double);

    Vec2 lerp(double, const Vec2&, const Vec2&);

    Vec3 lerp(double, const Vec3&, const Vec3&);
}

#endif //MATH_UTIL_H
