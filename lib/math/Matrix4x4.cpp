//
// Created by Leonard on 2025-01-23.
//

#include "Matrix4x4.h"

#include <format>



const Matrix4x4 Matrix4x4::IDENT = Matrix4x4();

Matrix4x4::Matrix4x4()
  : e11(1), e12(0), e13(0), e14(0),
    e21(0), e22(1), e23(0), e24(0),
    e31(0), e32(0), e33(1), e34(0),
    e41(0), e42(0), e43(0), e44(1) {}

Matrix4x4::Matrix4x4(
    const double e11, const double e12, const double e13, const double e14,
    const double e21, const double e22, const double e23, const double e24,
    const double e31, const double e32, const double e33, const double e34,
    const double e41, const double e42, const double e43, const double e44
)
  : e11(e11), e12(e12), e13(e13), e14(e14),
    e21(e21), e22(e22), e23(e23), e24(e24),
    e31(e31), e32(e32), e33(e33), e34(e34),
    e41(e41), e42(e42), e43(e43), e44(e44) {}

Matrix4x4::Matrix4x4(const Matrix3x3 &m, const Vec3 &v)
  : e11(m.e11), e12(m.e12), e13(m.e13), e14(v.x),
    e21(m.e21), e22(m.e22), e23(m.e23), e24(v.y),
    e31(m.e31), e32(m.e32), e33(m.e33), e34(v.z),
    e41(0), e42(0), e43(0), e44(1) {}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &m) const {
    return {
        e11 + m.e11, e12 + m.e12, e13 + m.e13, e14 + m.e14,
        e21 + m.e21, e22 + m.e22, e23 + m.e23, e24 + m.e24,
        e31 + m.e31, e32 + m.e32, e33 + m.e33, e34 + m.e34,
        e41 + m.e41, e42 + m.e42, e43 + m.e43, e44 + m.e44,
    };
}

Matrix4x4 Matrix4x4::operator-() const {
    return {
        -e11, -e12, -e13, -e14,
        -e21, -e22, -e23, -e24,
        -e31, -e32, -e33, -e34,
        -e41, -e42, -e43, -e44,
    };
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &m) const {
    return {
        e11 - m.e11, e12 - m.e12, e13 - m.e13, e14 - m.e14,
        e21 - m.e21, e22 - m.e22, e23 - m.e23, e24 - m.e24,
        e31 - m.e31, e32 - m.e32, e33 - m.e33, e34 - m.e34,
        e41 - m.e41, e42 - m.e42, e43 - m.e43, e44 - m.e44,
    };
}

Matrix4x4 Matrix4x4::operator*(const double d) const {
    return {
        e11 * d, e12 * d, e13 * d, e14 * d,
        e21 * d, e22 * d, e23 * d, e24 * d,
        e31 * d, e32 * d, e33 * d, e34 * d,
        e41 * d, e42 * d, e43 * d, e44 * d,
    };
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &m) const {
    return {
        e11 * m.e11 + e12 * m.e21 + e13 * m.e31 + e14 * m.e41,
        e11 * m.e12 + e12 * m.e22 + e13 * m.e32 + e14 * m.e42,
        e11 * m.e13 + e12 * m.e23 + e13 * m.e33 + e14 * m.e43,
        e11 * m.e14 + e12 * m.e24 + e13 * m.e34 + e14 * m.e44,

        e21 * m.e11 + e22 * m.e21 + e23 * m.e31 + e24 * m.e41,
        e21 * m.e12 + e22 * m.e22 + e23 * m.e32 + e24 * m.e42,
        e21 * m.e13 + e22 * m.e23 + e23 * m.e33 + e24 * m.e43,
        e21 * m.e14 + e22 * m.e24 + e23 * m.e34 + e24 * m.e44,

        e31 * m.e11 + e32 * m.e21 + e33 * m.e31 + e34 * m.e41,
        e31 * m.e12 + e32 * m.e22 + e33 * m.e32 + e34 * m.e42,
        e31 * m.e13 + e32 * m.e23 + e33 * m.e33 + e34 * m.e43,
        e31 * m.e14 + e32 * m.e24 + e33 * m.e34 + e34 * m.e44,

        e41 * m.e11 + e42 * m.e21 + e43 * m.e31 + e44 * m.e41,
        e41 * m.e12 + e42 * m.e22 + e43 * m.e32 + e44 * m.e42,
        e41 * m.e13 + e42 * m.e23 + e43 * m.e33 + e44 * m.e43,
        e41 * m.e14 + e42 * m.e24 + e43 * m.e34 + e44 * m.e44,
    };
}

Vec3 Matrix4x4::apply_only_rot(const Vec3 &v) const {
    return {
        e11 * v.x + e12 * v.y + e13 * v.z,
        e21 * v.x + e22 * v.y + e23 * v.z,
        e31 * v.x + e32 * v.y + e33 * v.z,
    };
}

Vec3 Matrix4x4::apply(const Vec3 &v) const {
    return {
        e11 * v.x + e12 * v.y + e13 * v.z + e14,
        e21 * v.x + e22 * v.y + e23 * v.z + e24,
        e31 * v.x + e32 * v.y + e33 * v.z + e34,
    };
}

Ray Matrix4x4::apply(const Ray &r) const {
    return {
        apply(r.from),
        apply_only_rot(r.dir)
    };
}

Matrix4x4 Matrix4x4::T() const {
    return {
        e11, e21, e31, e41,
        e12, e22, e32, e42,
        e13, e23, e33, e43,
        e14, e24, e34, e44,
    };
}

std::string Matrix4x4::to_string() const {
    return std::format(
        "[{:12.4f} {:12.4f} {:12.4f} {:12.4f}]\n[{:12.4f} {:12.4f} {:12.4f} {:12.4f}]\n[{:12.4f} {:12.4f} {:12.4f} {:12.4f}]\n[{:12.4f} {:12.4f} {:12.4f} {:12.4f}]",
        e11, e12, e13, e14,
        e21, e22, e23, e24,
        e31, e32, e33, e34,
        e41, e42, e43, e44
    );
}
