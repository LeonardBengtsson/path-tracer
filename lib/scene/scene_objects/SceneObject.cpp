//
// Created by Leonard on 2025-01-24.
//

#include "SceneObject.h"

#include <utility>



SceneObject::SceneObject(Aabb aabb, const Material *material)
  : aabb(std::move(aabb)), material(material) {}

bool SceneObject::possibly_intersects(const Ray& ray) const {
    return aabb.intersects(ray);
}

LightSpectrum SceneObject::eval_path(RayStack &ray_stack, const Ray &incident_ray, const Vec3 &surface_normal) const {
    return material->eval_path(this, ray_stack, incident_ray, surface_normal);
}
