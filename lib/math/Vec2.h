//
// Created by Leonard on 2025-01-23.
//

#ifndef VEC2_H
#define VEC2_H



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
    Vec2 operator/(double) const;
    double operator*(Vec2) const;

    double sq() const;
    double magn() const;
    Vec2 norm() const;
};



#endif //VEC2_H
