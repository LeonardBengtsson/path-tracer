//
// Created by Leonard on 2025-01-23.
//

#include "Vec2.h"

#include <cmath>
#include <format>
#include <string>



const Vec2 Vec2::ZERO = {0, 0};
const Vec2 Vec2::ONE = {1, 1};
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

std::string Vec2::debug_string() const {
    return std::format("({}, {})", x, y);
}

Vec2 Vec2::min(const Vec2 &v, const Vec2 &w) {
    return {std::min(v.x, w.x), std::min(v.y, w.y)};
}

Vec2 Vec2::max(const Vec2 &v, const Vec2 &w) {
    return {std::max(v.x, w.x), std::max(v.y, w.y)};
}
