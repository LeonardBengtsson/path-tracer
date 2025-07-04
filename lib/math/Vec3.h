//
// Created by Leonard on 2025-01-23.
//

#ifndef VEC3_H
#define VEC3_H
#include <string>

#include "Vec2.h"


class Vec3 {
public:
    static const Vec3 ZERO, ONE, X, Y, Z, MIN, MAX;

    double x, y, z;

    Vec3(const Vec3&);
    Vec3(double, double, double);
    Vec3(Vec2, double);
    Vec3(double, Vec2);
    Vec3(double);

    Vec3 operator+(const Vec3&) const;
    Vec3 operator+(double) const;
    Vec3 operator-() const;
    Vec3 operator-(const Vec3&) const;
    Vec3 operator-(double) const;
    Vec3 operator*(double) const;
    Vec3 operator/(const Vec3&) const;
    Vec3 operator/(double) const;
    double operator*(const Vec3&) const;

    double sq() const;
    double magn() const;
    Vec3 norm() const;

    std::string debug_string() const;

    static Vec3 min(const Vec3&, const Vec3&);
    static Vec3 max(const Vec3&, const Vec3&);

    static Vec3 cross(const Vec3&, const Vec3&);
};



#endif //VEC3_H
