//
// Created by Leonard on 2025-01-23.
//

#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include "Matrix3x3.h"
#include "Ray.h"


class Matrix4x4 {
private:
    Vec3 apply_only_rot(const Vec3& v) const;
public:
    static const Matrix4x4 IDENT;

    double e11, e12, e13, e14, e21, e22, e23, e24, e31, e32, e33, e34, e41, e42, e43, e44;

    Matrix4x4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    Matrix4x4(const Matrix3x3&, const Vec3&);

    Matrix4x4 operator+(const Matrix4x4&) const;
    Matrix4x4 operator-() const;
    Matrix4x4 operator-(const Matrix4x4&) const;
    Matrix4x4 operator*(double) const;
    Matrix4x4 operator*(const Matrix4x4&) const;

    Vec3 apply(const Vec3&) const;
    Ray apply(const Ray&) const;
    Matrix4x4 T() const;

    std::string to_string() const;
};



#endif //MATRIX4X4_H
