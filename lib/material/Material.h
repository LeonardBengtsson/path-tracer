//
// Created by Leonard on 2025-01-24.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "../math/Ray.h"
#include "../path_tracing/RayStack.h"
#include "../render/LightSpectrum.h"

class RayStack;
class SceneObject;

class Material {
private:
    const double roughness;
    const double minus_inv_attenuation_length;
    const bool transparent;
    const double refractive_index;
    const LightSpectrum emittance;

public:
    Material(double roughness, double attenuation_length, bool transparent, double refractive_index, const LightSpectrum &emittance);

    LightSpectrum eval_path(const SceneObject*, RayStack*, const Ray&, const Vec3&) const;
};



#endif //MATERIAL_H
