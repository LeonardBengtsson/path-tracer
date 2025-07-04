//
// Created by Leonard on 2025-01-24.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>

#include "../math/Vec3.h"
#include "scene_objects/SceneObject.h"
#include "../render/LightSpectrum.h"

class SceneObject;

class Scene {
private:
    std::vector<const SceneObject*> objects;
public:
    const LightSpectrum ambient_light;

    explicit Scene(const LightSpectrum&);

    void add_object(const SceneObject*);

    void iter_objects(void (*)(const SceneObject*)) const;

    void ray_cast(const Ray&, double&, Vec3&, Vec3&, const SceneObject*&) const;
};



#endif //SCENE_H
