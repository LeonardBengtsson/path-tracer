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
public:
    const Box aabb;
    const Material* const material;

    SceneObject(Box, const Material*);

    LightSpectrum push_rays(RayStack*, const Ray&, const Vec3&) const;

    virtual ~SceneObject() = default;

    virtual bool ray_cast_from_outside(const Ray&, double&, Vec3&, Vec3&) const = 0;
    virtual void ray_cast_from_inside(const Ray&, double&, Vec3&, Vec3&) const = 0;
};



#endif //SCENEOBJECT_H
