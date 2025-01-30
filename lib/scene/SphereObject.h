//
// Created by Leonard on 2025-01-28.
//

#ifndef SPHEREOBJECT_H
#define SPHEREOBJECT_H
#include "SceneObject.h"


class SphereObject final : public SceneObject {
public:
    const Vec3 center;
    const double radius;

    SphereObject(const Vec3&, double, const Material*);

    bool ray_cast_from_outside(const Ray&, double&, Vec3&, Vec3&) const override;

    void ray_cast_from_inside(const Ray&, double&, Vec3&, Vec3&) const override;
};



#endif //SPHEREOBJECT_H
