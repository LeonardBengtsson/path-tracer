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
    const double transparency;
    const double reflectivity;
    const LightSpectrum emittance;

public:
    Material(double, double, const LightSpectrum&);

    LightSpectrum eval_path(const SceneObject*, RayStack*, const Ray&, const Vec3&) const;
};



#endif //MATERIAL_H
