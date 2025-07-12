//
// Created by Leonard on 2025-07-04.
//

#include "MeshObject.h"

#include <format>
#include <iostream>

#include "../../math/aabb_util.h"
#include "../../config.h"

MeshObject::MeshObject(const std::vector<Vec3> &&tri_vertices, const Material *material)
  : SceneObject(aabb_util::wrap_aabb(std::span(tri_vertices)), material),
    tri_vertices(tri_vertices) {

    if constexpr (DEBUG_ASSERTS)
        assert(tri_vertices.size() % 3 == 0);
}

bool MeshObject::ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) const {
    double min_dist_sq = min_dist*min_dist;
    bool hit = false;
    for (size_t i = 0; i+2 < tri_vertices.size(); i += 3) {
        const Vec3 v1 = tri_vertices[i];
        const Vec3 v2 = tri_vertices[i+1];
        const Vec3 v3 = tri_vertices[i+2];

        const Vec3 o = v1 - ray.from;
        if (
            o.sq() > min_dist_sq &&
            (v2 - ray.from).sq() > min_dist_sq &&
            (v3 - ray.from).sq() > min_dist_sq
        ) {
            continue;
        }

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

        const Vec3 w2 = v1 - v2;
        const Vec3 w3 = v1 - v3;

        const double det_A = Matrix3x3::det(ray.dir, w2, w3);
        if (abs(det_A) < 0.00001)
            continue;
        const double inv_det_A = 1 / det_A;

        const double t = Matrix3x3::det(o, w2, w3) * inv_det_A;
        if (t < 0 || t >= min_dist)
            continue;

        const double b = Matrix3x3::det(ray.dir, o, w3) * inv_det_A;
        if (b < 0 || b > 1)
            continue;

        const double c = Matrix3x3::det(ray.dir, w2, o) * inv_det_A;
        if (c < 0 || b + c > 1)
            continue;

        min_dist = t;
        pos = ray.from + ray.dir * t;
        normal = Vec3::cross(w3, w2);

        min_dist_sq = min_dist*min_dist;
        hit = true;
    }
    return hit;
}

void MeshObject::ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &pos, Vec3 &normal) const {
    dist = std::numeric_limits<double>::max();
    double dist_sq = std::numeric_limits<double>::max();
    for (size_t i = 0; i+2 < tri_vertices.size(); i += 3) {
        const Vec3 v1 = tri_vertices[i];
        const Vec3 v2 = tri_vertices[i+1];
        const Vec3 v3 = tri_vertices[i+2];

        const Vec3 o = v1 - ray.from;
        if (
            o.sq() > dist_sq &&
            (v2 - ray.from).sq() > dist_sq &&
            (v3 - ray.from).sq() > dist_sq
        ) {
            continue;
        }

        const Vec3 w2 = v1 - v2;
        const Vec3 w3 = v1 - v3;

        const double det_A = Matrix3x3::det(ray.dir, w2, w3);
        if (abs(det_A) < 0.00001)
            continue;
        const double inv_det_A = 1 / det_A;

        const double t = Matrix3x3::det(o, w2, w3) * inv_det_A;
        if (t < 0 || t >= dist)
            continue;

        const double b = Matrix3x3::det(ray.dir, o, w3) * inv_det_A;
        if (b < 0 || b > 1)
            continue;

        const double c = Matrix3x3::det(ray.dir, w2, o) * inv_det_A;
        if (c < 0 || b + c > 1)
            continue;

        dist = t;
        pos = ray.from + ray.dir * t;
        normal = Vec3::cross(w2, w3);

        dist_sq = dist*dist;
    }
    normal = normal.norm();
}

