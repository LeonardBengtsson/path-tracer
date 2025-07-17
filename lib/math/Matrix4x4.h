//
// Created by Leonard on 2025-01-23.
//

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Matrix3x3.h"
#include "Ray.h"



class Matrix4x4 {
private:
    Vec3 apply_only_rot(const Vec3 &v) const;
public:
    static const Matrix4x4 IDENT;

    double
        e11, e12, e13, e14,
        e21, e22, e23, e24,
        e31, e32, e33, e34,
        e41, e42, e43, e44;

    Matrix4x4();

    Matrix4x4(
        double e11, double e12, double e13, double e14,
        double e21, double e22, double e23, double e24,
        double e31, double e32, double e33, double e34,
        double e41, double e42, double e43, double e44);

    /**
     * Instantiate an affine transformation matrix with matrix transformation @c m and offset @c v.
     */
    Matrix4x4(const Matrix3x3 &m, const Vec3 &v);

    Matrix4x4 operator+(const Matrix4x4 &m) const;
    Matrix4x4 operator-() const;
    Matrix4x4 operator-(const Matrix4x4 &m) const;
    Matrix4x4 operator*(double d) const;
    Matrix4x4 operator*(const Matrix4x4 &m) const;

    /**
     * Apply the affine transformation represented by this matrix to a vector.
     * @return The transformed vector.
     */
    Vec3 apply(const Vec3 &v) const;

    /**
     * Apply the affine transformation represented by this matrix to a ray.
     * @return The transformed ray.
     */
    Ray apply(const Ray &r) const;

    Matrix4x4 T() const;

    std::string to_string() const;
};



#endif //MATRIX4X4_H
