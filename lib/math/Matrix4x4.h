//
// Created by Leonard on 2025-01-23.
//

#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include "Matrix3x3.h"


class Matrix4x4 {
public:
    static const Matrix4x4 IDENT;

    const double e11, e12, e13, e14, e21, e22, e23, e24, e31, e32, e33, e34, e41, e42, e43, e44;

    Matrix4x4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    Matrix4x4(const Matrix3x3&, const Vec3&);

    Matrix4x4 operator+(const Matrix4x4&) const;
    Matrix4x4 operator-() const;
    Matrix4x4 operator-(const Matrix4x4&) const;
    Matrix4x4 operator*(double) const;
    Matrix4x4 operator*(const Matrix4x4&) const;

    Vec3 apply(const Vec3&) const;
    Matrix4x4 T() const;
    double det() const;
};



#endif //MATRIX4X4_H
