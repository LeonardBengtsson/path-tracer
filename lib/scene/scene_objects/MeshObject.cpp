//
// Created by Leonard on 2025-07-04.
//

#include "MeshObject.h"

#include <format>
#include <iostream>

#include "../../math/aabb_util.h"
#include "../../config.h"
#include "../../math/math_util.h"



MeshObject::MeshObject(std::vector<Vec3> &&tri_vertices, const Material *material)
  : SceneObject(aabb_util::wrap_aabb(std::span(tri_vertices)), material), tri_vertices(std::move(tri_vertices))
{
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

        const Vec3 w2 = v1 - v2;
        const Vec3 w3 = v1 - v3;

        const double t = math_util::ray_triangle_intersect(o, w2, w3, ray.dir, min_dist);
        if (t == -1)
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

        const double t = math_util::ray_triangle_intersect(o, w2, w3, ray.dir, dist);
        if (t == -1)
            continue;

        dist = t;
        pos = ray.from + ray.dir * t;
        normal = Vec3::cross(w2, w3);

        dist_sq = dist*dist;
    }
    normal = normal.norm();
}
