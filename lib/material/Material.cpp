//
// Created by Leonard on 2025-01-24.
//

#include "Material.h"

#include "../math/math_util.h"

Material::Material(const double transparency, const double reflectivity, const LightSpectrum &emissivity)
  : transparency(transparency),
    reflectivity(reflectivity),
    emissivity(emissivity) {}

LightSpectrum Material::push_rays(const SceneObject* const object, RayStack* const ray_stack, const Ray &incident_ray, const Vec3 &surface_normal) const {
    if (transparency > 0) {
        double delta_dist;
        Vec3 out_pos = Vec3::ZERO;
        Vec3 out_normal = Vec3::ZERO;
        object->ray_cast_from_inside(incident_ray, delta_dist, out_pos, out_normal);
        ray_stack->push({out_pos, incident_ray.dir}, LightTransformation::scale(transparency), delta_dist);
    }
    if (reflectivity > 0) {
        const Vec3 reflect_dir = math_util::reflect(incident_ray.dir, surface_normal);
        const Ray reflected_ray = {incident_ray.from + reflect_dir * 0.01, reflect_dir};
        ray_stack->push(reflected_ray, LightTransformation::scale(reflectivity * (incident_ray.dir * surface_normal)), 0.01);
    }

    return emissivity.scaled(1 - transparency - reflectivity);
}

