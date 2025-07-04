//
// Created by Leonard on 2025-01-23.
//

#ifndef VEC2_H
#define VEC2_H
#include <string>


class Vec2 {
public:
    static const Vec2 ZERO, ONE, X, Y;

    double x, y;

    Vec2(double, double);
    Vec2(double);

    Vec2 operator+(Vec2) const;
    Vec2 operator+(double) const;
    Vec2 operator-() const;
    Vec2 operator-(Vec2) const;
    Vec2 operator-(double) const;
    Vec2 operator*(double) const;
    Vec2 operator/(Vec2) const;
    Vec2 operator/(double) const;
    double operator*(Vec2) const;

    double sq() const;
    double magn() const;
    Vec2 norm() const;

    std::string debug_string() const;

    static Vec2 min(const Vec2&, const Vec2&);
    static Vec2 max(const Vec2&, const Vec2&);
};



#endif //VEC2_H
