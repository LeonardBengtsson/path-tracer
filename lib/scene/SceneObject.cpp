//
// Created by Leonard on 2025-01-24.
//

#include "SceneObject.h"

#include <utility>

SceneObject::SceneObject(Box aabb, const Material *material) : aabb(std::move(aabb)), material(material) {}

LightSpectrum SceneObject::push_rays(RayStack* const ray_stack, const Ray &incident_ray, const Vec3 &surface_normal) const {
    return material->push_rays(this, ray_stack, incident_ray, surface_normal);
}
