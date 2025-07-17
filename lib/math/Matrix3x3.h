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

    double e11, e12, e13, e21, e22, e23, e31, e32, e33;

    Matrix3x3();

    Matrix3x3(
        double e11, double e12, double e13,
        double e21, double e22, double e23,
        double e31, double e32, double e33);

    Matrix3x3(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);

    Matrix3x3 operator+(const Matrix3x3 &m) const;
    Matrix3x3 operator-() const;
    Matrix3x3 operator-(const Matrix3x3 &m) const;
    Matrix3x3 operator*(double d) const;
    Matrix3x3 operator*(const Matrix3x3 &m) const;
    Vec3 operator*(const Vec3 &v) const;

    Matrix3x3 T() const;
    double det() const;

    std::string to_string() const;

    /**
     * @return The change-of-basis matrix from the standard basis to the basis where
     * x -> right, y -> down, z -> forward.
     */
    static Matrix3x3 from_forward_down_vecs(const Vec3 &forward, const Vec3 &down);

    /**
     * @return The determinant of the matrix formed by the column vectors @c v1, @c v2, @c v3.
     */
    static double det(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);
};



#endif //MATRIX3X3_H
