//
// Created by Leonard on 2025-01-24.
//

#include "Material.h"

#include <cmath>

#include "../math/math_util.h"

Material::Material(const double reflectivity, const double transparency, const double refractive_index, const LightSpectrum &emittance)
  : reflectivity(reflectivity),
    transparency(transparency),
    refractive_index(refractive_index),
    emittance(emittance) {}

LightSpectrum Material::eval_path(const SceneObject* const object, RayStack* const ray_stack, const Ray &incident_ray, const Vec3 &surface_normal) const {
    if (transparency > 0) {
        Ray internal_ray = incident_ray;
        if (refractive_index != 1) {
            const Vec3 negative_normal = -surface_normal;
            const double cos_i = incident_ray.dir * negative_normal;
            const double sin_i = std::sqrt(1 - cos_i * cos_i);
            const double sin_b = sin_i / refractive_index;
            if (sin_b <= 1) {
                const double cos_b = std::sqrt(1 - sin_b * sin_b);
                const Vec3 i_parallel = negative_normal * cos_i;
                const Vec3 i_orthogonal = incident_ray.dir - i_parallel;
                const Vec3 b_parallel = negative_normal * cos_b;
                const Vec3 b_orthogonal = i_orthogonal / refractive_index; // 1 / refractive_index = sin_b / sin_i
                internal_ray = {incident_ray.from, b_parallel + b_orthogonal};
            }
        }
        double delta_dist;
        Vec3 out_pos = Vec3::ZERO;
        Vec3 out_normal = Vec3::ZERO;
        object->ray_cast_from_inside(internal_ray, delta_dist, out_pos, out_normal);
        ray_stack->push({out_pos, incident_ray.dir}, LightTransformation::of_factor(transparency), delta_dist);
    }
    if (reflectivity > 0) {
        const Vec3 reflect_dir = math_util::reflect(incident_ray.dir, surface_normal);
        const Ray reflected_ray = {incident_ray.from, reflect_dir};
        ray_stack->push(reflected_ray, LightTransformation::of_factor(reflectivity * -(incident_ray.dir * surface_normal)));
    }

    return emittance.scaled(1 - transparency - reflectivity);
}

