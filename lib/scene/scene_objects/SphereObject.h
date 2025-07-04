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

    bool ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) const override;

    void ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &pos, Vec3 &normal) const override;
};



#endif //SPHEREOBJECT_H
