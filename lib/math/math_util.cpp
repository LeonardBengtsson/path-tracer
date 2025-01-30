//
// Created by Leonard on 2025-01-23.
//

#include "math_util.h"

namespace math_util {
    double lerp(const double t, const double a, const double b) {
        return a + (b - a) * t;
    }

    Vec2 lerp(const double t, const Vec2 a, const Vec2 b) {
        return {
            lerp(t, a.x, b.x),
            lerp(t, a.y, b.y)
        };
    }

    Vec2 lerp(const Vec2 t, const Vec2 a, const Vec2 b) {
        return {
            lerp(t.x, a.x, b.x),
            lerp(t.y, a.y, b.y)
        };
    }

    Vec3 lerp(const double t, const Vec3 &a, const Vec3 &b) {
        return {
            lerp(t, a.x, b.x),
            lerp(t, a.y, b.y),
            lerp(t, a.z, b.z)
        };
    }

    Vec3 lerp(const Vec3 &t, const Vec3 &a, const Vec3 &b) {
        return {
            lerp(t.x, a.x, b.x),
            lerp(t.y, a.y, b.y),
            lerp(t.z, a.z, b.z)
        };
    }

    double map(const double l, const double a1, const double b1, const double a2, const double b2) {
        return lerp((l - a1) / (b1 - a1), a2, b2);
    }

    Vec2 map(const Vec2 l, const Vec2 a1, const Vec2 b1, const Vec2 a2, const Vec2 b2) {
        return {
            map(l.x, a1.x, b1.x, a2.x, b2.x),
            map(l.y, a1.y, b1.y, a2.y, b2.y)
        };
    }

    Vec3 map(const Vec3 &l, const Vec3 &a1, const Vec3 &b1, const Vec3 &a2, const Vec3 &b2) {
        return {
            map(l.x, a1.x, b1.x, a2.x, b2.x),
            map(l.y, a1.y, b1.y, a2.y, b2.y),
            map(l.z, a1.z, b1.z, a2.z, b2.z)
        };
    }

    Vec3 reflect(const Vec3 &v, const Vec3 &unit_axis) {
        return v - (unit_axis * (v * unit_axis) * 2);
    }
}
