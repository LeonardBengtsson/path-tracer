//
// Created by Leonard on 2025-01-24.
//

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H
#include "../../material/Material.h"
#include "../../path_tracing/RayStack.h"
#include "../../math/Aabb.h"

class Material;
class RayStack;

class SceneObject {
public:
    const Aabb aabb;

    const Material* const material;

    SceneObject(Aabb, const Material*);

    bool possibly_intersects(const Ray &ray) const;

    LightSpectrum eval_path(RayStack*, const Ray&, const Vec3&) const;

    virtual ~SceneObject() = default;

    // if ray does not hit object, return false
    // if ray does hit object, and distance is higher than `min_dist`, return true
    // if ray does hit object, and distance is lower than `min_dist`, return true and update `min_dist`, `pos`, `normal`
    virtual bool ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) const = 0;

    // assumed to always hit the object
    // if hit distance is lower than `min_dist`, update `min_dist`, `pos`, `normal`
    virtual void ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &pos, Vec3 &normal) const = 0;
};



#endif //SCENEOBJECT_H
