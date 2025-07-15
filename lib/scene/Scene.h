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
public:
    struct SceneObjectOps {
        static Aabb get_aabb(const std::unique_ptr<SceneObject> &object);
        static Aabb wrap_aabb(std::span<std::unique_ptr<SceneObject>> objects);
        static bool possibly_intersects(const std::unique_ptr<SceneObject> &object, const Ray &ray);
        static bool ray_cast(const std::unique_ptr<SceneObject> &object, const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal);
    };

private:
    using SceneObjectAabbBvh = AabbBvh<std::unique_ptr<SceneObject>, SceneObjectOps>;

    std::vector<std::unique_ptr<SceneObject>> objects;

    std::unique_ptr<SceneObjectAabbBvh> aabb_bvh = nullptr;

public:
    const LightSpectrum ambient_light;

    explicit Scene(const LightSpectrum&);

    void add_object(std::unique_ptr<SceneObject> &&object);

    void init(); // initialize bounding volume hierarchy

    void iter_objects(void (*fn)(const std::unique_ptr<SceneObject>&)) const;

    void ray_cast(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal, const std::unique_ptr<SceneObject>* &hit_object) const;
};



#endif //SCENE_H
