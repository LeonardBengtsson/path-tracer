//
// Created by Leonard on 2025-01-23.
//

#include "Ray.h"

Ray::Ray(const Vec3 &from, const Vec3 &dir) : from(from), dir(dir) {}

Ray Ray::norm() const {
    return {from, dir.norm()};
}
