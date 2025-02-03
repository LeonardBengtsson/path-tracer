//
// Created by Leonard on 2025-02-03.
//

#ifndef BOXOBJECT_H
#define BOXOBJECT_H
#include "SceneObject.h"


class BoxObject final : public SceneObject {
public:
    BoxObject(const Box &box, const Material *material);

    bool ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &point, Vec3 &normal) const override;

    void ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &point, Vec3 &normal) const override;
};



#endif //BOXOBJECT_H
