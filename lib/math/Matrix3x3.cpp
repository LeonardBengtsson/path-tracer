//
// Created by Leonard on 2025-01-23.
//

#include "Matrix3x3.h"

#include <format>



const Matrix3x3 Matrix3x3::IDENT = Matrix3x3();

Matrix3x3::Matrix3x3()
  : e11(1), e12(0), e13(0),
    e21(0), e22(1), e23(0),
    e31(0), e32(0), e33(1) {}

Matrix3x3::Matrix3x3(
    const double e11, const double e12, const double e13,
    const double e21, const double e22, const double e23,
    const double e31, const double e32, const double e33
)
  : e11(e11), e12(e12), e13(e13),
    e21(e21), e22(e22), e23(e23),
    e31(e31), e32(e32), e33(e33) {}

Matrix3x3::Matrix3x3(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
  : e11(v1.x), e12(v2.x), e13(v3.x),
    e21(v1.y), e22(v2.y), e23(v3.y),
    e31(v1.z), e32(v2.z), e33(v3.z) {}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3 &m) const {
    return {
        e11 + m.e11, e12 + m.e12, e13 + m.e13,
        e21 + m.e21, e22 + m.e22, e23 + m.e23,
        e31 + m.e31, e32 + m.e32, e33 + m.e33,
    };
}

Matrix3x3 Matrix3x3::operator-() const {
    return {
        -e11, -e12, -e13,
        -e21, -e22, -e23,
        -e31, -e32, -e33,
    };
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3 &m) const {
    return {
        e11 - m.e11, e12 - m.e12, e13 - m.e13,
        e21 - m.e21, e22 - m.e22, e23 - m.e23,
        e31 - m.e31, e32 - m.e32, e33 - m.e33,
    };
}

Matrix3x3 Matrix3x3::operator*(const double d) const {
    return {
        e11 * d, e12 * d, e13 * d,
        e21 * d, e22 * d, e23 * d,
        e31 * d, e32 * d, e33 * d,
    };
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &m) const {
    return {
        e11 * m.e11 + e12 * m.e21 + e13 * m.e31,
        e11 * m.e12 + e12 * m.e22 + e13 * m.e32,
        e11 * m.e13 + e12 * m.e23 + e13 * m.e33,
        e21 * m.e11 + e22 * m.e21 + e23 * m.e31,
        e21 * m.e12 + e22 * m.e22 + e23 * m.e32,
        e21 * m.e13 + e22 * m.e23 + e23 * m.e33,
        e31 * m.e11 + e32 * m.e21 + e33 * m.e31,
        e31 * m.e12 + e32 * m.e22 + e33 * m.e32,
        e31 * m.e13 + e32 * m.e23 + e33 * m.e33,
    };
}

Vec3 Matrix3x3::operator*(const Vec3 &v) const {
    return {
        e11 * v.x + e12 * v.y + e13 * v.z,
        e21 * v.x + e22 * v.y + e23 * v.z,
        e31 * v.x + e32 * v.y + e33 * v.z,
    };
}

Matrix3x3 Matrix3x3::T() const {
    return {
        e11, e21, e31,
        e12, e22, e32,
        e13, e23, e33
    };
}

double Matrix3x3::det() const {
    return e11 * e22 * e33 + e12 * e23 * e31 + e13 * e21 * e32
         - e11 * e23 * e32 - e12 * e21 * e33 - e13 * e22 * e31;
}

std::string Matrix3x3::to_string() const {
    return std::format(
        "[{:12.4f} {:12.4f} {:12.4f}]\n[{:12.4f} {:12.4f} {:12.4f}]\n[{:12.4f} {:12.4f} {:12.4f}]",
        e11, e12, e13,
        e21, e22, e23,
        e31, e32, e33
    );
}

Matrix3x3 Matrix3x3::from_forward_down_vecs(const Vec3 &forward, const Vec3 &down) {
    const Vec3 right = Vec3::cross(down, forward).norm();
    return {right, Vec3::cross(forward, right), forward};
}

double Matrix3x3::det(const Vec3& v1, const Vec3& v2, const Vec3& v3) {
    return v1.x * v2.y * v3.z + v2.x * v3.y * v1.z + v3.x * v1.y * v2.z
         - v1.x * v3.y * v2.z - v2.x * v1.y * v3.z - v3.x * v2.y * v1.z;
}
