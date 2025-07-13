//
// Created by Leonard on 2025-01-23.
//

#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include "Vec2.h"
#include "Vec3.h"
#include "Matrix3x3.h"

namespace math_util {
    inline double signum(const double x) {
        return x < 0 ? -1 : 1;
    }

    inline double minus_signum(const double x) {
        return x < 0 ? 1 : -1;
    }

    inline double lerp(const double t, const double a, const double b) {
        return a + (b - a) * t;
    }

    inline Vec2 lerp(const double t, const Vec2 a, const Vec2 b) {
        return {
            lerp(t, a.x, b.x),
            lerp(t, a.y, b.y)
        };
    }

    inline Vec2 lerp(const Vec2 t, const Vec2 a, const Vec2 b) {
        return {
            lerp(t.x, a.x, b.x),
            lerp(t.y, a.y, b.y)
        };
    }

    inline Vec3 lerp(const double t, const Vec3 &a, const Vec3 &b) {
        return {
            lerp(t, a.x, b.x),
            lerp(t, a.y, b.y),
            lerp(t, a.z, b.z)
        };
    }

    inline Vec3 lerp(const Vec3 &t, const Vec3 &a, const Vec3 &b) {
        return {
            lerp(t.x, a.x, b.x),
            lerp(t.y, a.y, b.y),
            lerp(t.z, a.z, b.z)
        };
    }

    inline double map(const double l, const double a1, const double b1, const double a2, const double b2) {
        return lerp((l - a1) / (b1 - a1), a2, b2);
    }

    inline Vec2 map(const Vec2 l, const Vec2 a1, const Vec2 b1, const Vec2 a2, const Vec2 b2) {
        return {
            map(l.x, a1.x, b1.x, a2.x, b2.x),
            map(l.y, a1.y, b1.y, a2.y, b2.y)
        };
    }

    inline Vec3 map(const Vec3 &l, const Vec3 &a1, const Vec3 &b1, const Vec3 &a2, const Vec3 &b2) {
        return {
            map(l.x, a1.x, b1.x, a2.x, b2.x),
            map(l.y, a1.y, b1.y, a2.y, b2.y),
            map(l.z, a1.z, b1.z, a2.z, b2.z)
        };
    }

    inline Vec3 reflect(const Vec3 &v, const Vec3 &unit_axis) {
        return v - (unit_axis * (v * unit_axis) * 2);
    }

    inline double ray_triangle_intersect(const Vec3 &o, const Vec3 &w2, const Vec3 &w3, const Vec3 &ray_dir, const double dist) {
        // returns the distance from the ray origin to the ray-triangle intersection, or -1 if the distance is larger
        // than `dist` or if there is no intersection

        // Möller-Trumbore algorithm
        //
        // assumes ray dir is unit length
        //
        // given ray origin (f), direction (d), and triangle vertices v₁, v₂, v₃:
        // let o = v₁ - f, w₂ = v₁ - v₂, w₃ = v₁ - v₃
        //
        // solve for non-negative t:
        // f + td = av₁ + bv₂ + cv₃
        // where the left-hand side expresses the intersection point using barycentric coordinates,
        // and a, b, c ≥ 0, a + b + c = 1
        //
        // f + td = av₁ + bv₂ + cv₃ ⇔
        // f + td = (1 - b - c)v₁ + bv₂ + cv₃ ⇔
        // f + td = v₁ + b(v₂ - v₁) + c(v₃ - v₁) ⇔
        // td = v₁ - f - bw₂ - cw₃ ⇔
        // td + bw₂ + cw₃ = o ⇔
        // A [t b c] = o
        // where A is the matrix
        // [ |  |  | ]
        // [ d  w₂ w₃]
        // [ |  |  | ]
        //
        // if det(A) == 0 then the ray is parallel with plane; no intersection
        //
        // we solve the linear system with cramer's rule:
        // t = det(A₁) / det(A)
        // if t < 0 then no intersection
        // b = det(A₂) / det(A)
        // if b < 0 or b > 1 then no intersection
        // c = det(A₃) / det(A)
        // if c < 0 or c > 1 then no intersection
        // return t

        const double det_A = Matrix3x3::det(ray_dir, w2, w3);
        if (abs(det_A) < 0.00001)
            return -1;
        const double inv_det_A = 1 / det_A;

        const double t = Matrix3x3::det(o, w2, w3) * inv_det_A;
        if (t < 0 || t >= dist)
            return -1;

        const double b = Matrix3x3::det(ray_dir, o, w3) * inv_det_A;
        if (b < 0 || b > 1)
            return -1;

        const double c = Matrix3x3::det(ray_dir, w2, o) * inv_det_A;
        if (c < 0 || b + c > 1)
            return -1;

        return t;
    }
}

#endif //MATH_UTIL_H
