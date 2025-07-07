//
// Created by Leonard on 2025-01-24.
//

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../math/Vec3.h"
#include "scene_objects/SceneObject.h"
#include "../render/LightSpectrum.h"
#include "../util/AabbBvh.h"

class SceneObject;

class Scene {
private:
    std::vector<std::unique_ptr<SceneObject>> objects;

    AabbBvh *aabb_bvh = nullptr;
public:
    const LightSpectrum ambient_light;

    explicit Scene(const LightSpectrum&);

    void add_object(std::unique_ptr<SceneObject> &&object);

    void init(); // initialize bounding volume hierarchy

    void iter_objects(void (*fn)(const std::unique_ptr<SceneObject>&)) const;

    void ray_cast(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal, const SceneObject* &hit_object) const;
};



#endif //SCENE_H
