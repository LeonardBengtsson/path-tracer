//
// Created by Leonard on 2025-01-23.
//

#ifndef MATH_UTIL_H
#define MATH_UTIL_H
#include "Vec2.h"
#include "Vec3.h"

namespace math_util {
    double lerp(double, double, double);
    Vec2 lerp(double, Vec2, Vec2);
    Vec2 lerp(Vec2, Vec2, Vec2);
    Vec3 lerp(double, const Vec3&, const Vec3&);
    Vec3 lerp(const Vec3&, const Vec3&, const Vec3&);

    double map(double, double, double, double, double);
    Vec2 map(Vec2, Vec2, Vec2, Vec2, Vec2);
    Vec3 map(Vec3&, Vec3&, Vec3&, Vec3&, Vec3&);

    Vec3 reflect(const Vec3&, const Vec3&);
}

#endif //MATH_UTIL_H
