//
// Created by Leonard on 2025-01-28.
//

#include "SphereObject.h"

#include <cmath>
#include <cassert>

#include "../../math/math_util.h"
#include "../../config.h"

SphereObject::SphereObject(const Vec3 &center, const double radius, const Material* const material)
  : SceneObject({center - radius, center + radius}, material),
    center(center),
    radius(radius)
{
#ifdef DEBUG_ASSERTS
    assert(radius >= 0);
#endif
}

bool SphereObject::ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) const {
    // assumes ray dir is unit length, and ray origin is not inside sphere
    //
    // given ray origin (f), direction (d), sphere center (c), radius (r):
    // we solve the following for non-negative t:
    // |(f + td) - c|² = r²
    //
    // let Δ = f - c
    // |Δ + td|² = r² ⇔
    // (Δ + td)·(Δ + td) = r² ⇔
    // (d·d)t² + (2Δ·d)t + Δ·Δ - r² = 0 ⇔
    // t² + (2Δ·d)t + Δ·Δ - r² = 0 (assume |d| = 1)
    //
    // let p_half = Δ·d
    // let q = Δ·Δ - r²
    // let D = p_half² - q = (Δ·d)² - Δ·Δ + r²
    // t₁ = -p_half - √D
    // t₂ = -p_half + √D
    //
    // we have 4 cases:
    // (1) D  < 0       (no intersection)
    // (2) 0  ≤ t₁ < t₂ (intersection with t = t₁, f is outside sphere)
    // (3) t₁ < 0  ≤ t₂ (intersection with t = t₂, f is inside sphere)
    // (4) t₁ < t₂ < 0  (no intersection)
    //
    // algorithm:
    // - check D < 0
    // - if f is outside sphere: check 0 ≤ t₁
    //     ⇔ 0 ≥ p_half + √D
    //     ⇔ -p_half ≥ √D
    //     ⇔ p_half < 0 AND p_half² ≥ D
    //     ⇔ p_half < 0 AND q ≥ 0
    //     ⇔ p_half < 0 (because |Δ| ≥ r ⇒ q ≥ 0)
    //   - return t₁
    // - if f is inside sphere: check 0 ≤ t₂
    //     ⇔ 0 ≤ -p_half + √D
    //     ⇔ p_half ≤ √D
    //     ⇔ p_half < 0 OR p_half² ≤ D
    //     ⇔ p_half < 0 OR q ≤ 0
    //   - which is true because |Δ| ≤ r ⇒ q ≤ 0
    //   - return t₂

    const Vec3 Delta = ray.from - center;
    const double p_half = Delta * ray.dir;
    const double q = Delta.sq() - radius * radius;
    const double D = p_half * p_half - q;

    if (D < 0 || p_half > 0)
        return false;

    //   min_dist < -p_half - √D
    // ⇔       √D < -(p_half + min_dist)
    // ⇔        D < (p_half + min_dist)² AND p_half + min_dist < 0
    const double pd = p_half + min_dist;
    if (D < pd * pd && pd < 0)
        return false;

    const double t1 = -p_half - std::sqrt(D);

    min_dist = t1;
    pos = ray.from + ray.dir * t1;
    normal = (pos - center).norm();
    return true;
}

void SphereObject::ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &pos, Vec3 &normal) const {
    const Vec3 Delta = ray.from - center;
    const double p_half = Delta * ray.dir;
    const double q = Delta.sq() - radius * radius;
    const double D = p_half * p_half - q;

    const double t2 = -p_half + std::sqrt(D);

    dist = t2;
    pos = ray.from + ray.dir * t2;
    normal = (center - pos).norm();
}
