//
// Created by Leonard on 2025-01-23.
//

#include "Ray.h"

#include <cassert>
#include <format>
#include <iostream>

#include "Vec3.h"
#include "../config.h"

const Ray Ray::X = {{0, 0, 0}, {1, 0, 0}};
const Ray Ray::Y = {{0, 0, 0}, {0, 1, 0}};
const Ray Ray::Z = {{0, 0, 0}, {0, 0, 1}};

Ray::Ray(const Vec3 &from, const Vec3 &dir) : from(from), dir(dir) {
#if DEBUG_ASSERTS
    assert(std::abs(dir.sq() - 1) < .0000001);
#endif
}

Ray Ray::norm() const {
    return {from, dir.norm()};
}
