//
// Created by Leonard on 2025-07-04.
//

#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include "SceneObject.h"


class MeshObject final : public SceneObject {
public:
    const std::vector<Vec3> tri_vertices;

    // vertices have to be given in counterclockwise order
    MeshObject(const std::vector<Vec3> &&tri_vertices, const Material *material);

    bool ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) const override;

    void ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &pos, Vec3 &normal) const override;
};



#endif //MESHOBJECT_H
