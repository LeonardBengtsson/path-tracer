//
// Created by Leonard on 2025-01-23.
//

#include "Ray.h"

#include <cassert>

#include "Vec3.h"

const Ray Ray::ZERO = {Vec3::ZERO, Vec3::ZERO};
const Ray Ray::X = {Vec3::ZERO, Vec3::X};
const Ray Ray::Y = {Vec3::ZERO, Vec3::Y};
const Ray Ray::Z = {Vec3::ZERO, Vec3::Z};

Ray::Ray(const Vec3 &from, const Vec3 &dir) : from(from), dir(dir) {
#ifdef DEBUG
    assert(dir.magn() == 1);
#endif
}

Ray Ray::norm() const {
    return {from, dir.norm()};
}
