//
// Created by Leonard on 2025-01-24.
//

#include "Material.h"

#include <cmath>

#include "../math/math_util.h"
#include "../config.h"

Material::Material(const double roughness, const double attenuation_length, const bool transparent, const double refractive_index, const LightSpectrum &emittance)
  : roughness(roughness),
    minus_inv_attenuation_length(attenuation_length == -1 ? 0 : -1 / attenuation_length),
    transparent(transparent),
    refractive_index(refractive_index),
    emittance(emittance) {}

void calc_refraction(
    const double refractive_index_quotient, // incoming n / outgoing n
    const Vec3 &surface_normal,
    const Vec3 &incident_dir,
    Vec3 &refraction_dir,                   // direction of light that was transmitted through the surface
    double &reflection_coefficient,         // coefficient for light that was reflected onto the surface
    double &transmittance_coefficient       // coefficient for light that was transmitted through the surface
) {
#if ENABLE_POLARIZATION
#else
    const Vec3 negative_normal = (surface_normal * incident_dir > 0) ? surface_normal : -surface_normal;
    const double cos_t = incident_dir * negative_normal;
    const double sin_t = std::sqrt(1 - cos_t * cos_t);
    const double sin_i = sin_t * refractive_index_quotient;
    if (sin_i <= 1) {
        const double cos_i = std::sqrt(1 - sin_i * sin_i);

        const Vec3 t_parallel = negative_normal * cos_t;
        const Vec3 t_orthogonal = incident_dir - t_parallel;
        const Vec3 i_parallel = negative_normal * cos_i;
        const Vec3 i_orthogonal = t_orthogonal * refractive_index_quotient; // refractive_index_quotient = sin_i / sin_t
        refraction_dir = i_parallel + i_orthogonal;

        const double Rs = std::pow((cos_i - refractive_index_quotient * cos_t) / (cos_i + refractive_index_quotient * cos_t), 2);
        const double Rp = std::pow((cos_t - refractive_index_quotient * cos_i) / (cos_t + refractive_index_quotient * cos_i), 2);
        reflection_coefficient = .5 * (Rs + Rp);
        transmittance_coefficient = 1 - reflection_coefficient;
    } else {
        // total internal reflection
        reflection_coefficient = 1;
        transmittance_coefficient = 0;
    }
#endif
}

LightSpectrum Material::eval_path(const SceneObject* const object, RayStack* const ray_stack, const Ray &incident_ray, const Vec3 &surface_normal) const {
#if DEBUG_SHADE_NORMALS
    return LightSpectrum::from_rgb(surface_normal.x * .5 + .5, surface_normal.y * .5 + .5, surface_normal.z * .5 + .5, 1);
#else
    if (transparent) {
        const Ray reflected_ray = {incident_ray.from, math_util::reflect(incident_ray.dir, surface_normal)};
        double reflection_factor = 0;
        Ray internal_ray = incident_ray;
        double internal_factor = 1;

        if (refractive_index != 1)
            calc_refraction(1 / refractive_index, surface_normal, incident_ray.dir, internal_ray.dir, reflection_factor, internal_factor);

        reflection_factor *= (1 - roughness);
        internal_factor *= (1 - roughness);
        if (reflection_factor > MIN_LIGHT_FACTOR)
            ray_stack->push(reflected_ray, LightTransformation::of_factor(reflection_factor));

        // internal reflections
        double internal_dist = 0;
        for (size_t bounces = 0; bounces < MAX_INTERNAL_BOUNCES && internal_factor > MIN_LIGHT_FACTOR; bounces++) {
            double delta_dist;
            Vec3 internal_hit_pos = incident_ray.from;
            Vec3 internal_hit_normal = surface_normal;
            object->ray_cast_from_inside(internal_ray, delta_dist, internal_hit_pos, internal_hit_normal);

            Vec3 escape_dir = incident_ray.dir;
            double continued_internal_factor;
            double escape_factor;
            calc_refraction(refractive_index, internal_hit_normal, internal_ray.dir, escape_dir, continued_internal_factor, escape_factor);

            internal_dist += delta_dist;
            if (escape_factor > 0) {
                const Ray escape_ray = {internal_hit_pos, escape_dir};
                const double total_factor = internal_factor * escape_factor * (1 - roughness) * std::exp(internal_dist * minus_inv_attenuation_length);
                ray_stack->push(escape_ray, LightTransformation::of_factor(total_factor), internal_dist, bounces + 1);
            }

            internal_ray = {internal_hit_pos, math_util::reflect(internal_ray.dir, internal_hit_normal)};
            internal_factor *= continued_internal_factor * (1 - roughness);
        }
    } else if (roughness < 1) {
        const Ray reflected_ray = {incident_ray.from, math_util::reflect(incident_ray.dir, surface_normal)};
        ray_stack->push(reflected_ray, LightTransformation::of_factor(1 - roughness));
    }
    return emittance.scaled(roughness);
#endif
}

