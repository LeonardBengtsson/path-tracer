//
// Created by Leonard on 2025-02-03.
//

#include "BoxObject.h"

#include <cmath>

#include "../../math/math_util.h"



BoxObject::BoxObject(const Aabb &box, const Material *material)
  : SceneObject(box, material) {}

bool BoxObject::ray_cast_from_outside(const Ray& ray, double& min_dist, Vec3& pos, Vec3& normal) const {
    // same algorithm as described in Aabb::ray_length
    double tx0 = (aabb.min.x - ray.from.x) / ray.dir.x;
    double tx1 = (aabb.max.x - ray.from.x) / ray.dir.x;
    if (tx0 > tx1)
        std::swap(tx0, tx1);

    double ty0 = (aabb.min.y - ray.from.y) / ray.dir.y;
    double ty1 = (aabb.max.y - ray.from.y) / ray.dir.y;
    if (ty0 > ty1)
        std::swap(ty0, ty1);

    if (tx0 > ty1 || ty0 > tx1)
      return false;

    double tz0 = (aabb.min.z - ray.from.z) / ray.dir.z;
    double tz1 = (aabb.max.z - ray.from.z) / ray.dir.z;
    if (tz0 > tz1)
        std::swap(tz0, tz1);

    if (tz0 > ty1 || tz0 > tx1 || tx0 > tz1 || ty0 > tz1)
        return false;

    const double t = std::max(std::max(tx0, ty0), tz0);
    if (t > min_dist || t < 0)
        return false;

    min_dist = t;
    pos = ray.from + ray.dir * t;
    // determine normal vector based on which side intersection was closest
    if (t == tx0) {
        normal = {math_util::minus_signum(ray.dir.x), 0, 0};
    } else if (t == ty0) {
        normal = {0, math_util::minus_signum(ray.dir.y), 0};
    } else {
        normal = {0, 0, math_util::minus_signum(ray.dir.z)};
    }
    return true;
}

void BoxObject::ray_cast_from_inside(const Ray& ray, double& dist, Vec3& pos, Vec3& normal) const {
    // which box corner is closest to where the ray will intersect
    const Vec3 corner = {
        ray.dir.x > 0 ? aabb.max.x : aabb.min.x,
        ray.dir.y > 0 ? aabb.max.y : aabb.min.y,
        ray.dir.z > 0 ? aabb.max.z : aabb.min.z
    };
    // the distance from the ray origin to its intersection with each respective plane
    // corner_i - origin_i < 0 if and only if dir_i < 0, so t_i > 0
    // if dir_i == 0, then t_i = std::numeric_limits<double>::infinity()
    const Vec3 t = math_util::safe_divide(corner - ray.from, ray.dir);
    // determine the nearest plane
    if (t.x < t.y && t.x < t.z) {
        dist = t.x;
        pos = ray.from + ray.dir * t.x;
        normal = ray.dir.x > 0 ? Vec3(-1, 0, 0) : Vec3(1, 0, 0);
    } else if (t.y < t.z) {
        dist = t.y;
        pos = ray.from + ray.dir * t.y;
        normal = ray.dir.y > 0 ? Vec3(0, -1, 0) : Vec3(0, 1, 0);
    } else {
        dist = t.z;
        pos = ray.from + ray.dir * t.z;
        normal = ray.dir.z > 0 ? Vec3(0, 0, -1) : Vec3(0, 0, 1);
    }
}
