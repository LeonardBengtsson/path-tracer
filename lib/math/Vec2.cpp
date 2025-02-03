//
// Created by Leonard on 2025-01-23.
//

#include "Vec2.h"
#include <cmath>

const Vec2 Vec2::ZERO = {0, 0};
const Vec2 Vec2::ONE = {1,  1};
const Vec2 Vec2::X = {1, 0};
const Vec2 Vec2::Y = {0, 1};

Vec2::Vec2(const double x, const double y) : x(x), y(y) {}

Vec2::Vec2(const double xy) : x(xy), y(xy) {}

Vec2 Vec2::operator+(const Vec2 v) const {
    return {x + v.x, y + v.y};
}

Vec2 Vec2::operator+(const double w) const {
    return {x + w, y + w};
}

Vec2 Vec2::operator-() const {
    return {-x, -y};
}

Vec2 Vec2::operator-(const Vec2 v) const {
    return {x - v.x, y - v.y};
}

Vec2 Vec2::operator-(const double w) const {
    return {x - w, y - w};
}

Vec2 Vec2::operator*(const double d) const {
    return {x * d, y * d};
}

Vec2 Vec2::operator/(const Vec2 v) const {
    return {x / v.x, y / v.y};
}


Vec2 Vec2::operator/(const double d) const {
    return {x / d, y / d};
}

double Vec2::operator*(const Vec2 v) const {
    return x * v.x + y * v.y;
}

double Vec2::sq() const {
    return x*x + y*y;
}

double Vec2::magn() const {
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::norm() const {
    const double m = magn();
    return {x / m, y / m};
}
