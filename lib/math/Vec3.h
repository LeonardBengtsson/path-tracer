//
// Created by Leonard on 2025-01-23.
//

#ifndef VEC3_H
#define VEC3_H



class Vec3 {
public:
    static const Vec3 ZERO;
    static const Vec3 X;
    static const Vec3 Y;
    static const Vec3 Z;

    const double x, y, z;

    Vec3(double, double, double);

    Vec3 operator+(const Vec3&) const;
    Vec3 operator-() const;
    Vec3 operator-(const Vec3&) const;
    Vec3 operator*(double) const;
    Vec3 operator/(double) const;
    double operator*(const Vec3&) const;

    double sq() const;
    double magn() const;
    Vec3 norm() const;

    static Vec3 cross(const Vec3&, const Vec3&);
};



#endif //VEC3_H
