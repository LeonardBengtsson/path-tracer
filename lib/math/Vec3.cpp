//
// Created by Leonard on 2025-01-23.
//

#include "Vec3.h"
#include <cmath>

const Vec3 Vec3::ZERO = {0, 0, 0};
const Vec3 Vec3::X = {1, 0, 0};
const Vec3 Vec3::Y = {0, 1, 0};
const Vec3 Vec3::Z = {0, 0, 1};

Vec3::Vec3(const double x, const double y, const double z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3 &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vec3 Vec3::operator-() const {
    return {-x, -y, -z};
}


Vec3 Vec3::operator-(const Vec3 &v) const {
    return {x - v.x, y - v.y, z - v.z};
}

Vec3 Vec3::operator*(const double d) const {
    return {x * d, y * d, z * d};
}

Vec3 Vec3::operator/(const double d) const {
    return {x / d, y / d, z / d};
}

double Vec3::operator*(const Vec3 &v) const {
    return x * v.x + y * v.y + z * v.z;
}

double Vec3::sq() const {
    return x*x + y*y + z*z;
}

double Vec3::magn() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::norm() const {
    const double m = magn();
    return {x / m, y / m, z / m};
}

Vec3 Vec3::cross(const Vec3 &v, const Vec3 &w) {
    return {v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x};
}