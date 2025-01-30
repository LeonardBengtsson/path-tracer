//
// Created by Leonard on 2025-01-23.
//

#ifndef MATRIX3X3_H
#define MATRIX3X3_H
#include <string>

#include "Vec3.h"


class Matrix3x3 {
public:
    static const Matrix3x3 IDENT;

    const double e11, e12, e13, e21, e22, e23, e31, e32, e33;

    Matrix3x3(double, double, double, double, double, double, double, double, double);
    Matrix3x3(const Vec3&, const Vec3&, const Vec3&);

    Matrix3x3 operator+(const Matrix3x3&) const;
    Matrix3x3 operator-() const;
    Matrix3x3 operator-(const Matrix3x3&) const;
    Matrix3x3 operator*(double) const;
    Matrix3x3 operator*(const Matrix3x3&) const;
    Vec3 operator*(const Vec3&) const;

    Matrix3x3 T() const;
    double det() const;

    std::string to_string() const;

    static Matrix3x3 from_forward_down_vecs(const Vec3&, const Vec3&);
};



#endif //MATRIX3X3_H
