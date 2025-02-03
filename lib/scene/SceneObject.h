//
// Created by Leonard on 2025-01-24.
//

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#include "../material/Material.h"
#include "../path_tracing/RayStack.h"
#include "../math/Box.h"

class Material;
class RayStack;

class SceneObject {
protected:
    const Box aabb;
public:
    const Material* const material;

    SceneObject(Box, const Material*);

    bool intersects(const Ray &ray) const;

    LightSpectrum eval_path(RayStack*, const Ray&, const Vec3&) const;

    virtual ~SceneObject() = default;

    virtual bool ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &point, Vec3 &normal) const = 0;
    virtual void ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &point, Vec3 &normal) const = 0;
};



#endif //SCENEOBJECT_H
