//
// Created by Leonard on 2025-01-24.
//

#include "Material.h"

#include "../math/math_util.h"

Material::Material(const double transparency, const double reflectivity, const LightSpectrum &emittance)
  : transparency(transparency),
    reflectivity(reflectivity),
    emittance(emittance) {}

LightSpectrum Material::eval_path(const SceneObject* const object, RayStack* const ray_stack, const Ray &incident_ray, const Vec3 &surface_normal) const {
    if (transparency > 0) {
        double delta_dist;
        Vec3 out_pos = Vec3::ZERO;
        Vec3 out_normal = Vec3::ZERO;
        object->ray_cast_from_inside(incident_ray, delta_dist, out_pos, out_normal);
        ray_stack->push({out_pos, incident_ray.dir}, LightTransformation::of_factor(transparency), delta_dist);
    }
    if (reflectivity > 0) {
        const Vec3 reflect_dir = math_util::reflect(incident_ray.dir, surface_normal);
        const Ray reflected_ray = {incident_ray.from, reflect_dir};
        ray_stack->push(reflected_ray, LightTransformation::of_factor(reflectivity * std::abs(incident_ray.dir * surface_normal)));
    }

    return emittance.scaled(1 - transparency - reflectivity);
}

