//
// Created by Leonard on 2025-01-23.
//

#ifndef RAY_H
#define RAY_H

#include "Vec3.h"



class Ray {
public:
    const Vec3 from, dir;

    Ray(const Vec3 &, const Vec3 &);

    Ray norm() const;
};



#endif //RAY_H
